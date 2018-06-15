// Generar un archivo binario de numero enteros ingresados desde el teclado u obtenidos al azar.
// Finalizar la carga con -1 o cuando el numero al azar sea 0. Luego se solicita: 

// 1) Ordenar el archivo de menor a mayor usando cualquier metodo de ordenamiento.
// 2) Informar la cantidad de veces que se repite cada valor.
// 3) Mostrar el numero que mas se repitio, Mostrar mas de uno solo si hay mas de uno.
// 4) Imprimir el archivo por pantalla

// No se puede utilizar vectores.

// Corte de control solucion
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int leerRegistro(FILE *f, int numreg);
void grabarRegistro(FILE *f, int numreg, int dato);

int main() {
	FILE *arch;
	int e, e2, aux, valor2, cant = 1, cant2 = 1;

	// Abro el archivo
	arch = fopen("enteros.dat", "wb+");
	if (arch == NULL) {
		puts("No se puede crear el archivo");
		return 1;
	}
	printf("Ingrese valores positivos enteros, cuando termine use el -1");
	scanf("%d", &e);
	while (e != -1) {
		fwrite(&e, sizeof(e), 1, arch);
		scanf("%d", &e);
	}
	int i, j, cantReg;
	// Calculo la cantidad de registros que se crearon en el archivo
	cantReg = ftell(arch) / sizeof(e);

	for (i = 0; i < cantReg - 1; i++)
	{
		for (j = i + 1; j < cantReg; j++) {

			// Le estamos mandando para que lea el registro de la posicion "i" y se lo asignemos a una variable
			e = leerRegistro(arch, i);
			// Le estamos mandando para que lea el registro de la posicion "j" y se lo asignemos a una variable
			e2 = leerRegistro(arch, j);

			// Ponemos como condicion que si el valor de la posicion "j" es menor al de la posicion "i"
			// queremos cambiar la posicion de "e" y mandarsela a "e2" para que se empiece a organizar el 
			// Archivo de menor a mayor
			if (e >= e2)
			{
				aux = e2;
				e2 = e;
				e = aux;
				// Grabamos ese valor e que es mayor al de e2 en "e2"
				grabarRegistro(arch, i, e);
				// Grabamos el valor de e2 que es menor en "e"
				grabarRegistro(arch, j, e2);
			}
		}
	}
	
	// Ya que tenemos el Archivo ordenado ahora nada mas nos queda recorrerlo y fijarnos cual va a ser el numero con mayor aparicion en el programa.
	for (i = 0; i < cantReg - 1; i++)
	{
			// Se vuelve a leer el registro y le pasamos la posicion "i".
			e = leerRegistro(arch, i);
			// Leemos el registro pero ahora adelantandonos a la siguiente posicion i + 1.
			e2 = leerRegistro(arch, i + 1);

			// Generamos la condicion
			if (e == e2)
			{
				// Vamos a sumar cantidad cada vez que "e" == "e2"
				cant ++;
				// Esto es lo que nos va a permitir poder chequear mas de una posible repeticion de numeros.
				if (cant >= cant2)
				{
					// igualamos la cantidad a otra variable para no perderla y asi comparar las proximas repeticiones.
					cant2 = cant;
					// Y obvio que tambien nos guardamos el valor que vamos a mostrar, el que tenga la mayor cantidad de apariciones en el proyecto.
					valor2 = e;
				}
			}
			else
			{
				//Volvemos a incializar a cantidad para que vuelva a emepezar ya que se terminaron las repeticiones de ese numero en particular
				cant = 1;
			}
	
	}

	// Esta funcion me permite volver al primer registro de mi archivo
	rewind(arch);

	// Leemos el archivo una vez mas para imprimirlo por pantalla
	fread(&e, sizeof(e), 1, arch);
	while (!feof(arch))
	{
		printf("%d, ", e);
		fread(&e, sizeof(e), 1, arch);
	}
	
	printf("el %d aparece %d \n", valor2, cant2);

	fclose(arch);
	
	return 0;
}

int leerRegistro(FILE *f, int numreg) {
	int registro;
	fseek(f, numreg * sizeof(registro), SEEK_SET);
	fread(&registro, sizeof(registro), 1, f);
	return registro;
}

void grabarRegistro(FILE *f, int numreg, int dato) {
	fseek(f, numreg * sizeof(dato), SEEK_SET);
	fwrite(&dato, sizeof(dato), 1, f);
}