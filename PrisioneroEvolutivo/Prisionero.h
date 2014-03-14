#ifndef PRISIONERO_H
#define PRISIONERO_H
#include "Jugador.h"
#include "MatrizDePagos.h"
#include <QVector>
#include <cstdlib>

using namespace std;

class Prisionero
{
	private:
		/*
		* Grupo de jugadores
		*/
		QVector<Jugador*> jugadores;
		/*
		* Total de jugadores
		*/
		int totalDeJugadores;
		int maximoPoblacion;
		int maximoEstados;
		/*
		* Matriz de pagos
		*/
		MatrizDePagos * matrizDePagos;

	public:
		//	Constructores
		Prisionero(int numeroJugadores, int numMaximoEstados);
		~Prisionero();

		//	Metodos del juego
		Jugador* obtenerMejorJugador();
		void iniciarMatrizDePagos(int T, int R, int P, int S);
		void jugar(int ca1ntidadDeJuegos);
		void limpiarEstadosJugadores();
		void auxRecursionLimpiarEstados(int* estadosUtiles, int estadoInicial, int numJugador);
		void inicializarPrisionero(int TC, int CC, int TT, int CT, int cantidadDeJuegos);

		//	Metodos Evolutivos
		void reducirPoblacion(int numeroSobrevivientes);
		void cruzarJugadores(int tamanoFinalPoblacion);
		void mutarJugadores(double porcentajeMutacion);
		void evolucionar(int numeroGeneraciones, int numeroJugadores, int cantidadDeJuegos, double porcentajeSobrevive, double porcentajeMutacion);

		//	Médotos auxiliares
		QVector<Jugador*> ordenar(QVector<Jugador*> entrada);
		QVector<Jugador*> mezclar(QVector<Jugador*> entrada1, QVector<Jugador*> entrada2);
		void imprimirPoblacion();
		void imprimirGananciaPromedio();
		void imprimirGananciaMejor();
		void imprimirTablaEstadosMejor();

};

#endif // PRISIONERO_H
