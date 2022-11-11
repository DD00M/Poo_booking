#include "utilizator_fisier.h"
#include "utilizator.h"

#include <fstream>

void utilizator_fisier::set_in_file(utilizator* aux)
{
	std::ofstream f;
	f.open("utilizatori.txt");

	f << aux->get_nume() << " " << aux->get_parola() << " " << aux->get_contor_rezervari_reusite() << "\n";

	f.close();
}
