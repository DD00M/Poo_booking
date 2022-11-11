#include "error_ALERTA.h"

error_ALERTA::error_ALERTA(std::string msj) :error(msj)
{
	this->m_type = "ALERTA";
	std::string aux = this->m_mesaj;
	this->m_mesaj = this->m_type + "->" + aux;
}

error_ALERTA::error_ALERTA(const error_ALERTA& src) : error(src)
{
}

error_ALERTA::~error_ALERTA()
{
}

std::string error_ALERTA::get_mesaj()
{
	return this->m_mesaj;
}
