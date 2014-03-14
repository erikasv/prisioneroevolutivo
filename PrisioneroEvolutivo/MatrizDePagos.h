#ifndef MATRIZDEPAGOS_H
#define MATRIZDEPAGOS_H

class MatrizDePagos
{
	/*
	* Forma de la matriz de pagos
	* |C C  C T|
	* |T C  T T|
	*
	* |R R  S T|
	* |T T	T T|
	*
	* Debe cumplirse que
	* T > R > P > S
	* (T+S)/2 < R
	*/
	int T,R,P,S;

	public:
		MatrizDePagos(int T, int R, int P, int S);
		~MatrizDePagos();

		int obtenerGananciaJugador(int jugadaPropia, int jugadaOponente);
};

#endif // MATRIZDEPAGOS_H

