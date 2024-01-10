/*
*Algoritmo de ordenaminto: Burbujeo.
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
*Pre-condiciones: vector no puede venir vacio.
*Post-condiciones:ordena ascendentemente todos los elementos de vector:
*/
void algoritmo_de_insercion(int vector[MAX_VECTOR]){

	int i,j,auxiliar;

	for(int i = 1; i < MAX_VECTOR; i++){

		j= i;
		auxiliar = vector[i];

		while((j > 0) && (auxiliar < vector[j-1])){

			vector[j] = vector[j-1];
			j--;
		}

		vector[j] = auxiliar;
	}
}


int main(){

	srand((unsigned)time(NULL));

	int vector_a_ordenar[MAX_VECTOR];

	cargar_vector_aleatoriamente(vector_a_ordenar);

	printf("Vector antes del ordenamiento:\n");
	imprimir_vector(vector_a_ordenar);

	printf("Vector despues del ordenamiento:\n");
	algoritmo_de_insercion(vector_a_ordenar);
	imprimir_vector(vector_a_ordenar);

	return 0;
}