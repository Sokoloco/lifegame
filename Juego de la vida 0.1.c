/*
 * Juego de la vida 0.1.c
 * 
 * Copyright 2016 Luis <luis@luis-VirtualBox>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h> //libreria estandar de c
#include <stdlib.h>//libreria con la cual sirve l malloc

#define chances 2 //manera rapida y conveniente de definir los chances de la vida de una celula
int malla = 0; //Es booleano decide si la malla se imprime o no

struct listaVida{
	int pos; //una asignacion de posicion ya on se utilizara es para debuguear
	struct listaVida *previo;
	int vivo;
	struct listaVida *siguiente;	
	}; //estructura de lista doblemente enlazada para guardar la lista de las celulas

struct listaVida* crearNodo(int i); //funcion de cracion de nodo (i determina la poscicion)
void crearLista(struct listaVida** cabeza, int i); //crea la lista como tal, se basa en la creacion de nodos (cabeza es una referencia a la Cabeza, y i es la posiocion)
void nextStage(struct listaVida* cabeza, int x, int y); //corre al siguiente paso de la vida de la malla celulas (referencia a cabeza y ancho yaltura respectivamente)
int casoEsquinaIzq(int x, struct listaVida* casoAct); //caso de una celula en la izquierda(ancho y el caso actual para determinar si vive o muere)
int casoEsquinaDer(int x, struct listaVida* casoAct); //caso de una celula a la derecha(ancho y el caso actual para determinar si vive o muere)
int casoDemas(int x,struct listaVida* casoAct); //todos los demas casos de celulas(ancho y el caso actual para determinar si vive o muere)

int main(int argc, char **argv){
	int width=0,height=0; //ancho y tamanho repectivamente de la lista
	char end[2]; //variable que para el recorrimiento de las vidas
	while((width <7 || height <7)){ //determina el tamanho de la lista el while se cumple hasta que se ingrese dos valores validos
	printf("El minimo de tamaño es 7X7 \n Indique el ancho de la lista: ");
	scanf("%d",&width); //llena el ancho de la lista
	printf("Indique el alto de la lista: ");
	scanf("%d",&height); //llena el alto de la lista
	}
	printf("¿Desea utilizar malla?(Ingrese 'y' para utilizar malla)");
	getchar(); //admite un valor para que pare rl ingreso de datos
	if(getchar() == 'y') //si se ingersa y se utiliza la malla sino no
		malla = 1; //booleano de malla a verdadero
	struct listaVida* Cabeza = NULL; // crea la cabeza de lalista
	for(int i = 0;i<width*height;i++){
		crearLista(&Cabeza, i); //crea la lista completa con base a la altura y anchura de la misma
	}
	end[1]= ' '; //pone a la condicion de terminacion en NULL
	for(int i;end[1] != 'y';i++){ //for infinito el cual mantiene la lista siguiendo
		struct listaVida* corrida = Cabeza; //asigna una variable a cabeza la cual se utiliza pra un corrida de impresion
		for(int i = 1;;corrida = corrida->siguiente,i++){
		printf("%d",corrida->pos);
		if(malla == 1) //validacion de malla
			printf("[");
		if(corrida->vivo == 1)
			printf("*"); // * si esta viva
		else
			printf(" "); //vacio si no esta viva 
		if(malla == 1) //cierra la malla si esta es verdadera
		printf("]");
		if(i%width == 0) //el i se compara con el ancho si esta produce 0 significa que se debe comenzar la siguiente fila
			printf("\n");
		if(corrida->siguiente == NULL) //condicion de parada adonde no hay mas lista
			break;
			}
		nextStage(Cabeza,width,height); //pone al siguiente paso
		printf("\nDesea terminar (Ingrese 'y' para terminar)\n");
		printf("Presione enter para el proximo estado\n");
		end[1]= getchar(); //toma un char que le agrega al end[1] si y esto signfica condicion de parada
		system("clear"); //limpia la salida
	}
	return 0;
}

struct listaVida* CrearNodo(int i) { //int i seria la posicion
 struct listaVida *ptr; //ptr desechable que se retornara
 
 ptr = (struct listaVida*)malloc(sizeof(struct listaVida)); //asigna un espacion para el nodo
 if(rand()%4>chances) //condicion al azar para determinar si una celula esta viva o muerta
	ptr->vivo = 1; //si se cumple se determina viva
else //si no se defina muerta
	ptr->vivo = 0; //muerta
	ptr->pos = i; //se le asigna una posiocion, est es para debuguear ya no se utilizara
 ptr->siguiente = ptr->previo = NULL;
 return ptr; //retorna el puntero
}
 

void crearLista(struct listaVida** cabeza, int i){
 struct listaVida* Nuevo; //puntero basuapara el cual se le pondra el nuevo nodo
 
 Nuevo = CrearNodo(i); //manda la poscion de i para poder determinar la posicion (ya no se utiliza)
 Nuevo->siguiente = *cabeza; //asigna la posion siguiente del nuevo nodo a cabeza
 Nuevo->previo = NULL; //pero el previo a nulo
 if (*cabeza != NULL) //si no es el primer nodo se determina que el previo es cabeza
	 (*cabeza)->previo = Nuevo; //asigna anterior a cabeza
 *cabeza = Nuevo; //nuevo se vuelve cabeza
}


int casoEsquinaIzq(int x, struct listaVida* casoAct){ //caso izq
	int lives = 0; //variable quedetermina cuantas celulas vivas hay alrededor
	struct listaVida* adel; //posicion que se recorrera para adelante
	struct listaVida* atras; //posicion que se recorrera para atras
	int ignorarT = 0, ignorarD = 0; //condicion booleana que determina si ya no hay posicion atras o adelante
	adel = atras = casoAct; //asigna los primeros valores de la recorrida al caso actual 
	adel = adel->siguiente; //pone adelante a adel
	if(adel->vivo == 1) //si se cumple que esta posicion esta viva se le agrega al entero que determina si vive o muere
		lives++; //se le agrega a la variable
	for(int i = 1;i!=x;i++){ //va a la posicion debajo y arriba del caso actual
		if(adel->siguiente!=NULL) //se le asigna si hay un siguiente
			adel = adel->siguiente;
		else //sino se ignora el resultado 
			ignorarD = 1;
		if(atras->previo!=NULL) //se le asigna si hay un anterior
			atras = atras->previo;
		else //sino se ignora el resultado 
			ignorarT = 1;
		}
		for(int iL = 0;iL<2;iL++,atras = atras->previo){ //ciclo que determina la poscion abajo y abajo derecha
			if(ignorarT !=0) //si se cumple la condicion booleana se ignora quiere decir que no hay previo
				break;
			if(atras->vivo == 1) // si hay una celula viva se le agrega a la vida
				lives++;
		}
		for(int iL = 0;iL<2;iL++,adel = adel->siguiente){//ciclo que determina la poscion arriba y arriba derecha
			if(ignorarD !=0)//si se cumple la condicion booleana se ignora quiere decir que no hay siguiente
				break;
			if(adel->vivo == 1)// si hay una celula viva se le agrega a la vida
				lives++;
		}
	return lives; //retorna si la celula vive o no
}
int casoEsquinaDer(int x, struct listaVida* casoAct){//caso izq
	int lives = 0; //variable quedetermina cuantas celulas vivas hay alrededor
	struct listaVida* adel;//posicion que se recorrera para adelante
	struct listaVida* atras;//posicion que se recorrera para atras
	int ignorarT = 0, ignorarD = 0;//condicion booleana que determina si ya no hay posicion atras o adelante
	adel = atras = casoAct;//asigna los primeros valores de la recorrida al caso actual 
	atras = atras->previo; //pone al trasero para atras no hay siguiente
	if(atras->vivo == 1) //si esta viva la celula le agrega a la variable si vive
		lives++;
	for(int i = 1;i!=x;i++){ //ciclo que pone las variables arriba y abajo de la celula actual
		if(adel->siguiente!=NULL) //si el diguiente es difrente de null se le asigna ese a siguiente
			adel = adel->siguiente;
		else //si no se ignora el resultado
			ignorarD = 1;
		if(atras->previo!=NULL) //si hay un previo se le asigna a este
			atras = atras->previo;
		else //sino se ignora el resultado
			ignorarT = 1;
		}
		for(int iL = 0;iL<2;iL++,atras = atras->previo){ //ciclo que mueve la posicion una al lado
			if(ignorarT !=0) //se evalua que no se ignore elresultado
				break;
			if(atras->vivo == 1) //si esta vivo se le agrega a la variable determinante
				lives++;
		}
		for(int iL = 0;iL<2;iL++,adel = adel->siguiente){ //ahora se hace para adelatne
			if(ignorarD !=0) //confrima que no se ignore el resultado
				break;
			if(adel->vivo == 1) //si esta vivo se le agrega a la variable determinante
				lives++;
		}
	return lives; //retorna si vive o no
}
int casoDemas(int x, struct listaVida* casoAct){ //cualquier otro caso (los del medio van aqui)
	struct listaVida* adel; //variable de corrida adelante
	struct listaVida* atras; //variable corrida atras
	adel = atras = casoAct; //se le asignan al caso actual
	int live = 0; //determinante
	int ignorarTra = 0, ignorarDelant = 0; //condiciones booleanas de resultado omitido
	adel = adel->siguiente; //siempre va a haber un siguiente se le asigna a este
	if(adel->vivo == 1)//si esta vivo se le agrega al determinente
		live++;
	atras = atras->previo; //siempre va a haber un previo, se le asigna a este
	if(atras->vivo == 1)//si esta vivo se le agrega al determinente
		live++;
	for(int i2 = 2; i2<x; i2++){ //elige las posiciones a tomar x veces adelante y atras
			if (atras->previo !=NULL) //si se puede elegir el siguiente se le asigna
				atras = atras->previo;
			else // si no se pudo elegir la siguiente cambia se ignara el resultado
				ignorarTra = 1;
			if (adel->siguiente != NULL)//si se cumple se asigna la siguiente
				adel = adel->siguiente;
			else //si no se ignora el resultado
				ignorarDelant = 1;
			}
			for(int iL = 0;iL<3;iL++){ //ciclo que mueve a atras
					if(ignorarTra != 0) //condicion booleana de ignorar o no
						break;
					else if (atras->vivo == 1)//si esta vivo se le asigna al determinante
						live++;
						if (atras->previo !=NULL)//si hay siguiente se le pasa a este
							atras = atras->previo;
						else //si no se termina el ciclo
							break;
						}
				for(int iL = 0;iL<3;iL++){//ciclo que mueve hacia adelante
					if(ignorarDelant != 0)//condicion booleana de ignorar o no
						break;
					else if (adel->vivo == 1) //si hay celula viva aqui se cambia le agrega al determinante
						live++;
						if (adel->siguiente != NULL) //si hay un siguiente se le asgina a este
							adel = adel->siguiente;
						else //si no se termina el ciclo
							break;
		}
	return live; //retorna el determinante
}

void nextStage(struct listaVida* cabeza,int x, int y){ //pone a la siguiente fase
	int toCambiar[x*y]; //lista a la cual se le pone la siguiente fase
	struct listaVida* recorrida = cabeza; //se le asigna la cabeza a la primer recorrida
	for(int i = 0;;recorrida = recorrida->siguiente,i++){
		int lives = 0; //condicion determinante si vive o no
		/*Los siguientes tres casos son los 3 posibles casos quese pueden dar
		 * Esquinina Izquierda, donde no tiene previo a la par ni izquierda debajo o arriba
		 * Esquinina Derecha, donde no tiene siguiente a la par ni derecha debajo o arriba
		 * Y los demas, donde si tiene 8 posiciones que evaluar
		 * */
		if(i == 0 || i%x == 0)
			lives = casoEsquinaIzq(x,recorrida);
		else if((i+1)%x == 0)
			lives = casoEsquinaDer(x,recorrida);
		else
			lives = casoDemas(x, recorrida);
			
		if(recorrida ->vivo == 1){//si la celula actual esta viva se evalua con base a 2 y 3
			if(lives == 2 || lives == 3) //si el determinantees 2 o 3 esta sigue viviendo
				toCambiar[i]= 1; //a la poscionde la lista desechable se le pone el valor de muerta o viva
			else
				toCambiar[i] = 0;
			}
		else{//si esta muerta se le evalua con 3
			if (lives == 3) //si el determinante es 3 vive
				toCambiar[i]= 1;
			else //si no muere
				toCambiar[i] = 0;
		}
	if (recorrida->siguiente == NULL) //condicion de parada
		break;
	}
	recorrida = cabeza;// de nuevo recorrida a cabeza pero esta ves para ponerla conjunto a la lista
	for(int i = 0;; i++,cabeza = cabeza->siguiente){ //ciclo para cambiar del arreglo a la lista doblemente enlazada
		cabeza->vivo = toCambiar[i]; //asigna los valores
		 if(cabeza->siguiente == NULL)// si no hay un siguientese para elciclo
			break;
	}
}
