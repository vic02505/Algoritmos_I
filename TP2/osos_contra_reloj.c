#include"osos_contra_reloj.h"

#define ARBOL 'A'
#define PIEDRA 'R'
#define KOALA 'K'

#define LINTERNA 'L'
#define VELA 'V'
#define BENGALA 'E'
#define PILA 'B'

#define POLAR 'I'
#define PANDA 'P'
#define PARDO 'G'
#define CHLOE 'C'

#define ARRIBA 'W'
#define IZQUIERDA 'A'
#define ABAJO 'S'
#define DERECHA 'D'
#define TIEMPO_TRANSCURRIDO 'T'

#define MAX_ELEMENTOS 600

#define LARGO_MAPA 20
#define ANCHO_MAPA 30


const int CANTIDAD_DE_ARBOLES = 350;
const int CANTIDAD_DE_PIEDRAS = 80;

const int CANTIDAD_INICIAL_DE_PILAS_EN_EL_MAPA = 30;
const int CANTIDAD_INCIAL_DE_VELAS_EN_EL_MAPA = 30;
const int CANTIDAD_INICIAL_DE_BENGALAS_EN_EL_MAPA = 10;

const int MOVIMIENTOS_INICIALES_LINTERNA_POLAR = 10;
const int MOVIMIENTOS_INICIALES_LINTERNA_PANDA = 10;
const int MOVIMIENTOS_INICIALES_LINTERNA_PARDO = 15;

const int CANTIDAD_INICIAL_DE_VELAS_EN_MOCHILA_POLAR = 6;
const int CANTIDAD_INICIAL_DE_VELAS_EN_MOCHILA_PANDA = 4;
const int CANTIDAD_INICIAL_DE_VELAS_EN_MOCHILA_PARDO = 4;

const int MOVIMIENTOS_VELA = 5;

const int CANTIDAD_INICIAL_DE_BENGALAS_EN_MOCHILA_POLAR = 0;
const int CANTIDAD_INICIAL_DE_BENGALAS_EN_MOCHILA_PANDA = 2;
const int CANTIDAD_INICIAL_DE_BENGALAS_EN_MOCHILA_PARDO = 0;

const int MOVIMEINTOS_BENGALA = 3;

const int COLUMNA_DE_INCIO = 0; 

const double TIEMPO_PERDIDO_ARBOL_POLAR = 1;
const double TIEMPO_PERDIDO_ARBOL_PANDA = 1;
const double TIEMPO_PERDIDO_ARBOL_PARDO = 0.5;

const double TIEMPO_PERDIDO_PIEDRAS_POLAR = 0;
const double TIEMPO_PERDIDO_PIEDRAS_PANDA = 2;
const double TIEMPO_PERDIDO_PIEDRAS_PARDO = 2;

const int FILA_INICIAL = 0;
const int FILA_FINAL = 19;

const int COLUMNA_INCIAL = 0;
const int COLUMNA_FINAL = 29;


/*
*Pre-condiciones: Tanto posicion como bengala deben ser mayores o iguales que -1 y menores que 600.
*Post-condiciones: Devuelve true si posicion_bengala es igual elemento_en_uso, y false en caso de que lo anterior no se cumpla o
*que posicion_bengala sea igual a -1.
*/
bool hay_una_bengala_activa(int posicion_bengala, int elemento_en_uso){

	bool bengala_activa = false;

	if(posicion_bengala == -1){

		bengala_activa = false;
	}
	else if(posicion_bengala == elemento_en_uso){

		bengala_activa = true;
	}
	
	return bengala_activa;
}


/*
*Pre-condiciones:
*-mochila debe haber sido previamente inicializada por el procedimiento inicializar_juego, y debe ser un campo del registro juego.
*-EL valor de posicion_a_eliminar no debe ser <0 o >=600.
*-cantidad_elementos debe ser >= 0 y =< 600.
*Post-condiciones: Elimina una posición del vector de registros, mochila, reepmlazando en el contenido de la posicion a eliminar 
*el contenido de la ultima posicion del vector, y posteriormente reduciendo el tope del mismo.
*/
void eliminar_elemento_de_mochila(elemento_mochila_t mochila[MAX_HERRAMIENTAS], int* cantidad_elementos, int posicion_a_eliminar){

	mochila[posicion_a_eliminar] = mochila[(*cantidad_elementos) - 1];
	(*cantidad_elementos)--;
}


/*
*Pre-condiciones: 
*-mochila y su respectivo tope deben haber sido previamente inciailizados por inicializar_juego, y deben ser campos del reigstro juego.
*-cantidad_elementos debe ser >= 0 y <= 600.
*-tipo_herramienta solo puede valer LINTERNA(L), VELA(V), O BENGALA(E).
*Post-condiciones: Devuelve la posicion de la primera herramienta del tipo buscado, encontrada en el vector de registros, mochila, devuelve 
*-1 en caso de no encontrar nada.
*/
int posicion_de_herramienta_en_mochila(elemento_mochila_t mochila[MAX_HERRAMIENTAS], int cantidad_elementos, char tipo_herramienta){

	int posicion = -1;

	int i = 0;
	while((i < cantidad_elementos) && (posicion == -1)){

		if(tipo_herramienta == mochila[i].tipo){

			posicion = i;
		}

		i++;
	}

	return posicion;
}


/*
*Pre.condiciones:
*-cantidad_elementos debe ser >= 0 y <=600.
*Post-condicones: Dado un vector de elementos del mapa (vector de registros), la función cambia el campo: visible, de cada una 
*de las posiciones del vector de registros a false.
*/
void reiniciar_estado_elementos_del_mapa(elemento_del_mapa_t elemento[MAX_ELEMENTOS], int cantidad_elementos){

	for(int i = 0; i < cantidad_elementos; i++){

		elemento[i].visible = false;
	}

}



/*
*Pre-condiciones: 
*-El contenido del registro posicion nueva debe cumplir con que fil es un número en el rango 0-19,
*y col es un número en el rango 0-29.
*-tope debe sr >=0 y <=600.
*Post-condiciones: Actualiza el vector de posiciones cargandolo con una posición adicional.
*/
void actualizar_vector_de_posicones(coordenada_t vector_de_posiciones[MAX_ELEMENTOS], int* tope, coordenada_t posicion_nueva){

	vector_de_posiciones[(*tope)] = posicion_nueva;
	(*tope)++;

}


/*
*Pre-condiciones:
*-Fila debe estar en el rango 0-19.
*-Columna debe estar en el rango 0-29.
*-tope debe ser mayor que cero y  menor o igual que 600.
*-Los campos del vector_de_posiciones (fil y col) deben cumplir con lo mencionado para fila y columna.
*Post-condiciones: Dado fila y columna y  un vector de posiciones con su tope, la función devuelve true, si estas posiciones no coinciden
*con niguna posicion del vector de posiciones, y false en caso de si lo hagan.
*/
bool es_posicion_unica(coordenada_t vector_de_posiciones[MAX_ELEMENTOS], int tope, int fila, int columna){

	bool es_unica = true;

	int i = 0;
	while((i < tope) && (es_unica == true)){

		if((fila == vector_de_posiciones[i].fil) && (columna == vector_de_posiciones[i].col)){

			es_unica = false;
		}

		i++;
	}


	return es_unica;
}


/*
*Pre_condiciones: x debe pertenecer al rango 0-19, y debe pertenecer al rango 0-29.
*Post-condiciones: Dada dos coordenadas (x1,y1) y (x2,y2), la función calcula y devuelve la distancia Manahttan entre ellas.
*/
int distancia_manhtattan(int x1, int y1,  int x2, int y2){

	return(abs(x1-x2) + abs(y1-y2));
}

