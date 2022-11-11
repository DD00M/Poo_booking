#pragma once
#include "persoana_i.h"

#include <iostream>
#include <vector>

class administrator;
class data_zilei;

class utilizator:
	public persoana_i
{
private:
	std::string m_nume;
	std::string m_parola;
	float m_pret_de_platit; 
	static int m_nr_rezervari_efectuate;
	std::vector<std::pair<std::string, std::string>>m_lista_rezervari;

	std::string m_filename;
public:
	utilizator();
	utilizator(std::string nume, std::string parola);
	utilizator(const utilizator& src);
	~utilizator();

	const std::string &get_nume() const;
	const std::string &get_parola() const;
	const std::string& get_filename() const;

	void set_price(float pret);
	void plaseaza_recenzie(std::string nume, std::string oras, std::string recenzie, int nota);
	static void contorizeaza_rezervare_reusita();
	static void scade_contor();
	static const int get_contor_rezervari_reusite();
	void plaseaza_rezervare(std::string nume, std::string oras, std::vector<std::string>, std::vector<std::string>, int, std::vector<data_zilei*>);
	const float &get_plata() const;
	void add_rezervare_goodORbad(std::string type, std::string m);
	int distribuie_bonus();

	friend std::ostream& operator<<(std::ostream& out, utilizator* admin);

	void print();
};

