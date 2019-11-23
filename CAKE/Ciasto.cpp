#pragma once
#include "Ciasto.h"
#include <iostream>

using namespace std;

int Ciasto::ile_obiektow=0;

Ciasto::Ciasto()
{
    waga = 0;
    ksztalt = "";
}

Ciasto::Ciasto(float waga_, string ksztalt_)
{
    waga = waga_;
    ksztalt = ksztalt_;
    ile_obiektow++;
    cout<<"Jestem w konstruktorze ciasta."<<endl;
}

Ciasto::Ciasto(Ciasto &cia)
{
    waga=cia.waga;
    ksztalt=cia.ksztalt;
}

Ciasto::~Ciasto()
{
    ile_obiektow--;
    cout<<"Jestem w destruktorze ciasta."<<endl;
}

float Ciasto::getWaga()
{
    return waga;
}

void Ciasto::setWaga(float wag)
{
    if (wag < 0) waga = 0;
    else waga = wag;
}

void Ciasto::wyswietl()
{
    cout<<"Aktualna liczba ciast to: "<< ile_obiektow<<endl<< "Waga ciasta wynosi: " << waga<< endl<< "Ksztalt ciasta to: " << ksztalt<< endl;
}

int Ciasto::liczba_obiektow()
{
    return ile_obiektow;
    cout<< ile_obiektow;
}

Ciasto& Ciasto::operator++ (int)
{
    setWaga(waga+0.5);
    return *this;
}

Ciasto& Ciasto::operator-- ()
{
    setWaga(waga-0.5);
    return *this;
}


void jesc(class Ciasto *c1)
{
    c1->ile_obiektow--;
    cout<<"Zjedzono ciasto";
}

