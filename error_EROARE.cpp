#include "error_EROARE.h"

error_EROARE::error_EROARE(std::string msj) :error(msj)
{
	this->m_type = "EROARE";
	std::string aux = this->m_mesaj;
	this->m_mesaj = this->m_type + "->" + aux;
}

error_EROARE::error_EROARE(const error_EROARE& src) : error(src)
{
}

error_EROARE::~error_EROARE()
{
}

std::string error_EROARE::get_mesaj()
{
	return this->m_mesaj;
}
