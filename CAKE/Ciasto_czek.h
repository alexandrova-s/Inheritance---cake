#include <iostream>
#include <string>
#ifndef CIASTO_CZEK_H
#define CIASTO_CZEK_H
#include "Ciasto.h"

using namespace std;

class Ciasto_czek : public Ciasto
{
        string czekolada;
        int ilosc_tabliczek;

    public:
        static int ile_obiektow;

        Ciasto_czek();
        Ciasto_czek(float waga_, string ksztalt_, string czeko, int il_tab);
        Ciasto_czek(Ciasto_czek & cczek);

        void info();

        void setCzekolada(string czeko);
        void wez_tabliczke();

        bool operator == (const Ciasto_czek &c);
        friend ostream& operator << (ostream &os, Ciasto_czek &cc);
        friend istream& operator >> (istream &in, Ciasto_czek &cc);


};

#endif // CIASTO_CZEK_H
