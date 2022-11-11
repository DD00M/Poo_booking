#pragma once

#include <iostream>

class administrator;

class administrator_FISIER
{
private:
	std::string m_nume;
public:
	static void set_in_file(administrator* aux);
};

