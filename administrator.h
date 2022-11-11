#pragma once

#include "persoana_i.h"

#include <iostream>
#include <vector>

class unitate_cazare;

class administrator :
	public persoana_i
{
private:
	std::string m_nume;
	std::string m_parola;
	std::vector<unitate_cazare*>m_lista_unitati_cazare;
	float portofel;

	std::string m_filename;
public:
	administrator();
	administrator(std::string nume, std::string parola);
	administrator(const administrator& src);
	~administrator();

	const std::string& get_nume() const;
	const std::string& get_parola() const;
	const std::string& get_filename() const;

	void add_unitate_cazare(unitate_cazare*);
	void give_verdict(std::string nume, std::string cazare, std::string oras, std::string verdict);
	void get_money(float sum);
	void print_top_cazari();
	void print_grad_ocupare_cazare(std::string nume, std::string oras);
	void sterge_cazare(std::string nume, std::string oras);

	const int get_size_vector_unitati_cazare();
	const float get_wallet()const;

	unitate_cazare* get_unitate_cazare_by_index(int index);

	//friend std::ostream& operator<<(std::ostream& out, administrator* admin);

	void print();
};

