#include "MD.h"
#include "IteratorMD.h"
#include <exception>
#include <iostream>

using namespace std;


int MD::dispersie(TCheie c) const
{
	//Complexitate: theta(1)
	return abs(c) % m;
}

MD::MD() {
	/* de adaugat */
	//Complexitate: theta(m)
	m = MAX;
	dimensiune = 0;
	for (int i = 0; i < m; ++i)
		lista[i] = nullptr;
}


void MD::adauga(TCheie c, TValoare v) {
	/* de adaugat */
	//Complexitate: theta(1)
	TElem e(c, v);
	int i = dispersie(c);
	PNod p = new Nod(e, nullptr);

	p->urm = lista[i];
	lista[i] = p;
	dimensiune++;
}


bool MD::sterge(TCheie c, TValoare v) {
	/* de adaugat */
	//Complexitate: presupunem dispersia uniforma: O(n/m)

	int i = dispersie(c); //stiu in ce lista e cheia cautata(daca e)
	PNod curent = lista[i];
	PNod anterior;
	TElem e = TElem(c, v);

	//o luam pe cazuri
	if (curent == nullptr)
		return false; // nu exista nimic in lista in care ar trebui sa existe elem cautat


	if (curent->urm == nullptr) // e doar un elem in lista
		if (curent->e == e) {
			delete curent;
			lista[i] = nullptr;
			dimensiune--;
			return true;
		}
		else
			return false;

	//in punctul asta avem certitudinea ca exista cel putin 2 elem in lista
	//il verificam pe primul separat
	if (curent->e == e)
	{
		lista[i] = curent->urm;
		delete curent;
		dimensiune--;
		return true;
	}

	//exista cel putin 2 elemente si cel cautat nu e primul

	anterior = curent;
	curent = curent->urm;

	while (curent != nullptr) {
		if (curent->e == e) {
			anterior->urm = curent->urm;
			delete curent;
			dimensiune--;
			return true;
		}
		anterior = curent;
		curent = curent->urm;
	}

	return false;
}


vector<TValoare> MD::cauta(TCheie c) const {
	/* de adaugat */
	//Complexitate(presup. dispersia uniforma): theta(n/m)
	int i = dispersie(c);

	vector<TValoare> v;

	PNod p = lista[i];
	while (p != nullptr) {
		if (p->e.first == c)
			v.push_back(p->e.second);
		p = p->urm;
	}

	return v;
}


int MD::dim() const {
	/* de adaugat */
	//Complexitate: theta(1)
	return dimensiune;
}


bool MD::vid() const {
	/* de adaugat */
	//Complexitate: theta(1)
	return dimensiune == 0;;
}

IteratorMD MD::iterator() const {
	//Complexitate:  O(m)
	return IteratorMD(*this);
}


MD::~MD() {
	/* de adaugat */
	//Complexitate: theta(n)
	for (int i = 0; i < m; ++i) {
		PNod p = lista[i];
		while (p != nullptr) {
			PNod temp = p;
			p = p->urm;
			delete temp;
		}
	}
}


/// Subalgoritm goleste(md)
///		pr: md multidictionar
///		post: md nu mai are niciun element
/// 
///		pentru i <- 0, m-1 executa
///			p  <- md.lista[i]           
///			cat timp p != NIL executa
///				temp <- p
///				p <- [p].urm
///				dealoca(temp)
///			sf cat timp
/// 
///			md.lista[i] <- NIL
///		sf pentru
///		
///		md.dimensiune <- 0
/// 
/// sfarsit subalgoritm
void MD::goleste()
{

	//Complexitate:
	//Caz favorabil = caz defavorabil = caz mediu = theta(n)

	for (int i = 0; i < m; ++i) {
		PNod p = lista[i];
		while (p != nullptr) {
			PNod temp = p;
			p = p->urm;
			delete temp;
		}
		lista[i] = nullptr;
	}

	dimensiune = 0;
}

TElem Nod::element()
{
	//Complexitate: theta(1)
	return e;
}

PNod Nod::urmator()
{
	//Complexitate: theta(1)
	return urm;
}
