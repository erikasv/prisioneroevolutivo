/*
 * Clase para realizar el proceso de juego, evolución y mutación de una
 * población de jugadores
 */
#include "Prisionero.h"

/*
 * Contructor
 * Inicializa los jugadores
 */
Prisionero::Prisionero(int numero, int numMaximoEstados)
{
    /*
     * Crear jugadores e inicializar su máquina de estados
     */
    for(int i=0; i<numero; i++)
    {
		Jugador* tmp = new Jugador(numMaximoEstados);
		tmp->iniciarJugador();

        jugadores.append(tmp);
        //cout << jugadores.at(i) <<endl;
    }

    totalDeJugadores = numero;
	maximoPoblacion = numero;
	maximoEstados=numMaximoEstados;
}

Prisionero::~Prisionero()
{
}

/*
 * Este metodo inicia la matriz de pagos
 */
void Prisionero::iniciarMatrizDePagos(int T, int R, int P, int S)
{
	matrizDePagos = new MatrizDePagos(T,R,P,S);
}

/*
 * Este metodo pone a jugar todos contra todos
 * Juega 1 contra 2,3,..,N
 * Juega 2 contra 3,4...,N
 * .
 * .
 * Juega N-1 contra N
 */
void Prisionero::jugar(int cantidadDeJuegos)
{
    for(int i=0; i<totalDeJugadores; i++)
    {
        for(int j=i+1; j<totalDeJugadores; j++)
        {
            Jugador * jugadorA = jugadores.at(i);
            Jugador * jugadorB = jugadores.at(j);

			jugadorA->obtenerMaquinaEstados()->resetearEstadoPresente();
			jugadorB->obtenerMaquinaEstados()->resetearEstadoPresente();
            	
            for (int var = 0; var < cantidadDeJuegos; var++)
            {
				//Juguemos
				//Jugada estado presente
				int jugadaJugadorA = jugadorA->miJugada();
				int jugadaJugadorB = jugadorB->miJugada();

                //Pasemos al proximo estado
                jugadorA->jugadaOponente(jugadaJugadorB);
                jugadorB->jugadaOponente(jugadaJugadorA);

                //Ganancias para cada uno
                jugadorA->agregarGanancia(matrizDePagos->obtenerGananciaJugador(jugadaJugadorA, jugadaJugadorB));
                jugadorB->agregarGanancia(matrizDePagos->obtenerGananciaJugador(jugadaJugadorB, jugadaJugadorA));                
            }
        }
    }
}

/*
 * Este método devuelve el mejor jugador actual
 */
Jugador* Prisionero::obtenerMejorJugador()
{
	Jugador* mejorJugador = jugadores.at(0);
	for (int i = 1; i < jugadores.size(); ++i)
	{
		if(jugadores.at(i)->obtenerGanancia()>mejorJugador->obtenerGanancia())
			mejorJugador=jugadores.at(i);
	}
	return mejorJugador;
}

/*
 * Este método reduce la población total a un valor dado específico
 */
void Prisionero::reducirPoblacion(int numeroSobrevivientes)
{
	//	Se agrega a la ganancia la penalización/premio por numero de estados
	double numEstadosPromedio=0;

	for (int i = 0; i < jugadores.size(); ++i)
		numEstadosPromedio+=jugadores.at(i)->obtenerNumeroEstados();

	numEstadosPromedio=numEstadosPromedio/(double)(jugadores.size());

	for (int i = 0; i < jugadores.size(); ++i)
		jugadores.at(i)->agregarGanancia(0.1*((numEstadosPromedio-(double)(jugadores.at(i)->obtenerNumeroEstados()))/(double)maximoEstados)*jugadores.at(i)->obtenerGanancia());

	//	Hace un llamado a ordenar los jugadores
	jugadores = ordenar(jugadores);
	int tamano = jugadores.size();
	jugadores.remove(numeroSobrevivientes, tamano-numeroSobrevivientes);
	totalDeJugadores=jugadores.size();
}

/*
 * Cruza los jugadores y produce una nueva generación
 * el tamaño final es cuantos hijos produce.
 * Se asume que la poblacion ya fue reducida
 */
