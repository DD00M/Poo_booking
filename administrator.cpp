#include "administrator.h"
#include "utilizator.h"
#include "unitate_cazare.h"
#include "SYSTEM.h"
#include "rezervare.h"

#include "error_TASTA.h"
#include "error_EROARE.h"

#include "logger.h"

#include <regex>
#include <string>

bool cmp(unitate_cazare* u1, unitate_cazare* u2) {
	return u1->get_top_cazare() > u2->get_top_cazare();
}

administrator::administrator()
{
	this->portofel = 0;
	this->m_filename = "administratori.txt";
}

administrator::administrator(std::string nume, std::string parola) :m_nume(nume), m_parola(parola)
{
	this->portofel = 0;
	this->m_filename = "administratori.txt";
}

administrator::administrator(const administrator& src)
{
	for (int i = 0; i < src.m_lista_unitati_cazare.size(); i++) {
		this->m_lista_unitati_cazare.push_back(src.m_lista_unitati_cazare[i]);
	}
	this->m_nume = src.m_parola;
	this->m_nume = src.m_nume;
	this->portofel = src.portofel;
}

administrator::~administrator()
{
}

const std::string& administrator::get_nume() const
{
	return this->m_nume;
}

const std::string& administrator::get_parola()const
{
	return this->m_parola;
}

const std::string& administrator::get_filename() const
{
	return this->m_filename;
}

void administrator::add_unitate_cazare(unitate_cazare* u)
{
	this->m_lista_unitati_cazare.push_back(u);
	SYSTEM::add_unitate(u->get_oras(), u);
	std::cout << "UNITATE DE CAZAREA ADAUGATA CU SUCCES\n";
}

void administrator::give_verdict(std::string nume, std::string cazare, std::string oras, std::string verdict)
{
	rezervare* aux_rez = nullptr;
	bool flag = 0;
	if (verdict == "aprobat") {
		int var = 0;
		utilizator::contorizeaza_rezervare_reusita();
		SYSTEM::plateste(nume, this);
		std::string aux = cazare + "-" + oras;
		SYSTEM::set_user_appointment(nume, verdict, aux);
		for (auto i = this->m_lista_unitati_cazare.begin(); i != this->m_lista_unitati_cazare.end(); i++) {
			for (int j = 0; j < (*i)->get_size_vector_rezervari(); j++) {
				if (((*i)->get_rezervare_by_index(j)->get_nume() == nume) && ((*i)->get_rezervare_by_index(j)->get_cazare() == cazare) && ((*i)->get_rezervare_by_index(j)->get_oras() == oras)) {
					std::vector<std::string>aux = (*i)->get_rezervare_by_index(j)->get_lista_camere();
					SYSTEM::occupy_days(cazare, oras, (*i)->get_rezervare_by_index(j)->get_lista_date());
					aux_rez = (*i)->get_rezervare_by_index(j);
					for (int k = 0; k < aux.size(); k++) {
						std::vector<std::string>aux_vec;

						std::regex del("x");
						std::sregex_token_iterator first{ aux[k].begin(), aux[k].end(), del, -1 }, last;
						aux_vec = { first, last };
						var += std::stoi(aux_vec[0]);
						SYSTEM::add_nr_camere_ocupate(cazare, oras, std::stoi(aux_vec[0]));

						aux_vec.erase(aux_vec.begin(), aux_vec.end());
					}
					flag = 1;
				}
			}
		}
		if (flag == 1) {
			SYSTEM::sterge_rezervare_from_cazare(cazare, oras, aux_rez);
			std::cout << "rezervarea lui: " << nume << " a fost trecuta de catre admistratorul: " << this->m_nume << " cu statusul: " << verdict << std::endl;
			float grad;
			grad = (float)((float)var / (float)SYSTEM::get_nr_total_camere_per_cazare(cazare, oras));
			SYSTEM::set_grad_ocupare(cazare, oras, grad);
		}
	}
	else if (verdict == "respins") {
		std::cout << "rezervarea lui: " << nume << " a fost trecuta de catre admistratorul: " << this->m_nume << " cu statusul: " << verdict << std::endl;
		
		utilizator::scade_contor();

		SYSTEM::set_user_wallet(nume, 0);
		std::string aux = cazare + "-" + oras;
		SYSTEM::set_user_appointment(nume, verdict, aux);
		
		for (auto i = this->m_lista_unitati_cazare.begin(); i != this->m_lista_unitati_cazare.end(); i++) {
			for (int j = 0; j < (*i)->get_size_vector_rezervari(); j++) {
				if (((*i)->get_rezervare_by_index(j)->get_nume() == nume) && ((*i)->get_rezervare_by_index(j)->get_cazare() == cazare) && ((*i)->get_rezervare_by_index(j)->get_oras() == oras)) {
					std::vector<std::string>aux = (*i)->get_rezervare_by_index(j)->get_lista_camere();
					aux_rez = (*i)->get_rezervare_by_index(j);
					for (int k = 0; k < aux.size(); k++) {
						std::vector<std::string>aux_vec;

						std::regex del("x");
						std::sregex_token_iterator first{ aux[k].begin(), aux[k].end(), del, -1 }, last;
						aux_vec = { first, last };

						SYSTEM::fix_rooms_by_type(std::stoi(aux_vec[1]), std::stoi(aux_vec[0]), cazare, oras);

						aux_vec.erase(aux_vec.begin(), aux_vec.end());
					}
				}
			}
		}
		SYSTEM::sterge_rezervare_from_cazare(cazare, oras, aux_rez);
	}
	else {
		throw error_TASTA("\nVerdict incorect!\n");
		logger::set_in_file(this->m_nume, "Raspuns invalid in cadrul verdictului");
	}
}

