/*
*-Procesamiento de archivos: Intersección entre dos archivos entre dos archivos.
*-Autor: Víctor Zacarías.
*-Ultima actualización: 2/8/2021.
*/

//Aclaración: Se realizara la diferencia entre de condicionales-regulares.

#define MAX 100

#define estudiantes_condicionales "estudiantes_condicionales.dat"
#define estudiantes_regulares "estudiantes_regulares.dat"
#define estudiantes_definitivos "estudiantes_definitivos.dat"

typedef struct estudiante{
	char nombre_completo[MAX];
	char fecha_de_nacimiento[MAX]; //d-m-a (todo númericamente).
	char dni[MAX]; //con puntos.
	int padron;
}estudiante_t;


void realizar_mezcla(char ruta_condicionales[MAX], char ruta_regulares[MAX], char ruta_definitivo[MAX]){

	estudiante_t info_condicionales;
	estudiante_t info_regulares;

	//Apertura.
	FILE* condicionales = fopen(ruta_condicionales, "r");
	if(!condicionales){
		printf("Error al arbrir el archivo '%s'\n", ruta_condicionales);
		return;
	}

	FILE* regulares = fopen(ruta_regulares, "r");
	if(!regulares){
		printf("Error al arbir el archivo '%s'", ruta_regulares);
		fclose(condicionales);
		return;
	}

	FILE* definitivos = fopen(ruta_definitivos, "w");
	if(!definitivos){
		printf("Error al arbrir el archivo '%s'", ruta_definitivos);
		fclose(condicionales);
		fclose(regulares);
		return;
	}

	//Operar.
	fread(&info_condicionales, sizeof(estudiante_t), 1, condicionales);
	fread(&info_regulares, sizeof(estudiante_t), 1, regulares);
	
	while((!feof(condicionales)) && (!feof(regulares))){

		if(info_condicionales.padron == info_regulares.padron){
			fwrite(&info_condicionales, sizeof(estudiante_t), 1, definitivos);
			fread(&info_condicionales, sizeof(estudiante_t), 1, condicionales);
			fread(&info_regulares, sizeof(estudiante_t), 1, regulares);	
		}
		else if(info_condicionales.padron > info_regulares.padron){
			fread(&info_regulares, sizeof(estudiante_t), 1, regulares);	
		}
		else{
			fread(&info_condicionales, sizeof(estudiante_t), 1, condicionales);
		}
	}
	
	//Cierre.
	fclose(condicionales);
	fclose(regulares);
	fclose(definitivos);
}
