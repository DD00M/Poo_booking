#include "unitate_cazare_HOTEL.h"
#include "rezervare.h"
#include "data_zilei.h"

#include <string>

unitate_cazare_HOTEL::unitate_cazare_HOTEL() :unitate_cazare()
{
}

unitate_cazare_HOTEL::unitate_cazare_HOTEL(std::string nume, std::string oras, int clasificare, std::vector<std::string>lista, std::vector<std::string> mese, std::vector<std::string> preturi) : unitate_cazare(nume, oras, clasificare,lista, mese, preturi)
{
}

unitate_cazare_HOTEL::unitate_cazare_HOTEL(const unitate_cazare_HOTEL& src) :unitate_cazare(src)
{
}

unitate_cazare_HOTEL::~unitate_cazare_HOTEL()
{
}

void unitate_cazare_HOTEL::print_cazare()
{
	std::cout << "Hotelul cu numele: " << this->m_denumire << " din orasul: " << this->m_oras << std::endl;
	std::cout << "---------Caracteristicile hotelului---------" << std::endl;
	if (this->m_clasificare == 1) {
		std::cout << "Hotelul are " << this->m_clasificare << " stea" << std::endl;
	}
	else {
		std::cout << "Hotelul are " << this->m_clasificare << " stele" << std::endl;
	}
	std::cout << "<------------------------------------------------------------------------------------------------------------------------------------->" << std::endl;
	std::cout << "NUMAR TOTAL DE LOCURI: " << this->m_spatii_cazare << std::endl;
	std::cout << "<------------------------------------------------------------------------------------------------------------------------------------->" << std::endl;
	std::cout << "ORGANIZAREA CAMERELOR SI LOCURI DISPONIBILE PER CAMERA: " << std::endl;
	for (int i = 0; i < this->m_lista_camere.size(); i++) {
		if (this->m_lista_camere[i].first != 1) {
			std::cout << i + 1 << ": " << this->m_lista_camere[i].first << " camere a cate " << this->m_lista_camere[i].second << " persoane" << std::endl;
		}
		else if (this->m_lista_camere[i].first == 1) {
			std::cout << i + 1 << ": " << this->m_lista_camere[i].first << " camera a cate " << this->m_lista_camere[i].second << " persoane" << std::endl;
		}
	}
	std::cout << "<------------------------------------------------------------------------------------------------------------------------------------->" << std::endl;
	std::cout << "MESELE PE CARE HOTELUL LE POATE OFERI CLIENTILOR: " << std::endl;
	for (int i = 0; i < this->m_lista_mese.size(); i++) {
		if (this->m_lista_mese[i].second == 1) {
			std::cout << i + 1 << ": " << this->m_lista_mese[i].first << " cu pretul: " << this->m_lista_mese[i].second << " leu" << std::endl;
		}
		else {
			std::cout << i + 1 << ": " << this->m_lista_mese[i].first << " cu pretul: " << this->m_lista_mese[i].second << " lei" << std::endl;
		}
	}
	std::cout << "<------------------------------------------------------------------------------------------------------------------------------------->" << std::endl;
	std::cout << "PRETURILE CAMERELOR SUNT: " << std::endl;
	for (int i = 0; i < this->m_lista_preturi.size(); i++) {
		if (this->m_lista_preturi[i].first == 1) {
			if (this->m_lista_preturi[i].second == 1) {
				std::cout << i + 1 << ": " << "Camera de " << this->m_lista_preturi[i].first << " persoana costa: " << this->m_lista_preturi[i].second << " leu" << std::endl;
			}
			else {
				std::cout << i + 1 << ": " << "Camera de " << this->m_lista_preturi[i].first << " persoana costa: " << this->m_lista_preturi[i].second << " lei" << std::endl;
			}
		}
		else {
			if (this->m_lista_preturi[i].second == 1) {
				std::cout << i + 1 << ": " << "Camera de " << this->m_lista_preturi[i].first << " persoane costa: " << this->m_lista_preturi[i].second << " leu" << std::endl;
			}
			else {
				std::cout << i + 1 << ": " << "Camera de " << this->m_lista_preturi[i].first << " persoane costa: " << this->m_lista_preturi[i].second << " lei" << std::endl;
			}
		}	
	}
	std::cout << "<------------------------------------------------------------------------------------------------------------------------------------->" << std::endl;
	std::cout << "LISTA CU DATELE DEJA OCUPATE DE CATRE CLIENTII NOSTRI(observatie: nu veti putea selecta o zi deja ocupata, pentru a nu fi nevoiti sa reluati cererea de rezervare, va rugam sa completati lista de zile cu atentie maxima!\n";
	for (int i = 0; i < this->m_lista_date_rezervari.size(); i++) {
		this->m_lista_date_rezervari[i]->print_zi();
	}
	std::cout << "<------------------------------------------------------------------------------------------------------------------------------------->" << std::endl;
	if (this->m_lista_recenzii.size() == 0) {
		std::cout << "Hotelul " << this->m_denumire << " nu a primit inca recenzii" << std::endl;
	}
	else {
		std::cout << "NUMARUL TOTAL DE RECENZII: " << this->m_lista_recenzii.size() << std::endl;
		std::cout << "MEDIA NOTELOR OFERITE DE CLIENTII ANTERIORI: " << this->m_medie_note << std::endl;
		std::cout << "RECENZIILE HOTELULUL PRIMITE DIN PARTEA CLIENTILOR: " << std::endl;
		for (int i = 0; i < this->m_lista_recenzii.size(); i++) {
			std::cout << i + 1 << ": " << this->m_lista_recenzii[i].first << " : " << this->m_lista_recenzii[i].second <<" : cu nota : " << this->m_lista_note[i] << std::endl;
		}
	}
	std::cout << "<------------------------------------------------------------------------------------------------------------------------------------->" << std::endl;
}

