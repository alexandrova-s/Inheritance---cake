#pragma once
#include "Ciasto_czek.h"
#include "kkontener.h"
#include <iostream>
#include <fstream>

template <class TYP>
Kontener<TYP>::Kontener(){
	liczba_elementow = 0;
	poczatek = NULL;
}

template <class TYP>
Kontener<TYP>::~Kontener(){
	while (liczba_elementow > 0)
		usunOstatni();
}

template <class TYP>
Wezel<TYP>* Kontener<TYP>::zwrocWskaznikWezla(int indeks){
	Wezel<TYP> *wezel = poczatek;

	for (int i = 0; i < indeks; i++) {
		if (wezel == NULL)
			return NULL;
		wezel = wezel->nastepny_wezel;
	}
	return wezel;
}

template <class TYP>
void Kontener<TYP>::dodajElement(const TYP &ob){
	if (indexOf(ob) == -1){ //sprawdzanie czy obiekt znajduje sie w kontenerze
		Wezel<TYP> *nowy_wezel, *pop_wezel;
		nowy_wezel = new Wezel<TYP>();

		nowy_wezel->poprzedni_wezel = NULL;
		nowy_wezel->nastepny_wezel = NULL;
		nowy_wezel->ob = ob;

		if (liczba_elementow == 0){
			poczatek = nowy_wezel;
		}
		else {
			Wezel<TYP> *tmp;
			tmp = zwrocWskaznikWezla(liczba_elementow - 1);
			tmp->nastepny_wezel = nowy_wezel;
			if (liczba_elementow > 1){
				pop_wezel = zwrocWskaznikWezla(liczba_elementow - 2);
				tmp->poprzedni_wezel = pop_wezel;
			}
		}

		liczba_elementow++;
	}
}

template <class TYP>
void Kontener<TYP>::usunOstatni(){
	if (liczba_elementow < 2){
		delete poczatek;
		poczatek = NULL;
	}
	else {
		Wezel<TYP> *tmp = zwrocWskaznikWezla(liczba_elementow - 2);
		delete tmp->nastepny_wezel;
	}

	liczba_elementow--;
}

template <class TYP>
void Kontener<TYP>::usunElement(int indeks){
	if (liczba_elementow == 1 || indeks == liczba_elementow - 1){
		usunOstatni();
		return;
	} else if(indeks == 0){
		Wezel<TYP> *tmp;
		tmp = new Wezel<TYP>();
		tmp = poczatek->nastepny_wezel;
		tmp->poprzedni_wezel = NULL;
		delete poczatek;
		poczatek = tmp;
	} else {
		Wezel<TYP> *wezel;
		wezel = zwrocWskaznikWezla(indeks);
		wezel->poprzedni_wezel->nastepny_wezel = wezel->nastepny_wezel;
		wezel->nastepny_wezel->poprzedni_wezel = wezel->poprzedni_wezel;
		delete wezel;
	}
	liczba_elementow--;
}

template <class TYP>
TYP& Kontener<TYP>::zwrocObiekt(int indeks){
	return zwrocWskaznikWezla(indeks)->ob;
}

template <class TYP>
void Kontener<TYP>::zmienKolejnosc(int a, int b){
	TYP ob_tmp;
	ob_tmp = (*this)[a];
	(*this)[a] = (*this)[b];
	(*this)[b] = ob_tmp;
}

template <class TYP>
void Kontener<TYP>::wyswietlWszystkieObiekty(){
	if (liczba_elementow != 0)
	for (int i = 0; i < liczba_elementow; i++){
		cout << "Obiekt nr " << indexOf((*this)[i]) << endl;
		(*this)[i].info();
	}
	else
		cout << "Brak obiektow." << endl;
}

template <class TYP>
int Kontener<TYP>::size(){
	return liczba_elementow;
}

template <class TYP>
int Kontener<TYP>::indexOf(const TYP &ob){
	int indeks = -1;
	for (int i = 0; i < liczba_elementow; i++)
		if ((*this)[i] == ob){
			indeks = i+1;
			break;
		}
	return indeks;
}

template <class TYP>
bool Kontener<TYP>::operator==(Kontener &k){
	for (int i = 0; i < k.liczba_elementow; i++)
		if (!(k[i] == (*this)[i]))
			return false;
	return true;
}

template <class TYP>
Kontener<TYP>& Kontener<TYP>::operator=(Kontener &k){
	for (int i = 0; i < k.liczba_elementow; i++)
		dodajElement(k[i]);
	return *this;
}

template <class TYP>
TYP& Kontener<TYP>::operator[](int i){
	if (i < 0 || i >= liczba_elementow)
		throw string("Nie istnieje taki obiekt.");
	return zwrocObiekt(i);
}
