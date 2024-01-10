/*
*-Algoritmos de diferencia:
*-Autor: Víctor Zacarías.
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
void realizar_diferencia_A_menos_B(int vector_A[MAX_VECTOR], int tope_A, int vector_B[MAX_VECTOR], int tope_B, int vector_diferencia[MAX_VECTOR], int* tope_diferencia){

	int i = 0;
	int j = 0;
	(*tope_diferencia) = 0;

	while((i < tope_A) && (j < tope_B)){

		if(vector_A[i] == vector_B[j]){
			i++;
			j++;
		}
		else if(vector_A[i] < vector_B[j]){
			vector_diferencia[(*tope_diferencia)] = vector_A[i];
			i++;
			(*tope_diferencia)++;
		}
		else{
			j++;
		}

	}

	while(i < tope_A){

		vector_diferencia[(*tope_diferencia)] = vector_A[i];
		i++;
		(*tope_diferencia)++;
	}

}


int main(){

	int vector_A[MAX_VECTOR] = {2,4,6,8,10,12,14};
	int tope_A = 7;

	int vector_B[MAX_VECTOR] = {3,5,6,9,12,13};
	int tope_B = 6;

	int vector_diferencia[MAX_VECTOR];
	int tope_diferencia;

	printf("-----------------------------------------------------------------------\n");
	printf("ESTA ES UNA DEMOSTRACIÓN DEL ALGORITMO DE DIFERENCIA ENTRE DOS VECTORES\n\n");
	printf(" Descripción: Se realizara la diferencia de (A-B)\n");
	printf(" La diferencia de (A-B) es igual a un vector que \n ");
	printf("contiene los elementos de A que no están en B.\n\n");
	printf("Vector A: ");
	mostrar_vector_por_pantalla(vector_A, tope_A);
	printf("\n");
	printf("Vector B: ");
	mostrar_vector_por_pantalla(vector_B, tope_B);
	printf("\n");
	realizar_diferencia_A_menos_B(vector_A, tope_A, vector_B, tope_B, vector_diferencia, &tope_diferencia);
	printf("\n");
	printf("Vector diferencia: ");
	mostrar_vector_por_pantalla(vector_diferencia, tope_diferencia);
	printf("\n");
	printf("-----------------------------------------------------------------------\n");
	printf("\n");

	return 0;
}