#ifndef ESTADO_H
#define ESTADO_H
#include <cstdlib> 
#include <iostream>

using namespace std;

class Estado
{
	/*
	* Este arreglo contiene los 4 elementos de un estado
	*/
	int * estadoPE;

	/*
	* Esta variable contiene el numero de estados
	*/
	int numeroEstados;

	/*
	* Esta variable contiene el estado actual
	*/
	int estadoActual;

	public:
		Estado(int numeroEstados);
		~Estado();

		void generarEstados();
		int obtenerEstado(int posicion);
};

#endif // ESTADO_H
