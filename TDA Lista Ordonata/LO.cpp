#include "Iterator.h"
#include "LO.h"
#include <exception>
#include <iostream>
using namespace std;

#include <exception>

int LO::aloca()
{
	//Complexitate: theta(1)
	//aloca un spatiu liber si returneaza pozitia pe care l-a alocat
	int i = prim_liber;
	if(i != -1) // nu o sa prea intre aici, ca nu o apelez in cazul asta, dar e bine de verificat
		prim_liber = urm[prim_liber];
	//i este pozitia pe care a alocat-o
	return i;
}

void LO::dealoca(int i)
{
	//Complexitate: theta(1)
	//i devine prima pozitie libera
	urm[i] = prim_liber;
	prim_liber = i;
}

void LO::initSpatiuLiber(int inceput)
{
	//Complexitate: theta(n)
	//face frumos vectorul cu spatii libere
	for (int i = inceput; i < capacitate - 1; ++i) {
		urm[i] = i + 1;
	}
	urm[capacitate - 1] = -1;
	prim_liber = inceput;
}

void LO::resize()
{
	//Complexitate: theta(n)
	capacitate *= 2;
	TElement* enou = new TElement[capacitate];
	int* urm_nou = new int[capacitate];
	
	for (int i = 0; i < dimensiune; ++i) {
		enou[i] = e[i];
		urm_nou[i] = urm[i];
	}
	

	delete[] e;
	delete[] urm;
	e = enou;
	urm = urm_nou;
	//dupa ce am alocat tot ce trebe, facem spatiile libere
	initSpatiuLiber(dimensiune);
}

LO::LO(Relatie r) {
	/* de adaugat */
	//Complexitate: thenta(n)
	capacitate = 2;
	dimensiune = 0;
	e = new TElement[2];
	urm = new int[2];
	initSpatiuLiber(0);
	prim = -1;
	rel = r;
}

// returnare dimensiune
//returneaza numarul de perechi (cheie, valoare) din dictionar
int LO::dim() const {
	/* de adaugat */
	//Complexitate: theta(1)
	return dimensiune;
}

// verifica daca LO e vida
bool LO::vida() const {
	/* de adaugat */
	// Complexitate: theta(1)
	return dimensiune == 0;
}

// returnare element
//arunca exceptie daca i nu e valid
TElement LO::element(int i) const {
	/* de adaugat */
	// Complexitate: O(n)
	if (i >= dimensiune || i < 0)
		throw exception();

	int poz = prim;
	int cnt = 0;
	TElement de_returnat;

	while (cnt != i) {
		cnt++;
		poz = urm[poz];
	}
	de_returnat = e[poz];
	return de_returnat;
}

// sterge element de pe o pozitie i si returneaza elementul sters
//arunca exceptie daca i nu e valid
TElement LO::sterge(int i) {
	/* de adaugat */
	//Complexitate: O(n)
	if (i >= dimensiune || i < 0)
		throw exception();

	int prev = prim;
	int cnt = 0;
	int actual = prim;
	TElement de_returnat;

	//cazul in care e primul

	//cand e doar un element si nu s-a aruncat exceptie, acel singur element trbuie sters,
	//deci intra in cazul de prim
	if (i == 0)
	{
		de_returnat = e[prim];
		prim = urm[prim];
	}
	//cand sunt cel putin doua elemente si nu primul trebuie sters
	//am nevoie de elementul anterior pentru a restabili legaturi
	else {
		while (cnt != i - 1) {
			cnt++;
			prev = urm[prev];
		}
		//in poz am indicele elementului anterior
		actual = urm[prev];
		de_returnat = e[actual];
		urm[prev] = urm[actual];
	}

	
	//dealocam 
	dealoca(actual);
	dimensiune--;
	return de_returnat;
}

// cauta element si returneaza prima pozitie pe care apare (sau -1)
int LO::cauta(TElement e) const {
	/* de adaugat */
	//Complexitate: O(n)
	if (dimensiune == 0)
		return -1;

	int poz = prim;
	int cnt = 0;
	TElement actual = this->e[poz];

	while (rel(actual, e) && cnt < dimensiune - 1){
		if (actual == e)
			return cnt;
		cnt++;
		poz = urm[poz];
		actual = this->e[poz];
	}

	//in cazul in care relatia ar fi doar < sau doar >, ar trebui o verificare suplimentara la iesirea din while
	//si pt ultimul element
	if (actual == e)
		return cnt;

	return -1;
}

// adaugare element in LO
void LO::adauga(TElement e) {
	/* de adaugat */
	//Complexitate: O(n)

	if (prim_liber == -1)
		resize();		
		
	int i = aloca();
	this->e[i] = e;
	urm[i] = -1;
	//caz de lista goala si caz de adaugare pe prima pozitie
	if (prim == -1 || !rel(this->e[prim], e))
	{
	
		urm[i] = prim;
		prim = i;
		dimensiune++;
		return;
	}
	//lista are un singur element si adugarea nu se face pe prima pozitie
	if (dimensiune == 1) {
		urm[prim] = i;
		dimensiune++;
		return;
	}
	//lista are cel putin doua elemente si adaugarea nu se face pe prima pozitie

	int actual = urm[prim];
	TElement e_actual = this->e[actual];
	int prev = prim;
	int cnt = 0;
	//Maxim cu e_actual pana la penultimul element ca sa nu ajunga actual -1
	while (rel(e_actual, e) && cnt < dimensiune - 2) {
		prev = actual;

		actual = urm[actual];
		e_actual = this->e[actual];
		cnt++;
	}

	//pt ultima pozitie
	if (rel(e_actual, e)) {
		prev = actual;
		actual = urm[actual];
	}
	
	urm[i] = actual;
	urm[prev] = i;
	dimensiune++;

}

// returnare iterator
Iterator LO::iterator() {
	//Complexitate: theta(1)
	return Iterator(*this);
}
/*
	Pseudocod
	Preconditii:l: Lo
			lista :LO
	Postconditii: Elementele din lista sunt sterse din l
				i = nr de elemente care au fost sterse
	Subalgortim eliminaToate():
		cnt <- 0
		Daca !vida(l) si !vida(lista)
		Atunci

			poz1 <- iterator(lista)
			poz2 <- iterator(l)

			cat timp (valid(poz1)); executa
				el1 <- element(poz1)

				Cat timp (valid(poz2)) excuta
					el2 <- element(poz2)

					daca (el1 = el2) atunci
						cnt <- cnt + 1
						sterge(poz2.curent)
					sf daca
					urmator(poz2)
				sf cat timp


			sf cat timp

		Altfel
			i <-0
		Sf Daca

		i <- cnt
		Sf subalgoritm


		
*/
int LO::eliminaToate(LO& lista)
{
	//Caz fav: nu se gasesc elemente in lista -> theta(n*m)
	//Caz defav: toate sunt in lista -> O(n*n*m)
	//Complexitate: O(n^2*m)
	int cnt = 0;
	if (lista.vida() || vida())
		return 0;

	Iterator poz1 = lista.iterator();
	Iterator poz2 = iterator();
	TElement el1, el2; //el1 in l param, el2 in l actuala
	while (poz1.valid()) {
		el1 = poz1.element();
		poz2.prim();
		while (poz2.valid()) {
			el2 = poz2.element();
			
			if (el1 == el2) {
				cnt++;
				sterge(poz2.curent);
			}
			poz2.urmator();
		}
		poz1.urmator();
	}
	return cnt;

}


//destructor
LO::~LO() {
	/* de adaugat */
	//Complexitate: theta(1)
	delete[] e;
	delete[] urm;
}
