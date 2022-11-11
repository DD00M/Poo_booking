#pragma once

#include "error_I.h"

#include <iostream>

class error :
	public error_I
{
protected:
	std::string m_type;
	std::string m_mesaj;
public:
	error(std::string mesaj);
	error(const error& src);
	virtual ~error();
};

