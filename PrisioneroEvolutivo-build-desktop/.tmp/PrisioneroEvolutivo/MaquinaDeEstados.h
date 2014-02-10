#ifndef MAQUINADEESTADOS_H
#define MAQUINADEESTADOS_H

#include <QVector>

class MaquinaDeEstados
{
	/*
	 * Tabla de estados contiene una lista de estados
	 * Son dos vectores por estado cada uno con una jugada distinta
	 * del oponente
	 * Traicionar = 0
	 * Cooperar = 1
	 * Cada estado tiene la siguiente forma
	 * [EstadoPresente salida PESiCooperan PESiTraicionan]
	 */
	QVector<QVector<int> > tablaDeEstados;
	
	
	/*
	 * Indica cual es el estado presente actual
	 * 
	 * este valor para indexar debe ser operado de la siguiente forma
	 * indice = (estadoPresente - 1)	 
	 *  Se resta uno porque se cuenta desde 1 y no 0.
	 */
	int estadoPresente;
	
public:
	MaquinaDeEstados();
	~MaquinaDeEstados();
	
	void irProximoEstado(int jugada);
	int obtenerSalidaEstadoPresente();
	int obtenerNumeroTotalEstados();
	
	void agregarEstados(QVector<int> estadoEntrada);
	void editarEstados(int estadoPresente, QVector<int> editarEstados);
	
};

#endif // MAQUINADEESTADOS_H
