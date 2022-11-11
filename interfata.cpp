#include "interfata.h"
#include "administrator.h"
#include "utilizator.h"
#include "administrator_FACTORY.h"
#include "utilizator_FACTORY.h"
#include "SYSTEM.h"
#include "unitate_cazare.h"
#include "unitate_cazare_FACTORY.h"
#include "unitate_cazare_HOTEL.h"
#include "unitate_cazare_PENSIUNE.h"
#include "rezervare.h"

#include "error.h"
#include "error_TASTA.h"
#include "error_ALERTA.h"
#include "error_EROARE.h"
#include "error_REZERVARE.h"

#include "logger.h"

#include "data_zilei_FACTORY.h"
#include "data_zilei.h"

#include <iostream>
#include <string>
#include <conio.h>
#include <algorithm>
#include <regex>

std::vector<std::string>interfata::m_lista_orase = std::vector<std::string>();
interfata* interfata::instance = nullptr;

interfata::interfata(std::vector<std::string> lista)
{
	for (int i = 0; i < lista.size(); i++) {
		interfata::m_lista_orase.push_back(lista[i]);
	}
}

interfata::~interfata()
{
}

interfata& interfata::get_instance(std::vector<std::string>lista)
{
	if (interfata::instance == nullptr) {
		interfata::instance = new interfata(lista);
	}
	return *interfata::instance;
	// TODO: insert return statement here
}

void interfata::remove_instance()
{
	if (interfata::instance != nullptr) {
		delete interfata::instance;
		interfata::instance = nullptr;
	}
}

bool interfata::search_for_town(std::string oras)
{
	if (std::find(interfata::m_lista_orase.begin(), interfata::m_lista_orase.end(), oras) != interfata::m_lista_orase.end()) {
		return 1;
	}
	else {
		return 0;
	}
}

void interfata::meniu()
{
	std::cout << "\nLISTA CU ORASELE DISPONIBILE: \n";
	for (int j = 0; j < interfata::m_lista_orase.size(); j++) {
		if (j % 4 == 0) {
			std::cout << std::endl;
			std::cout << "--------------------------------------------------------------------------------------------" << std::endl;
		}
		if (interfata::m_lista_orase[j].length() < 15){
			std::cout << j + 1 << " : " << interfata::m_lista_orase[j];
			for (int i = interfata::m_lista_orase[j].length(); i <= 15; i++) {
				std::cout << " ";
			}
			if (j < 9) {
				std::cout << " ";
			}
			std::cout << "||";
		}
		else if (interfata::m_lista_orase[j].length() == 15) {
			std::cout << j + 1 << " : " << interfata::m_lista_orase[j];
			std::cout << "  " << "||";
		}
	}
}

void interfata::inregistreaza_persoana()
{
	int tip;
	std::cout << std::endl;
	std::cout << "--------------------------------------------------------------------------------------------" << std::endl;
	std::cout << std::endl << "INREGISTRARE: " << std::endl;
	std::cout << "Cum doriti sa va inregistrati? In calitate de utilizator sau administrator? (1 = utilizator, 2 = administrator) : ";
	std::cin >> tip;
	if (tip == 1) {
		this->inregistreaza_utilizator();
	}
	else if (tip == 2)
	{
		this->inregistreaza_administrator();
	}
	else {
		logger::set_in_file("UNKNOWN", "a introdus o tasta invalida(" + std::to_string(tip) + ")" + " in cadrul inregistrarii");
		throw error_TASTA("A fost apasata o tasta invalida in cadrul inregistrarii!");
	}
}

