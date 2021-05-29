#pragma once
#include "SFML\Graphics.hpp"
#include "SFML/Audio.hpp"
#include "nodo.h"

using namespace std;
using namespace sf;

class enemigoCola
{

public:

	enemigoCola(float h); // constructor, le paso por parametro la coordenada en Y de la plataforma
	void dibujar(RenderWindow& ventana); // para dibujar los nodos

	void loadCola(); // para cargar la cola
	void insertarCola(); //para agregar nodos en la cola
	void removerCola(); // para quitar nodos en la cola
	void actualizar_cola(); // para actualizar las posiciones de los nodos
	void moverCola(); // para mover los shells por la pantalla
	Sprite get_sprite(); // retorna el sprite

private:

	// variable para indicar numero de plataforma
	float piso;

	// variables para asignar el color a los shells de la cola
	int indice_colorCola;
	string colorCola;

	//nodos para Cola, al ppio el primero y ultimo nodo no existen
	nodo* primeroCola = NULL;
	nodo* ultimoCola = NULL;

	float posCola; // posicion de los nodos en la cola
	
};

