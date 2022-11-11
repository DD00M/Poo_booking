#include <iostream>

#include "utilizator.h"
#include "administrator.h"
#include "unitate_cazare.h"
#include "unitate_cazare_HOTEL.h"
#include "unitate_cazare_PENSIUNE.h"

#include "SYSTEM.h"

#include "zi.h"
#include "data_zilei.h"

#include "error.h"

#include "administrator_FACTORY.h"
#include "utilizator_FACTORY.h"
#include "unitate_cazare_FACTORY.h"
#include "interfata.h"

#include "calendar.h"

using namespace std;

int main() {
	std::string nume = "ATM_BOOKING";
	SYSTEM& system = SYSTEM::get_instance(nume);
	calendar& my_calendar = calendar::get_instance(2021);
	std::cout << "-------------------------------------------------" << nume << "---------------------------------------------" << std::endl << std::endl << std::endl;
	std::cout << "--------------------------------------BY DUMITRASCU ANDREI-COSMIN, C112_D--------------------------------" << std::endl << std::endl << std::endl;
	interfata& menu = interfata::get_instance({ "bucuresti", "buzau", "brasov", "sibiu", "iasi", "baia mare", "timisoara", "oltenita", "sfantu gheorghe", "constanta", "craiova", "galati", "oradea", "pitesti", "braila", "arad", "bacau", "targu mures", "suceava", "piatra neamt", "ramnicu valcea", "focsani", "tulcea", "bistrita", "resita", "slatina", "bals", "deva", "giurgiu", "calarasi", "botosani", "mangalia", "tecuci", "dej", "pascani", "navodari", "mamaia", "costinesti", "vama veche", "fagaras", "sighisoara", "radauti", "buftea", "comanesti", "targu secuiesc", "cernavoda", "corabia", "adjud" ,"dabuleni","comarnic"});
	std::cout << "---------------------------------------------------------------------------------------------------------" << std::endl << std::endl << std::endl << std::endl;
	my_calendar.print();
	menu.meniu();
	int z = 0;
inceput:
	try {
		menu.inregistreaza_persoana();
	}
	catch (error& e) {
		std::cout << e.get_mesaj() << std::endl;
		z = 1;
		goto inceput;
	}
meniu:
	try{
		menu.meniu_persoana();
		if (z == 0) {
			std::cout << "DORITI SA VA DELOGATI? (1-da, 0-nu): ";
			int k;
			std::cin >> k;
			if (k == 1) {
				goto inceput;
			}if (k == 0) {
				goto meniu;
			}
		}
	}
	catch(error&e){
		std::cout << e.get_mesaj() << std::endl;
		goto meniu;
	}


	return 0; 
}