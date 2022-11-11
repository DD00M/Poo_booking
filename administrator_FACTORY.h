#pragma once

#include <iostream>

class administrator;

class administrator_FACTORY
{
public:
	static administrator* get_administrator(std::string nume, std::string parola);
};

