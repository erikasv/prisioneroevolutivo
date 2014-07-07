/*
 * Esta clase implementa el jugador evolutivo
 * Consta de una maquina de estados y una entrada que corresponde a la
 * jugada del adversario
 */
 #include "Jugador.h"
 
Jugador::Jugador(int numMaximoEstados, int retardoPagoIN, double interesIN)
{
	maquinaDeEstados = new MaquinaDeEstados();
	numeroEstados = rand()%numMaximoEstados + 1;
	gananciaJugador = 0;
	estado = new Estado(numeroEstados);
	retardoPago=retardoPagoIN;
	interes=interesIN;
	
	//Vector para pagar asignar el pago de las partidas anteriores
	pagoInmediato=(int)rand()%2;
	if(pagoInmediato){
	  pagos= QVector<int>(0);
	}
	else{
	  pagos= QVector<int>(retardoPago);
	  for (int i=0;i<retardoPago;i++){
	    pagos[i]=0;
	  }
	}
}

Jugador::Jugador(MaquinaDeEstados *maquinaIn, int numeroEstadosIN)
{
	maquinaDeEstados=maquinaIn;
	numeroEstados=numeroEstadosIN;
	gananciaJugador=0;
	estado = new Estado(numeroEstados); //Por lógica de la aplicación nunca se usa
}

Jugador::Jugador(MaquinaDeEstados *maquinaIn, int numeroEstadosIN, bool desicionPadre)
{
	maquinaDeEstados=maquinaIn;
	numeroEstados=numeroEstadosIN;
	gananciaJugador=0;
	estado = new Estado(numeroEstados); //Por lógica de la aplicación nunca se usa
	pagoInmediato=desicionPadre;
}

Jugador::~Jugador()
{
}

/*
 * Este metodo sirve para recibir la jugada del oponente y pasar al próximo estado
 */
void Jugador::jugadaOponente(int jugada)
{
	maquinaDeEstados->irProximoEstado(jugada);
}

/*
* Este método sirve para obtener la jugada del estado presente
*/
int Jugador::miJugada()
{
	return maquinaDeEstados->obtenerSalidaEstadoPresente();
}

/*
* Este método sirve para mutar la decisión del pago inmediato
*/
void Jugador::mutarPagoInmediato()
{
  pagoInmediato=(int)rand()%2;
}

bool Jugador::obtenerPagoInmediato()
{
  return pagoInmediato;
}

/*
 * Este método crea la maquina de estados por primera vez
 */
 void Jugador::iniciarJugador()
 {
    for(int i=0; i<numeroEstados; i++)
    {
        estado->generarEstados();
        int * estadoGenerado = new int[4];

        for(int j=0; j<4; j++)
        {
            estadoGenerado[j] = estado->obtenerEstado(j);
        }
        maquinaDeEstados->agregarEstados(estadoGenerado);
    }
}

/*
 * Método para ir sumando las ganancia del jugador a medida que juega
 */
void Jugador::agregarGanancia(int ganancia)
{
  //Modificada la ganancia asignada en cada juego.
  if(!pagoInmediato){
    gananciaJugador+=ganancia;
  }
  else{
    gananciaJugador+=pagos[0]+(pagos[0]*interes); //Se asume que el interés es por el tiempo de retraso, no por unidad de tiempo.
    pagos.pop_front();
    pagos.append(ganancia);
  }
}

void Jugador::asignarCastigo(int valor)
{
	gananciaJugador+=valor;
}

/*
 * Obtener número de estados de la maquina del jugador
 */
int Jugador::obtenerNumeroEstados()
{
    return maquinaDeEstados->obtenerNumeroTotalEstados();
}

/*
 * Obtener ganancia del jugador
 */
int Jugador::obtenerGanancia()
{
    return gananciaJugador;
}

void Jugador::resetearGanancia()
{
	gananciaJugador=0;
	
	for (int i=0;i<retardoPago;i++){
	  pagos[i]=0;
	}
}

/*
* Devuelve la maquina de estados
*/
MaquinaDeEstados* Jugador::obtenerMaquinaEstados()
{
	return maquinaDeEstados;
}

void Jugador::definirMaquinaEstados(MaquinaDeEstados *maquinaIN)
{
	maquinaDeEstados=maquinaIN;
}

void Jugador::imprimirMaquinaDeEstados()
{
	maquinaDeEstados->imprimirValores();
}
