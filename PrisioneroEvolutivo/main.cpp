/*
 * Carlos Andres Delgado 
 * Victor Alberto Romero
 * Proyecto Software Vida Artificial
 * Feb - Jun 2011
 */
#include <QtCore/QCoreApplication>
#include <iostream>
#include "Prisionero.h"
#include <time.h> 
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{
	/*
	* Generar numeros aleatorios diferentes
	* Se utiliza hora del sistema y PID del proceso
	*/
	srand(time(NULL) + getpid());

	//	Parámetros modificables mediante entrada
	int numeroGeneraciones= 1000;
	int numeroJugadores = 50;
	int cantidadDeJuegos=100; //CAMBIAR ESTO POR PROBABILIDAD DE ENCUENTROS. VER LIBRO PARA COMPROBAR VALOR.
	int retardoPago=0;
	double repartoPago=0.0;

	if(argc==4)
	{
		numeroGeneraciones = atoi(argv[1]);
		numeroJugadores    = atoi(argv[2]);
		cantidadDeJuegos   = atoi(argv[3]);
	}
	else if(argc==6)
	{
		numeroGeneraciones = atoi(argv[1]);
		numeroJugadores    = atoi(argv[2]);
		cantidadDeJuegos   = atoi(argv[3]);
		retardoPago	   = atoi(argv[3]);
		repartoPago        = atof(argv[5]);
	}

	//	Parámetros modificables en ejecución
	int numeroInicialEstados=200; //ERIKA: PORQUE ESE VALOR???
	double porcentajeSobrevive=0.6; //Debería llamarse matingpool :P
	double porcentajeMutacion=0.1;

	char respuesta;
	cout<<"¿Desea cambiar los valores específicos de la aplicación?[Y/N]"<<endl;
	cin>>respuesta;

	if(toupper(respuesta)=='Y')
	{
		cout<<"¿Cual desea que sea el número inical de estados?"<<endl;
		cin>>numeroInicialEstados;
		cout<<"¿Cual es el porcentaje de supervivencia? (en un rango de 0 a 1)"<<endl;
		cin>>porcentajeSobrevive;
		cout<<"¿Cual es el porcentaje de mutación? (en un rango de 0 a 1)"<<endl;
		cin>>porcentajeMutacion;
		cout<<"¿Cual es el retardo para el pago? (en un rango de 0 a 1)"<<endl;
		cin>>retardoPago;
		cout<<"¿Cual es el porcentaje de reparto del pago? (en un rango de 0 a 1)"<<endl;
		cin>>repartoPago;
	}

	int TC = 5;
	int CC = 3;
	int TT = 1;
	int CT = 0;

	cout<<"¿Desea cambiar los valores de la matriz de pesos??[Y/N]"<<endl;
	cin>>respuesta;

	if(toupper(respuesta)=='Y')
	{
		cout<<"¿Cual es mi ganancia si yo traiciono y mi compañero coopera?"<<endl;
		cin>>TC;
		cout<<"¿Cual es mi ganancia si yo coopero y mi compañero coopera?"<<endl;
		cin>>CC;
		cout<<"¿Cual es mi ganancia si yo traiciono y mi compañero traiciona?"<<endl;
		cin>>TT;
		cout<<"¿Cual es mi ganancia si yo coopero y mi compañero traiciona?"<<endl;
		cin>>CT;
	}

	Prisionero * objPrisionero = new Prisionero(numeroJugadores,numeroInicialEstados, retardoPago, repartoPago);
	objPrisionero->inicializarPrisionero(TC,CC,TT,CT,cantidadDeJuegos); //Se podrían pasar los valores T>C>P>S directamente, me parece más claro

	cout<<endl<<"--------------------------------------------------------------------"<<endl;
	cout<<"----------------------   Población Inicial   -----------------------"<<endl;
	cout<<"--------------------------------------------------------------------"<<endl<<endl;
	//	objPrisionero->imprimirPoblacion();
	objPrisionero->imprimirGananciaPromedio();
	objPrisionero->imprimirGananciaMejor();
	cout<<endl<<"Tabla de estados del mejor jugador:"<<endl;
	objPrisionero->imprimirTablaEstadosMejor();

	objPrisionero->evolucionar(numeroGeneraciones,numeroJugadores,cantidadDeJuegos,porcentajeSobrevive,porcentajeMutacion);

	cout<<endl<<"--------------------------------------------------------------------"<<endl;
	cout<<"----------------------   Población Final   -------------------------"<<endl;
	cout<<"--------------------------------------------------------------------"<<endl<<endl;
	//	objPrisionero->imprimirPoblacion();
	objPrisionero->imprimirGananciaPromedio();
	objPrisionero->imprimirGananciaMejor();
	cout<<endl<<"Tabla de estados del mejor jugador:"<<endl;
	objPrisionero->imprimirTablaEstadosMejor();

    return 0;
	
}
