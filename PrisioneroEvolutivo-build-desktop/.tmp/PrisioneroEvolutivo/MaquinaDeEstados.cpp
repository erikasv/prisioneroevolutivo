/*
 * Carlos Andres Delgado S
 * Victor Alberto Romero
 * Esta clase implementa la maquina de estados que utiliza cada jugador
 */
 
#include "MaquinaDeEstados.h"

	MaquinaDeEstados::MaquinaDeEstados()
	{
			//tablaDeEstados = new QVector<QVector<int> >();
			estadoPresente = 1; //Estado inicial S1

	}
	
	MaquinaDeEstados::~MaquinaDeEstados(){}
	

	/*
	 * Este metodo modifica el indica de acuerdo a la jugada del oponente
	 * [EP SALIDA PESICOOPERA PESITRAICIONA]
	 */
	void MaquinaDeEstados::irProximoEstado(int jugada)
	{
		//Jugada = 0 Traiciona Jugada = 1 Coopera
		
		//Nota tablaDeEstados.at (Retorna referencia)
		if(jugada == 0)
		{
				estadoPresente = tablaDeEstados[estadoPresente - 1][3];
		}
		else
		{
				estadoPresente = tablaDeEstados[estadoPresente - 1][2];
		}
	}
	
	/*
	 * Esta meotod permite conocer la salida o jugada del jugador en 
	 * estado presente
	 */
	int MaquinaDeEstados::obtenerSalidaEstadoPresente()
	{
		return tablaDeEstados[estadoPresente - 1][1];
	}
	
	/*
	 * Este metodo permite conocer el numero total de estados
	 */
	 
	int MaquinaDeEstados::obtenerNumeroTotalEstados()
	{
		return tablaDeEstados.size();
	}
	
	/*
	 * Este metodo permite agregar estados a la tabla de estados
	 * En orden (Importante)
	 */
	void  MaquinaDeEstados::agregarEstados(QVector<int> estadoEntrada)
	{
		tablaDeEstados.insert(estadoEntrada[0], estadoEntrada);
	}
	
	/*
	 * Este metodo permite cambiar un estado por otro
	 */
	void  MaquinaDeEstados::editarEstados(int estadoPresente, QVector<int> estadoEntrada)
	{
		tablaDeEstados[estadoPresente -1] = estadoEntrada;
	}
