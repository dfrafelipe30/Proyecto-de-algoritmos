//============================================================================
// Name        : ProyectoDeAlgoritmos.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>

#include <stdio.h>
//#include <conio.h>

using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct punto{
	int x;
	int y;
};

//stack
template<typename dato>
struct node{
	dato val;
	node<dato> *next;
};

// nodos del arbol de matricez
struct maze{
	int **matriz;//la matriz(puntero de punteros)
	int tamx;//tama�o en x de la matriz
	int tamy;//tama�o en y de la matriz
	int move;//el numero que toca poner al rodear otro
	node<punto> *actual;//lista de posiciones por rodear
	node<punto> *sig;//lista de posiciones en las que se agrega un numero
	maze *padre;//apuntador a padre
	node<maze*> *hijas;// lista de apuntadores a las hijas
	punto inicial;//
};

//funcion valor absoluto
int abso(int n){
	if(n<0){
		return -1*n;
	}
	return n;
}

//imprimir  50 lineas para simular limpiar patanlla
void espacio(){
	for(int i=0;i<50;i++){
		cout<<endl;
	}
}

//imprimir llave o puerta cuando se esta parado en ella
void keyon(int n){
	if(n<0)
	if(abso(n)%2==1)//verificar que sea impar
	cout<<"K"<<(abso(n)-5)/2+1;//se resta 5 para contrarestar el hecho que las llaves empiezan en -5, se divide en 2 para que la division entera agrupe
	// y se suma 1 por que dichos grupos empiezan en 0
	else
	cout<<"P"<<(abso(n)-5)/2+1;
	else
	cout<<"* ";
}

//imprimir llave o puerta cuando no se esta parado en ella
void keyoff(int n){
	if(n<0)
	if(abso(n)%2==1)
	cout<<"k"<<(abso(n)-5)/2+1;
	else
	cout<<"p"<<(abso(n)-5)/2+1;
	else
	cout<<"- ";
}

//funcion que dice si un entero esta entre 0 y lim
bool entre(int n,int lim){
	return 0<=n&&n<lim;
}

//imprimir los numeros en la matriz
void fea(maze &meow){
	for(int j=0;j<meow.tamy;j++){
		for(int i=0;i<meow.tamx;i++){
			if(meow.matriz[i][j]<0)
			cout<<meow.matriz[i][j];
			else
			cout<<" "<<meow.matriz[i][j];
		}
		cout<<endl;
	}
}

//imprimir la matriz de forma bonita, posx,posy son las posiciones sobre las que se ubica el asterisco
void bonita(maze &meow,int posx,int posy){
	for(int j=0;j<meow.tamy;j++){
		for(int i=0;i<meow.tamx;i++){
			if(i==posx&&j==posy){
			    switch(meow.matriz[i][j]){
				    case 0:cout<<"* ";break;
				    case 1:cout<<"I ";break;
				    case -1:cout<<"0 ";break;
				    case -2:cout<<"F ";break;
				    case -3:cout<<"* ";break;
				    case -4:cout<<"X";break;
				    default:keyon(meow.matriz[i][j]);break;
			    }
		    }
		    else{
		    	switch(meow.matriz[i][j]){
				    case 0:cout<<"- ";break;
				    case 1:cout<<"i ";break;
				    case -1:cout<<"O ";break;
				    case -2:cout<<"f ";break;
				    case -3:cout<<"- ";break;
				    case -4:cout<<"x ";break;
				    default:keyoff(meow.matriz[i][j]);break;
			    }
	        }

        }
        cout<<endl;
    }
}



template<typename dato>
void push(node<dato> * & p,dato elem){
	if(p==NULL){
		p=new node<dato>;
		(*p).val=elem;
		(*p).next=NULL;
	}
	else{
		node<dato> *aux=new node<dato>;
		(*aux).val=elem;
		(*aux).next=p;
		p=aux;
	}
}

template<typename dato>
void pop(node<dato> * & p){
	if(p!=NULL){
		if((*p).next!=NULL){
		    node<dato> *aux=(*p).next;
	        delete p;
	        p=aux;
	    }
	    else{
	    	delete p;
	    	p=NULL;
		}
	}
	else
	cout<<"meow";
}

// intercambia dos listas
template<typename dato>
void swap(node<dato> * &p,node<dato> * &p2){
	node<dato> *aux=p;
	p=p2;
	p2=aux;
}

