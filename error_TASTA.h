#pragma once
#include "error.h"

class error_TASTA :
	public error
{
public:
    error_TASTA(std::string msj);
    error_TASTA(const error_TASTA& src);
    ~error_TASTA();

    std::string get_mesaj();
};