void interfata::inregistreaza_utilizator()
{
	std::string nume;
	std::string parola;
	char cc;
	this->util_admin = 0;
	start:
	std::cout << "INREGISTRARE UTILIZATOR: " << std::endl;
	std::cout << "ID: ";
	std::cin.ignore();
	std::getline(std::cin, nume);
	this->m_nume = nume;
	if (SYSTEM::is_nume_utilizator(nume) == 1) {
		std::cout << "NUMELE: " << nume << " ESTE DEJA IN SISTEM, INTRODUCETI PAROLA: \n";
		logger::set_in_file(nume, "ESTE DEJA IN SISTEM");
	pass:
		parola.clear();
		std::cout << "PAROLA: ";
		char c;
		while (1) {
			c = _getch();
			if (c == '\r') { break; }
			else if (c == '\b') {
				if (parola.size() == 0) {
					continue;
				}
				parola.pop_back(); std::cout << "\b \b";
			}
			else { std::cout << "*"; }
			if (c == '\b') {
				continue;
			}
			parola += c;
		}
		if (SYSTEM::check_password_utilizator(nume, parola) == 0){
			dec:
			std::cout << "\nParola incorecta! doriti sa reintroduceti parola?:" << std::endl << "(y = da, doresc sa reintroduc parola ; n = nu, doresc sa creez un cont nou.) : ";
			std::cin >> cc;
			if (cc == 'y') {
				goto pass;
			}
			else if (cc == 'n') {
				goto start;
			}
			else {
				std::cout << "invalid key\n";
				goto dec;
			}
		}
		else if (SYSTEM::check_password_utilizator(nume, parola) == 1) {
			std::cout << "\nUtilizatorul cu numele: " << nume << ", a fost autentificat cu succes!\n";
			this->meniu_utilizator();
		}
	}
	else {
		std::cout << "PAROLA: ";
		char c;
		while (1) {
			c = _getch();
			if (c == '\r') { break; }
			else if (c == '\b') {
				if (parola.size() == 0) {
					continue;
				}
				parola.pop_back(); std::cout << "\b \b";
			}
			else { std::cout << "*"; }
			if (c == '\b') {
				continue;
			}
			parola += c;
		}
		utilizator* new_utilizator = utilizator_FACTORY::get_utilizator(nume, parola);
		std::cout << std::endl;
		SYSTEM::add_utilizator(new_utilizator);
	}
}

void interfata::inregistreaza_administrator()
{
	std::string nume;
	std::string parola;
	char cc;
	this->util_admin = 1;
start:
	std::cout << "INREGISTRARE ADMINISTRATOR: " << std::endl;
	std::cout << "ID: ";
	std::cin.ignore();
	std::getline(std::cin, nume);
	this->m_nume = nume;
	if (SYSTEM::is_nume_administrator(nume) == 1) {
		std::cout << "NUMELE: " << nume << " ESTE DEJA IN SISTEM, INTRODUCETI PAROLA: \n";
		logger::set_in_file(nume, "ESTE DEJA IN SISTEM");
	pass:
		parola.clear();
		std::cout << "PAROLA: ";
		char c;
		while (1) {
			c = _getch();
			if (c == '\r') { break; }
			else if (c == '\b') {
				if (parola.size() == 0) {
					continue;
				}
				parola.pop_back(); std::cout << "\b \b";
			}
			else { std::cout << "*"; }
			if (c == '\b') {
				continue;
			}
			parola += c;
		}
		if (SYSTEM::check_password_administrator(nume, parola) == 0) {
		dec:
			std::cout << "\nParola incorecta! doriti sa reintroduceti parola?:" << std::endl << "(y = da, doresc sa reintroduc parola ; n = nu, doresc sa creez un cont nou.) : ";
			std::cin >> cc;
			if (cc == 'y') {
				goto pass;
			}
			else if (cc == 'n') {
				goto start;
			}
			else {
				std::cout << "invalid key\n";
				goto dec;
			}
		}
		else if (SYSTEM::check_password_administrator(nume, parola) == 1) {
			std::cout << "\nAdministratorul cu numele: " << nume << ", a fost autentificat cu succes!\n";
			this->meniu_administrator();
		}
	}
	else {
		std::cout << "PAROLA: ";
		char c;
		while (1) {
			c = _getch();
			if (c == '\r') { break; }
			else if (c == '\b') {
				if (parola.size() == 0) {
					continue;
				}
				parola.pop_back(); std::cout << "\b \b";
			}
			else { std::cout << "*"; }
			if (c == '\b') {
				continue;
			}
			parola += c;
		}
		administrator* new_admin = administrator_FACTORY::get_administrator(nume, parola);
		std::cout << std::endl;
		SYSTEM::add_administrator(new_admin);
	}
}

