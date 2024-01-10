/*
*Algoritmo de ordenaminto: Inserción.
*Hecho por: Víctor Zacarías.
*Ultima actualización: 23/07/2021.
*/
#include<stdio.h>
	
#define MAX_VECTOR 9


/*
*Pre-condiciones: vector no puede estar vacio.
*Post-condiciones: Muestra por pantalla el contenido de vector.
*/
void imprimir_vector(int vector[MAX_VECTOR], int tope){

	printf("[");

	for(int i = 0; i < tope; i++){

		printf("%i;", vector[i]);
	}

	printf("]\n");
}


/*
*Pre-condiciones:
*-vector debe estar ordenada, de lo contrario el comportamiento de la función es indefinido.
*-tope debe ser menor a MAX_VECTOR.
*Post-condiciones: Inserta un número en un vector ordenando, manteniendo el orden del mismo.
*/
void insercion_ordenada(int vector[MAX_VECTOR], int* tope, int inserto){

	int i = (*tope);
	int auxiliar;

	while((i > 0) && (inserto < vector[i-1])){

		auxiliar = vector[i-1];
		vector[i] = auxiliar;
		i--;
	}

	vector[i] = inserto;
	(*tope)++;
}


int main(){

	int vector_de_trabajo[MAX_VECTOR] = {4,8,12,16,20,24,28,32};
	int tope = 8;
	int inserto;

	printf("Dispone del siguiente vector: ");
	imprimir_vector(vector_de_trabajo, tope);
	printf("Selccione el número que desea insertar en el vector (0-33): ");
	scanf("%i", &inserto);
	while((inserto < 0) || (inserto > 33)){
		printf("Seleccionó un número fuera de rango, por favor, ingreselo de nuevo (0-33): ");
		scanf("%i", &inserto);
	}

	insercion_ordenada(vector_de_trabajo, &tope, inserto);
	printf("\nVector actualizado: ");
	imprimir_vector(vector_de_trabajo, tope);

	return 0;
}
