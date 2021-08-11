#include "Iterator.h"
#include "LO.h"
#include <exception>

Iterator::Iterator(const LO& lo) : lista(lo) {
	/* de adaugat */
	//Complexitate: theta(1)
	curent = 0;
	poz_curenta = lista.prim;
}


void Iterator::prim() {
	/* de adaugat */
	//Complexitate: theta(1)
	curent = 0;
	poz_curenta = lista.prim;
}

void Iterator::urmator() {
	/* de adaugat */
	//complexitate: theta(1)
	if (!valid())
		throw std::exception();
	curent++;
	poz_curenta = lista.urm[poz_curenta];
}

bool Iterator::valid() const {
	/* de adaugat */
	//Complexitate: theta(1)
	//if (curent < 0 || curent >= lista.dimensiune)
		//return false;
	if(poz_curenta != -1)
		return true;
	return false;
}

TElement Iterator::element() const {
	/* de adaugat */
	//Complexitate: theta(1)
	if (!valid())
		throw std::exception();
	return lista.e[poz_curenta];
}


