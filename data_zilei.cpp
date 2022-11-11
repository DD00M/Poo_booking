#include "data_zilei.h"

#include <iostream>
#include <regex>
#include <string>

data_zilei::data_zilei(std::string data, std::string zi)
{
	//zz.ll.aaaa
	this->name = zi;
	std::vector<std::string>lista;
	std::regex del("-");
	std::sregex_token_iterator first(data.begin(), data.end(), del, -1), last;
	lista = { first, last };
	this->m_zi = std::stoi(lista[0]);
	this->m_luna = std::stoi(lista[1]);
	this->m_an = std::stoi(lista[2]);
	if (zi == "luni") {
		this->nameday = nume_zi::luni;
	}
	else if (zi == "marti") {
		this->nameday = nume_zi::marti;
	}
	else if (zi == "miercuri") {
		this->nameday = nume_zi::miercuri;
	}
	else if (zi == "joi") {
		this->nameday = nume_zi::joi;
	}
	else if (zi == "vineri") {
		this->nameday = nume_zi::vineri;
	}
	else if (zi == "sambata") {
		this->nameday = nume_zi::sambata;
	}
	else if (zi == "duminica") {
		this->nameday = nume_zi::duminica;
	}
}

data_zilei::data_zilei(const data_zilei& src)
{
	this->m_zi = src.m_zi;
	this->m_luna = src.m_luna;
	this->m_an = src.m_an;
	this->nameday = src.nameday;
}

data_zilei::~data_zilei()
{
}

int data_zilei::get_zi()
{
	return this->m_zi;
}

nume_zi data_zilei::get_nameday()
{
	return this->nameday;
}

int data_zilei::get_luna()
{
	return this->m_luna;
}

int data_zilei::get_an()
{
	return this->m_an;
}

std::string data_zilei::get_zi_string()
{
	std::string zi;
	if (this->m_zi < 10 && this->m_luna >= 10) {
		zi += "0" + std::to_string(this->m_zi) + "-" + std::to_string(this->m_luna) + "-" + std::to_string(this->m_an);
	}
	else if (this->m_zi < 10 && this->m_luna < 10) {
		zi += "0" + std::to_string(this->m_zi) + "-" + "0" + std::to_string(this->m_luna) + "-" + std::to_string(this->m_an);
	}
	else if (this->m_zi >= 10 && this->m_luna >= 10) {
		zi += std::to_string(this->m_zi) + "-" + std::to_string(this->m_luna) + "-" + std::to_string(this->m_an);
	}
	else if (this->m_zi >= 10 && this->m_luna < 10) {
		zi += std::to_string(this->m_zi) + "-" + "0" + std::to_string(this->m_luna) + "-" + std::to_string(this->m_an);
	}
	return zi;
}

std::string data_zilei::get_nume()
{
	return this->name;
}

void data_zilei::print_zi()
{
	std::cout << "[ " << this->m_zi << "-" << this->m_luna << "-" << this->m_an << " ]" << " : " << "[ " << this->name << " ]" << std::endl;
}
