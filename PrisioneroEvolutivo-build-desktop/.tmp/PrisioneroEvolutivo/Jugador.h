#ifndef JUGADOR_H
#define JUGADOR_H

class Jugador
{
private:
	MaquinaDeEstados maquinaDeEstados();
public:

	Jugador();
	~Jugador();

	jugadaOponente(int jugada);
	int miJugada();	
	
};

#endif // JUGADOR_H
