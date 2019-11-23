#include "Ciasto_czek.h"
#include <iostream>
#include <fstream>

using namespace std;

int Ciasto_czek::ile_obiektow=0;

Ciasto_czek::Ciasto_czek():Ciasto()
{
    waga = 0;
    ksztalt = "";
    czekolada = "";
    ilosc_tabliczek = 0;
    ++ile_obiektow;
}

Ciasto_czek::Ciasto_czek(float waga_, string ksztalt_, string czeko, int il_tab) :
    Ciasto(waga_, ksztalt_)
{
    waga = waga_;
    ksztalt = ksztalt_;
    czekolada = czeko;
    ilosc_tabliczek = il_tab;
    ++ile_obiektow;
    cout<<"Jestem w konstruktorze ciasta czekoladowego."<<endl;
}

Ciasto_czek::Ciasto_czek(Ciasto_czek & cczek):Ciasto(cczek)
{
    waga = cczek.waga;
    ksztalt = cczek.ksztalt;
    czekolada = cczek.czekolada;
    ilosc_tabliczek = cczek.ilosc_tabliczek;
}

void Ciasto_czek::info()
{
    cout<<"Do ciasta u¿yta zostala nastepujaca czekolada: "<< czekolada<< " w ilosci "<< ilosc_tabliczek<< endl;
}

void Ciasto_czek::setCzekolada(string czeko)
{
    czekolada = czeko;
}

void Ciasto_czek::wez_tabliczke()
{
    ilosc_tabliczek+=1;
    cout<<"Teraz uzyto "<< ilosc_tabliczek<<" tabliczek czekolady do ciasta "<<endl;
}

bool Ciasto_czek::operator == (const Ciasto_czek &c)
{
	if (c.waga == waga && c.ksztalt == ksztalt && c.czekolada == czekolada && c.ilosc_tabliczek == ilosc_tabliczek)
		return true;
	else
		return false;
}

ostream& operator << (ostream &os, Ciasto_czek &cc){
	os << cc.waga << cc.ksztalt<<cc.czekolada<<cc.ilosc_tabliczek;
	return os;
}

istream& operator >> (istream &in, Ciasto_czek &cc){
	in >> cc.waga >> cc.ksztalt >> cc.czekolada >> cc.ilosc_tabliczek;
	return in;
}