//mostrar la lista de llaves recojidas
void mostrar(node<int> * & p){
        if(p==NULL)
        return;
	node<int> *ite=p;
	cout<<"llaves recojidas: "<<endl;
	while(ite!=NULL){
		cout<<(*ite).val<<", ";
		ite=(*ite).next;
	}
	cout<<endl;
}

//armar un el laberinto raiz de forma interactiva
maze armar(){
	// i,j se usan para recorrer la matriz,posx,posy son la posicion del asterisco,llave es el numero que se pone en la matriz al ubicar una llave
	int i,j,posx=0,posy=0,llave=-5;
	char order='a';
	maze meow;
	meow.move=2;//el numero que se pone al rededor del numero por rodear
	meow.actual=NULL;//se inicial la lista de actuales vacia
	meow.sig=NULL;//se inicia la lista de siguientes vacia
	meow.hijas=NULL;//se inicia la lista de hijas vacia
	cout<<"digite tamanio en x"<<endl;
	cin>>meow.tamx;
	cout<<"digite tamanio en y"<<endl;
	cin>>meow.tamy;
	meow.matriz=new int * [meow.tamx];// hacer que matriz apunte a un arreglo de punteros de tama�o cantidad de columnas
	for(i=0;i<meow.tamx;i++){
		meow.matriz[i]=new int [meow.tamy];//hacer que cada puntero del arreglo apunto a un arreglo de enteros de tama�o cantidad de filas:
		for(j=0;j<meow.tamy;j++){
			meow.matriz[i][j]=0;//rellenar de 0
		}
	}
	meow.padre=NULL;//la matriz raiz no tiene padre
	while(order!='e'){
		bonita(meow,posx,posy);//imprimir de forma linda la matriz
		fea(meow);//imprimir la representacion numerico de la matriz
		cin>>order;
		switch(order){
			//actualizar la posicion segun los controles de juegos de pc wasd
			case 'a':posx--;break;
			case 'd':posx++;break;
			case 'w':posy--;break;
			case 's':posy++;break;
			//poner una pared
			case 'p':meow.matriz[posx][posy]=-1;break;
			//poner la posicion inicial
			case 'i':meow.matriz[posx][posy]=1;
			    punto point;
			    point.x=posx;
			    point.y=posy;
			    push(meow.actual,point);break;//la posicion inicial es el primer numnero por rodear por eso se agrega a la lista
			case 'f':meow.matriz[posx][posy]=-2;break;//poner la posicion final
			case 'k':meow.matriz[posx][posy]=llave;llave--;break;//poner una llave o una puerta dependiendo de la paridad
			default:break;
		}
		espacio();
	}
	return meow;
}



void crearhija(maze &meow,int key){
	//se crea el apuntador a la matriz hija
	maze *hija=new maze;
	//se agrega el apuntador a la lista de apuntadores de el maze madre
	push(meow.hijas,hija);
	(*hija).padre=&meow;//el padre de hija es el padre de hija
	(*hija).actual=NULL;//se inicial la lista de actual vacia
	(*hija).sig=NULL;//se inicia la lista de siguientes vacia
	(*hija).move=2;//se define el numero que se pone al rodear
	(*hija).tamx=meow.tamx;//se igualan los tama�os
	(*hija).tamy=meow.tamy;
	(*hija).matriz=new int* [meow.tamx];//se crea la matriz hija
	for(int i=0;i<meow.tamx;i++){
		(*hija).matriz[i]=new int [meow.tamy];
		for(int j=0;j<meow.tamy;j++){
			if(meow.matriz[i][j]==key){//si en la posicion i,j del padre hay una llave esta sera la pos inicial de la hija
				(*hija).matriz[i][j]=1;
				punto point;
				point.x=i;
				point.y=j;
			    push((*hija).actual,point);
			}
			else{
				if(meow.matriz[i][j]==key-1)//si en la pos i,j esta la puerta asociada a la llave se pone espacion vacio
				(*hija).matriz[i][j]=0;
				else{
					if(meow.matriz[i][j]<0)//se ponen las llaves y puertas que no se afectan
					(*hija).matriz[i][j]=meow.matriz[i][j];
					else
					(*hija).matriz[i][j]=0;
				}
			}
		}
	}
}

