#ifndef JUGADOR_H
#define JUGADOR_H
#include "MaquinaDeEstados.h"
#include <cstdlib> 
#include "Estado.h"

using namespace std;

class Jugador
{
	private:
		MaquinaDeEstados *maquinaDeEstados;
		Estado * estado;
		int numeroEstados;
		int gananciaJugador;

	public:
		Jugador(int numMaximoEstados);
		Jugador(MaquinaDeEstados* maquinaIn, int numeroEstadosIN);
		~Jugador();

		void jugadaOponente(int jugada);
		int miJugada();
		void agregarGanancia(int ganancia);
		void iniciarJugador();
		int obtenerNumeroEstados();
		int obtenerGanancia();
		void resetearGanancia();
		MaquinaDeEstados* obtenerMaquinaEstados();
		void definirMaquinaEstados(MaquinaDeEstados* maquinaIN);
		void imprimirMaquinaDeEstados();
};

#endif // JUGADOR_H
