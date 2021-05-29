#pragma once
#include "SFML\Graphics.hpp"
#include "SFML/Audio.hpp"
#include "nodo.h"

using namespace std;
using namespace sf;

class enemigoPila
{

public:

	enemigoPila(float h); // constructor, le paso por parametro la coordenada en Y de la plataforma
	void dibujar(RenderWindow& ventana); // para dibujar los nodos
	
	void loadPila(); // cargo la primer pila
	void pushPila(nodo *nuevo_shell); // para agregar nodos en la pila 1
	void popPila(); // para quitar nodos en la pila 1
	void pushPila2(nodo *aux); // para agregar nodos en la pila 2
	void popPila2(); // para quitar nodos en la pila 2
	void moverPila(); // para mover los shells de las pilas
	
	Sprite get_spritePila();
	Sprite get_spritePila2();

private:

	// variable para indicar numero de plataforma
	float piso;
	
	// variables para asignar el color a los shells de la pila:
	int indice_colorPila;
	int indice_colorPila2;
	string colorPila;
	string colorPila2;
	
	nodo* pila = NULL; // pila a la derecha de la pantalla
	nodo* pila2 = NULL; // pila a la izquierda de la pantalla
	nodo* nuevo_shell;
		
	float posPila; // posicion de los nodos en la pila
	float posPila2; // posicion de los nodos en la pila

	// banderas para chequear si la pila esta vacia
	bool pila_is_empty;
	bool pila2_is_empty;
};

