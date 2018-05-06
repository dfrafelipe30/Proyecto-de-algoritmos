/*
 * ImplementacionLista.cpp
 *
 *  Created on: 5/05/2018
 *      Author: Daniel Felipe
 */

#ifdef LISTAS_H_

#include<iostream>
using namespace std;

template <typename Dato>
Lista<Dato>::Lista(){
	Ini = NULL;
}
template <typename Dato>
Lista<Dato>::~Lista()
{
	while(Ini != NULL)
	{
		L * temp = Ini;
		Ini = temp -> sig;
		delete temp;
	}
}
template <typename Dato>
void Lista<Dato>::push(Dato dato)
{
	if(Ini == NULL)
	{
	L * temp = Ini;
	temp -> val = dato;
	temp -> sig = NULL;
	Ini = temp;
	}
	else{
		L * nuevo = new L;
		nuevo -> val = dato;
		nuevo ->sig = Ini;
		Ini = nuevo;
	}
}
template <typename Dato>
void Lista<Dato>::pop()
{
	if(Ini != NULL)
	{
		L * temp = Ini;
		Ini = temp -> sig;
		delete temp;
	}
	else{
		cerr << "No hay elementos en la lista" << endl;
	}

}
template <typename Dato>
void Lista<Dato>::swap(Lista<Dato>::L * & Ini1,Lista<Dato>::L * & Ini2)
{
	L * temp = Ini1;
	Ini1 = Ini2;
	Ini2 = temp;
}


#endif