/*
*Pre-condiciones: No tiene.
*Post-condiciones: Devuelve un número aleatorio entre 0-19.
*/
int fila_aleatoria(){

	return(rand()%20);
}


/*
*Pre-condiciones: No tiene.
*Post-condiciones: Devuelve un número aleatorio entre 0-29.
*/
int columna_aleatoria(){

	return(rand()%30);
}


/*
*Pre-condiciones:
*-EL vector de elementos y su tope deben ser previamente incializados por el procedimiento incializar_juego. Los mismos deben ser campos
*del registro juego.
*-cantidad_de_elementos debe ser mayor que 0 y menor o igual que 600.
*-fila debe ser un número en el rango 0-19.
*-columna debe ser un número en el rango 0-29.
*Post-condiciones:
*-Dado un vector de elementos del mapa, su tope, y una posición (fila, columna), devuelve true si esta posicion colisiona (coincide)
*con algunas de las posiciones contenida en el vector de elementos, y false en caso contrario. 
*/
bool hubo_colision(elemento_del_mapa_t elemento[MAX_ELEMENTOS], int cantidad_de_elementos, int fila, int columna){

	bool colision = false;

	int i = 0;
	while((i < cantidad_de_elementos) && (colision == false)){

		if((fila == elemento[i].posicion.fil) && (columna == elemento[i].posicion.col)){

			colision = true;
		}

		i++;

	}

	return colision;
}


/*SOLO USAR SI PREVIAMANTE SE SABE QUE SE PRODUJO UNA COLISION!!! -> Esto lo determina la función hubo_colision.
*Pre-condiciones: fila debe estar en el rango 0-19,  y columna debe estar en el ragno 0-29
*Post_condiciones: Devuelve el tipo de objeto con el que se produjo una colisión.
*/
char tipo_de_objeto_colisionado(elemento_del_mapa_t elemento[MAX_ELEMENTOS], int cantidad_de_elementos, int fila, int columna){

	char tipo = '0';

	bool colision = false;

	int i = 0;
	while((i < cantidad_de_elementos) && (colision == false)){

		if((fila == elemento[i].posicion.fil) && (columna == elemento[i].posicion.col)){

			colision = true;
			tipo = elemento[i].tipo;
		}

		i++;

	}

	return tipo;
}




/*SE RECOMIENDA USARLA SOLO SI PREVIAMANTE SE SABE QUE SE PRODUJO UNA COLISION!!!-> Esto lo determina la función hubo_colision.
*Pre-condiciones:
*-El vector de registros de tipo elemento_del_mapa_t junto con su tope, deben haber sido inicalizados previamente por el procedimento
*inicalizar_juego, ademas de ser campos del registro juego.
*-fila debe ser un número en el rango 0-19.
*-columna debe ser un número en el rango 0-29.
*Post-condiciones:
*-En caso de haber una colision entre elemento y la posicion (fila y columna), la función devuelve la posición donde se 
*produjo la colisión, en caso contrario devuelve -1; 
*/
int posicion_de_colision(elemento_del_mapa_t elemento[MAX_ELEMENTOS], int cantidad_de_elementos, int fila, int columna){

	int posicion = -1;

	int i = 0;
	while((i < cantidad_de_elementos) && (posicion == -1)){

		if((fila == elemento[i].posicion.fil) && (columna == elemento[i].posicion.col)){

			posicion = i;
		}

		i++;
	}

	return posicion;
}


/*
*Pre-condiciones:
*-El vector de registros de tipo elemento_del_mapa_t y su tope deben haber sido inicializado previamente por el procedimeinto 
*inicializar_juego. Tambien deben ser campos del registro juego.
*-cantidad_elementos debe ser un numero mayor que 0 y menor o igual que 600
*Post-condiciones: Dada una posición a elimnar, elimina dicha posición del vector de elementos del mapa.
*/
void eliminar_elemento(elemento_del_mapa_t elemento[MAX_ELEMENTOS], int* cantidad_de_elementos, int posicion_a_eliminar){

	if(cantidad_de_elementos > 0){

		elemento[posicion_a_eliminar] = elemento[(*cantidad_de_elementos)-1];
		(*cantidad_de_elementos)--;
	}
}


/*
*Pre-condiciones:
*-tipo_elemento solo puede tener los siguientes valores, PILA(B), VELA(V), BENGALA(E).
*-elementos_a_agregar no puede superar el tamanio de la mochila (600), y no puede ser 0.
*-La suma se elementos_a_agregar con cantidad_elementos no debe ser mayor que 600.
*Post-condiciones: Carga la mochila segun un tipo_elemento y la cantidad de elemetnos a agregrar.
*/
void agregar_elemento_a_mochila(elemento_mochila_t mochila[MAX_HERRAMIENTAS], int* cantidad_elementos, int tipo_elemento, int elementos_a_agregar){

	if(tipo_elemento == PILA){

		mochila[0].movimientos_restantes += 5;
	}
	else if(tipo_elemento == VELA){

		for(int i = (*cantidad_elementos); i < (*cantidad_elementos) + elementos_a_agregar; i++){

			mochila[i].tipo = VELA;
			mochila[i].movimientos_restantes = MOVIMIENTOS_VELA;
		}

		(*cantidad_elementos) += elementos_a_agregar;
	}
	else if(tipo_elemento == BENGALA){

		for(int i = (*cantidad_elementos); i < (*cantidad_elementos) + elementos_a_agregar; i++){

			mochila[i].tipo = BENGALA;
			mochila[i].movimientos_restantes = MOVIMEINTOS_BENGALA;
		}

		(*cantidad_elementos) += elementos_a_agregar;
	}

}


/*
*Pre-condiciones: Solo puede ser usada por incializar_personaje.
*Post-condiciones: Carga la cantidad incial de begnalas en la mochila, con toda su informaicón correspondiente.
*/
void incializar_bengalas_en_mochila(elemento_mochila_t mochila[MAX_HERRAMIENTAS], int* cantidad_elementos, int tipo_personaje){

	if(tipo_personaje == PANDA){

		agregar_elemento_a_mochila(mochila, cantidad_elementos, BENGALA, CANTIDAD_INICIAL_DE_BENGALAS_EN_MOCHILA_PANDA);
	}
}


/*
*Pre-condiciones: Solo puede ser usada por incializar_mochila.
*Post-condiciones: Carga velas a la mochila (con su información incial) segun las especificaciones del juego.
*/
void inicializar_velas_en_mochila(elemento_mochila_t mochila[MAX_HERRAMIENTAS], int* cantidad_elementos, int tipo_personaje){

	switch(tipo_personaje){

		case POLAR:
		agregar_elemento_a_mochila(mochila, cantidad_elementos, VELA, CANTIDAD_INICIAL_DE_VELAS_EN_MOCHILA_POLAR);
		break;

		case PANDA:
		agregar_elemento_a_mochila(mochila, cantidad_elementos, VELA, CANTIDAD_INICIAL_DE_VELAS_EN_MOCHILA_PANDA);
		break;

		case PARDO:
		agregar_elemento_a_mochila(mochila, cantidad_elementos, VELA, CANTIDAD_INICIAL_DE_VELAS_EN_MOCHILA_PARDO);
		break;
	}

}


/*
*Pre-condiciones: Solo puede ser usada por el procedimiento incializar_mochila.
*Post-condiciones: Carga una linterna en el vector mochila con toda su informaición inicial.
*/
void inicializar_linterna_en_mochila(elemento_mochila_t mochila[MAX_HERRAMIENTAS], int* cantidad_elementos, int tipo_personaje){

	switch(tipo_personaje){

		case POLAR:
		mochila[0].tipo = LINTERNA;
		mochila[0].movimientos_restantes = MOVIMIENTOS_INICIALES_LINTERNA_POLAR;
		(*cantidad_elementos)++;
		break;

		case PANDA:
		mochila[0].tipo = LINTERNA;
		mochila[0].movimientos_restantes = MOVIMIENTOS_INICIALES_LINTERNA_PANDA;
		(*cantidad_elementos)++;
		break;

		case PARDO:
		mochila[0].tipo = LINTERNA;
		mochila[0].movimientos_restantes = MOVIMIENTOS_INICIALES_LINTERNA_PARDO;
		(*cantidad_elementos)++;  
		break;
	}
}

