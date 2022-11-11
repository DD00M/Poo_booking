#pragma once
#include "unitate_cazare_i.h"

#include <iostream>
#include <vector>

class rezervare;
class data_zilei;

class unitate_cazare :
    public unitate_cazare_i
{
protected:
    std::string m_denumire;
    std::string m_oras;
    std::vector<std::pair<std::string, float>>m_lista_mese;
    std::vector<std::pair<std::string, std::string>>m_lista_recenzii;
    std::vector<int>m_lista_note;
    //nr camere x tip camera;
    std::vector<std::pair<int, int>>m_lista_camere;
    //camera = pret
    std::vector<std::pair<int, float>>m_lista_preturi;
    std::vector<data_zilei*>m_lista_date_rezervari;
    std::vector<rezervare*>m_lista_rezervari;
    int m_pret_camera;
    int m_clasificare;
    int m_spatii_cazare;
    int nr_total_camere;
    int m_spatii_ocupate;
    int m_numar_rezervari_aplicate;
    float m_grad_ocupare;
    float m_medie_note;
public:
    unitate_cazare();
    unitate_cazare(std::string nume, std::string oras, int clasificare, std::vector<std::string>lista_camere, std::vector<std::string>mese, std::vector<std::string> pret);
    unitate_cazare(const unitate_cazare& src);
    virtual ~unitate_cazare();

    rezervare* get_rezervare_by_index(int index);

    const std::string& get_nume() const;
    const std::string& get_oras() const;

    int get_size_vector_rezervari() const;
    int get_type(int index) const;
    int get_size_of_vector_camere() const;
    int get_size_of_vector_preturi() const;
    int get_nr_total_camere() const;
    int get_top_cazare() const;
    const int get_size_vector_mese();

    float get_grad_ocupare() const;
    float get_price_by_meal(std::string) const;

    std::pair<int, float> get_pret_by_camera(int type) const;
    std::pair<int, int> get_type_of_room(int index) const;

    bool is_meal(std::string);

    std::string set_number_of_rooms_by_type(int type, int nr_room);
    std::string get_dish_by_index(int index) const;

    void adauga_recenzie(std::string, std::string, int nota);
    void adauga_rezervare(rezervare*);
    void ocupa_spatii(int spatii);
    void add_again(int type, int nr_room);
    void ocupa_spatii_grad_ocupare(int spatii);
    void delete_rezervare(int index);

    void set_grad_ocupare(float grad);
    void ocupa_zile(std::vector<data_zilei*>data);

    std::vector<data_zilei*>get_arr_zile();
};

