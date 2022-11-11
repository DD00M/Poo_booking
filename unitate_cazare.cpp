#include "unitate_cazare.h"
#include "zi.h"

#include "data_zilei.h"

#include "error.h"
#include "error_ALERTA.h"
#include "error_EROARE.h"
#include "error_REZERVARE.h"

#include "logger.h"

#include <string>
#include <regex>

unitate_cazare::unitate_cazare()
{
	this->m_spatii_ocupate = 0;
	this->m_spatii_cazare = 0;
	this->nr_total_camere = 0;
}

unitate_cazare::unitate_cazare(std::string nume, std::string oras, int clasificare, std::vector<std::string>lista_camere, std::vector<std::string>mese, std::vector<std::string> pret) :m_denumire(nume), m_oras(oras), m_clasificare(clasificare)
{
	//axb
	std::vector<std::string>aux_pret;
	std::vector<std::string>aux_mese;
	int nr;
	int nr_preturi;
	this->m_spatii_ocupate = 0;
	this->m_spatii_cazare = 0;
	this->nr_total_camere = 0;
	for (int i = 0; i < mese.size(); i++) {
		std::regex del("=");
		std::sregex_token_iterator first{ mese[i].begin(), mese[i].end(), del, -1 }, last;
		aux_mese = { first, last };
		this->m_lista_mese.emplace_back(aux_mese[0], std::stoi(aux_mese[1]));
	}
	for (int i = 0; i < pret.size(); i++) {
		std::regex del("=");
		std::sregex_token_iterator first{ pret[i].begin(), pret[i].end(), del, -1 }, last;
		aux_pret = { first, last };
		nr = std::stoi(aux_pret[0]);
		nr_preturi = std::stoi(aux_pret[1]);
		//if (zi::get_zi() == "sambata" || zi::get_zi() == "duminica") {
			//this->m_lista_preturi.emplace_back(nr, 25 % nr_preturi + nr_preturi);
		//}
		//else {
			this->m_lista_preturi.emplace_back(nr, nr_preturi);
		//}
	}
	std::vector<std::string>aux;
	int nr_camere;
	int nr_locuri;
	for (int i = 0; i < lista_camere.size(); i++) {
		std::regex del("x");
		std::sregex_token_iterator first{ lista_camere[i].begin(), lista_camere[i].end(), del, -1 }, last;
		aux = { first, last };
		nr_camere = std::stoi(aux[0]);
		nr_locuri = std::stoi(aux[1]);
		this->m_spatii_cazare += nr_camere;
		this->nr_total_camere += nr_camere;
		this->m_lista_camere.emplace_back(nr_camere, nr_locuri);
		aux.erase(aux.begin(), aux.end());
	}
}

unitate_cazare::unitate_cazare(const unitate_cazare& src)
{
	this->m_denumire = src.m_denumire;
	this->m_clasificare = src.m_clasificare;
	this->m_oras = src.m_oras;
	this->m_spatii_cazare = src.m_spatii_cazare;
	this->m_pret_camera = src.m_pret_camera;
	for (int i = 0; i < src.m_lista_mese.size(); i++) {
		this->m_lista_mese.push_back(src.m_lista_mese[i]);
	}
}

unitate_cazare::~unitate_cazare()
{
}

int unitate_cazare::get_size_vector_rezervari()const
{
	return this->m_lista_rezervari.size();
}

int unitate_cazare::get_type(int index)const
{
	return this->m_lista_camere[index].second;
}

void unitate_cazare::ocupa_spatii(int spatii)
{
	this->m_spatii_cazare -= spatii;
}

void unitate_cazare::add_again(int type, int nr_room)
{
	for (auto i = this->m_lista_camere.begin(); i != this->m_lista_camere.end(); i++) {
		if (i->second == type) {
			this->m_spatii_cazare += nr_room;
			i->first += nr_room;
			break;
		}
	}
}

void unitate_cazare::ocupa_spatii_grad_ocupare(int spatii)
{
	this->m_spatii_ocupate += spatii;
}

void unitate_cazare::delete_rezervare(int index)
{
	this->m_lista_rezervari.erase(this->m_lista_rezervari.begin() + index);
}