/*
*Pre-condiciones: Solo puede ser usada por incializar_personaje.
*Post-condiciones: Inicializa la el vetor mochila con toda su información inicial.
*/
void inicializar_mochila(elemento_mochila_t mochila[MAX_HERRAMIENTAS], int* cantidad_elementos, int tipo_personaje){

	inicializar_linterna_en_mochila(mochila, cantidad_elementos, tipo_personaje); 
	inicializar_velas_en_mochila(mochila, cantidad_elementos, tipo_personaje);
	incializar_bengalas_en_mochila(mochila, cantidad_elementos, tipo_personaje);

}


/*
*Pre-condiciones: tipo_personaje solo puede contener los siguientes valores, POLAR(I), PANDA(P), o PARDO(G).
*Post-condiciones: Inicializa al personaje con toda su información inicial.
*/
void inicializar_personaje(personaje_t* personaje, char tipo_personaje){

	(*personaje).tipo = tipo_personaje;

	(*personaje).posicion.fil = fila_aleatoria();
	(*personaje).posicion.col = COLUMNA_DE_INCIO;

	(*personaje).cantidad_elementos = 0;
	inicializar_mochila((*personaje).mochila, &((*personaje).cantidad_elementos), tipo_personaje);

	(*personaje).elemento_en_uso = -1;

	(*personaje).tiempo_perdido = 0;

	(*personaje).ultimo_movimiento = DERECHA;


}


/*
*Pre.condiciones: Solo puede ser usada por inicializar_juego.
*Post-condicones: Carga a chloe al juego con toda su información inicial.
*/
void inicializar_chloe(coordenada_t* amiga_chloe, bool* chloe_visible, coordenada_t vector_de_posiciones[MAX_ELEMENTOS], int tope){

	int fila_actual;
	int columna_actual;

	(*chloe_visible) = false;

	do{
		(*amiga_chloe).fil = fila_aleatoria();
		(*amiga_chloe).col = columna_aleatoria();

		fila_actual = (*amiga_chloe).fil;
		columna_actual = (*amiga_chloe).col;
	}while(!es_posicion_unica(vector_de_posiciones, tope, fila_actual, columna_actual));

}


/*
*Pre-condicones: Solo puede ser usada por inicializar_obstaculos o inicializar_herramientas (las que estan en el mapa).
*-elementos_a_agregar solo puede ser: CANTIDAD_DE_ARBOLES, CANTIDAD_DE_PIEDRAS, CANTIDAD_INICIAL_DE_BENGALAS_EN_EL_MAPA,
*CANTIDAD_INCIAL_DE_VELAS_EN_EL_MAPA, CANTIDAD_INICIAL_DE_PILAS_EN_EL_MAPA.
*-tipo_a_agregar solo puede ser ARBOL, PIEDRA, KOALA, PILA, VELA, BENGALA.
*Post-condiciones: Cargar un vector de elementos_del_mapa (herramientas u obstaculos) con toda su información inicial.
*/
void cargar_elementos(elemento_del_mapa_t elemento[MAX_ELEMENTOS], int* cantidad_elementos, coordenada_t vector_de_posiciones[MAX_ELEMENTOS], int* tope, int elementos_a_agregar, char tipo_a_agregar){

	int fila_actual;
	int columna_actual;

	int inicio = (*cantidad_elementos);
	(*cantidad_elementos) += elementos_a_agregar;

	for(int i = inicio; i < (*cantidad_elementos); i++){

		do{
			elemento[i].tipo = tipo_a_agregar;
			elemento[i].posicion.fil = fila_aleatoria();
			elemento[i].posicion.col = columna_aleatoria();
			elemento[i].visible = false;

			fila_actual = elemento[i].posicion.fil;
			columna_actual = elemento[i].posicion.col;
		}while(!es_posicion_unica(vector_de_posiciones, *tope, fila_actual, columna_actual));

		actualizar_vector_de_posicones(vector_de_posiciones, tope, elemento[i].posicion);
	}
}


/*
*Pre-condiciones: Solo puede ser usada cargar_obstaculos.
*Post-condicones: Carga un unico koala el vector de registros con toda su información inicial. 
*/
void cargar_koala(elemento_del_mapa_t obstaculos[MAX_OBSTACULOS], int* cantidad_obstaculos, coordenada_t vector_de_posiciones[MAX_ELEMENTOS], int* tope){

	int fila;
	int columna;

	do{

		obstaculos[(*cantidad_obstaculos)].tipo = KOALA;
		obstaculos[(*cantidad_obstaculos)].posicion.fil = fila_aleatoria();
		obstaculos[(*cantidad_obstaculos)].posicion.col = columna_aleatoria();
		obstaculos[(*cantidad_obstaculos)].visible = false;

		fila = obstaculos[(*cantidad_obstaculos)].posicion.fil;
		columna = obstaculos[(*cantidad_obstaculos)].posicion.col;

	}while(!es_posicion_unica(vector_de_posiciones, *tope, fila, columna)); 

	(*cantidad_obstaculos)++;
	actualizar_vector_de_posicones(vector_de_posiciones, tope, obstaculos[(*cantidad_obstaculos)-1].posicion);
}


/*
*Pre.condiciones: Solo puede ser usada por inicializar_juego.
*Post-condicones: Carga el vector de obstaculos con todos su elementos.
*/
void inicializar_obstaculos(elemento_del_mapa_t obstaculos[MAX_OBSTACULOS], int* cantidad_obstaculos, coordenada_t vector_de_posiciones[MAX_ELEMENTOS], int* tope){

	(*cantidad_obstaculos) = 0;
	cargar_elementos(obstaculos, cantidad_obstaculos, vector_de_posiciones, tope, CANTIDAD_DE_ARBOLES, ARBOL);
	cargar_elementos(obstaculos, cantidad_obstaculos, vector_de_posiciones, tope, CANTIDAD_DE_PIEDRAS, PIEDRA);
	cargar_koala(obstaculos, cantidad_obstaculos, vector_de_posiciones, tope);
}


/*
*Pre-condicones: Solo puede ser usada por inicializar_juego.
*Post.condiciones: Cargar el vector de registos, herramientas, con todos su elementos iniciales (y son su información incial).
*/
void inicializar_herramientas_del_mapa(elemento_del_mapa_t herramientas[MAX_HERRAMIENTAS], int* cantidad_herramientas, coordenada_t vector_de_posiciones[MAX_ELEMENTOS], int* tope){

	(*cantidad_herramientas) = 0;
	cargar_elementos(herramientas, cantidad_herramientas, vector_de_posiciones, tope, CANTIDAD_INICIAL_DE_PILAS_EN_EL_MAPA, PILA);
	cargar_elementos(herramientas, cantidad_herramientas, vector_de_posiciones, tope, CANTIDAD_INCIAL_DE_VELAS_EN_EL_MAPA, VELA);
	cargar_elementos(herramientas, cantidad_herramientas, vector_de_posiciones, tope, CANTIDAD_INICIAL_DE_BENGALAS_EN_EL_MAPA, BENGALA);
}


