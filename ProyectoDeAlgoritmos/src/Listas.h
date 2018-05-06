/*
 * Listas.h
 *
 *  Created on: 5/05/2018
 *      Author: Daniel Felipe
 */

#ifndef LISTAS_H_
#define LISTAS_H_

template <typename Dato>
class Lista{
public:
	struct L{
		Dato val;
		L *sig;
	};

	Lista();
	~Lista();
	void push(Dato dato);
	void pop();
	void swap(L * & Ini1, L * & Ini2);


private:
	L *Ini;

};

#endif /* LISTAS_H_ */
#include "ImplementacionLista.cpp"