punto marcar(maze &meow,int rx,int ry){//rxy rx son la posicion desde la que se quiere encontrar un camino
	while(meow.matriz[rx][ry]!=1){//mientras rx,ry sea diferente de la pos inicial de esa matriz
		for(int aux=1;aux<9;aux+=2){
			if(entre(-1+rx+aux%3,meow.tamx)&&entre(-1+ry+aux/3,meow.tamy))
			if(meow.matriz[-1+rx+aux%3][-1+ry+aux/3]==meow.matriz[rx][ry]-1){//actualizar rx,ry segun se deba para marcar el camino
				meow.matriz[rx][ry]=-3;
				rx=-1+rx+aux%3;
				ry=-1+ry+aux/3;
				break;
			}
		}
	}

	meow.matriz[rx][ry]=-4;
	punto creador;
	creador.x=rx;
	creador.y=ry;
	meow.inicial=creador;// se define inicial para facilitar  la creacion de caminos
	return creador;//se retorna ese punto para marcar el camino de la siguiente matriz
}

void juntarsolucion(maze &meow,node<maze*> * &solu,int rx,int ry){//rx,ry es la poscion de la meta
	//cout<<"juntar"<<endl;
	push(solu,&meow);
	punto chosen;
	chosen=marcar(meow,rx,ry);
	//fea(meow);
	//cout<<endl;
	maze *ite=meow.padre;
	while(ite!=NULL){
		push(solu,ite);//se agregan las matricez que marcan conforman el camino correcto
		chosen=marcar(*ite,chosen.x,chosen.y);//se marca el camino el camino en la matriz y se prepara para marcar el de la siguiente
		//fea(*ite);
		//cout<<endl;
		ite=(*ite).padre;
	}
}

//to_do se usa para definir si han habido operaciones realizables durante ese recorrido,solved dice si ya se ha encontrado una solucion
//solu es una lista de apuntadores a las matrices que contienen la solucion
void rodear(maze &meow,bool &to_do,bool &solved,node<maze*> * &solu){
	int rx,ry;
	node<punto> *ite=meow.actual;//ite se usa para reccorer la lista de puntos por rodear
	punto creador;
	if(!solved)
	while(ite!=NULL){//se recorre la lista
		for(int aux=1;aux<9;aux+=2){
			rx=-1+(*ite).val.x+aux%3;
			ry=-1+(*ite).val.y+aux/3;
			if((entre(rx,meow.tamx))&&(entre(ry,meow.tamy))){
			    if(meow.matriz[rx][ry]==0){// se rellenan las casillas rellenables
		            meow.matriz[rx][ry]=meow.move;
		            creador.x=rx;
		            creador.y=ry;
		            push(meow.sig,creador);//se agrega el a la lista de de siguientes
		            to_do=true;//como se hizo una operacion entonces hay opreciones realizables
		        }
		        else{
		        	if(meow.matriz[rx][ry]<-4&&abso(meow.matriz[rx][ry])%2==1){//si se encuentra una llave
		        		crearhija(meow,meow.matriz[rx][ry]);
		        		meow.matriz[rx][ry]=meow.move;
		        		creador.x=rx;
		        		creador.y=ry;
		        		push(meow.sig,creador);
		        		to_do=true;
					}
					if(meow.matriz[rx][ry]==-2){//si se llega a la meta
						meow.matriz[rx][ry]=meow.move;
						juntarsolucion(meow,solu,rx,ry);
						solved=true;//se dice que se encontro una solucion
					}
				}
		    }
	    }
	    ite=(*ite).next;//actualizar la lista de actuales pues ya se uso el primer elemento
	    pop(meow.actual);
	    if(solved)
	    ite=NULL;
    }
    swap(meow.actual,meow.sig);//se intercambias las listas para preparar la siguiente iteracion
    meow.move++;
}



void recu(maze &meow,bool &to_do,bool &solved,int prof,node<maze*> * &solu){
	rodear(meow,to_do,solved,solu);
	//cout<<"prof "<<prof<<endl;
	//fea(meow);
	node<maze*> *ite=meow.hijas;
	while(ite!=NULL){
		recu(*((*ite).val),to_do,solved,prof+1,solu);
		ite=(*ite).next;
	}
}