void inicializar_juego(juego_t* juego, char tipo_personaje){

	coordenada_t vector_de_posiciones[MAX_ELEMENTOS];
	int tope = 0;

	inicializar_personaje(&(*juego).personaje, tipo_personaje);
	vector_de_posiciones[0] = (*juego).personaje.posicion;
	tope++;

	inicializar_chloe(&((*juego).amiga_chloe), &((*juego).chloe_visible), vector_de_posiciones, tope);
	vector_de_posiciones[1] = (*juego).amiga_chloe;
	tope++;

	inicializar_obstaculos((*juego).obstaculos, &((*juego).cantidad_obstaculos), vector_de_posiciones, &tope);
	inicializar_herramientas_del_mapa((*juego).herramientas, &((*juego).cantidad_herramientas), vector_de_posiciones, &tope);
	



}


int estado_juego(juego_t juego){

	int estado = 0;

	if((juego.personaje.posicion.fil == juego.amiga_chloe.fil) && (juego.personaje.posicion.col == juego.amiga_chloe.col)){

		estado = -1;
	}

	return estado;
}


/*
*Pre-condiciones:
*- juego debe haber sido previamente incializado por el procedimiento incializar_juego.
*-fila debe estar en el rango  0-19.
*-columna debe estar en el rango 0-29.
*Post-condiciones: Devuelve true si fila y columna son ocupadas por algunas de las posiciones contenidas en el registro juego.
*/
bool hay_espacio_para_personaje(juego_t juego, int fila, int columna){

	bool hay_espacio = true;

	if(hubo_colision(juego.obstaculos, juego.cantidad_obstaculos, fila, columna)){

		hay_espacio = false;
	}
	else if(hubo_colision(juego.herramientas, juego.cantidad_herramientas, fila, columna)){

		hay_espacio = false;
	}
	else if((fila == juego.amiga_chloe.fil) && (columna == juego.amiga_chloe.col)){

		hay_espacio = false;
	}

	return hay_espacio;
}


/*
*Pre-condiciones: juego debe haber sido inicializado previamente por el procedimiento inicializar_juego.
*Post-condiciones: Reinicia la posicion del personaje.
*/
void reiniciar_incio_personaje(juego_t* juego){

	int fila_actual;
	int columna_actual;

	do{

		(*juego).personaje.posicion.fil = fila_aleatoria();
		(*juego).personaje.posicion.col = COLUMNA_INCIAL;

		fila_actual = (*juego).personaje.posicion.fil;
		columna_actual = (*juego).personaje.posicion.col;
	}while(!hay_espacio_para_personaje(*juego, fila_actual, columna_actual));


}


/*
*Pre-condiciones: Solo puede ser usada por realizar_cambios_por_nueva_posicion.
*Post-condiciones: Suma una cantidad a tiempo perdido según el contenido de objeto_colisionado y personaje. En caso de haber colisionado
*con un Koala reinicia la posición del personaje a columna 0, y fila aleatoria.
*/
void modificar_estado_personaje(double* tiempo_perdido, char objeto_colisionado, char tipo_personaje){

	switch(objeto_colisionado){

		case ARBOL:

		if(tipo_personaje == PANDA){

			*tiempo_perdido += TIEMPO_PERDIDO_ARBOL_PANDA;
		}
		else if(tipo_personaje == POLAR){

			*tiempo_perdido += TIEMPO_PERDIDO_ARBOL_POLAR;
		}
		else if(tipo_personaje == PARDO){

			*tiempo_perdido+= TIEMPO_PERDIDO_ARBOL_PARDO;
		}
		break;

		case PIEDRA:

		if(tipo_personaje == PANDA){

			*tiempo_perdido += TIEMPO_PERDIDO_PIEDRAS_PANDA;
		}
		else if(tipo_personaje == POLAR){

			*tiempo_perdido += TIEMPO_PERDIDO_PIEDRAS_POLAR;
		}
		else if(tipo_personaje == PARDO){

			*tiempo_perdido+= TIEMPO_PERDIDO_PIEDRAS_PARDO;
		}
		break;
	}
}


/*
*Pre_condiciones: juego debe haber sido previamente incializado por el procedimiento incializar_juego.
*Post_condiciones: Coloca la visibilidad de las posiciones superiores a la del personaje en true si hay algun obstaculo o herramienta
*en ellas. 
*/
void apuntar_linterna_hacia_arriba(juego_t* juego, int fila_actual, int columna_actual){

	int j = columna_actual;

	int posicion_de_encendido;

	for(int i = fila_actual - 1; i >= FILA_INICIAL; i--){

		if(hubo_colision((*juego).obstaculos, (*juego).cantidad_obstaculos, i, j)){

			posicion_de_encendido = posicion_de_colision((*juego).obstaculos, (*juego).cantidad_obstaculos, i, j);

			(*juego).obstaculos[posicion_de_encendido].visible = true;
		}
		else if(hubo_colision((*juego).herramientas, (*juego).cantidad_herramientas, i, j)){

			posicion_de_encendido = posicion_de_colision((*juego).herramientas, (*juego).cantidad_herramientas, i, j);

			(*juego).herramientas[posicion_de_encendido].visible = true;
		}
		else if((i == (*juego).amiga_chloe.fil) && (j == (*juego).amiga_chloe.col)){

			(*juego).chloe_visible = true;
		}

	}	
}


/*
*Pre_condiciones: juego debe haber sido previamente incializado por el procedimiento incializar_juego.
*Post_condiciones: Coloca la visibilidad de las posiciones a la izquierda del personaje en true si hay algun obstaculo o herramienta
*en ellas, no hace nada en caso contrario.
*/
void apuntar_linterna_hacia_la_izquierda(juego_t* juego, int fila_actual, int columna_actual){

	int i = fila_actual;

	int posicion_de_encendido;

	for(int j = columna_actual - 1; j >= COLUMNA_INCIAL; j--){

		if(hubo_colision((*juego).obstaculos, (*juego).cantidad_obstaculos, i, j)){

			posicion_de_encendido = posicion_de_colision((*juego).obstaculos, (*juego).cantidad_obstaculos, i, j);
			(*juego).obstaculos[posicion_de_encendido].visible = true;
		}
		else if(hubo_colision((*juego).herramientas, (*juego).cantidad_herramientas, i, j)){

			posicion_de_encendido = posicion_de_colision((*juego).herramientas, (*juego).cantidad_herramientas, i, j);

			(*juego).herramientas[posicion_de_encendido].visible = true;
		}
		else if((i == (*juego).amiga_chloe.fil) && (j == (*juego).amiga_chloe.col)){

			(*juego).chloe_visible = true;
		}

	}	
}


/*
*Pre_condiciones: juego debe haber sido previamente incializado por el procedimiento incializar_juego.
*Post_condiciones: Coloca la visibilidad de las posiciones inferiores a la del personaje en true si hay algun obstaculo o herramienta
*en ellas. 
*/
void apuntar_linterna_hacia_abajo(juego_t* juego, int fila_actual, int columna_actual){

	int j = columna_actual;

	int posicion_de_encendido;

	for(int i = fila_actual + 1; i <= FILA_FINAL; i++){

		if(hubo_colision((*juego).obstaculos, (*juego).cantidad_obstaculos, i, j)){

			posicion_de_encendido = posicion_de_colision((*juego).obstaculos, (*juego).cantidad_obstaculos, i, j);

			(*juego).obstaculos[posicion_de_encendido].visible = true;
		}
		else if(hubo_colision((*juego).herramientas, (*juego).cantidad_herramientas, i, j)){

			posicion_de_encendido = posicion_de_colision((*juego).herramientas, (*juego).cantidad_herramientas, i, j);

			(*juego).herramientas[posicion_de_encendido].visible = true;
		}
		else if((i == (*juego).amiga_chloe.fil) && (j == (*juego).amiga_chloe.col)){

			(*juego).chloe_visible = true;
		}

	}	
}


