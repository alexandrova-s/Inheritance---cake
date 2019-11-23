#pragma once
#pragma once
#include <iostream>
#include <string>
#ifndef SZARLOTKA_H
#define SZARLOTKA_H
#include "Ciasto.h"

using namespace std;

class Szarlotka : public Ciasto
{
        string typ_jablek;
        int ilosc_jablek;

    public:
        Szarlotka (float waga_, string ksztalt_, string t_jablek, int il_jablek);

        void info();

        void setJablka(string t_jablek);
        void wiecej_jablek();
};


#endif // CIASTO_CZEK_H
