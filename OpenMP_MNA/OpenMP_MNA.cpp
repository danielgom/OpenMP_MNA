#include <iostream>
#include <omp.h>
#include <random>

#define N 100 // Numero de elementos del arreglo
#define chunk 5 // Pedazos que tomara cada hilo del arreglo, entre mas grande, menos hilos se usaran
#define mostrar 40 // La cantidad de elementos que se mostraran de cada arreglo

using namespace std;

void imprimeArreglo(float *d);
void iniciaArregloConValoresAleatorios(float* array, int size);

int main()
{
    cout << "Sumando arreglos en paralelo\n";

	// Se declaran los arreglos a utilizar
	float a[N], b[N], c[N];

	// Se llena el arreglo a con los numeros aleatorios
	iniciaArregloConValoresAleatorios(a, N);

	// Se llena el arreglo b con los numeros aleatorios
	iniciaArregloConValoresAleatorios(b, N);

	int pedazos = chunk;

	int i;

	// El siguiente bloque de codigo cofigura a OpenMP
	// Se indican los pedazos que cada hilo tomara de cada uno de los arreglos a, b, c
	// Por ultimo se planifican estos pedazos para cada hilo
	#pragma omp parallel for \
	shared(a, b, c, pedazos) private(i) \
	schedule(static, pedazos)

	// El siguiente codigo ya esta configurado para que se ejecute en paralelo

	// Suma de los elementos del arreglo A y B que se guardan en el arreglo C
	for (int i = 0; i < N; i++)
	{
		c[i] = a[i] + b[i];
	}

	// Se imprimen los arreglos y sus contenidos.
	cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << endl;
	imprimeArreglo(a);
	cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << endl;
	imprimeArreglo(b);
	cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << endl;
	imprimeArreglo(c);
}

// imprimeArreglo imprime de mejor manera visual el arreglo.
void imprimeArreglo(float *d) {
	for (int x = 0; x < mostrar; x++)
	{
		cout << d[x] << " - ";
	}
	cout << endl;
}

// iniciaArregloConValoresAleatorios genera un arreglo con tamaño definido con valores aleatorios del 0-1000
void iniciaArregloConValoresAleatorios(float* arreglo, int tamaño) {
	// Como su descripcion lo indica  // class to generate random numbers (from hardware where available)
	// Esta funcion es una clase que se usa para generar numeros aleatorios desde el hardware
	// Esta siendo usada aqui de manera que genera un "seed" la cual es la base para crear numeros aleatorios
	random_device rd;


	// Esta funcion se llama "Mersenne twister pseudo-random generator"
	// la cual genera un numero aleatorio de 32 bits con un estado de 19937 bits
	// esta funcion junto con el seed nos asegura que en cada ejecucion del programa
	// se tengan numeros aleatorios diferentes a la ejecucion anterior.
	mt19937 gen(rd());


	// Esta funcion genera una distribucion uniforme de numeros flotantes desde
	// 0 hasta 1000.
	uniform_real_distribution<> distr(0, 1000);

	// Por ultimo hacemos un For de manera secuencial para llenar los arreglos con numeros aleatorios
	// Vemos que el tamaño de los arreglos es dictado por el argumento de la funcion.
	for (int i = 0; i < tamaño; i++) {
		arreglo[i] = distr(gen);
	}
}