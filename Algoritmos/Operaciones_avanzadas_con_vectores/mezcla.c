/*
*Algoritmo de mezcla
*-Autor: Víctor Zacarías.
*-Utima actualización: 1/08/2021.
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
*Pre-condiciones: La suma de (tope_1 + tope_2) no debe superar MAX_VECTOR.
*Post-condiciones: Guarda la mezcla entre vector_1 y vector_2 en un tercer vector.
*/
void realizar_mezcla(int vector_1[MAX_VECTOR], int tope_1, int vector_2[MAX_VECTOR], int tope_2, int vector_final[MAX_VECTOR], int* tope_final){

	int i = 0;
	int j = 0;
	(*tope_final) = 0;

	while((i < tope_1) && (j < tope_2)){

		if(vector_1[i] <= vector_2[j]){

			vector_final[(*tope_final)] = vector_1[i];
			i++;
		}
		else{

			vector_final[(*tope_final)] = vector_2[j];
			j++;
		}	

		(*tope_final)++;
	}

	while(i < tope_1){
		vector_final[(*tope_final)] = vector_1[i];
		i++;
		(*tope_final)++;
	}

	while(j < tope_2){
		vector_final[(*tope_final)] = vector_2[j];
		j++;
		(*tope_final)++;
	}

}


int main(){

	int vector_1[MAX_VECTOR] = {2,4,6,8,10,12};
	int tope_1 = 6;

	int vector_2[MAX_VECTOR] = {1,3,5,7};
	int tope_2 = 4;

	int vector_final[MAX_VECTOR];
	int tope_final;

	printf("--------------------------------------------------------\n");
	printf("Demostración de algoritmo de mezcla entre dos vectores:\n\n");
	printf("Vector 1: ");
	mostrar_vector_por_pantalla(vector_1, tope_1);
	printf("\n");
	printf("Vector 2: ");
	mostrar_vector_por_pantalla(vector_2, tope_2);
	printf("\n\n");

	realizar_mezcla(vector_1, tope_1, vector_2, tope_2, vector_final, &tope_final);
	printf("EL TOPE DEL VECTOR MEZCLA ES %i\n", tope_final);
	printf("Vector mezcla: ");
	mostrar_vector_por_pantalla(vector_final, tope_final);
	printf("\n");
	printf("--------------------------------------------------------\n");

	return 0;
}