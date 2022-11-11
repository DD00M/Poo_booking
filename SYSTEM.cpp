#include "SYSTEM.h"
#include "unitate_cazare.h"
#include "utilizator.h"
#include "administrator.h"
#include "error_EROARE.h"
#include "error_ALERTA.h"
#include "error_REZERVARE.h"
#include "logger.h"
#include "rezervare.h"

#include "data_zilei.h"

#include "utilizator_fisier.h"
#include "administrator_FISIER.h"
#include "unitate_cazare_fisier.h"

#include <string>
#include <fstream>

SYSTEM* SYSTEM::instance = nullptr;
std::vector<utilizator*>SYSTEM::m_lista_utilizatori = std::vector<utilizator*>();
std::vector<administrator*>SYSTEM::m_lista_administratori = std::vector<administrator*>();
std::vector<std::pair<unitate_cazare*, std::string>>SYSTEM::m_lista_unitati_cazare = std::vector<std::pair<unitate_cazare*, std::string>>();

SYSTEM::SYSTEM(std::string nume) :m_nume(nume)
{
}

SYSTEM::SYSTEM(const SYSTEM& src)
{
	this->m_nume = src.m_nume;
	for (int i = 0; i < src.m_lista_utilizatori.size(); i++) {
		this->m_lista_utilizatori.push_back(src.m_lista_utilizatori[i]);
	}
}

SYSTEM::~SYSTEM()
{
}

SYSTEM& SYSTEM::get_instance(std::string nume)
{
	if (SYSTEM::instance == nullptr) {
		SYSTEM::instance = new SYSTEM(nume);
	}
	return *SYSTEM::instance;
	// TODO: insert return statement here
}

void SYSTEM::remove_instance()
{
	if (SYSTEM::instance != nullptr) {
		delete SYSTEM::instance;
		SYSTEM::instance = nullptr;
	}
}

void SYSTEM::add_utilizator(utilizator* to_add)
{
	bool flag = 0;
	for (auto i = SYSTEM::m_lista_utilizatori.begin(); i != SYSTEM::m_lista_utilizatori.end(); i++) {
		if ((*i)->get_nume() == to_add->get_nume()) {
			flag = 1;
			break;
		}
	}
	if (flag == 1) {
		std::string aux;
		aux = "numele de utilizator " + to_add->get_nume() + " a fost deja luat";
		logger::set_in_file("ALERTA", aux);
		throw error_ALERTA("Nume de utilizator deja luat!\n");
	}

	else if (flag == 0) {
		std::cout << "utilizatorul cu numele: " << to_add->get_nume() << ", a fost inregistrat cu succes!\n";
		SYSTEM::m_lista_utilizatori.push_back(to_add);
		utilizator_fisier::set_in_file(to_add);
	}
}

void SYSTEM::add_administrator(administrator* to_add)
{
	bool flag = 0;
	for (auto i = SYSTEM::m_lista_administratori.begin(); i != SYSTEM::m_lista_administratori.end(); i++) {
		if ((*i)->get_nume() == to_add->get_nume()) {
			flag = 1;
			break;
		}
	}
	if (flag == 1) {
		std::string aux;
		aux = "numele de administrator " + to_add->get_nume() + " a fost deja luat";
		logger::set_in_file("ALERTA", aux);
		aux += "\n";
		throw error_ALERTA(aux);
	}
	else if (flag == 0) {
		std::cout << "administratorul cu numele: " << to_add->get_nume() << ", a fost inregistrat cu succes!\n";
		SYSTEM::m_lista_administratori.push_back(to_add);
		administrator_FISIER::set_in_file(to_add);
	}
}

void SYSTEM::add_unitate(std::string oras, unitate_cazare* u_c)
{
	bool flag = 0;
	for (auto i = SYSTEM::m_lista_unitati_cazare.begin(); i != SYSTEM::m_lista_unitati_cazare.end(); i++) {
		if (oras == i->second && u_c->get_nume() == i->first->get_nume()) {
			flag = 1;
			break;
		}
	}
	if (flag == 1) {
		std::string aux;
		aux = "nu se poate adauga o cazare cu acelasi nume in acelasi oras! ex: " + oras + " : " + u_c->get_nume();
		logger::set_in_file("ALERTA", aux);
		aux += "\n";
		throw error_ALERTA(aux);
	}
	else if (flag == 0) {
		SYSTEM::m_lista_unitati_cazare.emplace_back(u_c, oras);
		unitate_cazare_fisier::add_in_file(u_c);
	}
}