void copiabonita(int **copia,int x,int y,int posx,int posy){
	for(int j=0;j<y;j++){
		for(int i=0;i<x;i++){
			if(i==posx&&j==posy){
			    switch(copia[i][j]){
				    case 0:cout<<"* ";break;
				    case 1:cout<<"I ";break;
				    case -1:cout<<"0 ";break;
				    case -2:cout<<"F ";break;
				    case -3:cout<<"* ";break;
				    case -4:cout<<"X";break;
				    default:keyon(copia[i][j]);break;
			    }
		    }
		    else{
		    	switch(copia[i][j]){
				    case 0:cout<<"- ";break;
				    case 1:cout<<"i ";break;
				    case -1:cout<<"O ";break;
				    case -2:cout<<"f ";break;
				    case -3:cout<<"- ";break;
				    case -4:cout<<"x ";break;
				    default:keyoff(copia[i][j]);break;
			    }
	        }

        }
        cout<<endl;
    }

}

void animar(node<int> * & llaves,int **copia,maze &meow){
	int i=meow.inicial.x,j=meow.inicial.y;
	char order;
	bool walk=true;
	while(walk){//mientras halla camino por recorrer
		walk=false;
		for(int aux=1;aux<9;aux+=2){
			if(entre(-1+i+aux%3,meow.tamx)&&entre(-1+j+aux/3,meow.tamy))
			if(meow.matriz[-1+i+aux%3][-1+j+aux/3]==-3){
				mostrar(llaves);
				copiabonita(copia,meow.tamx,meow.tamy,i,j);
				if(copia[-1+i+aux%3][-1+j+aux/3]<-4&&abso(copia[-1+i+aux%3][-1+j+aux/3])%2==1){
					push(llaves,(abso(copia[-1+i+aux%3][-1+j+aux/3])-5)/2+1);// recojer una llave
					copia[-1+i+aux%3][-1+j+aux/3]=0;
				}
				cin>>order;
				meow.matriz[i][j]=0;
				i=-1+i+aux%3;
				j=-1+j+aux/3;
				meow.matriz[i][j]=-4;
				walk=true;
			}
		}
	}
	copiabonita(copia,meow.tamx,meow.tamy,i,j);
}

void caminar(int **copia,node<maze*> * &solu,int &contpasos, int modalidad){//animar cada una de las matrices solucion
	node<maze*> *ite=solu;
	node<int> *llaves=NULL;
	while(ite!=NULL){
                if(modalidad==1)
		animar(llaves,copia,*((*ite).val));
		ite=(*ite).next;
                contpasos++;
	}
}

void clear(maze & meow){
     for(int i=0;i<meow.tamx;i++){
         delete[] meow.matriz[i];
     }
     delete meow.matriz;
     while(meow.hijas!=NULL){
         clear(*((*(meow.hijas)).val));
         pop(meow.hijas);
     }
     while(meow.actual!=NULL){
         pop(meow.actual);
     }
     while(meow.sig!=NULL){
         pop(meow.sig);
     }
     delete &meow;
}


maze deepcopy(maze &para){
     maze copia;
     copia.matriz=new int * [para.tamx];
     for(int i=0;i<para.tamx;i++){
         copia.matriz[i]=new int [para.tamy];
         for(int j=0;j<para.tamy;j++){
             copia.matriz[i][j]=para.matriz[i][j];
             if(copia.matriz[i][j]==1){
                 punto creador;
                 creador.x=i;
                 creador.y=j;
                 push(copia.actual,creador);
             }
         }
     }
     copia.move=2;
     copia.tamx=para.tamx;
     copia.tamy=para.tamy,
     copia.hijas=NULL,
     copia.padre=NULL;
     copia.actual=NULL;
     copia.sig=NULL;
     return copia;
}

     

int solve(maze &meow,int modalidad){
	bool solved=false,to_do=true;
	int **copia,contpasos=0;
	copia=new int * [meow.tamx];
	for(int i=0;i<meow.tamx;i++){
		copia[i]=new int[meow.tamy];
		for(int j=0;j<meow.tamy;j++){
			copia[i][j]=meow.matriz[i][j];
		}
	}

	node<maze*> *solu=NULL;
	char order;
	while(to_do){
		to_do=false;
		recu(meow,to_do,solved,0,solu);
		contpasos++;
		//cin>>order;
		if(solved)
		to_do=false;
	}
	if(solved){
		if(modalidad==1){
		      cout<<"solucion"<<endl;
	              caminar(copia,solu,contpasos,modalidad);
                      meow.matriz=copia;
                      contpasos--;
                      while(meow.hijas!=NULL){
                          clear(*((*(meow.hijas)).val));
                          pop(meow.hijas);
                      }
	              return contpasos;
		}
        else{
                caminar(copia,solu,contpasos,modalidad);
                contpasos--;
                while(meow.hijas!=NULL){
                    clear(*((*(meow.hijas)).val));
                    pop(meow.hijas);
                }
        	return contpasos;
		}
	}
	else
	cout<<"no es posible" << endl;
        meow.matriz=copia;
        while(meow.hijas!=NULL){
             clear(*((*(meow.hijas)).val));
             pop(meow.hijas);
        }
	return 0;
}

