#include "calendar.h"

#include <iostream>
#include <vector>

calendar* calendar::instance = nullptr;

calendar::calendar(int year)
{
	this->year = year;
}

calendar::~calendar()
{
}

calendar& calendar::get_instance(int year)
{
	if (calendar::instance == nullptr) {
		calendar::instance = new calendar(year);
	}
	return *calendar::instance;
}

void calendar::remove_intance()
{
	if (calendar::instance != nullptr) {
		delete calendar::instance;
		calendar::instance = nullptr;
	}
}

int calendar::zi(int zi, int luna)
{

	static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1,
					   4, 6, 2, 4 };
	this->year -= luna < 3;
	return (year + year / 4 - year / 100 +
		year / 400 + t[luna - 1] + zi) % 7;
}

std::string get_luna(int nr)
{
	std::vector<std::string> months = { "IANUARIE", "FEBRUARIE", "MARTIE", "APRILIE", "MAI", "IUNIE","IULIE", "AUGUST", "SEPTEMBRIE", "OCTOMBRIE", "NOIEMBRIE", "DECEMBRIE" };
	return (months[nr]);
}

int calendar::nr_zile(int luna) {
    {
        if (luna == 0)
            return (31);
        else if (luna == 1)
        {
            if (this->year % 400 == 0 ||
                (this->year % 4 == 0 && this->year % 100 != 0))
                return (29);
            else
                return (28);
        }
        else if (luna == 2)
            return (31);
        else if (luna == 3)
            return (30);
        else if (luna == 4)
            return (31);
        else if (luna == 5)
            return (30);
        else if (luna == 6)
            return (31);
        else if (luna == 7)
            return (31);
        else if (luna == 8)
            return (30);
        else if (luna == 9)
            return (31);
        else if (luna == 10)
            return (30);
        else if (luna == 11)
            return (31);
    }
    return -1;
}

void calendar::print()
{
    std::cout << "                \t\t\t\tCalendar: " << this->year << std::endl;
    int days;
    int current = zi(1, 1) - 1;

    for (int i = 0; i < 12; i++)
    {
        days = nr_zile(i);
        std::cout << "\n    \t\t\t\t------------" << get_luna(i).c_str() << "------------- \n";

        printf("\t\t\t\t  Dum  Lun  Mar  Mie  Joi  Vin  Sam\n");

        int k;
        std::cout << "\t\t\t\t";
        for (k = 0; k < current; k++) {
            std::cout << "     ";
        }

        for (int j = 1; j <= days; j++)
        {
            printf("%5d", j);

            if (++k > 6)
            {
                k = 0;
                printf("\n\t\t\t\t");
            }
        }

        if (k)
            printf("\n");

        current = k;
    }
}