void Prisionero::cruzarJugadores(int tamanoFinalPoblacion)
{
	int tamanoActualPoblacion = jugadores.size();
	int numEstadosA=0, numEstadosB=0, numEstadosC=0, jugadorA, jugadorB, tmp;

	for (int i = 0; i < totalDeJugadores; ++i)
	{
		jugadores.at(i)->resetearGanancia();
	}

	for (int i = 0; i < tamanoFinalPoblacion; ++i)
	{
		jugadorA = (1 + rand() % tamanoActualPoblacion) - 1;
		jugadorB = (1 + rand() % tamanoActualPoblacion) - 1;

		numEstadosA = jugadores.at(jugadorA)->obtenerNumeroEstados();
		numEstadosB = jugadores.at(jugadorB)->obtenerNumeroEstados();

		//Esto hace que el jugador A sea el de la maquina de estados mas pequena
		if(numEstadosA>numEstadosB)
		{
			tmp=numEstadosB;
			numEstadosB=numEstadosA;
			numEstadosA=tmp;
			tmp=jugadorB;
			jugadorB=jugadorA;
			jugadorA=tmp;
		}

		MaquinaDeEstados* maquinaNueva = new MaquinaDeEstados();

//		Aquí se calcula cuantos estados de cada jugador pasaran al hijo
		numEstadosA = (1 + rand() % numEstadosA);
		numEstadosB = (1 + rand() % numEstadosB);
		numEstadosC = numEstadosA + numEstadosB;


		for (int j = 0; j < numEstadosA; ++j)
		{
			QVector<int> estado = jugadores.at(jugadorA)->obtenerMaquinaEstados()->obtenerEstado(j+1);

			int PEC = estado.at(2);
			int PET = estado.at(3);

			if(PEC>numEstadosC) PEC=numEstadosC;
			if(PET>numEstadosC) PET=numEstadosC;

			estado.replace(2, PEC );
			estado.replace(3, PET );

			maquinaNueva->agregarEstados(estado);
		}

		int totalEstadosB = jugadores.at(jugadorB)->obtenerNumeroEstados();

		for (int j = totalEstadosB - numEstadosB; j < totalEstadosB; ++j)
		{
			QVector<int> estado = jugadores.at(jugadorB)->obtenerMaquinaEstados()->obtenerEstado(j+1);
			numEstadosA++;

			int PEC = estado.at(2)+ (numEstadosA - j) -1;
			int PET = estado.at(3)+ (numEstadosA - j) -1;

			if(PEC<1) PEC=1;
			if(PET<1) PET=1;

			estado.replace(0, numEstadosA);
			estado.replace(2, PEC );
			estado.replace(3, PET );

			maquinaNueva->agregarEstados(estado);
		}

		jugadores.append(new Jugador(maquinaNueva,numEstadosC));
	}
	totalDeJugadores=jugadores.size();
}

/*
 * Muta los jugadores.
 * La mutación consiste en intercambiar flechas en la maquina de estados
 * El porcentaje de entrada va de 0 a 1
 */
void Prisionero::mutarJugadores(double porcentajeMutacion)
{
	int totalMutaciones = (int)(porcentajeMutacion*totalDeJugadores);
	int jugadorMutar, numEstados, estadoMutar, estadoCopera, salidaEstado, estadoTraiciona;

	for (int i = 0; i < totalMutaciones; ++i)
	{
		jugadorMutar = (1 + rand() % totalDeJugadores) - 1;
		numEstados   = jugadores.at(jugadorMutar)->obtenerNumeroEstados();
		estadoMutar  = (1 + rand() % numEstados);

		QVector<int> estado = jugadores.at(jugadorMutar)->obtenerMaquinaEstados()->obtenerEstado(estadoMutar);

		salidaEstado = (estado.at(1)==0)? 1 : 0;
		estadoCopera = (1 + (rand() % (numEstados + 1)));
		estadoTraiciona = (1 + (rand() % (numEstados + 1)));

		estado.replace(1,salidaEstado);
		estado.replace(2,estadoCopera);
		estado.replace(3,estadoTraiciona);
		jugadores.at(jugadorMutar)->obtenerMaquinaEstados()->editarEstados(estado);

		if(estadoCopera>numEstados || estadoTraiciona>numEstados)
		{
			numEstados++;
			int * estadoNuevo = new int[4];

			estadoNuevo[0] = numEstados;
			estadoNuevo[1] = (1 + rand() % 2) - 1; //Numeros de 0 a 1
			estadoNuevo[2] = (1 + rand() % numEstados);
			estadoNuevo[3] = (1 + rand() % numEstados);

			jugadores.at(jugadorMutar)->obtenerMaquinaEstados()->agregarEstados(estadoNuevo);
		}
	}
}

void Prisionero::limpiarEstadosJugadores()
{
	int estadosMaximos = jugadores.at(0)->obtenerNumeroEstados();

	for (int i = 1; i < totalDeJugadores; ++i)
	{
		if(estadosMaximos < jugadores.at(i)->obtenerNumeroEstados())
			estadosMaximos = jugadores.at(i)->obtenerNumeroEstados();
	}

	estadosMaximos++;

	int* estadosUtiles = new int[estadosMaximos];

	for (int i = 0; i < totalDeJugadores; ++i)
	{
		for (int j = 0; j < estadosMaximos; j++) estadosUtiles[j]=0;

		auxRecursionLimpiarEstados(estadosUtiles, 1, i);

		int numEstadosUtiles=0;

		for (int j = 0; j < estadosMaximos; ++j)
		{
			numEstadosUtiles += estadosUtiles[j];
			if(estadosUtiles[j]==1)
				estadosUtiles[j]=numEstadosUtiles;
		}

		MaquinaDeEstados* maquina = jugadores.at(i)->obtenerMaquinaEstados();
		MaquinaDeEstados* maquinaNueva = new MaquinaDeEstados();

		for (int j = 0; j < maquina->obtenerNumeroTotalEstados(); ++j)
		{
			int* nuevoEstado = new int[4];

			if(estadosUtiles[maquina->obtenerEstado(j+1).at(0)-1]!=0)
			{
				nuevoEstado[0]= estadosUtiles[maquina->obtenerEstado(j+1).at(0)-1];
				nuevoEstado[1]= estadosUtiles[maquina->obtenerEstado(j+1).at(1)-1];
				nuevoEstado[2]= estadosUtiles[maquina->obtenerEstado(j+1).at(2)-1];
				nuevoEstado[3]= estadosUtiles[maquina->obtenerEstado(j+1).at(3)-1];

				maquinaNueva->agregarEstados(nuevoEstado);
			}
		}

		jugadores.at(i)->definirMaquinaEstados(maquinaNueva);
	}

	if (estadosUtiles !=0 )
		delete [] estadosUtiles;
	estadosUtiles=0;
}

