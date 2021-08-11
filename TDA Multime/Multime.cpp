#include "Multime.h"
#include "IteratorMultime.h"
#include <iostream>

using namespace std;

//o posibila relatie
bool rel(TElem e1, TElem e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}


void Multime::redim()
{
	//Complexity: theta(n)
	TElem *elemente_nou = new TElem[2 * capacitate];
	
	for (int i = 0; i < dimensiune; ++i)
		elemente_nou[i] = elemente[i];

	capacitate = 2 * capacitate;
	delete[] elemente;

	elemente = elemente_nou;
}

void Multime::divide()
{
	//Complexity: theta(n)
	TElem* elemente_nou = new TElem[capacitate/2];

	for (int i = 0; i < dimensiune; ++i)
		elemente_nou[i] = elemente[i];

	capacitate = capacitate / 2;
	delete[] elemente;

	elemente = elemente_nou;
}


Multime::Multime() {
	// Complexitate: theta(1)
	capacitate = 2;
	dimensiune = 0;
	elemente = new TElem[capacitate];
}


bool Multime::adauga(TElem elem) {
	//Complexitate: O(n)
	if (capacitate == dimensiune)
		redim();	

	int l = 0, r = dimensiune - 1, m;

	while (l <= r)
	{
		m = (l + r) / 2;
		if (elem == elemente[m])
			return false;
		if (rel(elem, elemente[m]))
			r = m - 1;
		else
			l = m + 1;
	}

	for (int i = dimensiune - 1; i >= l; --i)
		elemente[i + 1] = elemente[i];
	
	elemente[l] = elem;
	dimensiune++;
	return true;
}


bool Multime::sterge(TElem elem) {
	//Complexitate: O(n)
	int l = 0, r = dimensiune - 1, m, poz = -1;

	while (l <= r)
	{
		m = (l + r) / 2;
		if (elem == elemente[m])
		{
			poz = m;
			break;
		}
			
		if (rel(elem, elemente[m]))
			r = m - 1;
		else
			l = m + 1;
	}

	if (poz == -1)
		return false;

	for (int i = poz; i < dimensiune - 1; ++i)
		elemente[i] = elemente[i + 1];

	dimensiune--;

	if (dimensiune < capacitate / 2 && dimensiune != 0)
		divide();
	return true;
}


bool Multime::cauta(TElem elem) const {
	//Complexitate: O(log2 n)
	int l = 0, r = dimensiune - 1, m;

	while (l <= r)
	{
		m = (l + r) / 2;
		if (elem == elemente[m])
			return true;
		if (rel(elem, elemente[m]))
			r = m - 1;
		else
			l = m + 1;
	}
	return false;
}


int Multime::dim() const {
	//Complexitate: theta(1)
	return dimensiune;
}



bool Multime::vida() const {
	//Complexitate: theta(1)
	if(dimensiune == 0)
		return true;
	return false;
}

IteratorMultime Multime::iterator() const {
	//Complexitate: theta(1)
	return IteratorMultime(*this);
}


Multime::~Multime() {
	//Complexitate: theta(1)
	delete[] elemente;
}






