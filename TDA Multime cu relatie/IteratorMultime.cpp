#include "IteratorMultime.h"
#include "Multime.h"
#include <iostream>


IteratorMultime::IteratorMultime(const Multime& m) : mult(m){
	/* de adaugat */
	//Complexitate: O(h)
	curent = mult.radacina;
	while (curent != nullptr)
	{
		s.push(curent);
		curent = curent->fiu_stang;
	}

	if (!s.empty())
		curent = s.top();
}

TElem IteratorMultime::element()  {
	/* de adaugat */
	//Complexitate: theta(1)
	if (!valid())
		throw std::exception();

	return curent->valoare;

}

///Complexitate: caz fav = caz defav = caz mediu = theta(h)
/// 
/// subalgoritm anterior(i)
/// 
/// pre: i e un iterator e valid(se arunca exceptie daca nu e)
/// post: i' indica spre elementul anterior
/// 
/// primul <- i.mult.radacina
/// cat timp [primul].fiu_stang != NIL executa
///		primul <- [primul].fiu_stang
/// sf cat timp
/// 
/// daca i.curent = primul atunci
///		curent <- NIL
/// altfel
///			
///		daca [i.curent].fiu_stang != NIL atunci
///			i.curent <- [i.curent].fiu_stang
///			cat timp [i.curent].fiu_drept != NIL executa
///				i.curent <- [i.curent].fiu_drept
///			sf cat timp
/// 
///		altfel
///			creeaza(it, mult)
///			creeaza(it_ant, mult)
///			urmator(it)
///			
///			cat timp [it.curent]->valoare < [i.curent].valoare executa
///				urmator(it)
///				urmator(it_ant)
///			sf cat timp
///			
///			[i.curent] <- it_ant.curent
/// 
///		sf daca
/// 
/// sf daca
/// 
/// 
/// sf subalgoritm
void IteratorMultime::anterior()
{
	if (!valid())
		throw std::exception();
	PNod primul;

	primul = mult.radacina;
	while (primul->fiu_stang != nullptr)
	{
		primul = primul->fiu_stang;
	}

	if (curent == primul)
		curent = nullptr;
	else {
		if (curent->fiu_stang != nullptr) {
			curent = curent->fiu_stang;

			while (curent->fiu_drept != nullptr)
				curent = curent->fiu_drept;
		}
		else {
			IteratorMultime it(mult);
			it.urmator();
			IteratorMultime it_ant(mult);
			while (it.curent->valoare < curent->valoare) {
				it.urmator();
				it_ant.urmator();
			}

			this->curent = it_ant.curent;
		}
	}
}





bool IteratorMultime::valid() const {
	/* de adaugat */
	//Complexitate: theta(1)
	return curent != nullptr;
}

 
void IteratorMultime::urmator() {
	/* de adaugat */
	//Complexitate: O(h)
	if (!valid())
		throw std::exception();

	curent = s.top();
	s.pop();

	if (curent->fiu_drept != nullptr) {
		curent = curent->fiu_drept;
		while (curent != nullptr) {
			s.push(curent);
			curent = curent->fiu_stang;
		}
	}
	if (!s.empty())
		curent = s.top();
	else
		curent = nullptr;
	
}

void IteratorMultime::prim() {
	/* de adaugat */
	//Complexitate: O(h)
	while (!s.empty())
		s.pop();

	curent = mult.radacina;
	while (curent != nullptr)
	{
		s.push(curent);
		curent = curent->fiu_stang;
	}

	if (!s.empty())
		curent = s.top();

}