unitate_cazare* SYSTEM::get_cazare(std::string oras, std::string nume)
{
	for (auto i = SYSTEM::m_lista_unitati_cazare.begin(); i != SYSTEM::m_lista_unitati_cazare.end(); i++) {
		if (i->second == oras && i->first->get_nume() == nume) {
			return i->first;
		}
	}
}

unitate_cazare* SYSTEM::get_cazare_by_index_from_admin(std::string nume, int index)
{
	bool flag = 0;
	for (int i = 0; i < SYSTEM::m_lista_administratori.size(); i++) {
		if (SYSTEM::m_lista_administratori[i]->get_nume() == nume) {
			for (int j = 0; j < SYSTEM::m_lista_administratori[i]->get_size_vector_unitati_cazare(); j++) {
				if (j == index) {
					return SYSTEM::m_lista_administratori[i]->get_unitate_cazare_by_index(index);
					flag = 1;
				}
			}
		}
	}
	if (flag == 0) {
		logger::set_in_file("EROARE", "Nu aveti inca cazari introduse in lista dumneavoastra de cazari.");
		throw error_EROARE("Nu aveti inca cazari introduse in lista dumneavoastra de cazari.");
	}
}

utilizator* SYSTEM::get_utilizator(std::string nume)
{
	bool flag = 0;
	for (int i = 0; i < SYSTEM::m_lista_utilizatori.size(); i++) {
		if (SYSTEM::m_lista_utilizatori[i]->get_nume() == nume) {
			flag = 1;
			return m_lista_utilizatori[i];
		}
	}
	if (flag == 0) {
		logger::set_in_file(nume, "nu exista in sistem");
		throw error_ALERTA("Acest nume nu exista in sistem");
	}
}

administrator* SYSTEM::get_administrator(std::string nume)
{
	for (int i = 0; i < SYSTEM::m_lista_administratori.size(); i++) {
		if (SYSTEM::m_lista_administratori[i]->get_nume() == nume) {
			return m_lista_administratori[i];
		}
	}
}

float SYSTEM::get_wallet_admin(std::string admin)
{
	bool flag = 0;
	for (int i = 0; i < SYSTEM::m_lista_administratori.size(); i++) {
		if (SYSTEM::m_lista_administratori[i]->get_nume() == admin) {
			flag = 1;
			return SYSTEM::m_lista_administratori[i]->get_wallet();
		}
	}
	if (flag == 1) {
		logger::set_in_file(admin, "nu exista in baza de date");
		throw error_EROARE("nu exista acest nume in baza de date");
	}
}

void SYSTEM::modifica_in_cazare_recenzie(std::string oras, std::string nume, std::string nume_utilizator, std::string recenzie, int nota)
{
	bool flag = 0;
	for (auto i = SYSTEM::m_lista_unitati_cazare.begin(); i != SYSTEM::m_lista_unitati_cazare.end(); i++) {
		if (i->second == oras && i->first->get_nume() == nume) {
			flag = 1;
			i->first->adauga_recenzie(nume_utilizator, recenzie, nota);
		}
	}
	if (flag == 0) {
		std::cout << "nu";
	}
}

void SYSTEM::add_nr_camere_ocupate(std::string nume, std::string oras, int nr_camere)
{
	for (auto i = SYSTEM::m_lista_unitati_cazare.begin(); i != SYSTEM::m_lista_unitati_cazare.end(); i++) {
		if ((*i).first->get_nume() == nume && (*i).first->get_oras() == oras) {
			(*i).first->ocupa_spatii_grad_ocupare(nr_camere);
		}
	}
}

void SYSTEM::set_grad_ocupare(std::string nume, std::string oras, float grad)
{
	for (auto i = SYSTEM::m_lista_unitati_cazare.begin(); i != SYSTEM::m_lista_unitati_cazare.end(); i++) {
		if ((*i).first->get_nume() == nume && (*i).first->get_oras() == oras) {
			(*i).first->set_grad_ocupare(grad);
		}
	}
}

void SYSTEM::sterge_rezervare_from_cazare(std::string nume, std::string oras, rezervare* r)
{
	for (int i = 0; i < SYSTEM::m_lista_unitati_cazare.size(); i++) {
		if (SYSTEM::m_lista_unitati_cazare[i].first->get_nume() == nume && SYSTEM::m_lista_unitati_cazare[i].first->get_oras() == oras) {
			for (int j = 0; j < SYSTEM::m_lista_unitati_cazare[i].first->get_size_vector_rezervari(); j++) {
				if (SYSTEM::m_lista_unitati_cazare[i].first->get_rezervare_by_index(j) == r) {
					SYSTEM::m_lista_unitati_cazare[i].first->delete_rezervare(j);
				}
			}
			//SYSTEM::m_lista_unitati_cazare[i].first->delete_rezervare(i);
		}
	}
}

