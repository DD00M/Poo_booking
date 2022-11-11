#pragma once

#include <iostream>

class data_zilei;

class data_zilei_FACTORY
{
public:
	static data_zilei* get_data_zilei(std::string data, std::string zi);
};

