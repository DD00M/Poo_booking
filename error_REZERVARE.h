#pragma once
#include "error.h"
class error_REZERVARE :
    public error
{
public:
    error_REZERVARE(std::string msj);
    error_REZERVARE(const error_REZERVARE& src);
    ~error_REZERVARE();

    std::string get_mesaj();
};

