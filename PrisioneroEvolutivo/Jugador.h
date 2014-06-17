#ifndef JUGADOR_H
#define JUGADOR_H
#include "MaquinaDeEstados.h"
#include <cstdlib> 
#include <QVector>
#include "Estado.h"

using namespace std;

class Jugador
{
	private:
		MaquinaDeEstados *maquinaDeEstados;
		Estado * estado;
		int numeroEstados;
		int gananciaJugador;
		int retardoPago;
		QVector<int> pagos;

	public:
		Jugador(int numMaximoEstados, int retardoPagoIN);
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
