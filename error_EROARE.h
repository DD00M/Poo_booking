#pragma once
#include "error.h"
class error_EROARE :
    public error
{
public:
    error_EROARE(std::string msj);
    error_EROARE(const error_EROARE& src);
    ~error_EROARE();

    std::string get_mesaj();
};

