Prisionero Evolutivo
====================

Proyecto final de Prisionero Evolutivo. Curso Vida Artificial.

## Creado por:
- Victor Alberto Romero
- Carlos Andres Delgado

# Notas

## Implementado:

- Cromosomas
- Función de Aptitud
- Función de Cruce
- Función de Mutación
- Función de Limpieza de Estados (ver 3)
- Función de visualización
- Menú en el main

# Modelo teórico

1. Los cromosomas se modelaran como una matriz de enteros de cuatro columnas, por un numero variable de filas. Esto será implementado usando cuatro vectores. El primero vector poseerá los datos del estado actual, el segundo los de la jugada del oponente, el tercero la PRÓXIMA jugada propia y el cuarto el próximo estado.
	- Notación

		```
		Estado      := [ESTADOPRESENTE SALIDAEP PROXIMOESTADOSICOOPERAN PROXIMOESTADOSITRAICIONAN]
		Traicionar  := 0
		Cooperar    := 1
		```
	- La matriz de pagos es la misma de las guias, pero puede cambiar (Recordar reglas). Esta definida en el main.
	- Numero de estados: entre 1 y 200 (este valor esta dentro de Jugador.cpp).
	- La tabla de estados esta organizada de tal forma:

		```
		[   [1 X X X]
		    [2 X X X]
			.
			.
		    [N X X X] ]
		```
    - Para acceder a un estado conocido, solo basta con EstadoPresente - 1 
      (Porque el Vector esta indexado desde 0)
    - Poblacion inicial: 40 (Mirar main.cpp)
    - Cada jugador juega contra toda la poblacion unas 200 veces con cada uno

2. Para generar la mutación y la primera generación, se creará un estado
   aleatório, si el estado ya existe pues se usa el existente, sino se crea el
   nuevo.
	- Cruzar:
    		
		Mirar lo de superpoblacion (Cuantos hijos tienen cada jugador).
		
		Propuesta: Tomar dos jugadores, tomar 50% estados de uno y de otro.
		
		Nota: En este caso el numero de estados del hijo debe ser el promedio entre ambos
		
		* Ejemplo:
			
			JugadorA Tiene 40 estados.
			
			JugadorB tiene 120 estados.
			
			Si el valor es impar, tomar piso como mitad.
			
			En este caso el hijo tiene 80 (160/2) estados:
			
			20 son de A y 60 son de B.
			
			Podria ser:
			
			a. Se tomarian los 20 primeros de A y luego los 60 ultimos de B, 
			   recordad que la tabla de estados esta en orden.
			
			b. Se tomarian los 20 primeros de B, luego los 20 ultimos de A y 
			   finalmente los 40 ultimos de B.
			
			c. Otra combinacion pero..., tomar en cuenta que los estados de	A 
			   no pueden estar más alla del estado 40 del hijo.
	- Mutar:
		
		Propuesta: Tomar 10% de los estados, aleatoriamente (sin tomar el mismo) cambiar salida y los dos Proximos Estados por un valor aleatorio.
		
		* Ejemplo:
			
			Hijo tiene 40 estados, 10% son 4 estados, digamos que se seleccionaron 1, 4, 16, 22
			
			Hijo[1 - 1] = [1 1 12 12] Se representa asi [1 X Y Z]  X va entre 0 y 1, Y y Z entre 1 y 40.
			
			Por ejemplo queda asi: [1 0 33 22]
			
			El cromosoma 1 del hijo ha mutado y asi con los 4, 16 y 22.
			
3. La limpieza consiste en que después de efectuar mutación y cruce, se realizará una búsqueda por amplitud en las rutas de la maquina de estados para quitar los estados que nunca son usados. Esto tiene que ser ANTES de aplicar la función de amptitud.

4. Función de visualización.
    - Ganancia de cada jugador
    - Maquina de estados de cada jugador 

5. Funcion de aptitud.
    - Para valores altos de numero de veces que juegan dos jugadores. GananciaJugador >> Numero estados promedio
    - Aptitud = GananciaJugador - Numero estados promedio
    - Pasan 40% mas aptos.
    - Condicion de parada: 1000 iteraciones o GananciasPromedioTodos >= ValorRecompensa*Poblacion*NumerodeVecesqueJueganDosJugadoresunaPartida (Todos cooperan).


