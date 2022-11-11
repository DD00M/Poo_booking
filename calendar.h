#pragma once

//M-am inspirat in creearea acestui calendar de pe site-ul : https://www.geeksforgeeks.org/print-calendar-for-a-given-year/ care era gresit, l-am corectat eu

//enum class zile {
//	luni,
//	marti,
//	miercuri,
//	joi,
//	vineri,
//	sambata,
//	duminica
//};
//
//enum class luna {
//	ianuarie,
//	februarie,
//	martie,
//	aprilie,
//	mai,
//	iunie,
//	iulie,
//	august,
//	septembrie,
//	octombrie,
//	noiembrie,
//	decembrie
//};

class calendar
{
private:
	static calendar* instance;

	int year;

	calendar(int year);
	~calendar();
public:
	static calendar& get_instance(int year);
	static void remove_intance();

	void print();
	int zi(int zi, int luna);
	int nr_zile(int luna);
};

