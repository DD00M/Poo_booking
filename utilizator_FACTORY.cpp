#include "utilizator_FACTORY.h"
#include "utilizator.h"

utilizator* utilizator_FACTORY::get_utilizator(std::string nume, std::string parola)
{
    return new utilizator(nume, parola);
}