void interfata::meniu_persoana()
{
	if (this->util_admin == 0) {
		this->meniu_utilizator();
	}
	else if (this->util_admin == 1) {
		this->meniu_administrator();
	}
}

std::vector<std::string> separa(std::string c, std::string to_del) {
	std::regex del(c);
	std::sregex_token_iterator first{ to_del.begin(), to_del.end(), del, -1 }, last;
	std::vector<std::string>aux = { first, last };
	return aux;
}

void interfata::meniu_utilizator()
{
	char c;
	char cc;
	int k = 0;
	std::string nume_cazare;
	std::string oras;
	std::string nr_locuri;
	std::string nr_camere;
	std::string nr_loc;
	std::string masa;
	int nr_zile = 0;
	std::vector<std::string>vector_nr_loc;
	std::vector<std::string>mese;
	std::vector<data_zilei*>vector_zile;
start:
	std::cout << std::endl <<"-----------------------------------------------------------------------------------------------------------------" << std::endl;
	SYSTEM::get_discount_utilizator(this->m_nume);
	std::cout << std::endl;
	std::cout << "1. PLASEAZA REZERVARE: (press 1)\n";
	std::cout << "2. PLASEAZA RECENZIE: (press 2)\n";
	std::cout << "3. AFISEAZA VERDICTUL CERERILOR DE PANA ACUM: (press 3)\n";
	std::cout << "4. EXIT: (press 4)\n";
	std::cout << "5. LOG OFF: (press 5)\n";
	std::cout << std::endl << "-----------------------------------------------------------------------------------------------------------------" << std::endl;
	std::cin >> k;
	if (k == 1) {
	town:
		std::cout << "ALEGETI UN ORAS: ";
		std::cin.ignore();
		//std::cin >> c;
		std::getline(std::cin, oras);
		bool flag = SYSTEM::print_cazari_by_town(oras);
		if (flag == 0) {
			std::cout << "APASATI 0 PENTRU A VA REINTOARCE LA MENIUL PRINCIPAL: \n";
			std::cin >> k;
			if (k == 0) {
				goto start;
			}
			else
			goto town;
		}
		choice:
		std::cout << "DORITI SA CONTINUATI SAU ALEGETI UN NOU ORAS? (y = alege oras nou, n = continua cu orasul ales): ";
		std::cin >> c;
		if (c == 'y') {
			goto town;
		}
		else if (c == 'n') {
			std::cout << "ALEGETI CAZAREA PE CARE O DORITI: ";
			std::cin.ignore();
			//std::cin >> c;
			std::getline(std::cin, nume_cazare);
		room:
			std::cout << "DATI NUMARUL DE LOCURI PE CARE IL DORITI IN CAMERA: ";
			std::cin >> nr_locuri;

			if (SYSTEM::check_if_exist_nr_room(nume_cazare, oras, std::stoi(nr_locuri)) == 0) {
				std::cout << "ACEST TIP DE CAMERA NU EXISTA!!!(apasati y pt a continua, n pt a iesi): \n";
				if (c == 'y') {
					goto room;
				}
				else if (c == 'n') {
					goto start;
				}
			}
			std::cout << "DATI NUMARUL DE CAMERE PE CARE DORITI SA IL OCUPATI DIN TIPUL ALES ANTERIOR: ";
			std::cin >> nr_camere;

			if (SYSTEM::check_if_there_are_enough_rooms(nume_cazare, oras, std::stoi(nr_camere)) == 1) {
				std::cout << "ACEST TIP DE CAMERA NU ARE SUFICIENTE CAMERE!!!(apasati y pt a continua, n pt a iesi): \n";
				std::cin >> c;
				if (c == 'y') {
					goto room;
				}
				else if (c == 'n') {
					goto start;
				}
			}

			std::cout << "DORITI SA MAI ALEGETI SI ALT TIP DE CAMERA?: (y = da, n = nu): ";
			std::cin >> c;
			nr_loc = nr_camere + "x" + nr_locuri;
			vector_nr_loc.push_back(nr_loc);
			nr_loc.clear();
			if (c == 'y') {
				goto room;
			}
			else if (c == 'n') {
			gotomasa:
				std::cout << "CE MASA DORITI SA SERVITI? : (daca nu doriti nicio masa, va rugam lasati campul liber(apasati enter): ";
				std::cin.ignore();
				std::getline(std::cin, masa);
				if (SYSTEM::check_if_exist_dish(nume_cazare, oras, masa) == 0) {
					std::cout << "ACEASTA MASA NU POATE FI SERVITA AICI, VA RUGAM REINCERCATI SAU ANULATI REZERVAREA: (y-continui, n-exit): ";
					std::cin >> c;
					if (c == 'n') {
						goto start;
					}
				}
				if (masa == "") {
					goto datazi;
				}
				std::cout << "MAI DORITI SA SERVITI INCA UN TIP DE MASA? (y = da, n = nu):";
				std::cin >> c;
				mese.push_back(masa);
				if (c == 'y') {
					goto gotomasa;
				}
				else if (c == 'n') {
					datazi:
					std::cout << "DATI NUMARUL DE ZILE PE CARE DORITI SA LE PETRECETI IN CAZAREA ALEASA: ";
					std::cin >> nr_zile;
					for (int i = 0; i < nr_zile; i++) {
						date:
						std::cout << "DATI DATA ZILEI PE CARE DORITI SA O OCUPATI IMPREUNA CU NUMELE ZILEI: data(zz-ll-aaaa), numele:lowercase: ";
						std::string data;
						std::cin.ignore();
						std::getline(std::cin, data);
						std::vector<std::string>aux_arr = separa(" ", data);
						std::vector<std::string>date = separa("-", aux_arr[0]);
						std::vector<std::string>zi_date = separa("0", date[0]);
						std::vector<std::string>luna_date = separa("0", date[1]);
						if ((std::stoi(zi_date[0]) < 1) || (std::stoi(zi_date[0]) > 32)) {
							logger::set_in_file(m_nume, "A incercat sa introduca o data invalida => (" + aux_arr[0] + ")");
							std::cout << "DATA INVALIDA, INTRODUCETI ALTA DATA: (y = Introace-te la meniul principal, n = reintrodu data): ";
							char c;
							std::cin >> c;
							if (c == 'y') {
								goto start;
							}
							else if (c == 'n') {
								goto date;
							}
						}
						if ((std::stoi(luna_date[1]) < 1) || (std::stoi(luna_date[1]) > 13)) {
							logger::set_in_file(m_nume, "A incercat sa introduca o data invalida => (" + aux_arr[0] + ")");
							std::cout << "DATA INVALIDA, INTRODUCETI ALTA DATA: (y = Introace-te la meniul principal, n = reintrodu data): ";
							char c;
							std::cin >> c;
							if (c == 'y') {
								goto start;
							}
							else if (c == 'n') {
								goto date;
							}
						}
						if (SYSTEM::check_if_exist_data(nume_cazare, oras, aux_arr[0], aux_arr[1]) == 1) {
							std::cout << "DATA OCUPATA, INTRODUCETI ALTA DATA: (y = Introace-te la meniul principal, n = reintrodu data): ";
							char c;
							std::cin >> c;
							if (c == 'y') {
								goto start;
							}
							else if (c == 'n') {
								goto date;
							}
						}
						data_zilei* new_data = data_zilei_FACTORY::get_data_zilei(aux_arr[0], aux_arr[1]);
						vector_zile.push_back(new_data);
					}
				}
			}
		}
		else {
			std::cout << "invalid key\n";
			goto choice;
		}
		SYSTEM::get_utilizator(this->m_nume)->plaseaza_rezervare(nume_cazare, oras, vector_nr_loc, mese, nr_zile, vector_zile);
		std::cout << "DORITI SA SCRIETI O RECENZIE PENTRU CAZAREA LA CARE TOCMAI ATI APLICAT REZERVAREA? (y = da, n = nu):";
		std::cin >> c;
		if (c == 'y') {
			std::string recenzie;
			std::cout << "SCRIETI RECENZIA: ";
			std::cin.ignore();
			//std::cin >> c;
			std::getline(std::cin, recenzie);
			int nota;
			std::cout << "SCRIETI NOTA PE CARE DORITI SA O OFERITI PE O SCARA DE LA 1 LA 5(1-DELOC MULTUMIT, 5-CEL MAI MULTUMIT): ";
			std::cin >> nota;
			SYSTEM::get_utilizator(this->m_nume)->plaseaza_recenzie(nume_cazare, oras, recenzie, nota);
		}
		else if (c == 'n') {
			std::cout << "OK!\n";
		}
	}
	else if (k == 2) {
		std::cout << "ALEGETI UN ORAS: ";
		std::cin >> oras;
		if (interfata::search_for_town(oras) == 0) {
			logger::set_in_file(this->m_nume, "a incercat sa faca o recenzie intr-un oras inexistent in baza de date");
			throw error_EROARE("oras inexistent in baza de date");
		}
		std::cout << "ALEGETI CAZAREA PE CARE O DORITI: ";
		std::cin >> nume_cazare;
		if (SYSTEM::is_cazare_in_system(nume_cazare, oras) == 0) {
			logger::set_in_file(this->m_nume, "a incercat sa puna o recenzie la o cazare ( " + nume_cazare + " ) inexistenta in orasul " + oras);
			throw error_EROARE("aceasta cazare nu exista in orasul introdus. ne pare rau");
		}
		std::string recenzie;
		std::cout << "SCRIETI RECENZIA: ";
		std::cin.ignore();
		//std::cin >> c;
		std::getline(std::cin, recenzie);
		int nota;
		std::cout << "SCRIETI NOTA PE CARE DORITI SA O OFERITI PE O SCARA DE LA 1 LA 5(1-DELOC MULTUMIT, 5-CEL MAI MULTUMIT): ";
		std::cin >> nota;
		SYSTEM::get_utilizator(this->m_nume)->plaseaza_recenzie(nume_cazare, oras, recenzie, nota);
	}
	else if (k == 3) {
		//SYSTEM::get_utilizator(this->m_nume)->print();
		std::cout << SYSTEM::get_utilizator(this->m_nume);
}
	else if (k == 4) {
		std::cout << "SUNTETI SIGUR CA DORITI SA PARASITI APLICATIA?: (y = da, n = nu):\n";
		std::cin >> c;
		if (c == 'y') {
			exit(0);
		}
		else if (c == 'n') {
			goto start;
		}
	}
	else if (k == 5) {
		this->inregistreaza_persoana();
		if (this->util_admin == 0) {
			this->meniu_utilizator();
		}
		else if (this->util_admin == 1) {
			this->meniu_administrator();
		}
	}
	else {
		std::cout << "tasta incorecta\n";
		goto start;
	}
}

