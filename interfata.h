#pragma once

#include <iostream>
#include <vector>

class interfata
{
private:
	interfata(std::vector<std::string> lista);
	~interfata();

	static std::vector<std::string> m_lista_orase;
	static interfata* instance;
	int util_admin;
	std::string m_nume;
public:
	static interfata& get_instance(std::vector<std::string> lista);
	static void remove_instance();

	static bool search_for_town(std::string oras);

	void meniu();

	void inregistreaza_persoana();
	void inregistreaza_utilizator();
	void inregistreaza_administrator();

	void meniu_persoana();
	void meniu_utilizator();
	void meniu_administrator();
};