void SYSTEM::sterge_cazare_from_administrator(std::string nume, std::string cazare, std::string oras)
{
	bool flag = 0;
	for (int i = 0; i < SYSTEM::m_lista_administratori.size(); i++) {
		if (SYSTEM::m_lista_administratori[i]->get_nume() == nume) {
			flag = 1;
			SYSTEM::m_lista_administratori[i]->sterge_cazare(cazare, oras);
			std::cout << "CAZAREA A FOST STEARSA CU SUCCES\n";
		}
	}
	if (flag == 1) {
		logger::set_in_file(nume, "nu exista in baza de date");
		throw error_EROARE("nu exista acest nume in baza de date");
	}
}

void SYSTEM::occupy_days(std::string nume, std::string oras, std::vector<data_zilei*> lista)
{
	for (auto i = SYSTEM::m_lista_unitati_cazare.begin(); i != SYSTEM::m_lista_unitati_cazare.end(); i++) {
		if ((*i).first->get_nume() == nume && (*i).first->get_oras() == oras) {
			(*i).first->ocupa_zile(lista);
		}
	}
}

bool SYSTEM::print_cazari_by_town(std::string oras)
{
	bool flag = 0;
	std::cout << oras << " : " << std::endl;
	for (int i = 0; i < SYSTEM::m_lista_unitati_cazare.size(); i++) {
		if (oras == SYSTEM::m_lista_unitati_cazare[i].second) {
			SYSTEM::m_lista_unitati_cazare[i].first->print_cazare();
			flag = 1;
		}
	}
	if (flag == 0) {
		std::cout << "In acest oras nu exista cazari disponibile\n";
	}
	return flag;
}

bool SYSTEM::is_cazare_in_system(std::string nume, std::string oras)
{
	bool flag = 0;
	for (int i = 0; i < SYSTEM::m_lista_unitati_cazare.size(); i++) {
		if (SYSTEM::m_lista_unitati_cazare[i].first->get_oras() == oras && SYSTEM::m_lista_unitati_cazare[i].first->get_nume() == nume) {
			flag = 1;
		}
	}
	return flag;
}

bool SYSTEM::check_password_administrator(std::string nume, std::string parola)
{
	bool flag = 0;
	for (int i = 0; i < SYSTEM::m_lista_administratori.size(); i++) {
		if (SYSTEM::m_lista_administratori[i]->get_nume() == nume && SYSTEM::m_lista_administratori[i]->get_parola() == parola) {
			flag = 1;
		}
	}
	return flag;
}

bool SYSTEM::check_password_utilizator(std::string nume, std::string parola)
{
	bool flag = 0;
	for (int i = 0; i < SYSTEM::m_lista_utilizatori.size(); i++) {
		if (SYSTEM::m_lista_utilizatori[i]->get_nume() == nume && SYSTEM::m_lista_utilizatori[i] ->get_parola() == parola) {
			flag = 1;
		}
	}
	return flag;
}

bool SYSTEM::is_nume_administrator(std::string nume)
{
	bool flag = 0;
	for (int i = 0; i < SYSTEM::m_lista_administratori.size(); i++) {
		if (SYSTEM::m_lista_administratori[i]->get_nume() == nume) {
			flag = 1;
		}
	}
	return flag;
}

bool SYSTEM::is_nume_utilizator(std::string nume)
{
	bool flag = 0;
	for (int i = 0; i < SYSTEM::m_lista_utilizatori.size(); i++) {
		if (SYSTEM::m_lista_utilizatori[i]->get_nume() == nume) {
			flag = 1;
		}
	}
	return flag;
}

bool SYSTEM::check_if_exist_REZERVARI(std::string nume, std::string oras)
{
	bool flag = 0;
	for (int i = 0; i < SYSTEM::m_lista_unitati_cazare.size(); i++) {
		if ((SYSTEM::m_lista_unitati_cazare[i].first->get_nume() == nume) && (SYSTEM::m_lista_unitati_cazare[i].first->get_oras() == oras)) {
			if ((SYSTEM::m_lista_unitati_cazare[i].first->get_size_vector_rezervari() == 0)) {
				return 1;
			}
		}
	}
	return 0;
}

