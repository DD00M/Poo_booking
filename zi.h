#pragma once

#include <iostream>

enum class zile {
	luni,
	marti,
	miercuri,
	joi,
	vineri,
	sambata,
	duminica
};

class zi
{
private:
	static zi* instance;
	static zile m_zi;

	zi();
	zi(const zi& src);
	~zi();
public:
	static zi& get_instance();
	static void remove_instance();
	static std::string get_zi();
	void set_day(std::string zi);
	void set_to_luni();
	void set_to_marti();
	void set_to_miercuri();
	void set_to_joi();
	void set_to_vineri();
	void set_to_sambata();
	void set_to_duminica();
};

