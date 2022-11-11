#pragma once

#include <iostream>

class utilizator;

class utilizator_FACTORY
{
public:
	static utilizator* get_utilizator(std::string nume, std::string parola);
};