void Prisionero::auxRecursionLimpiarEstados(int* estadosUtiles, int estadoInicial, int numJugador)
{
	if(estadosUtiles[estadoInicial-1]==1)
		return;
	else
	{
		estadosUtiles[estadoInicial-1]=1;
		auxRecursionLimpiarEstados(estadosUtiles, jugadores.at(numJugador)->obtenerMaquinaEstados()->obtenerEstado(estadoInicial).at(2), numJugador);
		auxRecursionLimpiarEstados(estadosUtiles, jugadores.at(numJugador)->obtenerMaquinaEstados()->obtenerEstado(estadoInicial).at(3), numJugador);
	}
}

void Prisionero::imprimirPoblacion()
{
	for(int i=0; i<totalDeJugadores; i++)
	{
		cout<<"Jugador:"<<i<<"\t ganancia: \t"<<jugadores.at(i)->obtenerGanancia()<<"\t numEstados: \t"<<jugadores.at(i)->obtenerNumeroEstados()<<endl;
	}
}

void Prisionero::imprimirGananciaPromedio()
{
	double gananciaPromedio=0;

	for (int i = 0; i < totalDeJugadores; ++i) {
		gananciaPromedio+=jugadores.at(i)->obtenerGanancia();
	}
	gananciaPromedio = gananciaPromedio / totalDeJugadores;

	cout<<"La ganancia promedio es: "<<gananciaPromedio<<endl;
}

void Prisionero::imprimirGananciaMejor()
{
	Jugador* mejorJugador = obtenerMejorJugador();
	cout<<"La ganancia del mejor es: "<<mejorJugador->obtenerGanancia()<<endl;
}

void Prisionero::imprimirTablaEstadosMejor()
{
	obtenerMejorJugador()->imprimirMaquinaDeEstados();
}

/*
 * Método auxiliar que ordena los jugadores
 */
QVector<Jugador *> Prisionero::ordenar(QVector<Jugador *> entrada)
{
	int tamano=entrada.size();

	if(tamano==0 || tamano==1)
		return entrada;
	else
	{
		int mitad = tamano/2;
		QVector<Jugador*> array1, array2;

		for (int i = 0; i < mitad; ++i)
		{
			array1.append(entrada.at(i));
			array2.append(entrada.at(tamano-i-1));
		}
		if(mitad*2<tamano)
			array2.append(entrada.at(mitad));

		return mezclar(ordenar(array1),ordenar(array2));
	}
}

/*
 * Método auxiliar complemento para ordenar.
 */
QVector<Jugador *> Prisionero::mezclar(QVector<Jugador *> entrada1, QVector<Jugador *> entrada2)
{
	QVector<Jugador*> salida;

	int total = entrada1.size() + entrada2.size();

	for (int i = 0; i < total; ++i)
	{
		if(entrada1.size()==0)
		{
			salida.append(entrada2.at(0));
			entrada2.remove(0);
		}
		else if (entrada2.size()==0) {
			salida.append(entrada1.at(0));
			entrada1.remove(0);
		}
		else if(entrada1.at(0)->obtenerGanancia() > entrada2.at(0)->obtenerGanancia()){
			salida.append(entrada1.at(0));
			entrada1.remove(0);
		}
		else{
			salida.append(entrada2.at(0));
			entrada2.remove(0);
		}

	}

	return salida;
}

void Prisionero::inicializarPrisionero(int TC, int CC, int TT, int CT, int cantidadDeJuegos)
{
	iniciarMatrizDePagos(TC, CC, TT, CT);
	jugar(cantidadDeJuegos);
	limpiarEstadosJugadores();
}

void Prisionero::evolucionar(int numeroGeneraciones, int numeroJugadores, int cantidadDeJuegos, double porcentajeSobrevive, double porcentajeMutacion)
{
	for (int i = 0; i < numeroGeneraciones; ++i)
	{
		reducirPoblacion((int)(porcentajeSobrevive*numeroJugadores));
		cruzarJugadores(numeroJugadores);
		mutarJugadores(porcentajeMutacion);
		jugar(cantidadDeJuegos);
		limpiarEstadosJugadores();
	}
}
