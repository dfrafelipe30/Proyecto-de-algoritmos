//============================================================================
// Name        : ProyectoDeAlgoritmos.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
bool entre(int n,int lim){
	return -1<n&&n<lim;//determina si un numero esta entre 0 y lim
}

int main(int argc, char** argv) {
	bool done=false,posible=false,show=true;//posible dice si el laberinto tiene solucion, done dice si ya se ha hecho todo lo posible
	//show se usa para cordinar las impresiones en la construccion
	char order='r';//significa el comando interactivo
	// wasd para moversa arriva, dereche etc
	int i,j,y,x,posx=0,posy=0,move=1,aux=0,fx,fy;//i,j iterar en matriz,posx,posy posicion del crusor interactivo, move numero que toca rodear
	// aux se usa para rodear un numero , fx,fy posicion final
	cout<<"digite x de la matriz"<<endl;
	cin>>x;
	cout<<"digite y de la matriz"<<endl;
	cin>>y;
	int matriz[x][y];
	for(j=0;j<y;j++){
		for(i=0;i<x;i++){
			matriz[i][j]=0;//rellenar la matriz de 0
		}
	}
	while(order!='e'){// se debe presionar la letra "e"para salir del modo construccion
		if(show)
		for(j=0;j<y;j++){
			for(i=0;i<x;i++){
				if((i==posx)&&(j==posy)){//if para determinar si se esta en la posicion del cursor
					switch(matriz[i][j]){
						//imprimir bonito
						case 0:cout<<"* ";break;//cursor apuntando a espacio vacio
						case -3:cout<<"0 ";break;//cursor apuntando a pared
						case 1:cout<<"I ";break;//cursor apuntando a pos inicial
						case -2:cout<<"F ";break;//cursor apuntando a pos final
						default:break;
					}
				}
				else{
					switch(matriz[i][j]){
						case 0:cout<<"- ";break;//poner un - en espacio vacio
						case -3:cout<<"O ";break;//poner un O en pared
						case 1:cout<<"i ";break;// pos inicial
						case -2:cout<<"f ";break;//pos final
						default: break;
					}
				}
			}
			cout<<endl;
		}
		show=false;
		if(1==1){//if para determinar si una tecla ha sido presionada
			show=true;//
			cin << order;//obtener letra presionada
		    switch(order){//aplicar la orden que se recibe
			    case 'w':posy--;break;//subir el cursor
			    case 's':posy++;break;//bajar e cursor
			    case 'a':posx--;break;//mover a la izquierda el cursor
			    case 'd':posx++;break;//mover a la derecha
			    case 'p':matriz[posx][posy]=-3;break;//poner una pared
			    case 'i':matriz[posx][posy]=1;break;//poner posicion inicial
			    case 'f':matriz[posx][posy]=-2,fx=posx;fy=posy;break;//poner posicion final
		    }
	    }
	}
	while(!done){//mientras hallan cosas por hacer
		posible=false;//suponemos que no hay cosas por hacer
		for(j=0;j<y;j++){
			for(i=0;i<x;i++){
				if(matriz[i][j]==move){//si se esta en un numero que se debe rodear
					for(aux=0;aux<9;aux++){
						if(aux%2==1&&entre(i-1+(aux%3),x)&&entre(j-1+(aux/3),y)){//uso aritmetica modular en vez de un monton de if para marcar
						//las posiciones arriba abajo izq y derecha por que me dio pereza
							switch(matriz[i-1+(aux%3)][j-1+(aux/3)]){
								case 0:matriz[i-1+(aux%3)][j-1+(aux/3)]=move+1;posible=true;break;//rellenar szonas alrededor y mostrar que era poible hacer algo
								case -2:done=true;posible=true;break;//se encontro la pos final y mostrar que era posible hacer algo
								default:break;
							}
						}
					}
				}
			}
		}
		if(!posible){//si posible =false entoncesn no se hizo nada , es decir no queda nada por hacer asi que se debe romper el ciclo
			done=true;
		}
		move++;//le sumamos 1 al numero que toca rodear
	}
	move--;//le restamos uno para compensar el move++ de sobra al romper el ciclo
	if(posible){//i,j se ubican en la posicion final
		j=fy;
		i=fx;
		while(matriz[i][j]!=1){//mientras i,j apunte a una posicion diferente de la inicial
			for(aux=0;aux<9;aux++){
				if(aux%2==1&&entre(i-1+(aux%3),x)&&entre(j-1+(aux/3),y)){//aritmetica modular con la misma exuca anterior
					if(matriz[i-1+(aux%3)][j-1+(aux/3)]==move){
					    matriz[i][j]=-4;i=i-1+(aux%3);j=j-1+(aux/3);//alterar i,j para que se muevan al la casillauna unidad menor a la actual
					    // y marcar la actual como camino
					}
				}
		    }
		    move--;
		}
		matriz[i][j]=-4;//se marca comom camino la pos inicial
		for(j=0;j<y;j++){//imprimir bonito
			for(i=0;i<x;i++){
				switch(matriz[i][j]){
					case -4:cout<<"x ";break;
					case -3:cout<<"O ";break;
					default: cout<<"- ";break;
				}
			}
			cout<<endl;
		}
	}
	else{//en caso contrario el laberinto no tiene solucion
		cout<<"not posible";
	}
	return 0;
}
// optimizaciones: a la hora de rodear un numero se esta ejecutando una busqueda lineal sobre la matriz, para evitar eso pensaba en tener un queue
//con las cordenadas que toca rodear
//sobran variables booleanas
//se uso la version iterativa en vez de la recursiva por que la recursiva implementa deep first, es decir debe recorrer todos los caminos para determinar
//  el mas corto, esta version encuentra el camino mas corto al primerazo
// estaba pensando en implementar las llaves como numeros negativos y los muros asociados tambien como numeros negativos
//toca meterle colores por que se ve re feo
//la idea es que en el programa final todo lo que esta en la linea 74 hasta 91 sea una funcion, con la particularidad de que solo rodea un conjunto de numeros
// a la vez(es decir una vez rodeo el 1 voy y rodeo el 1 en las matrices hijas inmediatamente),para que cuando tenggamos el arbol de matrices podamos
// mantener la propiedad de econtrar el camino mas corto de primerazo y ademas se pueda usar de forma recursiva para aplica
