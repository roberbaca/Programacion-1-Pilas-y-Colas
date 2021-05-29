#pragma once
#include "SFML\Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>

using namespace std;
using namespace sf;

class personaje
{

public:

	personaje();
	void actualizar_pos(Time* tiempo); // calculo de la posicion del personaje
	void actualizar_mov(Event& evento); // eventos con el teclado para mover el personaje
	void cargar_graficos();
	Sprite get_sprite();
	void set_position(float x, float y);
	void set_hitTrue(); 
	bool get_hitState(); // para chequear si el jugador esta colisionando con un enemigo

	

private:

	float posicion_x, posicion_y; // posiciones en x e y
	float velocidad_y; // velocidad en eje y
	float velocidad_x; // velocidad en eje x
	float velocidad_yMax; // velocidad maxima en eje y (para limitar el efecto de la aceleracion de la gravedad)
	float gravedad; // gravedad en eje y
	float altura_salto; // altura maxima que puede alcanzar nuestro personaje
	bool esta_saltando; // bandera para verificar si el personaje esta en el aire
	bool hit; // bandera para saber si el personaje colisiono con un enemigo

	float h0, h1, h2, h3, h4, h5, h6; // coordenadas en Y de cada una de las plataformas

	float limite_derecha, limite_izquierda; // boundaries

	Sprite* spr_personaje;
	Texture* txt_personaje;

	Event* evento;

	Sound snd_jump;
	SoundBuffer buffer;
	
};