bool SYSTEM::check_if_exist_nr_room(std::string nume, std::string oras, int camera)
{
	bool flag = 0;
	for (int i = 0; i < SYSTEM::m_lista_unitati_cazare.size(); i++) {
		if (SYSTEM::m_lista_unitati_cazare[i].first->get_nume() == nume && SYSTEM::m_lista_unitati_cazare[i].first->get_oras() == oras) {
			for (int j = 0; j < SYSTEM::m_lista_unitati_cazare[i].first->get_size_of_vector_camere(); j++) {
				std::pair<int, int>aux = SYSTEM::m_lista_unitati_cazare[i].first->get_type_of_room(j);
				if (aux.second == camera) {
					flag = 1;
					return flag;
				}
			}
		}
	}
	logger::set_in_file(nume, "Camera de " + std::to_string(camera) + " nu exista");
	return 0;
}

bool SYSTEM::check_if_there_are_enough_rooms(std::string nume, std::string oras, int nr)
{
	bool flag = 0;
	for (int i = 0; i < SYSTEM::m_lista_unitati_cazare.size(); i++) {
		if (SYSTEM::m_lista_unitati_cazare[i].first->get_nume() == nume && SYSTEM::m_lista_unitati_cazare[i].first->get_oras() == oras) {
			std::pair<int, int>aux = SYSTEM::m_lista_unitati_cazare[i].first->get_type_of_room(i);
			if (aux.first - nr < 0) {
				flag = 1;
			}
		}
	}
	logger::set_in_file(nume, "Nu sunt suficiente locuri");
	return flag;
}

bool SYSTEM::check_if_exist_data(std::string nume, std::string oras, std::string data, std::string nume_zi)
{
	bool flag = 0;
	for (int i = 0; i < SYSTEM::m_lista_unitati_cazare.size(); i++) {
		if (SYSTEM::m_lista_unitati_cazare[i].first->get_nume() == nume && SYSTEM::m_lista_unitati_cazare[i].first->get_oras() == oras) {
			std::vector<data_zilei*> aux = SYSTEM::m_lista_unitati_cazare[i].first->get_arr_zile();
			for (int j = 0; j < aux.size(); j++) {
				if (aux[j]->get_zi_string() == data && aux[j]->get_nume() == nume_zi) {
					flag = 1;
				}
			}
		}
	}
	return flag;
}

bool SYSTEM::check_if_exist_dish(std::string nume, std::string oras, std::string dish)
{
	if (dish == "") {
		return 1;
	}
	bool flag = 0;
	for (int i = 0; i < SYSTEM::m_lista_unitati_cazare.size(); i++) {
		for (int j = 0; j < SYSTEM::m_lista_unitati_cazare[i].first->get_size_vector_mese(); j++) {
			if (SYSTEM::m_lista_unitati_cazare[i].first->get_dish_by_index(j) == dish) {
				flag = 1;
				return flag;
			}
		}
	}
	if (flag == 0) {
		logger::set_in_file(nume, "nu se poate servi: " + dish);
		return flag;
		//throw error_REZERVARE("nu se poate servi: " + dish + "\n");
	}
}

bool SYSTEM::check_existanta_cazare(std::string oras, std::string nume)
{
	for (auto i = SYSTEM::m_lista_unitati_cazare.begin(); i != SYSTEM::m_lista_unitati_cazare.end(); i++) {
		if (i->second == oras && i->first->get_nume() == nume) {
			return 1;
		}
	}
	return 0;
}

int SYSTEM::get_number_of_rooms_by_number_of_seats(std::string type)
{
	for (int i = 0; i < SYSTEM::m_lista_unitati_cazare.size(); i++) {
		for (int j = 0; j < SYSTEM::m_lista_unitati_cazare[i].first->get_size_of_vector_camere(); j++) {
			std::pair<int, int> aux;
			aux = SYSTEM::m_lista_unitati_cazare[i].first->get_type_of_room(j);
			if (aux.first == std::stoi(type)) {
				return aux.second;
			}
		}
	}
}

int SYSTEM::get_size_unitate_cazare_rezervari(std::string nume, std::string oras)
{
	for (int i = 0; i < SYSTEM::m_lista_unitati_cazare.size(); i++) {
		if (SYSTEM::m_lista_unitati_cazare[i].first->get_nume() == nume && SYSTEM::m_lista_unitati_cazare[i].first->get_oras() == oras) {
			return SYSTEM::m_lista_unitati_cazare[i].first->get_size_vector_rezervari();
		}
	}
}

int SYSTEM::get_size_administrator_unitati_cazare(std::string nume)
{
	for (int i = 0; i < SYSTEM::m_lista_administratori.size(); i++) {
		if (SYSTEM::m_lista_administratori[i]->get_nume() == nume) {
			return SYSTEM::m_lista_administratori[i]->get_size_vector_unitati_cazare();
		}
	}
}

