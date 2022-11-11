#pragma once

#include <iostream>
#include <vector>

class unitate_cazare;
class data_zilei;

class rezervare
{
private:
	std::string m_nume;
	std::string m_cazare;
	std::string m_oras;
	std::vector<std::string>m_lista_camere_dorite;
	std::vector<std::string>m_lista_mese;
	std::vector<data_zilei*>m_lista_date_zile;
	int m_nr_zile;
public:
	rezervare();
	rezervare(std::string nume, std::string cazare, std::string oras, std::vector<std::string>camere, std::vector<std::string>mese, std::vector<data_zilei*>);
	rezervare(const rezervare& src);
	~rezervare();

	std::vector<std::string> get_lista_camere();
	std::vector<data_zilei*> get_lista_date();
	const std::string &get_nume() const;
	const std::string &get_cazare() const;
	const std::string &get_oras() const;

	friend std::ostream& operator<<(std::ostream& out, rezervare* aux);
	void print();
};

