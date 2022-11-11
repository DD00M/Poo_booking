#include "error_TASTA.h"

error_TASTA::error_TASTA(std::string msj) :error(msj)
{
	this->m_type = "TASTA INCORECTA";
	std::string aux = this->m_mesaj;
	this->m_mesaj = this->m_type + "->" + aux;
}

error_TASTA::error_TASTA(const error_TASTA& src) :error(src)
{
}

error_TASTA::~error_TASTA()
{
}

std::string error_TASTA::get_mesaj()
{
	return this->m_mesaj;
}
