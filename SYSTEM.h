#pragma once

#include <iostream>
#include <vector>

class utilizator;
class administrator;
class unitate_cazare;
class data_zilei;
class rezervare;

class SYSTEM
{
private:
	std::string m_nume;
	static SYSTEM* instance;

	static std::vector<utilizator*>m_lista_utilizatori;
	static std::vector<administrator*>m_lista_administratori;
	static std::vector<std::pair<unitate_cazare*, std::string>>m_lista_unitati_cazare;

	SYSTEM(std::string nume);
	SYSTEM(const SYSTEM& src);
	~SYSTEM();
public:
	static SYSTEM& get_instance(std::string nume);
	static void remove_instance();

	static void add_utilizator(utilizator*);
	static void add_administrator(administrator*);
	
	static unitate_cazare* get_cazare(std::string oras, std::string nume);
	static unitate_cazare* get_cazare_by_index_from_admin(std::string nume, int index);
	
	static utilizator* get_utilizator(std::string nume);
	
	static administrator* get_administrator(std::string nume);

	static float get_wallet_admin(std::string admin);

	static bool check_existanta_cazare(std::string oras, std::string nume);
	static bool print_cazari_by_town(std::string oras);
	static bool is_cazare_in_system(std::string nume, std::string oras);
	static bool check_password_administrator(std::string nume, std::string parola);
	static bool check_password_utilizator(std::string nume, std::string parola);
	static bool is_nume_administrator(std::string nume);
	static bool is_nume_utilizator(std::string nume);
	static bool check_if_exist_REZERVARI(std::string nume, std::string oras);
	static bool check_if_exist_nr_room(std::string nume, std::string oras, int camera);
	static bool check_if_there_are_enough_rooms(std::string nume, std::string oras, int nr);
	static bool check_if_exist_data(std::string nume, std::string oras, std::string data, std::string nume_zi);
	static bool check_if_exist_dish(std::string nume, std::string oras, std::string dish);

	static int get_number_of_rooms_by_number_of_seats(std::string type);
	static int get_size_unitate_cazare_rezervari(std::string nume, std::string oras);
	static int get_size_administrator_unitati_cazare(std::string nume);

	static rezervare* get_rezervare_by_index(std::string nume, std::string oras, int index);

	static std::string set_rooms_by_type(int type, int how_may_rooms, std::string nume, std::string oras);

	static int get_nr_total_camere_per_cazare(std::string nume, std::string oras);

	static void add_unitate(std::string oras, unitate_cazare* u_c);
	static void fix_rooms_by_type(int type, int how_may_rooms, std::string nume, std::string oras);
	static void plateste(std::string utilizator, administrator* admin);
	static void set_user_wallet(std::string user, float suma);
	static void set_user_appointment(std::string user, std::string type, std::string rezervare);
	static void modifica_in_cazare_recenzie(std::string oras, std::string nume, std::string nume_utilizator, std::string recenzie, int nota);
	static void add_nr_camere_ocupate(std::string nume, std::string oras, int nr_camere);
	static void set_grad_ocupare(std::string nume, std::string oras, float grad);
	static void occupy_days(std::string nume, std::string oras, std::vector<data_zilei*>lista);
	static void sterge_rezervare_from_cazare(std::string nume, std::string oras, rezervare* r);
	static void sterge_cazare_from_administrator(std::string nume, std::string cazare, std::string oras);
	static void get_discount_utilizator(std::string nume);
};