void formatopre(maze & meow){
    cout<<"{";
    for(int j=0;j<meow.tamy;j++){
       cout<<"{";
       for(int i=0;i<meow.tamx;i++){
           if(i==meow.tamx-1)
           cout<<meow.matriz[i][j];
           else
           cout<<meow.matriz[i][j]<<",";
       }
       cout<<"},";
    }
    cout<<"}" << endl;
}


int jugar(maze &meow){
        int **copia;
        int i=0,j=0,posx,posy,auxx,auxy;
        char order;
        node<int> *llaves=NULL;
        copia=new int * [meow.tamx];
        for(i=0;i<meow.tamx;i++){
            copia[i]=new int [meow.tamy];
            for(j=0;j<meow.tamy;j++){
                copia[i][j]=meow.matriz[i][j];
                if(copia[i][j]==1){
                    posx=i;
                    posy=j;
                }
            }
        }
        auxx=posx;
        auxy=posy;
        int cont=solve(meow,0),movi=0;
        copiabonita(copia,meow.tamx,meow.tamy,posx,posy);
        while(movi<=cont){
            cin>>order;
            switch(order){
                 case 'a':auxx=posx-1;auxy=posy;break;
	         case 'd':auxx=posx+1;auxy=posy;break;
		 case 'w':auxy=posy-1;auxx=posx;break;
	         case 's':auxy=posy+1;auxx=posx;break;
                 default: break;
            }
            if(copia[auxx][auxy]==-1 ||(abso(copia[auxx][auxy])%2==0 && copia[auxx][auxy]<-4)){
                 cout<<"no se puede atravesar esa casilla"<<endl;
            }
            else{
                 if(abso(copia[auxx][auxy])%2==1 && copia[auxx][auxy]<-4){
                     cout<<"se ha recojido una llave"<<endl;
                     //movi--;
                     for(j=0;j<meow.tamy;j++){
                         for(i=0;i<meow.tamx;i++){
                              if(copia[i][j]==copia[auxx][auxy]-1){
                                   copia[i][j]=0;
                              }
                         }
                     }
                     push(llaves,(abso(copia[auxx][auxy])-5)/2+1);
                 }
                 posx=auxx;
                 posy=auxy;
                 movi++;
            }    
            copiabonita(copia,meow.tamx,meow.tamy,posx,posy);
            mostrar(llaves);
            if(copia[posx][posy]==-2){
                 cout<<"llego al final"<<endl;
                 return 0;
            }
               
        }
        cout<<"perdio"<<endl;
        return 1;
}
maze labe1(){
   maze lab1;
   int algo[10][10]={{0,-1,0,0,0,0,0,0,-1,0},{-1,-15,-10,0,0,0,0,-8,-17,-1},{0,-1,0,0,0,0,0,0,-1,0},{-16,0,0,-5,0,-7,0,0,0,0},{-19,-14,0,0,1,0,0,0,0,0},{-18,0,0,-9,0,-11,0,0,0,0},{0,0,0,0,0,0,0,0,-1,-1},{0,0,-12,0,0,0,0,-20,-2,-1},{0,-1,-13,-6,0,0,0,0,-1,-1},{0,0,-1,0,0,0,0,0,0,0}};
   lab1.matriz=new int * [10];
   for(int i=0;i<10;i++){
       lab1.matriz[i]= new int [10];
       for(int j=0;j<10;j++){
           lab1.matriz[i][j]=algo[j][i];
       }
   }
   
   lab1.hijas=NULL;
   lab1.padre=NULL;
   lab1.move=2;
   lab1.tamx=10;
   lab1.tamy=10;
   lab1.actual=NULL;
   lab1.sig=NULL;
   punto creador;
   creador.x=4;
   creador.y=4;
   push(lab1.actual,creador);
   return lab1;
}

