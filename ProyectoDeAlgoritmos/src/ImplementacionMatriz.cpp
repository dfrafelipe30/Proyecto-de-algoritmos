/*
 * ImplementacionMatriz.cpp
 *
 *  Created on: 5/05/2018
 *      Author: Daniel Felipe
 */


#ifdef MATRIZ_H_

#include<iostream>
using namespace std;

template <typename Dato>
M<Dato>::M()
{
	madre = NULL;//inicializacion de la madre.

	madre->tamX = 5;
	madre->tamY = 5;

	madre -> MI = new int * [madre -> tamX];
	for(int i = 0; i<madre->tamX;i++)
	{
		madre->MI[i] = new int [madre->tamY];
		for(int j = 0; j < madre->tamY;j++)
		{
			madre->MI[i][j] = 0;
		}
	}
	madre->padre = NULL;
	madre->hija = NULL;
	madre->Xa = NULL;
	madre->Ya = NULL;
	madre->Xs = NULL;
	madre->Ys = NULL;

	madre->Xa->push(0);
	madre->Ya->push(0);

	//pareddes.
	madre->MI[3][3] = -1;
	madre->MI[1][2] = -1;
	madre->MI[3][4] = -1;
	madre->MI[3][5] = -1;
	madre->MI[5][3] = -1;
}



#endif
