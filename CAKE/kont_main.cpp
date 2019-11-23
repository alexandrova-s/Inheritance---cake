#include <iostream>
#include <iomanip>
#include "Ciasto.h"
#include "Ciasto_czek.h"
#include "Szarlotka.h"
#include "kontenerek.h"

using namespace std;

int main()
{
    dlist<Ciasto> L;
    Ciasto c1(3.20, "Kolo");
    Ciasto c2(3.50, "Kwadrat");
    Ciasto c3(3.60, "Trojkat");
    Ciasto c4(3.80, "Prostokat");

  L.printl();
  L.push_front(c1);
  L.printl();
  L.push_back(c2);
  L.printl();
  L.push_back(c3);
  L.insert_before(L.tail, c1);
  L.insert_after(L.head, c4);
  L.printl();
  L.printl();
  L.pop_front();
  L.printl();
  L.pop_back();
  L.printl();
  L.remove(L.head->next->next);
  L.printl();

  return 0;
}
