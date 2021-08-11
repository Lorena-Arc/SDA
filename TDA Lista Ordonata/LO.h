#pragma once

class Iterator;

typedef int TComparabil;
typedef TComparabil TElement;

typedef bool (*Relatie)(TElement, TElement);

#define NULL_TELEMENT -1

class LO {
private:
	friend class Iterator;
private:
	/* aici e reprezentarea */
	int capacitate, dimensiune;
	int prim, prim_liber;
	TElement* e;
	int* urm;
	int aloca();
	void dealoca(int i);
	void initSpatiuLiber(int inceput);
	void resize();
	Relatie rel;

public:
	// constructor
	LO(Relatie r);

	// returnare dimensiune
	int dim() const;

	// verifica daca LO e vida
	bool vida() const;

	// returnare element
	//arunca exceptie daca i nu e valid
	TElement element(int i) const;

	// adaugare element in LO a.i. sa se pastreze ordinea intre elemente
	void adauga(TElement e);

	// sterge element de pe o pozitie i si returneaza elementul sters
	//arunca exceptie daca i nu e valid
	TElement sterge(int i);

	// cauta element si returneaza prima pozitie pe care apare (sau -1)
	int cauta(TElement e) const;

	// returnare iterator
	Iterator iterator();

	int eliminaToate(LO& lista);

	//destructor
	~LO();

};
