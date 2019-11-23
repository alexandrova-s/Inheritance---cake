#pragma once
#include "Ciasto_czek.h"
#include "Ciasto.h"

#include <iostream>

using namespace std;

template <class TYP>
struct Wezel {
	TYP ob;
	Wezel *poprzedni_wezel;
	Wezel *nastepny_wezel;
};

template <class TYP>
class Kontener
{
private:
	Wezel<TYP> *poczatek;
	int liczba_elementow;
public:
	Kontener();
	void dodajElement(const TYP &ob);
	void usunElement(int indeks);
	void usunOstatni();
	TYP& zwrocObiekt(int indeks);
	void zmienKolejnosc(int a, int b);
	void wyswietlWszystkieObiekty();
	Wezel<TYP>* zwrocWskaznikWezla(int indeks);
	int size();
	int indexOf(const TYP &);
	~Kontener();

	bool operator== (Kontener &);
	Kontener& operator= (Kontener &);
	TYP& operator[](int i);
};
#include"kkontener.cpp"
