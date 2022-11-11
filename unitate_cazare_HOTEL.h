#pragma once
#include "unitate_cazare.h"
class unitate_cazare_HOTEL :
    public unitate_cazare
{
public:
    unitate_cazare_HOTEL();
    unitate_cazare_HOTEL(std::string nume, std::string oras, int clasificare, std::vector<std::string>lista, std::vector<std::string>mese, std::vector<std::string> preturi);
    unitate_cazare_HOTEL(const unitate_cazare_HOTEL& src);
    ~unitate_cazare_HOTEL();

    void print_cazare();
};

