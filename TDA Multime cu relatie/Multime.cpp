#include "Multime.h"
#include <iostream>

using namespace std;

//o posibila relatie
bool rel(TElem e1, TElem e2) {
	//Complexitate: theta(1)
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}

void Multime::distruge(PNod p)
{
	//Complexitate: theta(n)
	if (p != nullptr) {
		distruge(p->fiu_stang);
		distruge(p->fiu_drept);
		delete p;
	}
}

PNod Multime::minim(PNod p)
{
	//Complexitate: O(h)
	auto x = p;
	while (x->fiu_stang != nullptr)
		x = x->fiu_stang;
	return x;
}

PNod Multime::creeaza_frunza(TElem elem)
{
	//Complexitate: theta(1)
	auto p = new Nod(elem);
	return p;
}

PNod Multime::cauta_rec(PNod p, TElem e) const
{
	//Complexitate: O(h)
	if (p == nullptr || p->valoare == e)
		return p;

	if (rel(e, p->valoare))
		cauta_rec(p->fiu_stang, e);
	else
		cauta_rec(p->fiu_drept, e);
	
}

PNod Multime::adauga_rec(PNod p, TElem e)
{
	//Complexitate: O(h)
	if (p == nullptr)
	{
		p = creeaza_frunza(e);
		dimensiune++;
		return p;
	}

	if (rel(e, p->valoare)) {
		if (e == p->valoare)
			throw(std::exception());

		p->fiu_stang = adauga_rec(p->fiu_stang, e);
	}
	else {
		p->fiu_drept = adauga_rec(p->fiu_drept, e);
	}
	return p;
}

PNod Multime::sterge_rec(PNod p, TElem e)
{
	//Complexitate: O(h)
	if (p == nullptr)
		throw std::exception();
	if (rel(e, p->valoare) && e != p->valoare) {
		p->fiu_stang = sterge_rec(p->fiu_stang, e);
		return p;
	}
	
	if (!rel(e, p->valoare)) {
		p->fiu_drept = sterge_rec(p->fiu_drept, e);
		return p;
	}

	if (e == p->valoare) {
		if (p->fiu_drept != nullptr && p->fiu_stang != nullptr)
		{
			auto temp = minim(p->fiu_drept);
			p->valoare = temp->valoare;
			p->fiu_drept = sterge_rec(p->fiu_drept, p->valoare);
			return p;
		}
		else {
			auto temp = p;
			PNod repl;
			if (p->fiu_stang == nullptr)
				repl = p->fiu_drept;
			else 
				repl = p->fiu_stang;
			delete temp;
			return repl;

		}

	}
	
}

Multime::Multime() {
	/* de adaugat */
	//Complexitate: theta(1)
	dimensiune = 0;
	radacina = nullptr;
}


bool Multime::adauga(TElem elem) {
	/* de adaugat */
	//Complexitate: O(h)
	PNod p;
	try {
		p = adauga_rec(radacina, elem);
	}
	catch (...) {
		return false;
	}

	radacina = p;
	return true;
	
}


bool Multime::sterge(TElem elem) {
	/* de adaugat */
	//Complexitate: O(h)
	try {
		radacina = sterge_rec(radacina, elem);
	}
	catch (...) {
		return false;
	}
	dimensiune--;
	return true;
}


bool Multime::cauta(TElem elem) const {
	/* de adaugat */
	//Complexitate: O(h)
	auto p = cauta_rec(radacina, elem);
	if (p != nullptr)
		return true;

	return false;
}


int Multime::dim() const {
	/* de adaugat */
	//Complexitate: theta(1)
	return dimensiune;
}



bool Multime::vida() const {
	/* de adaugat */
	//Complexitate: theta(1)
	return dimensiune == 0;
}

IteratorMultime Multime::iterator() const {
	
	//Complexitate: O(h)
	return IteratorMultime(*this);
}


Multime::~Multime() {
	/* de adaugat */
	//Complexitate: theta(n)
	distruge(radacina);
}






