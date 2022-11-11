#include "error_REZERVARE.h"

error_REZERVARE::error_REZERVARE(std::string msj) :error(msj)
{
	this->m_type = "REZERVARE";
	std::string aux = this->m_mesaj;
	this->m_mesaj = this->m_type + "->" + aux;
}

error_REZERVARE::error_REZERVARE(const error_REZERVARE& src) :error(src)
{
}

error_REZERVARE::~error_REZERVARE()
{
}

std::string error_REZERVARE::get_mesaj()
{
	return this->m_mesaj;
}
