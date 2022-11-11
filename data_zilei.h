#pragma once

#include <iostream>
#include <string>

enum class nume_zi {
	luni,
	marti,
	miercuri,
	joi,
	vineri,
	sambata,
	duminica
};

class data_zilei
{
private:
	std::string name;
	nume_zi nameday;
	int m_zi;
	int m_luna;
	int m_an;
public:
	data_zilei(std::string data, std::string zi);
	data_zilei(const data_zilei& src);
	~data_zilei();

	int get_zi();
	nume_zi get_nameday();
	int get_luna();
	int get_an();

	std::string get_zi_string();
	std::string get_nume();

	void print_zi();
};