maze labe2(){
   maze lab2;
   int algo[8][6] = {{0,-5,1,0,0,0},{0,-7,0,0,0,0},{0,0,0,0,0,0},{0,0,0,-1,0,0},{0,0,0,-1,0,0},{0,0,0,-1,0,0},{0,0,-8,0,0,0},{0,0,-6,-2,0,0}};
   lab2.matriz=new int * [6];
   for(int i=0;i<6;i++){
       lab2.matriz[i]= new int [8];
       for(int j=0;j<8;j++){
           lab2.matriz[i][j]=algo[j][i];
       }
   }
   
   lab2.hijas=NULL;
   lab2.padre=NULL;
   lab2.move=2;
   lab2.tamx=6;
   lab2.tamy=8;
   lab2.actual=NULL;
   lab2.sig=NULL;
   punto creador;
   creador.x=2;
   creador.y=0;
   push(lab2.actual,creador);
   return lab2;
}

maze labe3(){
   maze lab2;
   int algo[7][7] ={{1,0,-5,0,-13,0,0},{0,0,-6,0,-12,0,0},{0,0,-7,0,-11,0,0},{0,0,-8,0,-10,0,0},{0,0,-9,0,0,0,0},{0,0,0,-1,0,0,0},{0,0,-1,-2,-1,0,0}};
   lab2.matriz=new int * [7];
   for(int i=0;i<7;i++){
       lab2.matriz[i]= new int [7];
       for(int j=0;j<7;j++){
           lab2.matriz[i][j]=algo[j][i];
       }
   }
   
   lab2.hijas=NULL;
   lab2.padre=NULL;
   lab2.move=2;
   lab2.tamx=7;
   lab2.tamy=7;
   lab2.actual=NULL;
   lab2.sig=NULL;
   punto creador;
   creador.x=0;
   creador.y=0;
   push(lab2.actual,creador);
   return lab2;
}


maze labe4(){
maze lab2;
   int algo[17][17] ={{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-5},{-1,-1,-1,-1,-1,-6,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1},{0,0,0,-1,0,0,0,0,0,-1,0,0,0,0,0,0,-21},{-16,-1,0,0,0,0,0,-1,0,0,0,-1,-1,0,0,0,0},{-1,-1,-1,-1,0,-1,-1,-1,-1,0,-1,-1,-1,0,-1,-1,-1},{-1,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,0},{-11,-10,0,0,0,0,-1,0,0,0,0,0,-1,-1,-1,0,0},{-1,-1,-1,0,0,0,-1,-1,-1,-1,-14,-1,-1,0,0,0,0},{-17,0,-1,-1,0,-1,-1,0,0,0,0,0,0,0,-1,-1,-1},{0,0,-1,0,-1,-1,-1,-15,-1,0,0,0,-1,0,0,0,0},{0,0,-1,0,0,0,-1,-1,-1,0,-1,-1,-1,0,0,0,0},{0,-8,-9,-1,0,0,0,-1,0,0,0,0,-1,-1,-1,-1,-1},{0,0,-1,0,0,0,0,-1,-1,-1,-1,0,-1,0,0,0,-7},{0,0,-1,0,-1,-1,-1,-1,0,-1,-1,0,0,0,-1,-1,-1},{-1,-1,-1,0,0,0,0,-1,0,-1,-1,0,-1,-1,-1,0,-13},{0,0,-18,0,0,-1,-1,-1,0,-22,0,0,-12,0,-1,-1,0},{-19,0,-1,0,0,-1,-2,-20,0,0,0,0,-1,0,0,0,0}};
   lab2.matriz=new int * [17];
   for(int i=0;i<17;i++){
       lab2.matriz[i]= new int [17];
       for(int j=0;j<17;j++){
     

      lab2.matriz[i][j]=algo[j][i];
       }
   }
   
   lab2.hijas=NULL;
   lab2.padre=NULL;
   lab2.move=2;
   lab2.tamx=17;
   lab2.tamy=17;
   lab2.actual=NULL;
   lab2.sig=NULL;
   punto creador;
   creador.x=0;
   creador.y=0;
   push(lab2.actual,creador);
   return lab2;
}
    
int main() {
	char op;
	maze meow=armar();
        formatopre(meow);
	maze temp = labe3();
        bonita(temp,-1,-1);
        //cin>>op;
        //jugar(temp);
        solve(temp,1);
	return 0;
}
