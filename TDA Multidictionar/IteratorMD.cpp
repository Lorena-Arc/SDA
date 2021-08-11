#include "IteratorMD.h"
#include "MD.h"

using namespace std;

IteratorMD::IteratorMD(const MD& _md) : md(_md) {
	/* de adaugat */
	//Complexitate: O(m)
	poz = 0;
	deplasare();
}

void IteratorMD::deplasare()
{
	//Complexitate: O(m)
	while (poz < md.m && md.lista[poz] == nullptr)
		poz++;

	if (poz < md.m)
		curent = md.lista[poz];
}

TElem IteratorMD::element() const {
	/* de adaugat */
	//Complexitate: theta(1)
	if (!valid())
		throw std::exception();
	return curent->element();
}

bool IteratorMD::valid() const {
	/* de adaugat */
	//Complexitate: theta(1)
	return poz < md.m && curent != nullptr;
}

void IteratorMD::urmator() {
	/* de adaugat */
	//Complexitate: O(m)
	if (!valid())
		throw std::exception();

	curent = curent->urmator();

	if (curent == nullptr) {
		poz = poz + 1;
		deplasare();
	}
}

void IteratorMD::prim() {
	/* de adaugat */
	//Complexitate: O(m)
	poz = 0;
	deplasare();
}