void unitate_cazare::set_grad_ocupare(float grad)
{
	this->m_grad_ocupare = grad;
}

void unitate_cazare::ocupa_zile(std::vector<data_zilei*> data)
{
	for (int i = 0; i < data.size(); i++) {
		this->m_lista_date_rezervari.push_back(data[i]);
	}
}

std::vector<data_zilei*> unitate_cazare::get_arr_zile()
{
	return this->m_lista_date_rezervari;
}

float unitate_cazare::get_grad_ocupare() const
{
	return this->m_grad_ocupare;
}

rezervare* unitate_cazare::get_rezervare_by_index(int index)
{
	return this->m_lista_rezervari[index];
}

const std::string &unitate_cazare::get_nume() const
{
	return this->m_denumire;
}

const std::string &unitate_cazare::get_oras() const
{
	return this->m_oras;
}

void unitate_cazare::adauga_recenzie(std::string nume, std::string mesaj, int nota)
{
	this->m_lista_recenzii.emplace_back(nume, mesaj);
	this->m_lista_note.push_back(nota);
	float value;
	int big_nr = 0;
	for (int i = 0; i < this->m_lista_note.size(); i++) {
		big_nr += this->m_lista_note[i];
	}
	value = (float)(((float)big_nr) / this->m_lista_note.size());
	this->m_medie_note = value;
}

int unitate_cazare::get_size_of_vector_camere()const
{
	return this->m_lista_camere.size();
}

std::pair<int, int> unitate_cazare::get_type_of_room(int index)const
{
	if (this->m_lista_camere.size() < index) {
		
	}
	else {
		for (int i = 0; i < this->m_lista_camere.size(); i++) {
			if (i == index) {
				return this->m_lista_camere[i];
			}
		}
	}
}

std::string unitate_cazare::set_number_of_rooms_by_type(int type, int nr_room)
{
	std::string aux;
	for (auto i = this->m_lista_camere.begin(); i != this->m_lista_camere.end(); i++) {
		if (i->second == type) {
			if (i->first - nr_room < 0) {
				throw error_ALERTA("NU MAI SUNT CAMERE DISPONIBILE!");
				logger::set_in_file(this->m_denumire, "NU MAI SUNT CAMERE DISPONIBILE!");
			}
			else if (i->first - nr_room >= 0) {
				this->m_spatii_cazare -= nr_room;
				i->first -= nr_room;
				aux = std::to_string(nr_room) + "x" + std::to_string(i->second);
				return aux;
			}
		}
	}
}

std::string unitate_cazare::get_dish_by_index(int index) const
{
	return this->m_lista_mese[index].first;
}

void unitate_cazare::adauga_rezervare(rezervare* r)
{
	unitate_cazare::m_numar_rezervari_aplicate++;
	this->m_lista_rezervari.push_back(r);
}

std::pair<int, float> unitate_cazare::get_pret_by_camera(int type)const
{
	for (int i = 0; i < this->m_lista_preturi.size(); i++) {
		if (this->m_lista_preturi[i].first == type) {
			return this->m_lista_preturi[i];
		}
	}
}

int unitate_cazare::get_size_of_vector_preturi()const
{
	return this->m_lista_preturi.size();
}

float unitate_cazare::get_price_by_meal(std::string meal)const
{
	for (int i = 0; i < this->m_lista_mese.size(); i++) {
		if (this->m_lista_mese[i].first == meal) {
			return this->m_lista_mese[i].second;
		}
	}
}

int unitate_cazare::get_nr_total_camere()const
{
	return this->nr_total_camere;
}

int unitate_cazare::get_top_cazare()const
{
	return this->m_numar_rezervari_aplicate;
}

const int unitate_cazare::get_size_vector_mese()
{
	return this->m_lista_mese.size();
}

bool unitate_cazare::is_meal(std::string d)
{
	bool flag = 0;
	for (int i = 0; i < this->m_lista_mese.size(); i++) {
		if (this->m_lista_mese[i].first == d) {
			flag = 1;
			break;
		}
	}
	return flag;
}
