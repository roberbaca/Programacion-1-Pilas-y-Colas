#pragma once
#include "SFML\Graphics.hpp"
#include "SFML/Audio.hpp"
#include "personaje.h"
#include "puerta.h"
#include "enemigoPila.h"
#include "enemigoCola.h"


using namespace std;
using namespace sf;

class juego
{

public:

	juego(Vector2i resolucion, string titulo); // constructor

	void cargar_imagenes();
	void procesar_eventos();
	void game_loop();
	void dibujar();
	void chequear_colisiones();
	void fin_juego();
	void actualizarContador();
	void play_sounds();

private:

	RenderWindow* ventana1;
	View* camara1;
	Event* evento1;

	bool gameOver; // bandera para fin del juego

	// variables para controlar el tiempo y los fps
	float fps, tiempoFrame, tiempo2;
	Time* tiempo1;
	Time* dt;
	Clock* reloj1;
	Clock* reloj2;
	Clock relojContador;

	// variables para controlar el cronometro en reversa
	int tiempo_juego;
	float tiempoInicio;
	float tiempoFin;
	int seconds;
	bool alarm;
	bool sound_on;

	// texto y fuentes
	Text textoContador;
	Font fuenteContador;

	// sonidos
	Sound snd_timer;
	Sound snd_hit;
	Sound snd_gameOver;
	Sound snd_victory;

	SoundBuffer buffer_timer;
	SoundBuffer buffer_hit;
	SoundBuffer buffer_gameOver;
	SoundBuffer buffer_victory;
	

	// musica del juego
	Music musica;
	
	// sprite y textura del background
	Sprite* spr_fondo;
	Texture* txt_fondo;

	// creo una instancia de la puerta
	puerta* door;
	
	// creo una instancia del enemigo
	enemigoPila* enemyPila1 = NULL;
	enemigoCola* enemyCola1 = NULL;
	enemigoPila* enemyPila2 = NULL;
	enemigoCola* enemyCola2 = NULL;
	enemigoPila* enemyPila3 = NULL;
	enemigoCola* enemyCola3 = NULL;

	// creo una instancia del personaje
	personaje* player1;

	float h0, h1, h2, h3, h4, h5, h6; // pisos
};

