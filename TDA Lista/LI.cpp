#include <exception>
#include <iostream>
#include "LI.h"
#include "IteratorLI.h"

LI::LI() {
	/* de adaugat */
	//Complexitate theta(1)
	this->prim = nullptr;
	this->ultim = nullptr;
	this->dimensiune = 0;
}

int LI::dim() const {
	/* de adaugat */
	//Complexitate theta(1)
	return dimensiune;
}


bool LI::vida() const {
	/* de adaugat */
	//Complexitate theta(1)
	return dimensiune==0;
}

TElem LI::element(int i) const {
	/* de adaugat */
	//Complexitate O(n)
	if (i < 0 || i >= dim())
		throw std::exception();

	PNod p = prim;
	for (int j = 0; j < i; ++j)
		p = p->urm;

	return p->e;
}

TElem LI::modifica(int i, TElem e) {
	/* de adaugat */
	//Complexitate O(n)
	if (i < 0 || i >= dim())
		throw std::exception();

	PNod p = prim;
	for (int j = 0; j < i; ++j)
		p = p->urm;
	TElem vechi = p->e;
	p->e = e;
	return vechi;
}

void LI::adaugaSfarsit(TElem e) {
	/* de adaugat */
	//Complexitate theta(1)
	PNod nou = new Nod{ e, nullptr };
	if (prim == nullptr) {
		prim = nou;
		ultim = nou;
	}
	else {
		ultim->urm = nou;
		ultim = nou;
	}
	dimensiune++;
}

void LI::adauga(int i, TElem e) {
	/* de adaugat */
	//Complexitate O(n)
	if (i < 0 || i >= dim())
		throw std::exception();

	PNod nou = new Nod{ e, nullptr };
	PNod p = prim;
	if (i == 0) {
		nou->urm = prim;
		prim = nou;
	}
	else {
		for (int j = 0; j < i - 1; ++j) 
			p = p->urm;
		PNod spate = p->urm;
		p->urm = nou;
		nou->urm = spate;
	}
	dimensiune++;
}

TElem LI::sterge(int i) {
	/* de adaugat */
	//Complexitate O(n)

	if (i < 0 || i >= dim())
		throw std::exception();

	PNod p = prim;
	PNod nod_vechi = nullptr;
	TElem vechi;
	if (i == 0) {
		vechi = prim->e;
		nod_vechi = prim;
		prim = p->urm;
	}
	else {
		for (int j = 0; j < i - 1; ++j)
			p = p->urm;

		nod_vechi = p->urm;
		vechi = nod_vechi->e;
		p->urm = nod_vechi->urm;
	}
	dimensiune--;
	delete nod_vechi;
	return vechi;
}

int LI::cauta(TElem e) const {
	/* de adaugat */
	//Complexitate O(n)
	int poz = 0;
	PNod p = prim;
	while (p != nullptr) {
		if (p->e == e)
			return poz;
		poz++;
		p = p->urm;
	}

	return -1;
}

IteratorLI LI::iterator() const {
	//Complexitate theta(1)
	return  IteratorLI(*this);
}

/*
pre:elem:Telem
	lista:LI
post:poz_gasit:int 
	poz_gasit = ultima pozitie pe care apare elem in lista
	poz_gasit = -1 daca elem nu apare in lista

subalgoritm ultimulIndex(lista, elem, poz_gasit)
	p <- lista.prim
	poz <- 0
	poz_gasit <- -1

	Cat timp (p != NIL)
		Daca([p].e = elem)
			poz_gasit <- poz
		Sf. daca
		poz <- poz + 1
		p <- [p].urm
	Sf. Cat timp
Sf. subalgoritm

*/

int LI::ultimulIndex(TElem elem) const
{
	/*
	Complexitate
	Caz favorabil = caz defavorabil = caz mediu = theta(n)
	*/
	PNod p = prim;
	int poz = 0;
	int poz_gasit = -1;

	while (p != nullptr)
	{
		if (p->e == elem)
			poz_gasit = poz;
		poz++;
		p = p->urm;
	}

	return poz_gasit;
}

LI::~LI() {
	/* de adaugat */
	//Complexitate theta(n)
	while (prim != nullptr) {
		PNod temp = prim;
		prim = prim->urm;
		delete temp;
	}
}
