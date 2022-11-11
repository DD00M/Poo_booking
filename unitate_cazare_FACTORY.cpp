#include "unitate_cazare_FACTORY.h"
#include "unitate_cazare_HOTEL.h"
#include "unitate_cazare_PENSIUNE.h"

unitate_cazare* unitate_cazare_FACTORY::get_unitate_cazare(std::string tip, std::string nume, std::string oras, int nr_stele, std::vector<std::string> camere, std::vector<std::string> mese, std::vector<std::string> preturi)
{
    if (tip == "hotel") {
        return new unitate_cazare_HOTEL(nume, oras, nr_stele, camere, mese, preturi);
    }
    else if (tip == "pensiune") {
        return new unitate_cazare_PENSIUNE(nume, oras, nr_stele, camere, mese, preturi);
    }
    return nullptr;
}
