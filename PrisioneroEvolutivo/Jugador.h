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
		double numeroEstados;
		int gananciaJugador;
		int retardoPago;
		QVector<int> pagos;
		bool interes;
		bool pagoInmediato; //1 true -> desea el pago inmedaito
		bool recienJugo;
		int grupo;

	public:
		Jugador(int numMaximoEstados, int retardoPagoIN, double interesIN);
		Jugador(MaquinaDeEstados* maquinaIn, int numeroEstadosIN);
		Jugador(MaquinaDeEstados* maquinaIn, int numeroEstadosIN, bool desicionPadre);
		~Jugador();

		void jugadaOponente(int jugada);
		int miJugada();
		bool obtenerPagoInmediato();
		void mutarPagoInmediato();
		bool obtenerRecienJugo();
		void asignarRecienJugo(bool val);
		int obtenerGrupo();
		void agregarGanancia(int ganancia);
		void asignarCastigo(int valor);
		void asignarPagoExtra(double pago);
		void iniciarJugador();
		int obtenerNumeroEstados();
		int obtenerGanancia();
		void resetearGanancia();
		MaquinaDeEstados* obtenerMaquinaEstados();
		void definirMaquinaEstados(MaquinaDeEstados* maquinaIN);
		void imprimirMaquinaDeEstados();
};

#endif // JUGADOR_H
