#include "IteratorMultime.h"
#include "Multime.h"
#include <exception>


IteratorMultime::IteratorMultime(const Multime& m): mult(m) {
	//Complexitate: Theta(1)
	curent = 0;
}

TElem IteratorMultime::element() const {
	/* de adaugat */
	// Complexitate: Theta(1)
	if (!valid())
		throw std::exception();
	return mult.elemente[curent];
}

bool IteratorMultime::valid() const {
	/* de adaugat */
	//Complexitate: Theta(1)
	return curent < mult.dim() && curent >= 0;
}

void IteratorMultime::urmator() {
	/* de adaugat */
	//Complexitate: Theta(1)
	if (!valid())
		throw std::exception();
	curent++;
}

void IteratorMultime::prim() {
	/* de adaugat */
	//Complexitate: Theta(1)
	curent = 0;
}

