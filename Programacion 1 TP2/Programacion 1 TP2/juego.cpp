#include "juego.h"


juego::juego(Vector2i resolucion, string titulo)
{
	fps = 60.f; // para que corra a 60 frames por segundo
	ventana1 = new RenderWindow(VideoMode(resolucion.x, resolucion.y), titulo);
	ventana1->setFramerateLimit(fps);

	// coordenadas en el eje Y de cada piso
	h0 = 524;
	h1 = 449;
	h2 = 374;
	h3 = 298;
	h4 = 222;
	h5 = 149;
	h6 = 73;

	gameOver = false;

	cargar_imagenes();

	evento1 = new Event;

	// incializamos los relojes:
	reloj1 = new Clock;
	reloj2 = new Clock;
	tiempo1 = new Time;
	dt = new Time;
	alarm = false;

	// cronometro
	tiempoInicio = 0.f;
	tiempoFin = 0.f;
	tiempo_juego = 30; // contador en reversa de 30 seg.
	seconds = 0;

	// incializamos la puerta
	door = new puerta();

	// incializamos los enemigos:	
	enemyCola1 = new enemigoCola(h1); // creo una cola en el piso 1
	enemyPila1 = new enemigoPila(h2); // creo una pila en el piso 2
	enemyCola2 = new enemigoCola(h3); // creo una cola en el piso 3
	enemyPila2 = new enemigoPila(h4); // creo una pila en el piso 4
	enemyCola3 = new enemigoCola(h5); // creo una cola en el piso 5
	enemyPila3 = new enemigoPila(h6); // creo una pila en el piso 6

	// incializamos el personaje
	player1 = new personaje();

	sound_on = false;

	// para reproducir la musica del juego (con loop)
	if (!musica.openFromFile("resources/music/musica1.wav"))
	{
		// error		
	}
	musica.setLoop(true);
	musica.play();

	
	// SONIDOS

	if (!buffer_timer.loadFromFile("resources/sounds/timer.wav"))
	{
		// Error...
	}
	snd_timer.setBuffer(buffer_timer);

	if (!buffer_victory.loadFromFile("resources/sounds/levelend.wav"))
	{
		// Error...
	}
	snd_victory.setBuffer(buffer_victory);

	if (!buffer_gameOver.loadFromFile("resources/sounds/gameOver.wav"))
	{
		// Error...
	}
	snd_gameOver.setBuffer(buffer_gameOver);

	if (!buffer_hit.loadFromFile("resources/sounds/takedamage.wav"))
	{
		// Error...
	}
	snd_hit.setBuffer(buffer_hit);


	// loop principal del juego
	game_loop(); 

}


void juego::cargar_imagenes()
{
	ventana1->setMouseCursorVisible(false); // oculatmos el cursor del mouse

	// cargamos las texturas del background
	txt_fondo = new Texture;
	txt_fondo->loadFromFile("resources/images/fondo_plataformas.png");
	spr_fondo = new Sprite(*txt_fondo);

	// fuente para el contador en reversa
	if (!fuenteContador.loadFromFile("resources/fonts/Square.ttf"))
	{
		//error
	}

	textoContador.setFont(fuenteContador);
	textoContador.setCharacterSize(24);
}



void juego::procesar_eventos()
{
	while (ventana1->pollEvent(*evento1))
	{
		switch (evento1->type)
		{
		case Event::Closed:
			exit(1);
			break;
		}
	}
}


void juego::dibujar()
{
	// dibujamos el background, la puerta y al personaje del jugador
	ventana1->draw(*spr_fondo);
	ventana1->draw(door->get_sprite());
	ventana1->draw(player1->get_sprite());

	
	// dibujamos pilas y colas
	enemyPila1->dibujar(*ventana1);
	enemyCola1->dibujar(*ventana1);

	enemyPila2->dibujar(*ventana1);
	enemyCola2->dibujar(*ventana1);

	enemyPila3->dibujar(*ventana1);
	enemyCola3->dibujar(*ventana1);
	
	// dibujamos el cronometro
	ventana1->draw(textoContador);
}



