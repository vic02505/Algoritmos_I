//Test de personalidad de Los Osos Escandalosos version 1.0:
#include"test_de_personalidad.h"

#define POLAR 'I'
#define PANDA 'P'
#define PARDO 'G'

#define ANIME 'A'
#define MUSICA_POP 'M'
#define LIMPIEZA 'L'

#define BAMBU  'B'
#define PESCADO 'P'
#define FOCAS 'F'

const int PRIMER_PISO = 1;
const int ULTIMO_PISO = 18;

const int VOLUMEN_GRITO_NULO = 1;
const int VOLUMEN_GRITO_DESGARRADOR = 18;

const int PUNTOS_LIMPIEZA = 1;
const int PUNTOS_ANIME = 2;
const int PUNTOS_MUSICA_POP = 3;

const int PUNTOS_FOCAS = 3;
const int PUNTOS_BAMBU = 6;
const int PUNTOS_PESCADO = 9;

const int PUNTAJE_MINIMO_CORRESPONDIENTE_POLAR =  5;
const int PUNTAJE_MAXIMO_CORRESPONDIENTE_A_POLAR = 24;
const int PUNTAJE_MINIMO_CORRESPONDIENE_A_PANDA = 25;
const int PUNTAJE_MAXIMO_CORRESPONDIENTE_A_PANDA = 43;
const int PUNTAJE_MINIMO_CORRESPONDIENTE_A_PARDO = 44;
const int PUNTAJE_MAXIMO_CORRESPONDIENTE_A_PARDO = 63;


/*
*Pre-condiciones: El parametro debe contener algun valor.
*Post-condiciones: Devuelve true si el puntaje corresponde a Polar y false en caso contrario.
*/
bool es_polar(int puntaje){
	return(puntaje >= PUNTAJE_MINIMO_CORRESPONDIENTE_POLAR) && (puntaje <= PUNTAJE_MAXIMO_CORRESPONDIENTE_A_POLAR);
}


/*
*Pre-condiciones: El parametro debe contener algun valor.
*Post-condiciones: Devuelve true si el puntaje corresponde a Panda y false en caso contrario.
*/
bool es_panda(int puntaje){
	return(puntaje >= PUNTAJE_MINIMO_CORRESPONDIENE_A_PANDA) && (puntaje <= PUNTAJE_MAXIMO_CORRESPONDIENTE_A_PANDA);
}


/*
*Pre-condiciones: El parametro debe contener algun valor.
*Post-condicones: Devuelve true si el puntaje corresonde a Pardo y false en caso contrario.
*/
bool es_pardo(int puntaje){
	return(puntaje >= PUNTAJE_MINIMO_CORRESPONDIENTE_A_PARDO) && (puntaje <= PUNTAJE_MAXIMO_CORRESPONDIENTE_A_PARDO);
}


/*
*Pre-condiciones: El parametro debe contener algun valor.
*Post condiciones: Devuelve true si canal es valido y false en caso contraio.
*/
bool es_canal_valido(char canal){	
	return((canal == ANIME) || (canal == MUSICA_POP) || (canal == LIMPIEZA));
}


/*
*Pre-condiciones: El parametro debe contener algun valor.
*Post condiciones: Devuelve true si alimento es valido y false en caso contrario.
*/
bool es_alimento_valido(char alimento){
	return((alimento == BAMBU) || (alimento == PESCADO) || (alimento == FOCAS));
}


/*
*Pre-condiciones: El parametro debe contener algun valor.
*Post condiciones: DevueLve true si piso es valido y false en caso contrario.
*/
bool es_piso_de_torre_valida(int piso){
	return((piso >= PRIMER_PISO) && (piso <= ULTIMO_PISO));
}


/*
*Pre-condiciones: El parametro debe contener algun valor.
*Post condiciones: Devuelve true si nivel_de_grito es valido y false en caso contario.
*/
bool es_fuerza_de_grito_valida(int nivel_de_grito){
	return((nivel_de_grito >= VOLUMEN_GRITO_NULO) && (nivel_de_grito <= VOLUMEN_GRITO_DESGARRADOR));
}


