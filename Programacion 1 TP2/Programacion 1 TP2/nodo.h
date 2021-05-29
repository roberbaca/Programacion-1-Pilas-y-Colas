#pragma once
#include "SFML\Graphics.hpp"
#include "SFML/Audio.hpp"

using namespace std;
using namespace sf;

class nodo
{

public:

	nodo(Vector2f coord, string colorShell);
	
	void dibujar(RenderWindow& ventana);
	void cargar_graficos();
	Sprite get_sprite(); // devuelve el sprite
	void mover(int velocidad); // permite el movimiento de los shell
	float get_positionX(); // devuelve la posicion en x
	void set_texture(string textura); // permite cambiar textura para asignar los distintos colores de lo shell
	void set_position(Vector2f coord); // permite cambiar la posicion
	String get_color(); // para obtener el color asignado al nodo

private:

	Vector2f coordenadas;

	//sprite y texturas de los shell
	Sprite* spr_shell;
	Texture* txt_shell;
	string colorNodo;
	nodo* siguiente;

	//clases amigas para que puedan acceder a los atributos privados
	friend class enemigoPila; 
	friend class enemigoCola;
};