void juego::game_loop()
{
	// Asignar a tiempoInicio una unica vez, el tiempo actual + el tiempo de juego en segundos.
	tiempoInicio = relojContador.getElapsedTime().asSeconds() + tiempo_juego;

	// bucle del juego
	while (ventana1->isOpen())
	{
		*tiempo1 = reloj1->getElapsedTime();

		if (tiempo2 + tiempoFrame < tiempo1->asSeconds()) // para que transcurra 1 fps entre ciclos
		{
			tiempo2 = tiempo1->asSeconds();

			*dt = reloj2->restart(); // el tiempo dt lo uso para las formulas de MRU del personaje

			actualizarContador(); // cronometro en reversa

			ventana1->clear(); // limpiar la ventana

			procesar_eventos(); // solo se usa para cerrar la ventana

			if (!gameOver) // movimientos del juegador. Evito que el jugador se mueva al finalizar el juego
			{	
				player1->actualizar_pos(dt);
				player1->actualizar_mov(*evento1);
								
				/*  ----------------------
						PILAS
					----------------------
				*/
				enemyPila1->moverPila();
				enemyPila1->popPila();
				enemyPila1->popPila2();

				// Hago que las PILAS se activen a distinto tiempo para que sea mas dificil llegar a la puerta

				if (reloj1->getElapsedTime().asSeconds() > 0.3)
				{
					enemyPila2->moverPila();
					enemyPila2->popPila();
					enemyPila2->popPila2();
				}

				if (reloj1->getElapsedTime().asSeconds() > 0.5)
				{
					enemyPila3->moverPila();
					enemyPila3->popPila();
					enemyPila3->popPila2();
				}

				/*  ----------------------
							COLAS
					----------------------
				*/
				enemyCola1->moverCola();
				enemyCola1->removerCola();

				// Hago que las COLAS se activen a distinto tiempo para que sea mas dificil llegar a la puerta
				if (reloj1->getElapsedTime().asSeconds() > 0.5)
				{
					enemyCola2->moverCola();
					enemyCola2->removerCola();
				}
	
				if (reloj1->getElapsedTime().asSeconds() > 0.8)
				{
					enemyCola3->moverCola();
					enemyCola3->removerCola();
				}
			}

			chequear_colisiones(); // chequeo si el personaje colisiona con los shells
		
			fin_juego(); // chequeo condicion de victoria o derrota

			dibujar();

			ventana1->display(); // mostrar la ventana 
		}
	}
}


void juego::chequear_colisiones()
{
	//colisiones con los enemigos en COLAS
	if ((enemyCola1->get_sprite().getGlobalBounds().intersects(player1->get_sprite().getGlobalBounds())) ||
		(enemyCola2->get_sprite().getGlobalBounds().intersects(player1->get_sprite().getGlobalBounds())) ||
		(enemyCola3->get_sprite().getGlobalBounds().intersects(player1->get_sprite().getGlobalBounds())))
	{
		player1->set_hitTrue(); // indico que el personaje colisiono con un enemigo. El personaje cae al piso 0.
		if (!sound_on)
		{
			snd_hit.play();
			sound_on = true;
		}
	}

	//colisiones con los enemigos en PILAS 
	if ((enemyPila1->get_spritePila().getGlobalBounds().intersects(player1->get_sprite().getGlobalBounds())) ||
		(enemyPila2->get_spritePila().getGlobalBounds().intersects(player1->get_sprite().getGlobalBounds())) ||
		(enemyPila3->get_spritePila().getGlobalBounds().intersects(player1->get_sprite().getGlobalBounds())))
	{
		player1->set_hitTrue(); // indico que el personaje colisiono con un enemigo. El personaje cae al piso 0.
		if (!sound_on)
		{
			snd_hit.play();
			sound_on = true;
		}
	}

	//colisiones con los enemigos en PILAS2 
	if ((enemyPila1->get_spritePila2().getGlobalBounds().intersects(player1->get_sprite().getGlobalBounds())) ||
		(enemyPila2->get_spritePila2().getGlobalBounds().intersects(player1->get_sprite().getGlobalBounds())) ||
		(enemyPila3->get_spritePila2().getGlobalBounds().intersects(player1->get_sprite().getGlobalBounds())))
	{
		player1->set_hitTrue(); // indico que el personaje colisiono con un enemigo. El personaje cae al piso 0.
		if (!sound_on)
		{
			snd_hit.play();
			sound_on = true;
		}
	}

	// chequeo si el jugador NO esta colisionando con un enemigo, pongo la bandera de sonido en false
	if (player1->get_hitState() == false)
	{
		sound_on = false;
	}
}



void juego::fin_juego()
{
	if (gameOver)
	{
		musica.setLoop(false);
		musica.stop();
	}

	if (!gameOver)
	{
		if (door->get_sprite().getGlobalBounds().intersects(player1->get_sprite().getGlobalBounds()) && (player1->get_sprite().getPosition().y == h6))
		{
			snd_victory.play(); // sonido de victoria. Objetivo cumplido. Ganaste el juego.
			textoContador.setFillColor(Color::Green);
			textoContador.setString("GANASTE !!!");
			gameOver = true; // se cumple la condicion de fin de juego.
		}

		if (seconds <= 0)  // condicion de DERROTA. Se acabo el tiempo
		{	
			snd_gameOver.play(); // sonido de derrota.Perdiste.
			textoContador.setFillColor(Color::Red);
			textoContador.setString("GAME OVER !");
			gameOver = true; // se cumple la condicion de fin de juego.
		}
	}
}



void juego::actualizarContador()
{
	if (!gameOver)
	{
		tiempoFin = relojContador.getElapsedTime().asSeconds(); // Asignar a tiempoFin, el tiempo actual en cada framerate

		seconds = (int)(tiempoInicio - tiempoFin);

		if (seconds >= 0)
		{
			char buffer[20];
			sprintf_s(buffer, "Tiempo: %i", seconds);
			textoContador.setString(buffer);
		}
		
		/* 
			Cuando quedan menos de 10 segundos, el cronometro se pone rojo
			Suena una alarma avisando que quedan pocos segundos.
		*/

		if (seconds <= 5)
		{
			musica.stop();
			textoContador.setFillColor(Color::Red);
						
			if (!alarm)
			{
				snd_timer.play();
				alarm = true;
			}
		}
	}
}
