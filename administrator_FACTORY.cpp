#include "administrator_FACTORY.h"
#include "administrator.h"

administrator* administrator_FACTORY::get_administrator(std::string nume, std::string parola)
{
    return new administrator(nume, parola);
}
