#include <fstream>
#include <iostream>
#include <iomanip>
#include <string> // string z biblioteki STL
using namespace std;
#include "ListTemplate.h" // szablon kontenera listy uporz�dkowanej clist (w�asna
implementacja)
int main(int argc, char* argv[])
{
clist<string, string> v;
clist_iterator<string, string> it(v);
string key, value;
ifstream* inFile = new ifstream; // plik tekstowy o formacie: klucz, warto��
\n
inFile->open("test2.txt");
while (!inFile->bad() && !inFile->eof())
{
getline(*inFile, key, ','); // klucz,
if (inFile->eof()) break;
getline(*inFile, value, '\n'); // warto�� \n
v.insert(key, value);
};
inFile->close();
delete inFile; inFile = NULL;
// wyprowadzenie danych uporz�dkowanych
ofstream* oFile = new ofstream; // plik tekstowy o formacie: klucz, warto�� \n
oFile->open("out2.txt");
if (it.first())
{
do
{
it.current(key, value);
*oFile << "\n" << setw(40) << setiosflags(ios_base::left) << key << " --- " <<
value;
} while (it.next());
}
*oFile << endl;
oFile->close();
delete oFile; oFile = NULL;
cout << "by" << endl;
return 0;
}
// List.h
#include <iostream>
using namespace std;
// deklaracja nazwy kontenera i iteratora pozwala si� do nich odwo�a�
template<class K, class V> class clist;
template<class K, class V> class clist_iterator;

// klasa wezel: listy dwukierunkowej
template<class K, class V>
class node
{
friend class clist<K, V>; // klasa kontenera i klasa iteratora
friend class clist_iterator<K, V>; // ma dost�p do sk�adowych
private:
K key;
V value; // klucz, warto��
node *prev; // poprzedni
node *next; // nast�pny
node(K &k, V &v) : key(k), value(v) // konstruktor
{
prev = next = 0;
}
~node() // destruktor
{
delete next;
};
// UWAGA!
// zanim usuniesz wezel listy usun wskazanie na nast�pny element bo skasuje ca�a list�
// next=0;
};
// klasa kontener: lista dwukierunkowa uporzadkowana (implementacja bez tzw. stra�nika)
template<class K, class V>
class clist
{
friend class clist_iterator<K, V>; // iterator ma dost�p do sk�adowych prywatnych
node<K, V> *head; // g�owa listy
int size; // liczba w�z��w
void removenode(node<K, V>* n); // usu� w�ze�
node<K, V>* search(K &k); // znajd� w�ze� o kluczu == v
public:
clist() { head = 0; size = 0; }; // konstruktor
~clist() { delete head; }; // destruktor
void clean() { ~clist(); clist(); }; // reinicjalizacja listy
int insert(K &k, V &v); // wstaw w�ze�
int remove(K &k); // usu� w�ze� (zwraca status)
int getsize() { return size; }; // podaj liczb� element�w
};
// klasa iterator: klasa zaprzyjazniona klasy clist
template<class K, class V>
class clist_iterator
{
friend class clist<K, V>; // kontener ma dost�p do iteratora
clist<K, V>* cur_list; // lista obs�ugiwana przez iterator

node<K, V>* cur_node; // bie��cy w�ze�
public:
clist_iterator(clist<K, V>& list); // zainicjuj iterator
 // znajd� element w kontenerze: 1 - OK, 0 - nie
ma elementu
int first(); // najmniejszy
int last(); // najwi�kszy
int next(); // nast�pny
int prev(); // poprzedni (wg kolejno�ci kluczy)
int find(K &k); // klucz r�wny k
// zwraca wska�nik do element�w
int current(K& key, V& value); // daj klucz i warto��
};
// klasa lista uporzadkowana
// implementacja
template<class K, class V>
int clist<K, V>::insert(K &k, V &v)
{ // wstawiany w�ze� jest g�ow� listy
if (head == 0)
{
head = new node<K, V>(k, v);
size++;
return 1;
}
// szukaj elementu wiekszego - tam wstawisz w�ze�
node<K, V>** p = &head;
node<K, V>* n = NULL;
do
{
if (k>(*p)->key) // je�li k > od key bie��cego w�z�a => id� dalej
{
if ((*p)->next != 0)
{
p = &((*p)->next);
}
else // dostaw na ko�cu listy
{
n = new node<K, V>(k, v);
(*p)->next = n;
n->prev = *p;
n->next = 0;
break;
}
}
else // je�li k < od key bie��cego, wstaw nowy w�ze� przed
{
n = new node<K, V>(k, v);
n->next = *p;
n->prev = (*p)->prev;
(*p)->prev = n;
(*p) = n;
break;
}
} while (1);
// rozmiar kontenera
size++;

return 1;
}
template<class K, class V>
int clist<K, V>::remove(K& k)
{
node<K, V>* n;
// znajdz
n = search(k);
if (n) { removenode(n); return 1; }
else return 0;
}
// przeszukiwanie liniowe (dla listy uporz�dkowanej powinno by� przeszukiwanie binarne)
template<class K, class V>
node<K, V>* clist<K, V>::search(K& k)
{
node<K, V>* n = head; // szukanie zacznij od g�owy listy
while (n)
{ // por�wnaj klucz z kluczem w bie��cym w�le
if (k == n->key) return n; // je�li znalaz�e� klucz - sukces
else n = n->next; // wi�ksze klucze le�� dalej
};
return 0;
}
template<class K, class V>
void clist<K, V>::removenode(node<K, V> *n)
{
node<K, V> **pn; // na usuwany wezel wskazuje
if (n == head)
pn = &head; // wskaznik na g�ow� listy
else
pn = &(n->prev->next); // wskaznik na nast�pny
// �acz w�z�y
*pn = n->next;
n->next->prev = n->prev;
// kasuj w�ze� bez nast�pnych (uwaga na rekurencyjny destruktor)
n->next = n->prev = 0; // wezel juz nie ma nast�pnego
delete n; // kasuj
size--; // rozmiar kontenera
}
// ITERATOR
// klasa iterator: klasa zaprzyjazniona klasy clist
// implementacja
template<class K, class V>
int clist_iterator<K, V>::find(K& k)
{
node<K, V>* c = cur_list->search(k);
if (c) { cur_node = c; return 1; }
else return 0;
}
template<class K, class V>
clist_iterator<K, V>::clist_iterator(clist<K, V>& list)
{
    cur_list = &list;
first();
}
template<class K, class V>
int clist_iterator<K, V>::first()
{
cur_node = cur_list->head;
if (cur_node == 0) return 0;
return 1;
}
template<class K, class V>
int clist_iterator<K, V>::next()
{
if (cur_node->next) // wezel ma nast�pny
{
cur_node = cur_node->next;
return 1;
}
else return 0;
}
template<class K, class V>
int clist_iterator<K, V>::last()
{
node<K, V>* n = this->cur_list->head;
if (n == 0) return 0;
while (n->next) n = n->next;
cur_node = n; // ustaw na ostatni element
return 1;
}
template<class K, class V>
int clist_iterator<K, V>::prev()
{
if (cur_node->prev)
{
cur_node = cur_node->prev;
return 1;
}
else return 0;
}
template<class K, class V>
int clist_iterator<K, V>::current(K& key, V& value)
{
if (cur_node)
{
key = cur_node->key;
value = cur_node->value;
return 1;
}
else return 0;
}

