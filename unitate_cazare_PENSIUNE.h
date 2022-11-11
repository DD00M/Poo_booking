#pragma once
#include "unitate_cazare.h"
class unitate_cazare_PENSIUNE :
    public unitate_cazare
{
public:
    unitate_cazare_PENSIUNE();
    unitate_cazare_PENSIUNE(std::string nume, std::string oras, int clasificare, std::vector<std::string> lista , std::vector<std::string>mese, std::vector<std::string> preturi);
    unitate_cazare_PENSIUNE(const unitate_cazare_PENSIUNE& src);
    ~unitate_cazare_PENSIUNE();

    void print_cazare();
};

