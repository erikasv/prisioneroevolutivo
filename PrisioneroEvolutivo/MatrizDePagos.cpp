/*
* Carlos Andres Delgado
* Victor Alberto Romero
* 
* Esta clase se utiliza para almacenar la matriz de pagos y retornar
* los puntos por jugador de acuerdo a alguna jugada
*/
#include "MatrizDePagos.h"

MatrizDePagos::MatrizDePagos(int T, int R, int P, int S)
{
	this->T = T;
	this->R = R;
	this->P = P;
	this->S = S;
	reparto=0.0;
}

MatrizDePagos::~MatrizDePagos()
{
}

void setReparto(double repartoIN)
{
    reparto=repartoIN;
}

int MatrizDePagos::obtenerGananciaJugador(int jugadaPropia, int jugadaOponente)
{
    switch(jugadaPropia)
    {
        case 0:
                if(jugadaOponente == 0)
                {
                    //TraicionarYo - TraicionarOponente
                    return P;
                }
                else
                {
                    //TraicionarYo - CooperarOponente
                    return T;
                }
                break;

        case 1:
                if(jugadaOponente == 0)
                {
                    //CooperarYo - TraicionarOponente
                    return S;
                }
                else
                {
                    //CooperarYo - CooperarOponente
                    return R;
                }
                break;

				default: return 0; break; //Estos return 0 son para evitar el warning ERIKA:???
    }
    return 0;
}