/*
*Pre_condiciones: juego debe haber sido previamente incializado por el procedimiento incializar_juego.
*Post_condiciones: Coloca la visibilidad de las posiciones a la derecha del personaje en true si hay algun obstaculo o herramienta
*en ellas, no hace nada en caso contrario.
*/
void apuntar_linterna_hacia_la_derecha(juego_t* juego, int fila_actual, int columna_actual){

	int i = fila_actual;

	int posicion_de_encendido;

	for(int j = columna_actual + 1; j <= COLUMNA_FINAL; j++){

		if(hubo_colision((*juego).obstaculos, (*juego).cantidad_obstaculos, i, j)){

			posicion_de_encendido = posicion_de_colision((*juego).obstaculos, (*juego).cantidad_obstaculos, i, j);

			(*juego).obstaculos[posicion_de_encendido].visible = true;
		}
		else if(hubo_colision((*juego).herramientas, (*juego).cantidad_herramientas, i, j)){

			posicion_de_encendido = posicion_de_colision((*juego).herramientas, (*juego).cantidad_herramientas, i, j);

			(*juego).herramientas[posicion_de_encendido].visible = true;
		}
		else if((i == (*juego).amiga_chloe.fil) && (j == (*juego).amiga_chloe.col)){

			(*juego).chloe_visible = true;
		}

	}	
}


/*
*Pre_condiciones: EL reigstro personaje debe haber sido previamente inicializado por el procedimiento iniclializar_juego, y ser un campo
*del registro juego.
*Post-condiciones: Devuelve true si el elemento en uso dentro de personaje corresonde a una linterna, y false en caso contrario.
*/
bool hay_linterna_encnedida(personaje_t personaje, int posicion_linterna){

	return(personaje.elemento_en_uso == posicion_linterna);
}


/*NOTA: Solo usar cuando el registro juego haya sido incializado por el procedimiento incializar_juego.
*Pre-condiciones: fila debe estar en el rango 0-19 y  columna en el rango 0-29.
*Post-condiciones: Devuelve true si fila y columna no coinciden con ninguna de las posiciones guardadas en los campos del registro
*inicializar_juego,y false en caso contrario.
*/
bool posicion_generada_es_unica(juego_t juego, int fila, int columna){

	bool estado_de_unicidad = true;

	if(hubo_colision(juego.obstaculos, juego.cantidad_obstaculos, fila, columna)){

		estado_de_unicidad = false;
	}
	else if(hubo_colision(juego.herramientas, juego.cantidad_herramientas, fila, columna)){

		estado_de_unicidad = false;
	}
	else if((fila == juego.amiga_chloe.fil) && (columna == juego.amiga_chloe.col)){

		estado_de_unicidad = false;
	}
	else if((fila == juego.personaje.posicion.fil) && (columna == juego.personaje.posicion.col)){

		estado_de_unicidad = false;
	}

	return estado_de_unicidad;
}

/*
*Pre-condiciones: juego debe haber sido previamente incializado por el procedimiento incializar_juego.
*Post-condicoines: Agrega un koala con toda su información incial al campo de juego, llamado obstaculos.
*/
void agregar_koala(juego_t* juego){

	int fila_actual;
	int columna_actual;

	do{
		(*juego).obstaculos[(*juego).cantidad_obstaculos].tipo = KOALA;
		(*juego).obstaculos[(*juego).cantidad_obstaculos].posicion.fil = fila_aleatoria();
		(*juego).obstaculos[(*juego).cantidad_obstaculos].posicion.col = columna_aleatoria();
		(*juego).obstaculos[(*juego).cantidad_obstaculos].visible = false;

		fila_actual = (*juego).obstaculos[(*juego).cantidad_obstaculos].posicion.fil;
		columna_actual = (*juego).obstaculos[(*juego).cantidad_obstaculos].posicion.col; 
	}while(!posicion_generada_es_unica(*juego, fila_actual, columna_actual));

	(*juego).cantidad_obstaculos++;
}


/*
*Pre.condiciones: EL registro juego debe haber sido previamente inciazliado por el procedimiento inicializar_juego.
*Post-condicoines: Cambia la visibilidad de los elementos del mapa segun el ultimo movimiento del personaje.
*/
void encender_linterna(juego_t* juego){

	int posicion_linterna = posicion_de_herramienta_en_mochila((*juego).personaje.mochila, (*juego).personaje.cantidad_elementos, LINTERNA);
	int posicion_bengala = posicion_de_herramienta_en_mochila((*juego).personaje.mochila, (*juego).personaje.cantidad_elementos, BENGALA);

	int fila_actual = (*juego).personaje.posicion.fil;
	int columna_actual = (*juego).personaje.posicion.col;

	if((!hay_linterna_encnedida((*juego).personaje, posicion_linterna)) && ((*juego).personaje.mochila[posicion_linterna].movimientos_restantes > 0) && (!hay_una_bengala_activa(posicion_bengala, (*juego).personaje.elemento_en_uso))){

		(*juego).personaje.mochila[posicion_linterna].movimientos_restantes--;
		agregar_koala(juego);
		(*juego).personaje.elemento_en_uso = posicion_linterna;

		switch((*juego).personaje.ultimo_movimiento){

			case ARRIBA:

			reiniciar_estado_elementos_del_mapa((*juego).obstaculos, (*juego).cantidad_obstaculos);
			reiniciar_estado_elementos_del_mapa((*juego).herramientas, (*juego).cantidad_herramientas);
			(*juego).chloe_visible = false;
			apuntar_linterna_hacia_arriba(juego, fila_actual, columna_actual);
			break;

			case IZQUIERDA:
			reiniciar_estado_elementos_del_mapa((*juego).obstaculos, (*juego).cantidad_obstaculos);
			reiniciar_estado_elementos_del_mapa((*juego).herramientas, (*juego).cantidad_herramientas);
			(*juego).chloe_visible = false;
			apuntar_linterna_hacia_la_izquierda(juego, fila_actual, columna_actual);
			break;

			case ABAJO:
			reiniciar_estado_elementos_del_mapa((*juego).obstaculos, (*juego).cantidad_obstaculos);
			reiniciar_estado_elementos_del_mapa((*juego).herramientas, (*juego).cantidad_herramientas);
			(*juego).chloe_visible = false;
			apuntar_linterna_hacia_abajo(juego, fila_actual, columna_actual);
			break;

			case DERECHA:
			reiniciar_estado_elementos_del_mapa((*juego).obstaculos, (*juego).cantidad_obstaculos);
			reiniciar_estado_elementos_del_mapa((*juego).herramientas, (*juego).cantidad_herramientas);
			(*juego).chloe_visible = false;
			apuntar_linterna_hacia_la_derecha(juego, fila_actual, columna_actual);
			break;
		}
	}
	else if(!hay_una_bengala_activa(posicion_bengala, (*juego).personaje.elemento_en_uso)){

		reiniciar_estado_elementos_del_mapa((*juego).obstaculos, (*juego).cantidad_obstaculos);
		reiniciar_estado_elementos_del_mapa((*juego).herramientas, (*juego).cantidad_herramientas);
		(*juego).chloe_visible = false;
		(*juego).personaje.elemento_en_uso = -1;
	}
	else if(hay_una_bengala_activa(posicion_bengala, (*juego).personaje.elemento_en_uso)){


		if((*juego).personaje.mochila[posicion_bengala].movimientos_restantes > 0){
			(*juego).personaje.mochila[posicion_bengala].movimientos_restantes--;
		}
		else{

			reiniciar_estado_elementos_del_mapa((*juego).obstaculos, (*juego).cantidad_obstaculos);
			reiniciar_estado_elementos_del_mapa((*juego).herramientas, (*juego).cantidad_herramientas);
			(*juego).chloe_visible = false;

			(*juego).personaje.elemento_en_uso = -1;
			eliminar_elemento_de_mochila((*juego).personaje.mochila, &((*juego).personaje.cantidad_elementos), posicion_bengala);		
		}						
	}	
}


