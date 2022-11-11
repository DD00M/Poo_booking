#pragma once
#include "error.h"
class error_ALERTA :
    public error
{
public:
    error_ALERTA(std::string msj);
    error_ALERTA(const error_ALERTA& src);
    ~error_ALERTA();

    std::string get_mesaj();
};