void administrator::get_money(float sum)
{
	this->portofel += sum;
}

void administrator::print_top_cazari()
{
	int index = 1;
	std::cout << "<------------------------------------------------------------------------------------------------------------------------------------->" << std::endl;
	std::cout << "VA PUNEM LA DISPOZITIE STATISTICA UNITATILOR DUMNEAVOASTRA DE CAZARE, DE LA CELE MAI DORITE, LA CELE MAI PUTIN DORINTE: " << std::endl;
	std::sort(this->m_lista_unitati_cazare.begin(), this->m_lista_unitati_cazare.end(), cmp);
	std::cout << "--------------------------------" << std::endl;
	std::cout << "----NUME CAZARE -> NUME ORAS----" << std::endl;
	std::cout << "--------------------------------" << std::endl;
	for (auto i = this->m_lista_unitati_cazare.begin(); i != this->m_lista_unitati_cazare.end(); i++) {
		std::cout << index << " : " << (*i)->get_nume() << " -> " << (*i)->get_oras() << std::endl;
		index++;
	}
	std::cout << "<------------------------------------------------------------------------------------------------------------------------------------->" << std::endl;
}

void administrator::print_grad_ocupare_cazare(std::string nume, std::string oras)
{
	std::cout << "<------------------------------------------------------------------------------------------------------------------------------------->" << std::endl;
	for (auto i = this->m_lista_unitati_cazare.begin(); i != this->m_lista_unitati_cazare.end(); i++) {
		if ((*i)->get_nume() == nume && (*i)->get_oras() == oras) {
			std::cout << "GRADUL DE OCUPARE PENTRU UNITATEA DE CAZARE: " << nume << " DIN: " << oras << " ESTE: " << (*i)->get_grad_ocupare() * 100 << "%" << std::endl;
		}
	}
}

void administrator::sterge_cazare(std::string nume, std::string oras)
{
	bool flag = 0;
	for (int i = 0; this->m_lista_unitati_cazare.size(); i++) {
		if (this->m_lista_unitati_cazare[i]->get_nume() == nume && this->m_lista_unitati_cazare[i]->get_oras() == oras) {
			flag = 1;
			this->m_lista_unitati_cazare.erase(this->m_lista_unitati_cazare.begin() + i);
		}
	}
	if (flag == 0) {
		logger::set_in_file(this->m_nume, "A incercat sa stearga cazarea " + nume + " din " + oras);
		throw error_EROARE("A incercat sa stearga cazarea " + nume + " din " + oras + " care nu exista in lista dvs");
	}
}

const int administrator::get_size_vector_unitati_cazare()
{
	return this->m_lista_unitati_cazare.size();
}

const float administrator::get_wallet() const
{
	return this->portofel;
}

unitate_cazare* administrator::get_unitate_cazare_by_index(int index)
{
	return this->m_lista_unitati_cazare[index];
}

void administrator::print()
{
	std::cout << "ADMINISTRATORUL: " << this->m_nume << std::endl;
	std::cout << "Suma actuala in cont incasata in urma rezervarilor: " << this->portofel << " lei" << std::endl;
	char check;
	std::cout << "Doriti sa vedeti lista dumneavoastra de cazari? (y = da, n = nu)" << std::endl << "raspuns: ";
	std::cin >> check;
	if (check == 'y') {
		for (auto i = this->m_lista_unitati_cazare.begin(); i != this->m_lista_unitati_cazare.end(); i++) {
			(*i)->print_cazare();
		}
	}
	else if (check == 'n') {
		std::cout << "Numarul de cazari: " << this->m_lista_unitati_cazare.size() << std::endl;
	}
}

//std::ostream& operator<<(std::ostream& out, administrator* admin)
//{
//	// TODO: insert return statement here
//}
