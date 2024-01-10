/*
*-Algoritmo de intersección:
*-Autor: Víctor Zacarías:
*-Ultima actualización: 1/08/2021.
*/
#include<stdio.h>

#define MAX_VECTOR 100

/*
*Pre-condiciones: tope debe ser menor o igual que MAX_VECTOR.
*Post-condiciones: Muestra por pantalla cada uno de los elementos de vector.
*/
void mostrar_vector_por_pantalla(int vector[MAX_VECTOR], int tope){

	printf("[");

	for(int i = 0; i < tope; i++){	

		printf("%i;", vector[i]);
	}

	printf("]");
}


/*
*Pre-condiciones:
*Post-condiciones:
*/
void realizar_interseccion(int vector_A[MAX_VECTOR], int tope_A, int vector_B[MAX_VECTOR], int tope_B, int vector_final[MAX_VECTOR], int* tope_final){

	int i = 0;
	int j = 0;
	(*tope_final) = 0;

	while((i < tope_A) && (j < tope_B)){

		if(vector_A[i] == vector_B[j]){
			vector_final[(*tope_final)] = vector_A[i];
			(*tope_final)++;
			i++;
			j++;
		}
		else if(vector_A[i] < vector_B[j]){
			i++;
		}
		else{
			j++;
		}

	}

}


int main(){

	int vector_A[MAX_VECTOR] = {2,4,6,8,10,12,14,16,18};
	int tope_A = 9;

	int vector_B[MAX_VECTOR] = {1,2,3,4,5,6,7,8,9,10,12,14};
	int tope_B = 12;

	int vector_final[MAX_VECTOR];
	int tope_final;

	printf("-----------------------------------------------------\n");
	printf("DEMOSTRACIÓN DE ALGORITMO DE INTSERCCIÓN DE VECTORES\n\n");
	printf("Vector A:");
	mostrar_vector_por_pantalla(vector_A, tope_A);
	printf("\n");
	printf("Vector B: ");
	mostrar_vector_por_pantalla(vector_B, tope_B);
	printf("\n\n");
	realizar_interseccion(vector_A, tope_A, vector_B, tope_B, vector_final, &tope_final);
	printf("La intersección de A con B es: ");
	mostrar_vector_por_pantalla(vector_final, tope_final);
	printf("\n");
	printf("-----------------------------------------------------\n");

	return 0;
}