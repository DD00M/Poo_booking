#pragma once

#include <iostream>
#include <vector>

class unitate_cazare;

class unitate_cazare_FACTORY
{
public:
	static unitate_cazare* get_unitate_cazare(std::string tip, std::string nume, std::string oras, int nr_stele, std::vector<std::string> camere, std::vector<std::string>mese, std::vector<std::string>preturi);
};