/*
*Pre-condiciones: No tiene.
*Post-condiciones: Imprime por pantalla un mensaje de bienvenida al usuario.
*/
void dar_la_bienvenida(){

	printf("¡¡HOLA!! Se te da la bienvenida al test de personalidad de Los Osos Escandolosos :),");
	printf(" Para una mejor experiencia se te recomienda usar la terminal en pantalla completa\n\n");
}


/*
*Pre-condiciones: No tiene.
*Post-condiciones: EL procedmiento asignara un valor ingresado por el usuario a la variable mandada por referencia.
*/
void pedir_canal_de_tv(char* canal){

	printf("Vas a ver television por un rato, ¿pones el canal de ANIME (A), MUSICA POP (M), o LIMPIEZA (L)?: ");
	scanf(" %c", canal);
	while(!es_canal_valido(*canal)){
		printf("Ingresaste un valor invalido, por favor, vuelvelo a ingresar, recuerda que las opciones son");
		printf(" Anime (A), MUSICA POP (M), O LIMPIEZA (L): ");
		scanf(" %c", canal);
	}
}


/*
*Pre-condiciones: No tiene.
*Post-condiciones: EL procedmiento asignara un valor ingresado por el usuario a la variable mandada por referencia.
*/
void pedir_alimento(char* alimento){

 	printf("\nSolo podes guadar un alimento en tu vianda, ¿que guardas? Bambu (B), Pescado (P), o Focas (F): ");
	scanf(" %c", alimento);
	while(!es_alimento_valido(* alimento)){
		printf("Ingresaste un valor invalido, por favor, vuelvelo a ingresar, recuerda que las opciones son");
		printf(" Bambu (B), Pescado (P), o Focas (F): ");
		scanf(" %c", alimento);
	}
}


/*
*Pre-condiciones: No tiene.
*Post-condiciones: EL procedmiento asignara un valor ingresado por el usaurio a la variable mandada por referencia.
*/
void pedir_piso_de_torre(int* piso){

	printf("\nTe compras una torre de %i pisos con tu dos hermanos, ¿En que piso te gustaría vivir? (%i-%i): ", ULTIMO_PISO, PRIMER_PISO, ULTIMO_PISO);
	scanf("%i", piso);
	while(!es_piso_de_torre_valida(*piso)){
		printf("Ingresaste una valor invalido, por favor, vuelvelo a ingresar, (%i-%i): ", PRIMER_PISO, ULTIMO_PISO );
		scanf("%i", piso);
	}
}


/*
*Pre-condiciones: No tiene.
*Post-condiciones: EL procedmiento asignara un valor ingresado por el usuario a la variable mandada por referencia.
*/
void pedir_nivel_de_grito(int* nivel_de_grito){

	printf("\n¡Oh, una rata! ¿Que tan fuerte gritas del %i al %i?: ", VOLUMEN_GRITO_NULO, VOLUMEN_GRITO_DESGARRADOR);
	scanf("%i", nivel_de_grito);
	while(!es_fuerza_de_grito_valida(*nivel_de_grito)){
		printf("Ingresaste un valor invalido, por favor, vuelvelo a ingresar (%i-%i): ", VOLUMEN_GRITO_NULO, VOLUMEN_GRITO_DESGARRADOR);
		scanf("%i", nivel_de_grito);		
	}
}


/*
*Pre-condiciones: EL parametro mandado a la funcion solo puede tener los siguientes valores: Anime(A), Muisca Pop (M) o Limpieza (L).
*Post-condiciones: La funcion devuelve un valor que representa un puntaje por el parametro mandado.
*/
int puntaje_por_canal_de_television(char canal){

	int puntaje = 0;

	switch(canal){

		case LIMPIEZA:
		puntaje = PUNTOS_LIMPIEZA;
		break;

		case ANIME:
		puntaje = PUNTOS_ANIME;
		break;

		case MUSICA_POP:
		puntaje = PUNTOS_MUSICA_POP;
		break;
	}

	return puntaje;
}


