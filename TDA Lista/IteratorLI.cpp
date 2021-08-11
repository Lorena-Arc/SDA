#include "IteratorLI.h"
#include "LI.h"
#include <exception>

IteratorLI::IteratorLI(const LI& li) : lista(li) {
	/* de adaugat */
	//Complexitate: tehta(1)
	curent = 0;
	pointer_la_curent = lista.prim;
}

void IteratorLI::prim() {
	/* de adaugat */
	//Complexitate theta(1)
	curent = 0;
	pointer_la_curent = lista.prim;
}

void IteratorLI::urmator() {
	/* de adaugat */
	//Complexitate theta(1)
	if (!valid())
		throw std::exception();
	curent++;
	pointer_la_curent = pointer_la_curent->urm;
}

bool IteratorLI::valid() const {
	/* de adaugat */
	//Complexitate theta(1)
	if (curent >= 0 && curent < lista.dim())
		return true;
	return false;
}

TElem IteratorLI::element() const {
	/* de adaugat */
	//Complexitate theta(1)
	if (!valid())
		throw std::exception();
	return pointer_la_curent->e;
	return -1;
}
