#include <iostream>
#include <iomanip>
#include "Ciasto.h"
#include "Ciasto_czek.h"
#include "Szarlotka.h"

using namespace std;

// Element listy
//--------------
template <class T, class V>
struct dlistEl
{
  dlistEl * next;   // nastêpnik
  dlistEl * prev;   // poprzednik
  T t;
  V v;
};

// Definicja obiektu listy dwukierunkowej
//---------------------------------------
template <class T, class V>
class dlist
{
  public:
    dlistEl<T, V> * head;  // pocz¹tek listy
    dlistEl<T, V> * tail;  // koniec listy
    unsigned count;  // licznik elementów

    dlist();         // konstruktor
    ~dlist();        // destruktor
    void printl();
    void push_front(const T &t);
    void push_back(const T &t);
    void insert_before(dlistEl<T, V> * e, const T &t);
    void insert_after(dlistEl<T, V> * e, const T &t);
    void push_front(const V &v);
    void push_back(const V &v);
    void insert_before(dlistEl<T, V> * e, const V &v);
    void insert_after(dlistEl<T, V> * e, const V &v);
    void remove(dlistEl<T, V> * e);
    void pop_front();
    void pop_back();
    friend ostream& operator<<(ostream& os, const T& d);
};

//------------------------------------
// Metody obiektu listy dwukierunkowej
//------------------------------------

// Inicjuje pola zmiennej listy
//-----------------------------
template <class T, class V>
dlist<T, V>::dlist()
{
  head  = tail  = NULL;
  count = 0;
}

// Usuwa listê z pamiêci
//----------------------
template <class T, class V>
dlist<T, V>::~dlist()
{
  while(count) pop_front();
}

template <class T, class V>
ostream& operator<<(ostream& os, const T &d)
{
    os << " " << d.t;
    return os;
}
// Wyœwietla zawartoœæ elementów listy
//----------------------------------------------
template <class T, class V>
void dlist<T, V>::printl()
{
  dlistEl<T, V> * p;

  cout << setw(3) << count << " : [";
  p = head;
  while(p)
  {
    //cout << p->t;
    p = p->next;
  }
  cout << " ]\n\n";
}

// Dodaje nowy element na pocz¹tek listy
//------------------------------------------------
template <class T, class V>
void dlist<T, V>::push_front(const T &t)
{
  dlistEl<T, V> * p;

  p = new dlistEl<T, V>;
  p->t = t;
  p->prev = NULL;
  p->next = head;
  head  = p;
  count++;
  if(p->next) p->next->prev = p;
  else tail = p;
}

// Dodaje nowy element na koniec listy
//----------------------------------------------
template <class T, class V>
void dlist<T, V>::push_back(const T &t)
{
  dlistEl<T, V> * p;

  p = new dlistEl<T, V>;
  p->t = t;
  p->next = NULL;
  p->prev = tail;
  tail  = p;
  count++;
  if(p->prev) p->prev->next = p;
  else head = p;
}

// Dodaje nowy element przed wybranym
//-----------------------------------
template <class T, class V>
void dlist<T, V>::insert_before(dlistEl<T, V> * e, const T &t)
{
  dlistEl<T, V> * p;

  if(e == head) push_front(t);
  else
  {
    p = new dlistEl<T, V>;
    p->t = t;
    p->next = e;
    p->prev = e->prev;
    count++;
    e->prev->next = p;
    e->prev = p;
  }
}

// Dodaje nowy element za wybranym
//--------------------------------
template <class T, class V>
void dlist<T, V>::insert_after(dlistEl<T, V> * e, const T &t)
{
  dlistEl<T, V> * p;

  if(e == tail) push_back(t);
  else
  {
    p = new dlistEl<T, V>;
    p->t = t;
    p->next = e->next;
    p->prev = e;
    count++;
    e->next->prev = p;
    e->next = p;
  }
}

template <class T, class V>
void dlist<T, V>::push_front(const V& v)
{
  dlistEl<T, V> * p;

  p = new dlistEl<T, V>;
  p->v = v;
  p->prev = NULL;
  p->next = head;
  head  = p;
  count++;
  if(p->next) p->next->prev = p;
  else tail = p;
}

// Dodaje nowy element na koniec listy
//----------------------------------------------
template <class T, class V>
void dlist<T, V>::push_back(const V &v)
{
  dlistEl<T, V> * p;

  p = new dlistEl<T, V>;
  p->v = v;
  p->next = NULL;
  p->prev = tail;
  tail  = p;
  count++;
  if(p->prev) p->prev->next = p;
  else head = p;
}

// Dodaje nowy element przed wybranym
//-----------------------------------
template <class T, class V>
void dlist<T, V>::insert_before(dlistEl<T, V> * e, const V &v)
{
  dlistEl<T, V> * p;

  if(e == head) push_front(v);
  else
  {
    p = new dlistEl<T, V>;
    p->v = v;
    p->next = e;
    p->prev = e->prev;
    count++;
    e->prev->next = p;
    e->prev = p;
  }
}

// Dodaje nowy element za wybranym
//--------------------------------
template <class T, class V>
void dlist<T, V>::insert_after(dlistEl<T, V> * e, const V &v)
{
  dlistEl<T, V> * p;

  if(e == tail) push_back(v);
  else
  {
    p = new dlistEl<T, V>;
    p->v = v;
    p->next = e->next;
    p->prev = e;
    count++;
    e->next->prev = p;
    e->next = p;
  }
}
// Usuwa wybrany element z listy
//------------------------------
template <class T, class V>
void dlist<T, V>::remove(dlistEl<T, V> * e)
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
template <class T, class V>
void dlist<T, V>::pop_front()
{
  if(count) remove(head);
}

// Usuwa element z koñca listy
//----------------------------
template <class T, class V>
void dlist<T, V>::pop_back()
{
  if(count) remove(tail);
}

