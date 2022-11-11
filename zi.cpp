#include "zi.h"

zile zi::m_zi = zile::luni;
zi* zi::instance = nullptr;

zi::zi()
{
}

zi::zi(const zi& src)
{
	this->m_zi = src.m_zi;
}

zi::~zi()
{
}

zi& zi::get_instance()
{
	if (zi::instance == nullptr) {
		zi::instance = new zi();
	}
	return *zi::instance;
}

void zi::remove_instance()
{
	if (zi::instance != nullptr) {
		delete zi::instance;
		zi::instance = nullptr;
	}
}

std::string zi::get_zi()
{
	if (zi::m_zi == zile::luni) {
		return "luni";
	}
	else if (zi::m_zi == zile::marti) {
		return "marti";
	}
	else if (zi::m_zi == zile::miercuri) {
		return "miercuri";
	}
	else if (zi::m_zi == zile::joi) {
		return "joi";
	}
	else if (zi::m_zi == zile::vineri) {
		return "vineri";
	}
	else if (zi::m_zi == zile::sambata) {
		return "sambata";
	}
	else if (zi::m_zi == zile::duminica) {
		return "duminica";
	}
}

void zi::set_day(std::string zi)
{
	if (zi == "luni") {
		this->set_to_luni();
	}
	else if (zi == "marti") {
		this->set_to_marti();
	}
	else if (zi == "miercuri") {
		this->set_to_miercuri();
	}
	else if (zi == "joi") {
		this->set_to_joi();
	}
	else if (zi == "vineri") {
		this->set_to_vineri();
	}
	else if (zi == "sambata") {
		this->set_to_sambata();
	}
	else if (zi == "duminica") {
		this->set_to_duminica();
	}
}

void zi::set_to_luni()
{
	this->m_zi = zile::luni;
}

void zi::set_to_marti()
{
	this->m_zi = zile::marti;
}

void zi::set_to_miercuri()
{
	this->m_zi = zile::miercuri;
}

void zi::set_to_joi()
{
	this->m_zi = zile::joi;
}

void zi::set_to_vineri()
{
	this->m_zi = zile::vineri;
}

void zi::set_to_sambata()
{
	this->m_zi = zile::sambata;
}

void zi::set_to_duminica()
{
	this->m_zi = zile::duminica;
}