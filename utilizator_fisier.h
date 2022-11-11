#pragma once

#include <iostream>

class utilizator;

class utilizator_fisier
{
private:
	std::string m_nume;
public:
	static void set_in_file(utilizator*);
};

