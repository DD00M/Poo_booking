#include "administrator_FISIER.h"
#include "administrator.h"

#include <fstream>

void administrator_FISIER::set_in_file(administrator* aux)
{
	std::ofstream f;
	f.open("administratori.txt");

	f << aux->get_nume() << " " << aux->get_parola() << " " << aux->get_wallet() << "\n";

	f.close();
}