/*
*Pre-condiciones: No tiene.
*Post-condiciones: Devuelve ture si jugada corresponde a la activación de alguna herramienta, o el tiempo acutal, y false en caso contrario.
*/
bool se_activo_una_herramienta(char jugada){

	return((jugada == LINTERNA) || (jugada == VELA) || (jugada == BENGALA));
}


/*
*Pre-condiciones: juego debe haber sido previamente incializada por incializar_juego.
*Post-condiciones: Realiza cambios en juego según la nueva posición del personaje.
*/
void realizar_cambios_por_nueva_posicion(juego_t* juego){

	char objeto_colisionado;

	int posicion_de_choque;

	int fila_actual = (*juego).personaje.posicion.fil;
	int columna_actual = (*juego).personaje.posicion.col;

	if(hubo_colision((*juego).obstaculos, (*juego).cantidad_obstaculos, fila_actual, columna_actual)){

		objeto_colisionado = tipo_de_objeto_colisionado((*juego).obstaculos, (*juego).cantidad_obstaculos, fila_actual, columna_actual);

		if(objeto_colisionado != KOALA){
			modificar_estado_personaje(&((*juego).personaje.tiempo_perdido), objeto_colisionado, (*juego).personaje.tipo);
		}
		else{
			reiniciar_incio_personaje(juego);
		}
	}
	else if(hubo_colision((*juego).herramientas, (*juego).cantidad_herramientas, fila_actual, columna_actual)){

		objeto_colisionado = tipo_de_objeto_colisionado((*juego).herramientas, (*juego).cantidad_herramientas, fila_actual, columna_actual);
		posicion_de_choque = posicion_de_colision((*juego).herramientas, (*juego).cantidad_herramientas, fila_actual, columna_actual);

		agregar_elemento_a_mochila((*juego).personaje.mochila, &((*juego).personaje.cantidad_elementos), objeto_colisionado, 1);
		eliminar_elemento((*juego).herramientas, &((*juego).cantidad_herramientas), posicion_de_choque);
	}

}

/*
*Pre-condiciones: No tiene.
*Post-condiciones: Devuelve true si fila y columna estan en un rango valido (0-19 y 0-29 respectivamente), y false en caso contrario. 
*/
bool posicion_esta_dentro_del_mapa(int fila, int columna){

	return((fila >= FILA_INICIAL && fila <= FILA_FINAL) && (columna >= COLUMNA_INCIAL && columna <= COLUMNA_FINAL));
}


/*
*Pre-condicones: posicion_personaje debe contener previamente una posicion_valida. fil-> 0-19, col 0-29. 
*Post-condiciones: Cambia la posicion del personaje segun la jugada realizada.
*/
void mover_personaje(coordenada_t* posicion_personaje, char jugada){


	switch(jugada){

		case ARRIBA:
		if(posicion_esta_dentro_del_mapa((*posicion_personaje).fil-1, (*posicion_personaje).col)){
			(*posicion_personaje).fil -= 1;
		}	
		break;

		case IZQUIERDA:
		if(posicion_esta_dentro_del_mapa((*posicion_personaje).fil, (*posicion_personaje).col-1)){
			(*posicion_personaje).col -= 1;
		}
		break;

		case ABAJO:
		if(posicion_esta_dentro_del_mapa((*posicion_personaje).fil+1, (*posicion_personaje).col)){
			(*posicion_personaje).fil += 1;
		}	
		break;

		case DERECHA:
		if(posicion_esta_dentro_del_mapa((*posicion_personaje).fil, (*posicion_personaje).col+1)){
			(*posicion_personaje).col += 1;
		}
		break;
	}
}


/*
*Pre-condiciones: No tiene.
*Post.condiciones: Devuelve true si jugada corresponde a un movimiento valido (WASD), o false en caso contrario.
*/
bool se_realizo_un_movimiento(char jugada){

	return((jugada == ARRIBA) || (jugada == IZQUIERDA) || (jugada == ABAJO) || (jugada == DERECHA));
}


/*
*Pre-condiciones: elemento en uso debe ser mayor o igual que -1.
*Post-condicones: Devuelve true si elemento_en_uso es mayor que -1, y false si es igual a -1;   
*/
bool hay_una_herramienta_activa(int elemento_en_uso){

	return (elemento_en_uso > -1);

}

/*NOTA: Solo usar si previamente se sabe que hay una linterna en uso.
*Pre-condiciones: juego debe haber sido previamente inicializado por inicializar_juego.
*Post-condicones: Actualiza el rango de ilumnación de linterna segun la nueva posición del personaje. Si la linterna se queda sin
*movimientos (0), esta misma será apagada.
*/
void usar_linterna(juego_t* juego){

	int posicion_linterna = posicion_de_herramienta_en_mochila((*juego).personaje.mochila, (*juego).personaje.cantidad_elementos, LINTERNA);
	int direccion_actual = (*juego).personaje.ultimo_movimiento;

	int fila_actual = (*juego).personaje.posicion.fil;
	int columna_actual = (*juego).personaje.posicion.col;

	reiniciar_estado_elementos_del_mapa((*juego).obstaculos, (*juego).cantidad_obstaculos);
	reiniciar_estado_elementos_del_mapa((*juego).herramientas, (*juego).cantidad_herramientas);
	(*juego).chloe_visible = false;

	if((*juego).personaje.mochila[posicion_linterna].movimientos_restantes > 0){

		switch(direccion_actual){

			case ARRIBA:
			apuntar_linterna_hacia_arriba(juego, fila_actual, columna_actual);
			(*juego).personaje.mochila[posicion_linterna].movimientos_restantes--;
			break;

			case IZQUIERDA:
			apuntar_linterna_hacia_la_izquierda(juego, fila_actual, columna_actual);
			(*juego).personaje.mochila[posicion_linterna].movimientos_restantes--;
			break;

			case ABAJO:
			apuntar_linterna_hacia_abajo(juego, fila_actual, columna_actual);
			(*juego).personaje.mochila[posicion_linterna].movimientos_restantes--;
			break;

			case DERECHA:
			apuntar_linterna_hacia_la_derecha(juego, fila_actual, columna_actual);
			(*juego).personaje.mochila[posicion_linterna].movimientos_restantes--;
			break;
		}
	}
	else{

		(*juego).personaje.elemento_en_uso = -1;
	}
}


/*
*Pre-condicones: el vector elemento debe haber sido previamente incializados en el procedimiento incializar_juego. 
*incializar_juego.
*Post-condicones: Dada una fila y una columna, verifica si esta posicion coincide con una del vector de elementos, si coincide,
*cambia la visibiladad de estas dentro del vector de elementos a true, en caso contrario, no hace nada.
*/
void iluminar_con_vela(juego_t* juego, int fila, int columna){

	int posicion_a_iluminar;

	if((fila >= FILA_INICIAL && fila <= FILA_FINAL) && (columna >= COLUMNA_INCIAL && columna <= COLUMNA_FINAL)){

		if(hubo_colision((*juego).obstaculos, (*juego).cantidad_obstaculos, fila, columna)){

			posicion_a_iluminar = posicion_de_colision((*juego).obstaculos, (*juego).cantidad_obstaculos, fila, columna);

			(*juego).obstaculos[posicion_a_iluminar].visible = true;

		}
		else if(hubo_colision((*juego).herramientas, (*juego).cantidad_herramientas, fila, columna)){

			posicion_a_iluminar = posicion_de_colision((*juego).herramientas, (*juego).cantidad_herramientas, fila, columna);

			(*juego).herramientas[posicion_a_iluminar].visible = true;

		}
		else if((*juego).amiga_chloe.fil == fila && (*juego).amiga_chloe.col == columna){

			(*juego).chloe_visible = true;
		}
	}
}