void interfata::meniu_administrator()
{
	int k;
	char c;
	std::string nume_cazare;
	std::string oras;
	std::string nr_locuri;
	std::string nr_camere;
	std::string nr_loc;
	std::string masa;
	int nr_zile = 0;
	std::vector<std::string> vector_nr_loc;
	std::vector<std::string>mese;
	int nr_stele;
	std::string pret;
	std::string pret_camera;
	std::string aux_pret_camera;
	std::vector<std::string>lista_preturi;
start:
	std::cout << std::endl << "-----------------------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << "PORTOFEL: " << SYSTEM::get_wallet_admin(this->m_nume) << " LEI\n\n";
	std::cout << "1. ADAUGA CAZARE: (press 1): \n";
	std::cout << "2. STERGE CAZARE: (press 2): \n";
	std::cout << "3. OFERA VERDICT UNEI REZERVARI APLICATE UNEIA DINTRE CAZARILE DUMNEAVOASTRA: (press 3) \n";
	std::cout << "4. AFISEAZA STATISTICA CAZARILOR DUMNEAVOASTRA IN FUNCTIE DE CELE MAI SOLICITATE: (press 4): \n";
	std::cout << "5. AFISEAZA GRADUL DE OCUPARE AL UNEI CAZARI: (press 5): \n";
	std::cout << "6. EXIT: (press 6): \n";
	std::cout << "7. LOG OFF: (press 7):";
	std::cout << std::endl << "-----------------------------------------------------------------------------------------------------------------" << std::endl;
	std::cin >> k;
	if (k == 1) {
		std::string tip;
		std::cout << "DATI TIPUL DE CAZARE: hotel / pensiune : ";
		std::cin >> tip;
		std::cout << "ALEGETI UN ORAS: ";
		std::cin.ignore();
		std::getline(std::cin, oras);

		if (interfata::search_for_town(oras) == 0) {
			logger::set_in_file(this->m_nume, "a incercat sa introduca o cazare intr-un oras inexistent in baza de date");
			throw error_EROARE("orasul unde doriti sa introduceti cazarea nu exista in baza noastra de date! ne pare rau!");
		}

		std::cout << "ALEGETI NUMELE CAZARII DE INTRODUS: ";
		//std::cin.ignore();
		std::getline(std::cin, nume_cazare);
		if (tip == "hotel") {
			std::cout << "DATI NUMARUL DE STELE AL HOTELULUI: ";
		}
		else if (tip == "pensiune") {
			std::cout << "DATI NUMARUL DE MARGARETE ALE PENSIUNII: ";
		}
		std::cin >> nr_stele;
	roomx:
		std::cout << "DATI NUMARUL DE LOCURI AL CAMEREI: ";
		std::cin >> nr_locuri;
		std::cout << "DATI NUMARUL DE CAMERE CU NUMARUL DE LOCURI ANTERIOR: ";
		std::cin >> nr_camere;
		std::cout << "DATI PRETUL PENTRU TIPUL DE CAMERA CU " << nr_locuri << " LOCURI: ";
		std::cin >> pret_camera;
		std::cout << "DORITI SA MAI INTRODUCETI SI ALT TIP DE CAMERA?: (y = da, n = nu): ";
		std::cin >> c;
		nr_loc = nr_camere + "x" + nr_locuri;
		aux_pret_camera = nr_locuri + "=" + pret_camera;
		vector_nr_loc.push_back(nr_loc);
		lista_preturi.push_back(aux_pret_camera);
		nr_loc.clear();
		aux_pret_camera.clear();
		if (c == 'y') {
			goto roomx;
		}
		else if (c == 'n') {
		gotomasax:
			std::cout << "INTRODUCETI PRIMUL TIP DE MASA CARE SE POATE SERVI: ";
			std::cin.ignore();
			std::getline(std::cin, masa);
			std::cout << "INTRODUCETI PRETUL PENTRU: " << masa << " : ";
			std::cin >> pret;
			masa = masa + "=" + pret;
			std::cout << "MAI DORITI SA SERVITI INCA UN TIP DE MASA? (y = da, n = nu):";
			std::cin >> c;
			mese.push_back(masa);
			if (c == 'y') {
				goto gotomasax;
			}
		}
		unitate_cazare* new_unitate = unitate_cazare_FACTORY::get_unitate_cazare(tip, nume_cazare, oras, nr_stele, vector_nr_loc, mese, lista_preturi);
		SYSTEM::get_administrator(this->m_nume)->add_unitate_cazare(new_unitate);
	}
	else if (k == 2) {
		for (int i = 0; i < SYSTEM::get_size_administrator_unitati_cazare(this->m_nume); i++) {
			SYSTEM::get_cazare_by_index_from_admin(this->m_nume, i)->print_cazare();
		}
		if (SYSTEM::get_size_administrator_unitati_cazare(this->m_nume) == 0) {
			logger::set_in_file(this->m_nume, "nu exista cazari inca in lista pentru a fi sterse");
			throw error_EROARE("nu exista cazari inca in lista pentru a fi sterse");
		}
		std::cout << "DATI NUMELE ORASULUI: ";
		std::cin.ignore();
		std::getline(std::cin, oras);
		std::cout << "DATI NUMELE CAZARII: ";
		std::getline(std::cin, nume_cazare);
		SYSTEM::sterge_cazare_from_administrator(this->m_nume, nume_cazare, oras);
	}
	else if (k == 3) {
		std::cout << "DATI NUMELE CAZARII: ";
		std::string cazare;
		std::cin.ignore();
		std::getline(std::cin, cazare);
		std::cout << "DATI ORASUL: ";
		std::string oras_verdict;
		//std::cin.ignore();
		std::getline(std::cin, oras_verdict);
		for (int i = 0; i < SYSTEM::get_size_unitate_cazare_rezervari(cazare, oras_verdict); i++) {
			std::cout << SYSTEM::get_rezervare_by_index(cazare, oras_verdict, i);
		}
		if (SYSTEM::check_if_exist_REZERVARI(cazare, oras_verdict) == 1) {
			std::cout << "NU EXISTA REZERVARI IN CADRUL CAZARII\n";
			goto start;
		}
		std::cout << "DATI UTILIZATORUL CARUIA DORITI SA II DATI VERDICTUL: ";
		std::string nume;
		//std::cin.ignore();
		std::getline(std::cin, nume);
		std::cout << "DATI VERDICTUL: (aprobat/respins): ";
		std::string verdict;
		std::cin >> verdict;
		SYSTEM::get_administrator(this->m_nume)->give_verdict(nume, cazare, oras_verdict, verdict);
	}
	else if (k == 4) {
		SYSTEM::get_administrator(this->m_nume)->print_top_cazari();
	}
	else if (k == 5) {
		for (int i = 0; i < SYSTEM::get_size_administrator_unitati_cazare(this->m_nume); i++) {
			SYSTEM::get_cazare_by_index_from_admin(this->m_nume, i)->print_cazare();
		}
		//again:
		std::cout << "DATI NUMELE CAZARII: ";
		std::cin.ignore();
		std::getline(std::cin, nume_cazare);
		std::cout << "DATI NUMELE ORASULUI: ";
		std::getline(std::cin, oras);
		if (SYSTEM::check_existanta_cazare(nume_cazare, oras) == 1) {
			SYSTEM::get_administrator(this->m_nume)->print_grad_ocupare_cazare(nume_cazare, oras);
		}
		else {
			logger::set_in_file(this->m_nume, "A incercat sa afiseze gradul de ocupare al unei cazari inexistente");
			throw error_TASTA("Combinatie de intrare cazare-oras incorecta, va rugam verificati si reincercati! (cazarea: " + nume_cazare + " din orasul: " + oras + " nu exista)");
			//goto again;
		}
	}
	else if (k == 6) {
		std::cout << "SUNTETI SIGUR CA DORITI SA PARASITI APLICATIA?: (y = da, n = nu):\n";
		std::cin >> c;
		if (c == 'y') {
			exit(0);
		}
		else if (c == 'n') {
			goto start;
		}
	}
	else if (k == 7) {
		this->inregistreaza_persoana();
		if (this->util_admin == 0) {
			this->meniu_utilizator();
		}
		else if (this->util_admin == 1) {
			this->meniu_administrator();
		}
	}
	else {
		std::cout << "TASTA INCORECTA!\n";
	}
}
