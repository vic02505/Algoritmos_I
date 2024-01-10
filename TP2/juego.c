#include<time.h>
#include<stdlib.h>
#include"osos_contra_reloj.h"
#include"test_de_personalidad.h"
#include"utiles.h"

const static char TIEMPO_TRNASCURRIDO = 'T';

/*
*Pre-condiciones: No tiene.
*Post-condiciones: Inicializa la variable jugada con algun valor valido.
*/
void pedir_accion(char* jugada){

	printf("\n\n¿Que movimiento deseea realizar? W: arriba, A: izquierda, S: abajo, D: derecha, L: linterna, V: vela, E: bengala, T: tiempo: ");
	scanf(" %c", jugada);
	while(!es_jugada_valida(*jugada)){

		printf("\n¿Que movimiento deseea realizar? W: arriba, A: izquierda, S: abajo, D: derecha, L: linterna, V: vela, E: bengala, T: tiempo: ");
		scanf(" %c", jugada);
	}
}

/*
*Pre-condiciones: No tiene.
*Post-condiciones: Deveulve true si se termino el juego, y false en caso contrario.
*/
bool se_termino_el_juego(juego_t juego){

	bool finalizo_el_juego = false;

	if(estado_juego(juego) == -1){

		finalizo_el_juego = true;
	}

	return finalizo_el_juego;
}

/*
*Pre-condiciones: No tiene.
*Post-condiciones: Imprime por pantalla si se gano o se perdio el juego dependiedo del tiempo_perido_total.
*/
void anunciar_final_del_juego(double tiempo_perdido_total){

	if(tiempo_perdido_total > 120){

		printf("\n\n¡¡PERDISTE!!\n\n");
	}else{

		printf("\n\n¡¡GANASTE!!\n\n");
	}

}


int main(){

	srand((unsigned)time(NULL));

	juego_t juego;

	char personalidad;
	char jugada = '0'; 

	double tiempo_transcurrido = 0; 
	double tiempo_perdido_total = 0;

	test_de_personalidad(&personalidad);
	inicializar_juego(&juego, personalidad);
	iniciar_cronometro();

	while(!se_termino_el_juego(juego)){ 

		system("clear");

		mostrar_juego(juego);

		if(jugada == TIEMPO_TRNASCURRIDO){

			printf(" %f", tiempo_actual());
		}	

		pedir_accion(&jugada);

		if(jugada != TIEMPO_TRNASCURRIDO){
			realizar_jugada(&juego, jugada);
		}		
	}	



	tiempo_transcurrido = tiempo_actual();
	detener_cronometro();

	tiempo_perdido_total = (juego.personaje.tiempo_perdido) + tiempo_transcurrido;

	anunciar_final_del_juego(tiempo_perdido_total);
		
	return 0;
}