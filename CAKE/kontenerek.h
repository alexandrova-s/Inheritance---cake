#include <iostream>
#include <iomanip>
#include "Ciasto.h"
#include "Ciasto_czek.h"
#include "Szarlotka.h"

using namespace std;

// Element listy
//--------------
template <class T>
struct dlistEl
{
  dlistEl<T> * next;   // nastêpnik
  dlistEl<T> * prev;   // poprzednik
  T data;
};

// Definicja obiektu listy dwukierunkowej
//---------------------------------------
template <class T>
class dlist
{
  public:
    dlistEl<T> * head;  // pocz¹tek listy
    dlistEl<T> * tail;  // koniec listy
    unsigned count;  // licznik elementów

    dlist();         // konstruktor
    ~dlist();        // destruktor
    void printl();
    void push_front(const T &data);
    void push_back(const T &data);
    void insert_before(dlistEl<T> * e, const T &data);
    void insert_after(dlistEl<T> * e, const T &data);
    void remove(dlistEl<T> * e);
    void pop_front();
    void pop_back();
    friend ostream& operator<<(ostream& os, const T& d);
};

//------------------------------------
// Metody obiektu listy dwukierunkowej
//------------------------------------

// Inicjuje pola zmiennej listy
//-----------------------------
template <class T>
dlist<T>::dlist()
{
  head  = tail  = NULL;
  count = 0;
}

// Usuwa listê z pamiêci
//----------------------
template <class T>
dlist<T>::~dlist()
{
  while(count) pop_front();
}

// Wyœwietla zawartoœæ elementów listy
//----------------------------------------------
template <class T>
void dlist<T>::printl()
{
  dlistEl<T> * p;

  cout << setw(3) << count << " : [";
  p = head;
  while(p)
  {
//    cout << p->data;
    p = p->next;
  }
  cout << " ]\n\n";
}

// Dodaje nowy element na pocz¹tek listy
//------------------------------------------------
template <class T>
void dlist<T>::push_front(const T &data)
{
  dlistEl<T> * p;

  p = new dlistEl<T>;
  p->data = data;
  p->prev = NULL;
  p->next = head;
  head  = p;
  count++;
  if(p->next) p->next->prev = p;
  else tail = p;
}

// Dodaje nowy element na koniec listy
//----------------------------------------------
template <class T>
void dlist<T>::push_back(const T &data)
{
  dlistEl<T> * p;

  p = new dlistEl<T>;
  p->data = data;
  p->next = NULL;
  p->prev = tail;
  tail  = p;
  count++;
  if(p->prev) p->prev->next = p;
  else head = p;
}

// Dodaje nowy element przed wybranym
//-----------------------------------
template <class T>
void dlist<T>::insert_before(dlistEl<T> * e, const T &data)
{
  dlistEl<T> * p;

  if(e == head) push_front(data);
  else
  {
    p = new dlistEl<T>;
    p->data = data;
    p->next = e;
    p->prev = e->prev;
    count++;
    e->prev->next = p;
    e->prev = p;
  }
}

// Dodaje nowy element za wybranym
//--------------------------------
template <class T>
void dlist<T>::insert_after(dlistEl<T> * e, const T &data)
{
  dlistEl<T> * p;

  if(e == tail) push_back(data);
  else
  {
    p = new dlistEl<T>;
    p->data = data;
    p->next = e->next;
    p->prev = e;
    count++;
    e->next->prev = p;
    e->next = p;
  }
}

// Usuwa wybrany element z listy
//------------------------------
template <class T>
void dlist<T>::remove(dlistEl<T> * e)
{
  count--;
  if(e->prev) e->prev->next = e->next;
  else        head = e->next;
  if(e->next) e->next->prev = e->prev;
  else        tail = e->prev;
  delete e;
}

// Usuwa element z pocz¹tku listy
//-------------------------------
template <class T>
void dlist<T>::pop_front()
{
  if(count) remove(head);
}

// Usuwa element z koñca listy
//----------------------------
template <class T>
void dlist<T>::pop_back()
{
  if(count) remove(tail);
}
