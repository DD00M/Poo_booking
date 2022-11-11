#include "logger.h"

#include <fstream>

int logger::m_count_err = 0;
std::string logger::m_fisier = " ";

logger::logger()
{
	logger::m_fisier = "depanare.log";
}

logger::logger(const logger& src)
{
	logger::m_count_err = src.m_count_err;
	logger::m_fisier = src.m_fisier;
}

logger::~logger()
{
}

void logger::set_in_file(std::string tip, std::string mesaj)
{
	logger::m_count_err++;
	std::ofstream f;
	logger::m_fisier = "depanare.log";
	f.open(logger::m_fisier, std::ios::app);
	f << logger::m_count_err << " : " << "[" << tip << "]" << " : ";
	f << mesaj;
	f << "\n";

	f.close();
}
