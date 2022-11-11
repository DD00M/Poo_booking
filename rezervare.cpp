#include "rezervare.h"
#include "unitate_cazare.h"

rezervare::rezervare()
{
}

rezervare::rezervare(std::string nume, std::string cazare, std::string oras, std::vector<std::string> camere, std::vector<std::string> mese, std::vector<data_zilei*> date) :m_nume(nume), m_cazare(cazare), m_oras(oras)
{
	for (int i = 0; i < camere.size(); i++) {
		this->m_lista_camere_dorite.push_back(camere[i]);
	}
	for (int j = 0; j < mese.size(); j++) {
		this->m_lista_mese.push_back(mese[j]);
	}
	for (int k = 0; k < date.size(); k++) {
		this->m_lista_date_zile.push_back(date[k]);
	}
}

rezervare::rezervare(const rezervare& src)
{
	this->m_nume = src.m_nume;
	for (int i = 0; i < src.m_lista_camere_dorite.size(); i++) {
		this->m_lista_camere_dorite.push_back(src.m_lista_camere_dorite[i]);
	}
	for (int j = 0; j < src.m_lista_mese.size(); j++) {
		this->m_lista_mese.push_back(src.m_lista_mese[j]);
	}
}

rezervare::~rezervare()
{
}

std::vector<std::string> rezervare::get_lista_camere()
{
	return this->m_lista_camere_dorite;
}

std::vector<data_zilei*> rezervare::get_lista_date()
{
	return this->m_lista_date_zile;
}

const std::string& rezervare::get_nume()const
{
	return this->m_nume;
}

const std::string& rezervare::get_cazare()const
{
	return this->m_cazare;
}

const std::string& rezervare::get_oras()const
{
	return this->m_oras;
}

void rezervare::print()
{
	std::cout << "NUMELE UTILIZATORULUI: " << this->m_nume << std::endl;
	std::cout << "NUMELE CAZARII: " << this->m_cazare << std::endl;
	std::cout << "NUMELE ORASULUI: " << this->m_oras << std::endl;
	std::cout << "NUMAR DE CAMERE x NUMAR DE LOCURI/CAMERA\n";
	for (int i = 0; i < this->m_lista_camere_dorite.size(); i++) {
		std::cout << this->m_lista_camere_dorite[i] << std::endl;
	}
	std::cout << "MESELE ALESE: \n";
	for (int i = 0; i < this->m_lista_mese.size(); i++) {
		std::cout << this->m_lista_mese[i] << std::endl;
	}
}

std::ostream& operator<<(std::ostream& out, rezervare* aux)
{
	out << "NUMELE UTILIZATORULUI: " << aux->m_nume << std::endl;
	out << "NUMELE CAZARII: " << aux->m_cazare << std::endl;
	out << "NUMELE ORASULUI: " << aux->m_oras << std::endl;
	out << "NUMAR DE CAMERE x NUMAR DE LOCURI/CAMERA\n";
	for (int i = 0; i < aux->m_lista_camere_dorite.size(); i++) {
		out << aux->m_lista_camere_dorite[i] << std::endl;
	}
	out << "MESELE ALESE: \n";
	for (int i = 0; i < aux->m_lista_mese.size(); i++) {
		std::cout << aux->m_lista_mese[i] << std::endl;
	}
	return out;
}
