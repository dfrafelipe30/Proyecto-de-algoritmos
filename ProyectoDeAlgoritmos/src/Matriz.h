/*
 * Matriz.h
 *
 *  Created on: 5/05/2018
 *      Author: Daniel Felipe
 */

#ifndef MATRIZ_H_
#define MATRIZ_H_
#include "Listas.h"

template <typename Dato>
class M{
public:
	struct matriz{
		int **MI;

		Lista<int> * Xa;
		Lista<int> * Ya;

		Lista<int> * Xs;
		Lista<int> * Ys;

		matriz * padre;
		Lista<matriz*> hija;

		int tamX;
		int tamY;
	};

	M();
	~M();


private:
	matriz * madre;
};



#endif /* MATRIZ_H_ */
#include "ImplementacionMatriz.cpp"
