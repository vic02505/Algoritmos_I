/*
*Algoritmo de ordenaminto: Selección.
*Hecho por: Víctor Zacarías.
*Ultima actualización: 18/07/2021.
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX_VECTOR 10


/*
*Pre-condiciones: No tiene.
*Post-condiciones: Devuelve un número aleatorio entre 0 y 20.
*/
int numero_aleatorio(){

	return(rand()%21);
}


/*
*Pre-condiciones: No tiene.
*Post-condiciones: Carga todas las posiciones de vector con un número aleatorio entre 0 y 20.
*/
void cargar_vector_aleatoriamente(int vector[MAX_VECTOR]){

	for(int i = 0; i < MAX_VECTOR; i++){

		vector[i] = numero_aleatorio();
	}
}


/*
*Pre-condiciones: vector no puede estar vacio.
*Post-condiciones: Muestra por pantalla el contenido de vector.
*/
void imprimir_vector(int vector[MAX_VECTOR]){

	printf("[");

	for(int i = 0; i < MAX_VECTOR; i++){

		printf("%i;", vector[i]);
	}

	printf("]\n");
}


/*
*Pre-condiciones: vector no puede estar vacio.
*Post-condiciones: Ordena ascendentemente cada uno de los elementos de vector.
*/
void algoritmo_de_sleccion(int vector[MAX_VECTOR]){

	int minimo;
	int auxiliar;

	for(int i = 0; i < MAX_VECTOR-1; i++){

		minimo = i;

		for(int j = (i+1); j < MAX_VECTOR; j++){

			if(vector[minimo] > vector[j]){

				minimo = j;				
			}
		}

		auxiliar = vector[i];
		vector[i] = vector[minimo];
		vector[minimo] = auxiliar;

	}
}


int main(){

	srand((unsigned)time(NULL));

	int vector_a_ordenar[MAX_VECTOR];

	cargar_vector_aleatoriamente(vector_a_ordenar);

	printf("Vector antes del ordenamiento:\n");
	imprimir_vector(vector_a_ordenar);

	printf("\nVector despues del ordenamiento:\n");
	algoritmo_de_sleccion(vector_a_ordenar);
	imprimir_vector(vector_a_ordenar);

	return 0;
}