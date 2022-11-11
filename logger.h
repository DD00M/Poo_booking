#pragma once

#include <iostream>
#include <string>

class logger
{
private:
	static std::string m_fisier;
	static int m_count_err;
public:
	logger();
	logger(const logger& src);
	~logger();

	static void set_in_file(std::string, std::string);
};
