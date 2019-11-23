#include "Szarlotka.h"
#include <iostream>

using namespace std;

Szarlotka::Szarlotka(float waga_, string ksztalt_, string t_jablek, int il_jablek): Ciasto(waga_, ksztalt_)
{
    waga = waga_;
    ksztalt = ksztalt_;
    typ_jablek = t_jablek;
    ilosc_jablek = il_jablek;
    cout<<"Jestem w konstruktorze szarlotki."<<endl;
}

void Szarlotka::info()
{
    cout<<"Do ciasta u¿yte zostaly jablka typu: "<< typ_jablek<< " w ilosci "<< ilosc_jablek<< endl;
}

void Szarlotka::setJablka(string t_jablek)
{
    typ_jablek = t_jablek;
}

void Szarlotka::wiecej_jablek()
{
    ilosc_jablek+=2;
    cout<<"Teraz do zrobienia szarlotki uzyto "<< ilosc_jablek<< " jablek"<< endl;
}
