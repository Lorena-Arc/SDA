#pragma once
#include "Multime.h"
#include <stack>
using std::stack;

class Nod;

typedef int TElem;
typedef Nod* PNod;

class IteratorMultime
{
	friend class Multime;
	friend class Nod;

private:

	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	IteratorMultime(const Multime& m);

	//contine o referinta catre containerul pe care il itereaza
	const Multime& mult;

	/* aici e reprezentarea  specifica a iteratorului */
	PNod curent;
	stack<PNod> s;
	stack<PNod> s_nou;


public:

		//reseteaza pozitia iteratorului la inceputul containerului
		void prim();

		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
		void urmator();

		//verifica daca iteratorul e valid (indica un element al containerului)
		bool valid() const;

		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
		TElem element();

		void anterior();


};

