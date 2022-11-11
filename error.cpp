#include "error.h"
#include <fstream>

error::error(std::string mesaj)
{
	this->m_mesaj = mesaj + "\n";
}

error::error(const error& src)
{
	this->m_mesaj = src.m_mesaj;
}

error::~error()
{
}