/*
*Pre_condiciones: No tiene.
*Post-condicones: Devuelve true si elemento_en_uso es igual a posicion vela.
*/
bool hay_vela_encendida(int elemento_en_uso, int posicion_vela){

	return (elemento_en_uso == posicion_vela);
}

/*
*Pre-condiciones: El vector de obstaculos debe haber sido previamente inicializado por el procedimiento incializar_juego.
*Post-condicones: Hace visible las posiciones del vector de obstaculos que coindican con fila y columna.
*/
void iluminar_con_vela_mapa(juego_t* juego, int fila, int columna){

	iluminar_con_vela(juego, fila -1, columna);
	iluminar_con_vela(juego, fila, columna -1);
	iluminar_con_vela(juego, fila +1, columna);
	iluminar_con_vela(juego, fila, columna +1);
	iluminar_con_vela(juego, fila -1, columna +1);
	iluminar_con_vela(juego, fila +1, columna -1);
	iluminar_con_vela(juego, fila -1, columna -1);
	iluminar_con_vela(juego, fila +1, columna +1);

}


/*
*Pre-condiciones: El registro juego debio haber sido previamente incializado por el procedimiento inicializar_juego.
*Post-condicones: Enciende la vela cambiando la visibilidad de los elementos del mapa de acuerdo a la posicion actual del personaje.
*/
void encender_vela(juego_t* juego){

	int posicion_bengala = posicion_de_herramienta_en_mochila((*juego).personaje.mochila, (*juego).personaje.cantidad_elementos, BENGALA);
	int posicion_vela = posicion_de_herramienta_en_mochila((*juego).personaje.mochila, (*juego).personaje.cantidad_elementos, VELA);

	int fila_actual = (*juego).personaje.posicion.fil;
	int columna_actual = (*juego).personaje.posicion.col;

	if(!hay_vela_encendida((*juego).personaje.elemento_en_uso, posicion_vela) && ((*juego).personaje.mochila[posicion_vela].movimientos_restantes > 0) && (!hay_una_bengala_activa(posicion_bengala, (*juego).personaje.elemento_en_uso))){

		reiniciar_estado_elementos_del_mapa((*juego).obstaculos, (*juego).cantidad_obstaculos);
		reiniciar_estado_elementos_del_mapa((*juego).herramientas, (*juego).cantidad_herramientas);
		(*juego).chloe_visible = false;

		iluminar_con_vela_mapa(juego, fila_actual, columna_actual);

		(*juego).personaje.elemento_en_uso = posicion_vela;
		(*juego).personaje.mochila[posicion_vela].movimientos_restantes--;
	}
	else if((*juego).personaje.mochila[posicion_vela].movimientos_restantes == 0){

		reiniciar_estado_elementos_del_mapa((*juego).obstaculos, (*juego).cantidad_obstaculos);
		reiniciar_estado_elementos_del_mapa((*juego).herramientas, (*juego).cantidad_herramientas);
		(*juego).chloe_visible = false;
		eliminar_elemento_de_mochila((*juego).personaje.mochila, &((*juego).personaje.cantidad_elementos), posicion_vela);
		(*juego).personaje.elemento_en_uso = -1;
	}
	else if(!hay_una_bengala_activa(posicion_bengala, (*juego).personaje.elemento_en_uso)){

		reiniciar_estado_elementos_del_mapa((*juego).obstaculos, (*juego).cantidad_obstaculos);
		reiniciar_estado_elementos_del_mapa((*juego).herramientas, (*juego).cantidad_herramientas);
		(*juego).chloe_visible = false;
		(*juego).personaje.elemento_en_uso = -1;
	}
	else if(hay_una_bengala_activa(posicion_bengala, (*juego).personaje.elemento_en_uso)){

		if((*juego).personaje.mochila[posicion_bengala].movimientos_restantes > 0){
			(*juego).personaje.mochila[posicion_bengala].movimientos_restantes--;
		}
		else{

			reiniciar_estado_elementos_del_mapa((*juego).obstaculos, (*juego).cantidad_obstaculos);
			reiniciar_estado_elementos_del_mapa((*juego).herramientas, (*juego).cantidad_herramientas);
			(*juego).chloe_visible = false;

			(*juego).personaje.elemento_en_uso = -1;
			eliminar_elemento_de_mochila((*juego).personaje.mochila, &((*juego).personaje.cantidad_elementos), posicion_bengala);
		}	
	}
}


/*
*Pre-condiciones: EL registro juego debe haber sido inicializado previamente por el procedmiento inicializar_juego.
*Post-condiciones: Actualiza el registro juego de acuerdo a la funcionalidad de la vela.
*/
void usar_vela(juego_t* juego){

	int posicion_vela = posicion_de_herramienta_en_mochila((*juego).personaje.mochila, (*juego).personaje.cantidad_elementos, VELA);

	int fila_actual = (*juego).personaje.posicion.fil;
	int columna_actual = (*juego).personaje.posicion.col;

	reiniciar_estado_elementos_del_mapa((*juego).obstaculos, (*juego).cantidad_obstaculos);
	reiniciar_estado_elementos_del_mapa((*juego).herramientas, (*juego).cantidad_herramientas);
	(*juego).chloe_visible = false;


	if((*juego).personaje.mochila[posicion_vela].movimientos_restantes > 0){

		iluminar_con_vela_mapa(juego, fila_actual, columna_actual);

		(*juego).personaje.mochila[posicion_vela].movimientos_restantes--;
	}
	else{

		eliminar_elemento_de_mochila((*juego).personaje.mochila, &((*juego).personaje.cantidad_elementos), posicion_vela);
		(*juego).personaje.elemento_en_uso = -1;
	}

}


/*
*Pre-condiciones:
*-El vector elemento y su tope deben haber sido previamente inicializados por el procedimiento inicializar_juego, ademas deben ser campos
*del registro juego.
*-fila_actual debe estar en el rango 0-19.
*-columna_actual debe estar en el rango 0-29.
*Post-condiciones:
*/
void iluminar_con_bengala(elemento_del_mapa_t elemento[MAX_ELEMENTOS], int cantidad_elementos, int fila_actual, int columna_actual){

	int fila_temporal;
	int columna_temporal;

	for(int i = 0; i < cantidad_elementos; i++){

		fila_temporal = elemento[i].posicion.fil;
		columna_temporal = elemento[i].posicion.col;

		if((distancia_manhtattan(fila_actual, columna_actual, fila_temporal, columna_temporal) <= 3) && (distancia_manhtattan(fila_actual, columna_actual, fila_temporal, columna_temporal) >= 0)){

			elemento[i].visible = true;
		}

	}

}