/*
*Pre-condiciones: El parametro mandado a la funcion solo puede tener los siguientes valores, Focas(F), Bambu(B), o Pescado(P)
*Post-condiciones: La función devuelve un valor que representa el puntaje por el parametro mandado.
*/
int puntaje_por_alimento(char alimento){

	int puntaje = 0;

	switch(alimento){

		case FOCAS:
		puntaje = PUNTOS_FOCAS;
		break;

		case BAMBU:
		puntaje = PUNTOS_BAMBU;
		break;

		case PESCADO:
		puntaje = PUNTOS_PESCADO;
		break;
	}

	return puntaje;
}


/*
*Pre-condiciones: La funcion espera recibir como parametro un numero en el siguiente rango (1-18).
*Post-condicones: La funcion devuelve un valor que representa un puntaje por el parametro recibido.
*/
int puntaje_por_piso_de_edificio(int piso){

	int puntaje = piso;

	return puntaje;
}


/*
*Pre-condiciones: La funcion espera recibir como parametro un numero en el siguiente rango (1-18).
*Post-condiciones: La funcion devuelve un valor que representa un puntaje por el parametro recibido.
*/
int puntaje_por_fuerza_de_grito(int fuerza_de_grito){

	int puntaje = fuerza_de_grito;

	return puntaje;
}


/*
*Pre-condiciones: Los parametros usados deben haber sido previamente calcuados por la funcones a las sus nombres hacen referencia.
*Post condiciones: La funcion devuelve un valor que representa el puntaje total por los parametros ingresados.
*/
int puntaje_total(int puntaje_por_alimento, int puntaje_por_canal_de_tv, int puntaje_por_piso, int puntaje_por_fuerza_de_grito){
	
	return((puntaje_por_alimento*puntaje_por_canal_de_tv) + puntaje_por_piso + puntaje_por_fuerza_de_grito);
}


/*
*Pre-condiciones: El puntaje total debe ser previamente calculado por la funcion puntaje_total
*Post-condiciones: Devuelve un personaje segun el puntaje_total mandado como parametro.
*/
void determinar_personaje(int puntaje_total, char* personaje){

	if(es_polar(puntaje_total)){
		*personaje = POLAR;
	}
	else if(es_panda(puntaje_total)){
		*personaje = PANDA;
	}
	else if(es_pardo(puntaje_total)){
		*personaje = PARDO;
	}	
}


/*
*Pre-condiciones: El parametro personaje solo puede contener los siguientes valores: Polar (I), Panda (P), Pardo (G).
*Pos-condiciones: Imprime por pantalla una oracion anunciando el personaje.
*/
void decir_personaje(char personaje){

	switch(personaje){

		case POLAR:
		printf("\nSe determino que eres - Polar (%c) -", POLAR);
		break;

		case PANDA:
		printf("\nSe determino que eres - Panda (%c) -", PANDA);
		break;

		case PARDO:
		printf("\nSe determino que eres - Pardo (%c) -", PARDO);
		break;
	}
}


/*
*
*
*/
void test_de_personalidad(char* personalidad_detectada){

	char canal_de_television;
	char alimento_guardado;
	int piso_de_edificio;
	int fuerza_de_grito;


	int multiplicador_por_canal_de_television = 0;
	int puntos_por_alimento_guardado = 0;
	int puntos_por_piso_de_edificio = 0;
	int puntos_por_fuerza_de_grito = 0;
	int puntos_totales = 0;

	char personaje = '0';

	dar_la_bienvenida();
	pedir_canal_de_tv(&canal_de_television);
	pedir_alimento(&alimento_guardado);
	pedir_piso_de_torre(&piso_de_edificio);
	pedir_nivel_de_grito(&fuerza_de_grito);

	multiplicador_por_canal_de_television = puntaje_por_canal_de_television(canal_de_television);
	puntos_por_alimento_guardado = puntaje_por_alimento(alimento_guardado);
	puntos_por_piso_de_edificio = puntaje_por_piso_de_edificio(piso_de_edificio);
	puntos_por_fuerza_de_grito = puntaje_por_fuerza_de_grito(fuerza_de_grito);
	puntos_totales = puntaje_total(puntos_por_alimento_guardado, multiplicador_por_canal_de_television, puntos_por_piso_de_edificio, puntos_por_fuerza_de_grito);
	
	determinar_personaje(puntos_totales, &personaje);
	(*personalidad_detectada) =  personaje;
	decir_personaje(personaje);
	
}