rezervare* SYSTEM::get_rezervare_by_index(std::string nume, std::string oras, int index)
{
	bool flag = 0;
	for (int i = 0; i < SYSTEM::m_lista_unitati_cazare.size(); i++) {
		if (SYSTEM::m_lista_unitati_cazare[i].first->get_nume() == nume && SYSTEM::m_lista_unitati_cazare[i].first->get_oras() == oras) { 
			for (int j = 0; j < SYSTEM::m_lista_unitati_cazare[i].first->get_size_vector_rezervari(); j++) {
				if (j == index) {
					return SYSTEM::m_lista_unitati_cazare[i].first->get_rezervare_by_index(index);
					flag = 1;
				}
			}
		}
	}
	if (flag == 0) {
		logger::set_in_file(nume, "nu exista rezervari");
		throw error_EROARE("nu aveti rezervari aplicate cazarilor dumneavoastra\n");
	}
}

std::string SYSTEM::set_rooms_by_type(int type, int how_may_rooms, std::string nume, std::string oras)
{
	for (int i = 0; i < SYSTEM::m_lista_unitati_cazare.size(); i++) {
		if (SYSTEM::m_lista_unitati_cazare[i].first->get_nume() == nume && SYSTEM::m_lista_unitati_cazare[i].first->get_oras() == oras) {
			for (int j = 0; j < SYSTEM::m_lista_unitati_cazare[i].first->get_size_of_vector_camere(); j++) {
				if (SYSTEM::m_lista_unitati_cazare[i].first->get_type(j) == type) {
					return SYSTEM::m_lista_unitati_cazare[i].first->set_number_of_rooms_by_type(type, how_may_rooms);
				}
			}
		}
	}
}

int SYSTEM::get_nr_total_camere_per_cazare(std::string nume, std::string oras)
{
	for (auto i = SYSTEM::m_lista_unitati_cazare.begin(); i != SYSTEM::m_lista_unitati_cazare.end(); i++) {
		if ((*i).first->get_nume() == nume && (*i).first->get_oras() == oras) {
			return (*i).first->get_nr_total_camere();
		}
	}
}

void SYSTEM::get_discount_utilizator(std::string nume)
{
	bool flag = 0;
	for (int i = 0; i < SYSTEM::m_lista_utilizatori.size(); i++) {
		if (SYSTEM::m_lista_utilizatori[i]->get_nume() == nume) {
			flag = 1;
			std::cout << "Discount-ul de care beneficiati in urma rezervarilor aprobate: " << SYSTEM::m_lista_utilizatori[i]->distribuie_bonus() << "% din suma finala! :)" << std::endl;
		}
	}
	if (flag == 0) {
		logger::set_in_file(nume, "Nu exista in baza de date");
		throw error_EROARE("numele nu exista in baza de date\n");
	}
}

void SYSTEM::fix_rooms_by_type(int type, int how_may_rooms, std::string nume, std::string oras)
{
	for (int i = 0; i < SYSTEM::m_lista_unitati_cazare.size(); i++) {
		if (SYSTEM::m_lista_unitati_cazare[i].first->get_nume() == nume && SYSTEM::m_lista_unitati_cazare[i].first->get_oras() == oras) {
			for (int j = 0; j < SYSTEM::m_lista_unitati_cazare[i].first->get_size_of_vector_camere(); j++) {
				if (SYSTEM::m_lista_unitati_cazare[i].first->get_type(j) == type) {
					SYSTEM::m_lista_unitati_cazare[i].first->add_again(type, how_may_rooms);
				}
			}
		}
	}
}

void SYSTEM::plateste(std::string utilizator, administrator* admin)
{
	for (auto i = SYSTEM::m_lista_utilizatori.begin(); i != SYSTEM::m_lista_utilizatori.end(); i++) {
		if ((*i)->get_nume() == utilizator) {
			float suma = (*i)->get_plata();
			admin->get_money(suma);
			(*i)->set_price(0);
		}
	}
}

void SYSTEM::set_user_wallet(std::string user, float suma)
{
	for (auto i = SYSTEM::m_lista_utilizatori.begin(); i != SYSTEM::m_lista_utilizatori.end(); i++) {
		if ((*i)->get_nume() == user) {
			(*i)->set_price(suma);
		}
	}
}

void SYSTEM::set_user_appointment(std::string user, std::string type, std::string rezervare)
{
	bool flag = 0;
	for (auto i = SYSTEM::m_lista_utilizatori.begin(); i != SYSTEM::m_lista_utilizatori.end(); i++) {
		if ((*i)->get_nume() == user) {
			flag = 1;
			(*i)->add_rezervare_goodORbad(type, rezervare);
		}
	}
}

