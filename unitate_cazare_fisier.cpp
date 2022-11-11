#include "unitate_cazare_fisier.h"
#include "unitate_cazare.h"

#include <fstream>

void unitate_cazare_fisier::add_in_file(unitate_cazare* aux)
{
	std::ofstream f;
	
	f.open("unitati_cazare.txt");

	f << aux->get_nume() << " " << aux->get_oras() << "\n";

	f.close();
}