/*
*Pre-condiciones: juego debe haber sido previamente inicializado por el procedimiento inicializar_juego.
*Post-condiones: Actualiza el registro juego de acuerdo a la funcionalidad de la bengalas.
*/
void enceder_bengala(juego_t* juego){

	int posicion_bengala = posicion_de_herramienta_en_mochila((*juego).personaje.mochila, (*juego).personaje.cantidad_elementos, BENGALA);

	int fila_actual = fila_aleatoria();
	int columna_actual = columna_aleatoria();

	if(posicion_bengala != -1 && (*juego).personaje.elemento_en_uso != posicion_bengala){

		reiniciar_estado_elementos_del_mapa((*juego).obstaculos, (*juego).cantidad_obstaculos);
		reiniciar_estado_elementos_del_mapa((*juego).herramientas, (*juego).cantidad_herramientas);
		(*juego).chloe_visible = false;

		iluminar_con_bengala((*juego).obstaculos, (*juego).cantidad_obstaculos, fila_actual, columna_actual);
		iluminar_con_bengala((*juego).herramientas, (*juego).cantidad_herramientas, fila_actual, columna_actual);


		if(distancia_manhtattan(fila_actual, columna_actual, (*juego).amiga_chloe.fil, (*juego).amiga_chloe.col) >= 0 && distancia_manhtattan(fila_actual, columna_actual, (*juego).amiga_chloe.fil, (*juego).amiga_chloe.col) <= 3){

			(*juego).chloe_visible = true;
		}

		(*juego).personaje.elemento_en_uso = posicion_bengala;
		(*juego).personaje.mochila[posicion_bengala].movimientos_restantes--;
	}
	else if(posicion_bengala != -1 && (*juego).personaje.elemento_en_uso == posicion_bengala){

		if((*juego).personaje.mochila[posicion_bengala].movimientos_restantes > 0){
			(*juego).personaje.mochila[posicion_bengala].movimientos_restantes--;
		}
		else{

			reiniciar_estado_elementos_del_mapa((*juego).obstaculos, (*juego).cantidad_obstaculos);
			reiniciar_estado_elementos_del_mapa((*juego).herramientas, (*juego).cantidad_herramientas);
			(*juego).chloe_visible = false;

			(*juego).personaje.elemento_en_uso = -1;
			eliminar_elemento_de_mochila((*juego).personaje.mochila, &((*juego).personaje.cantidad_elementos), posicion_bengala);
		}
	}
}



/*SOLO USAR PARA CUANDO HAYA UNA BENGALA ACTIVA. -> Para activarla usar el procedimiento encender_bengala.
*Pre-condiciones: El registro juego debe haber sido previamente inicializado por el procedimiento inicializar_juego.
*Post-condiciones: Actualiza el registro juego de acuerdo a la funcionalidad de la bengala.
*/
void usar_bengala(juego_t* juego){

	int posicion_bengala = posicion_de_herramienta_en_mochila((*juego).personaje.mochila, (*juego).personaje.cantidad_elementos, BENGALA);

	int fila = fila_aleatoria();
	int columna = columna_aleatoria();

	if((*juego).personaje.mochila[posicion_bengala].movimientos_restantes > 0){

		reiniciar_estado_elementos_del_mapa((*juego).obstaculos, (*juego).cantidad_obstaculos);
		reiniciar_estado_elementos_del_mapa((*juego).herramientas, (*juego).cantidad_herramientas);
		(*juego).chloe_visible = false;

		iluminar_con_bengala((*juego).obstaculos, (*juego).cantidad_obstaculos, fila, columna);
		iluminar_con_bengala((*juego).herramientas, (*juego).cantidad_herramientas, fila, columna);

		if(distancia_manhtattan(fila, columna, (*juego).amiga_chloe.fil, (*juego).amiga_chloe.col) >= 0 && distancia_manhtattan(fila, columna, (*juego).amiga_chloe.fil, (*juego).amiga_chloe.col) <= 3){

			(*juego).chloe_visible = true;
		}

		(*juego).personaje.mochila[posicion_bengala].movimientos_restantes--;
	}else{

		(*juego).personaje.elemento_en_uso = -1;
		eliminar_elemento_de_mochila((*juego).personaje.mochila, &((*juego).personaje.cantidad_elementos), posicion_bengala);

		reiniciar_estado_elementos_del_mapa((*juego).obstaculos, (*juego).cantidad_obstaculos);
		reiniciar_estado_elementos_del_mapa((*juego).herramientas, (*juego).cantidad_herramientas);
		(*juego).chloe_visible = false;
	}

}


void realizar_jugada(juego_t* juego, char jugada){

	if(se_realizo_un_movimiento(jugada)){

		(*juego).personaje.ultimo_movimiento = jugada;
		mover_personaje(&((*juego).personaje.posicion), jugada);
		realizar_cambios_por_nueva_posicion(juego);

		if(hay_una_herramienta_activa((*juego).personaje.elemento_en_uso)){

			int tipo_de_herramienta_en_uso = (*juego).personaje.mochila[(*juego).personaje.elemento_en_uso].tipo;

			switch(tipo_de_herramienta_en_uso){

				case LINTERNA:
				usar_linterna(juego);
				break;

				case VELA:
				usar_vela(juego);
				break;

				case BENGALA:
				usar_bengala(juego);
				break;
			}
		}

	}
	else if(se_activo_una_herramienta(jugada)){

		switch(jugada){

			case LINTERNA:
			encender_linterna(juego);
			break;

			case VELA:
			encender_vela(juego);
			break;

			case BENGALA:
			enceder_bengala(juego);
			break;
		}
	}

	if((*juego).personaje.tipo == PANDA && (*juego).personaje.tiempo_perdido >= 30){

		(*juego).chloe_visible = true;
	}	
}


/*
*Pre-condicones: No tiene.
*Post-condicones: Inicializa todas la posicones de la matriz mapa, con el caracter '*'.
*/
void incializar_mapa(char mapa[LARGO_MAPA][ANCHO_MAPA]){

	for(int i = 0; i < LARGO_MAPA; i++){

		for(int j = 0; j < ANCHO_MAPA; j++){

			mapa[i][j] = '*';
		}
	}

}


/*
*Pre-condiciones: mapa no puede estar vacío.
*Post-condiciones: Muestra el contenido del mapa por pantalla.
*/
void mostrar_mapa(char mapa[LARGO_MAPA][ANCHO_MAPA]){

	printf("\n");

	for(int i = 0; i < LARGO_MAPA; i++){

		for(int j = 0; j < ANCHO_MAPA; j++){

			printf("  ");
			printf("%c ", mapa[i][j]);
		}

		printf("\n");
	}
}


/*
*Pre-condiciones: El vector de registros elementos debe estar previamente incializado por el procedimiento inicializar_juego.
*Post-condicones: Carga parte de la información del vector elementos (campo posicion) en la matriz mapa.
*/
void cargar_elementos_al_mapa(char mapa[LARGO_MAPA][ANCHO_MAPA], elemento_del_mapa_t elementos[MAX_ELEMENTOS], int cantidad_elementos){

	for(int i = 0; i < cantidad_elementos; i++){

		if(elementos[i].visible == true){

			mapa[elementos[i].posicion.fil][elementos[i].posicion.col] = elementos[i].tipo;
		}
	}

}


void mostrar_juego(juego_t juego){

	char mapa[LARGO_MAPA][ANCHO_MAPA];

	incializar_mapa(mapa);

	if(juego.chloe_visible == true){
		mapa[juego.amiga_chloe.fil][juego.amiga_chloe.col] = CHLOE;
	}
		
	cargar_elementos_al_mapa(mapa, juego.obstaculos, juego.cantidad_obstaculos);
	cargar_elementos_al_mapa(mapa, juego.herramientas, juego.cantidad_herramientas);
	mapa[juego.personaje.posicion.fil][juego.personaje.posicion.col] = juego.personaje.tipo;

	mostrar_mapa(mapa);

	int cant_koalas = 0;

	for(int i = 0; i < juego.cantidad_obstaculos; i++){

		if(juego.obstaculos[i].tipo == KOALA){
			cant_koalas++;
		}

	}

	printf("\n\n TIEMPO PERDIDO : %f", juego.personaje.tiempo_perdido);
	printf("\n\n TIEMPO TRANCUSRRIDO (PRESIONE T PARA VER): ");
}



bool es_jugada_valida(char jugada){

	bool estado_de_validez = false;

	if((jugada == ARRIBA) || (jugada == IZQUIERDA) || (jugada == ABAJO) || (jugada == DERECHA) || (jugada == LINTERNA) || (jugada == VELA) || (jugada == BENGALA) || (jugada == TIEMPO_TRANSCURRIDO)){

		estado_de_validez = true;
	}

	return estado_de_validez;
}