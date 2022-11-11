#pragma once

#include <iostream>

class unitate_cazare;

class unitate_cazare_fisier
{
private:
	std::string m_filename;
public:
	static void add_in_file(unitate_cazare* aux);
};

