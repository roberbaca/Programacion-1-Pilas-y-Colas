#include "enemigoPila.h"


enemigoPila::enemigoPila(float h) // constructor
{	
	piso = h;

	// bool para chequear cuando una de las pilas esta vacía
	pila_is_empty = true; // pila 1 esta vacia
	pila2_is_empty = true; // pila 2 esta vacia

	loadPila(); // cargamos la pila
}

void enemigoPila::dibujar(RenderWindow &ventana)
{

	// simplemente recorro las pilas para dibujar sus nodos

	nodo* aux;

	if (pila)
	{
		aux = pila;

		while (aux)
		{
			aux->dibujar(ventana);
			aux = aux->siguiente;
		}

		pila->dibujar(ventana);
	}

	nodo* aux2;

	if (pila2)
	{
		aux2 = pila2;

		while (aux2)
		{
			aux2->dibujar(ventana);
			aux2 = aux2->siguiente;
		}

		pila2->dibujar(ventana);
	}
}


void enemigoPila::loadPila()
{
	/* 
		Esto se ejecuta 1 sola vez para crear la primer pila a 
		la derecha de la pantalla.
	*/
	 
	// variables para la Pila
	posPila = 800; // posicion incial del 1er shell en la pila 1
	posPila2 = 0; // posicion incial del 1er shell en la pila 2
	indice_colorPila = 0;
	colorPila = "verde";
	
	for (int j = 0; j < 4; j++) // agrego 4 shells a la pila. 
	{
		pushPila(nuevo_shell);
	}
}


void enemigoPila::pushPila(nodo *nuevo_shell)
{
	// agregamos nuevos nodos a la pila

	posPila -= 30; // cada vez que ingresa un nuevo nodo a la pila, se mueve una posicion a la izquierda

	// llevo un indice para crear nodos con distintos colores
	switch (indice_colorPila)
	{
	case 0:
		colorPila = "verde";
		break;

	case 1:
		colorPila = "azul";
		break;

	case 2:
		colorPila = "rojo";
		break;

	case 3:
		colorPila = "amarillo";
		break;
	}

	nuevo_shell = new nodo({ posPila,piso }, colorPila); // creo un nuevo nodo a la pila.
	nuevo_shell->siguiente = pila; // le indicamos que el siguiente es el total de la pila
	pila = nuevo_shell; // modifico la pila
	 
	// para ir variando entre los 4 colores de shell posibles:
	if (indice_colorPila < 3)
	{
		indice_colorPila++;
	}

	else
	{
		indice_colorPila = 0;
	}

}

void enemigoPila::popPila()
{
	// saco los nodos de la pila 1 empezando desde el ultimo agregado y los agrego a la Pila 2 en la izquierda de la pantalla

	if ((pila) && (pila->get_positionX() < posPila2 + 31)) 
	{
		nodo* aux = pila; // accedo al primer nodo de la pila
		aux->get_sprite() = pila->get_sprite(); // guardo su valor
		colorPila2 = aux->get_color(); // guardo su color
		pila = aux->siguiente;// MODIFICO la pila indicando que el tope ahora es la siguiente a la primera
		// delete aux;//dejo de reservar la memoria para ese nodo quitado. No lo elimino para poder agregarlo a la Pila 2
		
		pushPila2(aux); // agrego un nodo a la pila 2
	}

	// cuando la pila 1 esta vacia, significa que la pila 2 esta completa
	if (pila == NULL)
	{
		posPila = 800;
		pila_is_empty = true;
		pila2_is_empty = false;
	}
}


void enemigoPila::pushPila2(nodo* aux2)
{
	// agregamos nuevos nodos a la pila

	posPila2 += 30; // cada vez que ingresa un nuevo nodo a la pila, se mueve una posicion a la derecha
	
	aux2 = new nodo({ posPila2,piso }, colorPila2); // creo un nuevo nodo a la pila.
	aux2->siguiente = pila2; // le indicamos que el siguiente es el total de la pila
	pila2 = aux2; // modifico la pila
}


void enemigoPila::popPila2()
{
	// saco los nodos de la pila 2 empezando desde el ultimo agregado y los agrego a la Pila 1 en la derecha de la pantalla

	if ((pila2) && (pila2->get_positionX() > posPila - 31))
	{
		nodo* aux2 = pila2; //accedo al primer nodo de la pila
		aux2->get_sprite() = pila2->get_sprite(); // guardo su valor
		colorPila = aux2->get_color(); // guardo su color
		pila2 = aux2->siguiente;// MODIFICO la pila indicando que el tope ahora es la siguiente a la primera
		// delete aux; dejo de reservar la memoria para ese elemento quitado. No lo elimino para poder agregarlo a la Pila 1

		pushPila(aux2); // agrego un nodo a la pila 1
	}

	// cuando la pila 2 esta vacia, significa que la pila 1 esta completa
	if (pila2 == NULL)
	{
		posPila2 = 0;
		pila_is_empty = false;
		pila2_is_empty = true;
	}
}


void enemigoPila::moverPila()
{
	/* 
		Esta funcion hace que los nodos avancen por la pantalla.
		Si la Pila de la izquierda esta vacia, entonces puedo mover los
		nodos de la pila 1 hacia la pila 2 . Y viceversa.
	*/
   
  	if ((pila2_is_empty) && (pila != NULL))
	{
		pila->mover(-6); // movimiento a la izquierda
	}	

	if ((pila_is_empty) && (pila2 != NULL))
	{
		pila2->mover(6); // movimiento a la derecha
	}
}

Sprite enemigoPila::get_spritePila()
{
	if (pila)
	{
		return pila->get_sprite();
	}
}


Sprite enemigoPila::get_spritePila2()
{
	if (pila2)
	{
		return pila2->get_sprite();
	}

}

