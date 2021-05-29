#include "enemigoCola.h"


enemigoCola::enemigoCola(float h) // constructor
{
	piso = h;
	loadCola(); // cargamos la cola
}


void enemigoCola::loadCola()
{
	posCola = 120; // posicion en X incial del 1er shell
	indice_colorCola = 0;
	colorCola = "verde";

	for (int i = 0; i < 4; i++) // agrego 4 shells a la cola
	{
		posCola = 120 - i * 30;
		insertarCola();
	}
}


void enemigoCola::insertarCola()
{
	// agregamos nuevos nodos a la cola

	// llevo un indice para crear nodos con distintos colores
	switch (indice_colorCola)
	{
	case 0:
		colorCola = "verde";
		break;

	case 1:
		colorCola = "azul";
		break;

	case 2:
		colorCola = "rojo";
		break;

	case 3:
		colorCola = "amarillo";
		break;
	}

	nodo* nuevo_nodo = new nodo({ posCola,piso }, colorCola); // reservamos la memoria para el nuevo nodo
	nuevo_nodo->siguiente = NULL; // le indicamos que no tiene otro nodo despues de él

	// si no es el primer nodo que insertamos en la cola
	if (!primeroCola)
	{
		primeroCola = nuevo_nodo; // esto se ejecuta una sola vez. El primero será el que creamos anteriomente
	}

	else
	{
		// como no es el primer nodo, vamos a decir que el siguiente del último es el que creamos
		ultimoCola->siguiente = nuevo_nodo;
	}

	// y finalmente, siempre el que creamos actualmente es el último
	ultimoCola = nuevo_nodo;

	// para ir variando entre los 4 colores de shell posibles:
	if (indice_colorCola < 3)
	{
		indice_colorCola++;
	}

	else
	{
		indice_colorCola = 0;
	}
}


void enemigoCola::removerCola()
{
	// saco lo elementos de la cola empezando desde el primer agregado y los llevo a la derecha de la pantalla

	if (primeroCola->get_positionX() > 800) // si el primero de la cola se fue de la pantalla, entonces lo elimino de la cola:
	{
		nodo* aux = primeroCola; // accedo al primer nodo de la cola

		aux->get_sprite() = primeroCola->get_sprite(); // guardo su valor

		primeroCola = aux->siguiente; // modifico la cola, ahora el primero es la siguiente

		delete aux; // dejo de reservar la memoria para el nodo que saque. 

		actualizar_cola(); // actualizo las posiciones de los nodos restantes en la cola

		insertarCola(); // agrego un nuevo nodo a la cola
	}
}


void enemigoCola::dibujar(RenderWindow& ventana)
{
	// simplemente recorro la cola para dibujar sus nodos

	nodo* aux_cola;

	if (primeroCola)
	{
		aux_cola = primeroCola;

		while (aux_cola)
		{
			aux_cola->dibujar(ventana);
			aux_cola = aux_cola->siguiente;
		}

		primeroCola->dibujar(ventana);
	}
}


void enemigoCola::moverCola()
{
	/*
		Esta funcion hace que los nodos avancen por la pantalla.
		Le paso por parametro el sentido de movimiento, positivo
		para el movimiento a la derecha y negativo para el
		desplazamiento hacia la izquierda de la pantalla.
	*/

	if (primeroCola)
	{
		primeroCola->mover(4);
	}
}


void enemigoCola::actualizar_cola()
{
	/*
		Actualizamos las posiciones de los nodos.
		Cuando el primero sale de la pantalla, los otros
		nodos se mueven una posicion hacia adelante.
	*/

	nodo* aux3;

	if (primeroCola)
	{
		primeroCola->set_position({ 120, piso });
		aux3 = primeroCola;
		aux3 = aux3->siguiente;
		aux3->set_position({ 90, piso });
		aux3 = aux3->siguiente;
		aux3->set_position({ 60, piso });
	}
}


Sprite enemigoCola::get_sprite()
{
	return primeroCola->get_sprite();
}
