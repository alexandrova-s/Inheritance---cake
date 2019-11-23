#include <iostream>
#include "Ciasto_czek.h"
#include "kkontener.h"
#include "kkontener.cpp"
#include "Szarlotka.h"

using namespace std;

int main()
{
    Ciasto_czek ccz1(3.20, "Okrag", "Wedel", 3);
    ccz1.wyswietl();
    ccz1.info();

    Szarlotka sz1(2.90, "Prostokat", "Champion", 5);
    sz1.wyswietl();
    sz1.info();

    cout<<endl;

    cout<<"Dodaje czekolady do ciasta czekoladowego i jablka do szarlotki."<< endl;
    ccz1.wez_tabliczke();
    ccz1.setCzekolada("Wawel");
    sz1.wiecej_jablek();
    sz1.setJablka("Lobo");
    ccz1.setWaga(3.35);
    sz1.setWaga(3.74);
    cout<<endl;
    ccz1.wyswietl();
    ccz1.info();
    sz1.wyswietl();
    sz1.info();

    cout<<endl;

    ccz1++;
    --sz1;

    ccz1.wyswietl();
    sz1.wyswietl();

    jesc(&ccz1);
    cout<<" czekoladowe. \nZostal kawalek szarlotki:"<< endl;
    --sz1;
    --sz1;
    --sz1;
    sz1.wyswietl();


    cout<<" \n \n \n KONTENER \n \n \n";


    Kontener<Ciasto_czek> Kon;

    Ciasto_czek c1(3.20, "Kolo", "Wedel", 3);
    Ciasto_czek c2(3.50, "Kwadrat", "Wawel", 4);
    Ciasto_czek c3(3.60, "Trojkat", "Milka", 7);
    Ciasto_czek c4(3.80, "Prostokat", "Choco", 9);

    Kon.dodajElement(c1);
    Kon.dodajElement(c2);
    Kon.dodajElement(c3);
    Kon.wyswietlWszystkieObiekty();

    Kon.zmienKolejnosc(1, 2);
    Kon.wyswietlWszystkieObiekty();

    Kon.usunOstatni();
    Kon.wyswietlWszystkieObiekty();

    Kon.dodajElement(c4);
    Kon.dodajElement(c2);

    return 0;

}
