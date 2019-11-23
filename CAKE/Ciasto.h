#pragma once
#include <iostream>
#include <string>
#ifndef CIASTO_H
#define CIASTO_H


using namespace std;

class Ciasto
{
    protected:
        float waga;
        string ksztalt;

    public:
        static int ile_obiektow;

        Ciasto();
        Ciasto(float waga_, string ksztalt_);
        Ciasto(Ciasto &cia);

        virtual ~Ciasto();

        virtual float getWaga();
        virtual void setWaga(float wag);
        virtual void wyswietl();

        static int liczba_obiektow();

        Ciasto& operator++ (int);
        Ciasto& operator-- ();

        friend void jesc(class Ciasto*);

};

#endif // CIASTO_H
