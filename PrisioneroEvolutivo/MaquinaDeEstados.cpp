/*
 * Carlos Andres Delgado S
 * Victor Alberto Romero
 * Esta clase implementa la maquina de estados que utiliza cada jugador
 */
 
#include "MaquinaDeEstados.h"

MaquinaDeEstados::MaquinaDeEstados()
{
    tablaDeEstados = new QVector<QVector<int> >();
    estadoPresente = 1; //Estado inicial S1
}

MaquinaDeEstados::~MaquinaDeEstados()
{
}

/*
 * Este metodo modifica el indica de acuerdo a la jugada del oponente
 * [EP SALIDA PESICOOPERA PESITRAICIONA]
 */
void MaquinaDeEstados::irProximoEstado(int jugada)
{
    //Jugada = 0 Traiciona -- Jugada = 1 Coopera

    //Nota tablaDeEstados.at (Retorna referencia)
    if(jugada == 0)
    {
        estadoPresente = tablaDeEstados->at(estadoPresente - 1).at(3);
    }
    else
    {
        estadoPresente = tablaDeEstados->at(estadoPresente - 1).at(2);
    }
}

/*
 * Esta meotod permite conocer la salida o jugada del jugador en
 * estado presente
 */
int MaquinaDeEstados::obtenerSalidaEstadoPresente()
{
    return tablaDeEstados->at(estadoPresente - 1).at(1);
}

/*
 * Este metodo permite conocer el numero total de estados
 */
int MaquinaDeEstados::obtenerNumeroTotalEstados()
{
    return tablaDeEstados->size();
}

/*
 * Este metodo permite agregar estados a la tabla de estados
 * El indice es el estado de entrada - 1
 * Recordad: Los estados inician desde 1 y no 0
 */
void  MaquinaDeEstados::agregarEstados(int * estadoEntrada)
{
    QVector<int> estado;
    estado << estadoEntrada[0] << estadoEntrada[1] << estadoEntrada[2] << estadoEntrada[3];
    tablaDeEstados->insert(estado[0] - 1, estado);
}

void  MaquinaDeEstados::agregarEstados(QVector<int> estadoEntrada)
{
	tablaDeEstados->insert(estadoEntrada.at(0) - 1, estadoEntrada);
}

/*
 * Este metodo permite cambiar un estado por otro
 */
void  MaquinaDeEstados::editarEstados(int * estadoEntrada)
{
    QVector<int> estado;
    estado << estadoEntrada[0] << estadoEntrada[1] << estadoEntrada[2] << estadoEntrada[3];
    tablaDeEstados->replace(estado[0] - 1, estado);
}

void MaquinaDeEstados::editarEstados(QVector<int> estadoEntrada)
{
	tablaDeEstados->replace(estadoEntrada.at(0)-1, estadoEntrada);
}

QVector<int> MaquinaDeEstados::obtenerEstado(int numEstado)
{
	return tablaDeEstados->at(numEstado-1);
}

void MaquinaDeEstados::resetearEstadoPresente()
{
	estadoPresente=1;
}

void MaquinaDeEstados::eliminarEstado(int numEstado)
{
	tablaDeEstados->remove(numEstado-1);
}

void MaquinaDeEstados::imprimirValores()
{
	int numeroEstados = tablaDeEstados->size();

	cout<<"+--------------------------------+"<<endl;
	cout<<"|        Tabla de Estados        |"<<endl;
	cout<<"+--------------------------------+"<<endl;
	cout<<"| EP \t S \t PEC \t PET \t |"<<endl;

	cout<<"|                                |"<<endl;
	for (int i = 0; i < numeroEstados; ++i)
	{
		int estado = tablaDeEstados->at(i).at(0);
		char salida = 'C';
		if(tablaDeEstados->at(i).at(1) == 0) salida='T';
		int PEC = tablaDeEstados->at(i).at(2);
		int PET = tablaDeEstados->at(i).at(3);
		cout<<"| "<<estado<<" \t "<<salida<<" \t "<<PEC<<" \t "<<PET<<"\t |"<<endl;
	}

	cout<<"+--------------------------------+"<<endl;
}
