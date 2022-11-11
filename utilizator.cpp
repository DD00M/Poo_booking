#include "utilizator.h"
#include "SYSTEM.h"
#include "unitate_cazare.h"
#include "rezervare.h"
#include "administrator.h"

#include "error_EROARE.h"
#include "error_ALERTA.h"
#include "error_REZERVARE.h"
#include "logger.h"

#include "zi.h"
#include "data_zilei.h"

#include <regex>
#include <string>


///////////

int get_week_end_days(std::vector<data_zilei*>lista, int nr_total_zile) {
	int zile_week_end = 0;

	zile_week_end = (nr_total_zile / 7) * 2;
	if ((nr_total_zile % 7) + (int)lista[0]->get_nameday() == 6) {
		zile_week_end++;
	}
	else if ((nr_total_zile % 7) + (int)lista[0]->get_nameday() > 6) {
		zile_week_end += 2;
	}
	else if (lista[0]->get_nameday() == nume_zi::duminica) {
		zile_week_end--;
	}

	return zile_week_end;
}

/// ///////


int utilizator::m_nr_rezervari_efectuate = 0;

int utilizator::distribuie_bonus() {
	if (utilizator::m_nr_rezervari_efectuate == 0) {
		return 0;
	}
	if (utilizator::m_nr_rezervari_efectuate == 1) {
		return 2;
	}
	else {
		return 4 * utilizator::m_nr_rezervari_efectuate - 2;
	}
}

utilizator::utilizator()
{
	this->m_pret_de_platit = 0;
	this->m_filename = "utilizatori.txt";
}

utilizator::utilizator(std::string nume, std::string parola) :m_nume(nume), m_parola(parola)
{
	this->m_pret_de_platit = 0;
	this->m_filename = "utilizatori.txt";
}

utilizator::utilizator(const utilizator& src)
{
	this->m_parola = src.m_parola;
	this->m_nume = src.m_nume;
	this->m_pret_de_platit = src.m_pret_de_platit;
}

utilizator::~utilizator()
{
}

const std::string& utilizator::get_nume() const
{
	return this->m_nume;
}

const std::string& utilizator::get_parola() const 
{
	return this->m_parola;
}

const std::string& utilizator::get_filename() const
{
	return this->m_filename;
}

void utilizator::set_price(float pret)
{
	this->m_pret_de_platit = pret;
}

void utilizator::plaseaza_recenzie(std::string nume, std::string oras, std::string recenzie, int nota)
{
	std::cout << "recenzia utilizatorului " << this->m_nume << " a fost inregistrata cu succes!\n";
	
	SYSTEM::modifica_in_cazare_recenzie(oras, nume, this->m_nume, recenzie, nota);
}

void utilizator::contorizeaza_rezervare_reusita()
{
	if (utilizator::m_nr_rezervari_efectuate > 6) {
		utilizator::m_nr_rezervari_efectuate = 5;
	}
	else {
		utilizator::m_nr_rezervari_efectuate++;
	}
}

void utilizator::scade_contor()
{
	utilizator::m_nr_rezervari_efectuate--;
}

const int utilizator::get_contor_rezervari_reusite()
{
	return utilizator::m_nr_rezervari_efectuate;
}

