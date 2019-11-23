#include <fstream>
#include <iostream>
#include <iomanip>
#include <string> // string z biblioteki STL
using namespace std;
#include "ListTemplate.h" // szablon kontenera listy uporz¹dkowanej clist (w³asna
implementacja)
int main(int argc, char* argv[])
{
clist<string, string> v;
clist_iterator<string, string> it(v);
string key, value;
ifstream* inFile = new ifstream; // plik tekstowy o formacie: klucz, wartoœæ
\n
inFile->open("test2.txt");
while (!inFile->bad() && !inFile->eof())
{
getline(*inFile, key, ','); // klucz,
if (inFile->eof()) break;
getline(*inFile, value, '\n'); // wartoœæ \n
v.insert(key, value);
};
inFile->close();
delete inFile; inFile = NULL;
// wyprowadzenie danych uporz¹dkowanych
ofstream* oFile = new ofstream; // plik tekstowy o formacie: klucz, wartoœæ \n
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
// deklaracja nazwy kontenera i iteratora pozwala siê do nich odwo³aæ
template<class K, class V> class clist;
template<class K, class V> class clist_iterator;

// klasa wezel: listy dwukierunkowej
template<class K, class V>
class node
{
friend class clist<K, V>; // klasa kontenera i klasa iteratora
friend class clist_iterator<K, V>; // ma dostêp do sk³adowych
private:
K key;
V value; // klucz, wartoœæ
node *prev; // poprzedni
node *next; // nastêpny
node(K &k, V &v) : key(k), value(v) // konstruktor
{
prev = next = 0;
}
~node() // destruktor
{
delete next;
};
// UWAGA!
// zanim usuniesz wezel listy usun wskazanie na nastêpny element bo skasuje ca³a listê
// next=0;
};
// klasa kontener: lista dwukierunkowa uporzadkowana (implementacja bez tzw. stra¿nika)
template<class K, class V>
class clist
{
friend class clist_iterator<K, V>; // iterator ma dostêp do sk³adowych prywatnych
node<K, V> *head; // g³owa listy
int size; // liczba wêz³ów
void removenode(node<K, V>* n); // usuñ wêze³
node<K, V>* search(K &k); // znajdŸ wêze³ o kluczu == v
public:
clist() { head = 0; size = 0; }; // konstruktor
~clist() { delete head; }; // destruktor
void clean() { ~clist(); clist(); }; // reinicjalizacja listy
int insert(K &k, V &v); // wstaw wêze³
int remove(K &k); // usuñ wêze³ (zwraca status)
int getsize() { return size; }; // podaj liczbê elementów
};
// klasa iterator: klasa zaprzyjazniona klasy clist
template<class K, class V>
class clist_iterator
{
friend class clist<K, V>; // kontener ma dostêp do iteratora
clist<K, V>* cur_list; // lista obs³ugiwana przez iterator

node<K, V>* cur_node; // bie¿¹cy wêze³
public:
clist_iterator(clist<K, V>& list); // zainicjuj iterator
 // znajdŸ element w kontenerze: 1 - OK, 0 - nie
ma elementu
int first(); // najmniejszy
int last(); // najwiêkszy
int next(); // nastêpny
int prev(); // poprzedni (wg kolejnoœci kluczy)
int find(K &k); // klucz równy k
// zwraca wskaŸnik do elementów
int current(K& key, V& value); // daj klucz i wartoœæ
};
// klasa lista uporzadkowana
// implementacja
template<class K, class V>
int clist<K, V>::insert(K &k, V &v)
{ // wstawiany wêze³ jest g³ow¹ listy
if (head == 0)
{
head = new node<K, V>(k, v);
size++;
return 1;
}
// szukaj elementu wiekszego - tam wstawisz wêze³
node<K, V>** p = &head;
node<K, V>* n = NULL;
do
{
if (k>(*p)->key) // jeœli k > od key bie¿¹cego wêz³a => idŸ dalej
{
if ((*p)->next != 0)
{
p = &((*p)->next);
}
else // dostaw na koñcu listy
{
n = new node<K, V>(k, v);
(*p)->next = n;
n->prev = *p;
n->next = 0;
break;
}
}
else // jeœli k < od key bie¿¹cego, wstaw nowy wêze³ przed
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
// przeszukiwanie liniowe (dla listy uporz¹dkowanej powinno byæ przeszukiwanie binarne)
template<class K, class V>
node<K, V>* clist<K, V>::search(K& k)
{
node<K, V>* n = head; // szukanie zacznij od g³owy listy
while (n)
{ // porównaj klucz z kluczem w bie¿¹cym wêŸle
if (k == n->key) return n; // jeœli znalaz³eœ klucz - sukces
else n = n->next; // wiêksze klucze le¿¹ dalej
};
return 0;
}
template<class K, class V>
void clist<K, V>::removenode(node<K, V> *n)
{
node<K, V> **pn; // na usuwany wezel wskazuje
if (n == head)
pn = &head; // wskaznik na g³owê listy
else
pn = &(n->prev->next); // wskaznik na nastêpny
// ³acz wêz³y
*pn = n->next;
n->next->prev = n->prev;
// kasuj wêze³ bez nastêpnych (uwaga na rekurencyjny destruktor)
n->next = n->prev = 0; // wezel juz nie ma nastêpnego
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
if (cur_node->next) // wezel ma nastêpny
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