void utilizator::plaseaza_rezervare(std::string nume, std::string oras, std::vector<std::string> dorinta, std::vector<std::string>mese, int nr_zile, std::vector<data_zilei*>lista_zile)
{
	float pret = 0;
	int nr_camere = 0;
	int nr_locuri = 0;
	int nr_zile_week_end = get_week_end_days(lista_zile, nr_zile - 1);
	std::vector<std::string>aux;
	std::vector<std::string>my_vec;
	aux.clear();
	my_vec.clear();
	if (SYSTEM::check_existanta_cazare(oras, nume) == 1) {
		for (int i = 0; i < dorinta.size(); i++) {
			std::regex del("x");
			std::sregex_token_iterator first{ dorinta[i].begin(), dorinta[i].end(), del, -1 }, last;
			aux = { first, last };
			nr_camere = std::stoi(aux[0]);
			nr_locuri = std::stoi(aux[1]);
			std::string to_insert = SYSTEM::set_rooms_by_type(nr_locuri, nr_camere, nume, oras);
			my_vec.push_back(to_insert);
			std::pair<int, float>aux_pereche = SYSTEM::get_cazare(oras, nume)->get_pret_by_camera(nr_locuri);
			//this->m_pret_de_platit* (nr_zile - 1 - nr_zile_week_end) + (((25 * this->m_pret_de_platit) / 100) * nr_zile_week_end);
			//pret = nr_camere * aux_pereche.second;
			pret = aux_pereche.second * (nr_zile - 1 - nr_zile_week_end) + (((25 * aux_pereche.second) / 100) * nr_zile_week_end + aux_pereche.second);
			this->m_pret_de_platit += pret * nr_camere;
		}
		if (mese.size() != 0) {
			for (int j = 0; j < mese.size(); j++) {
				if (SYSTEM::get_cazare(oras, nume)->is_meal(mese[j]) == 1) {
					float pret_2 = SYSTEM::get_cazare(oras, nume)->get_price_by_meal(mese[j]);
					this->m_pret_de_platit += pret_2 * nr_zile;
				}
				else {
					std::string aux_z;
					aux_z = "(" + this->m_nume + "," + mese[j] + ")" + "masa respectiva nu este in hotel";
					logger::set_in_file("EROARE", aux_z);
					aux_z.clear();
					aux_z = "nu am putut gasi masa: " + mese[j] + " in lista pe care o pune la dispozitie cazarea, ne cerem scuze, " + this->m_nume;
					throw error_EROARE(aux_z);
				}
			}
		}
		rezervare* new_rezervare = new rezervare(this->m_nume, nume, oras, my_vec, mese, lista_zile);
		SYSTEM::get_cazare(oras, nume)->adauga_rezervare(new_rezervare);
		std::cout << "AVETI DE PLATIT : " << this->m_pret_de_platit << " lei" << std::endl;
		if (utilizator::m_nr_rezervari_efectuate == 0) {
			//this->m_pret_de_platit = this->m_pret_de_platit * (nr_zile - 1);
			SYSTEM::set_user_wallet(this->m_nume, this->m_pret_de_platit);
		}
		else {
			this->m_pret_de_platit = this->m_pret_de_platit - (this->distribuie_bonus() * this->m_pret_de_platit) / 100;
			//this->m_pret_de_platit = this->m_pret_de_platit * (nr_zile - 1);
			SYSTEM::set_user_wallet(this->m_nume, this->m_pret_de_platit);
		}
	}
	else {
		std::string aux_z;
		aux_z = "cazarea: " + nume + " din orasul: " + oras + " nu exista in baza de date" + ", ne pare rau, " + this->m_nume;
		logger::set_in_file("EROARE", aux_z);
		aux_z.clear();
		aux_z = "cazarea: " + nume + " din orasul: " + oras + " nu exista in baza de date";
		throw error_EROARE(aux_z);
	}
}

const float &utilizator::get_plata() const
{
	return this->m_pret_de_platit;
}

void utilizator::add_rezervare_goodORbad(std::string type, std::string m)
{
	this->m_lista_rezervari.emplace_back(type, m);
}

void utilizator::print()
{
	std::cout << "UTILIZATORUL: " << this->m_nume << std::endl;
	//std::cout << "Suma din cos: " << this->m_pret_de_platit << " lei" << std::endl;
	std::cout << "Discount-ul de care beneficiati in urma rezervarilor aprobate: " << this->distribuie_bonus() << "% din suma finala! :)" << std::endl;
	//char decizie;
	//std::cout << "Doriti sa va vedeti istoricul rezervarilor? (y = da, n = nu)" << std::endl << "raspuns: ";
	//std::cin >> decizie;
	//if (decizie == 'y') {
	std::cout << "numar total de rezervari: " << this->m_lista_rezervari.size() << std::endl;	
	if (this->m_lista_rezervari.size() == 0) {
		logger::set_in_file(this->m_nume, "nu are rezervari");
		throw error_REZERVARE("Nu aveti inca rezervari facute");
	}
		std::cout << "VERDICT-REZERVARE" << std::endl;
		for (int i = 0; i < this->m_lista_rezervari.size(); i++) {
			std::cout << i + 1 << " : " << "[" << this->m_lista_rezervari[i].first << "]" << " " << this->m_lista_rezervari[i].second << std::endl;
		}
	//}
	//else if (decizie == 'n') {
	//}
}

std::ostream& operator<<(std::ostream& out, utilizator* admin)
{
	out << "UTILIZATORUL: " << admin->m_nume << std::endl;
	//std::cout << "Suma din cos: " << this->m_pret_de_platit << " lei" << std::endl;
	out << "Discount-ul de care beneficiati in urma rezervarilor aprobate: " << admin->distribuie_bonus() << "% din suma finala! :)" << std::endl;
	//char decizie;
	//std::cout << "Doriti sa va vedeti istoricul rezervarilor? (y = da, n = nu)" << std::endl << "raspuns: ";
	//std::cin >> decizie;
	//if (decizie == 'y') {
	out << "numar total de rezervari: " << admin->m_lista_rezervari.size() << std::endl;
	if (admin->m_lista_rezervari.size() == 0) {
		logger::set_in_file(admin->m_nume, "nu are rezervari");
		throw error_REZERVARE("Nu aveti inca rezervari facute");
	}
	out << "VERDICT-REZERVARE" << std::endl;
	for (int i = 0; i < admin->m_lista_rezervari.size(); i++) {
		out << i + 1 << " : " << "[" << admin->m_lista_rezervari[i].first << "]" << " " << admin->m_lista_rezervari[i].second << std::endl;
	}
	return out;
}
