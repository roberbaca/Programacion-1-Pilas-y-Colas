#include "personaje.h"

personaje::personaje() // constructor
{
	posicion_x = 380;
	posicion_y = 524;
	velocidad_x = 0;
	velocidad_y = 0;
	velocidad_yMax = 250;
	gravedad = 20;
	altura_salto = 180;
	
	esta_saltando = false;
	hit = false;

	// posiciones en el eje Y de cada plataforma. 

	h0 = 524;
	h1 = 449;
	h2 = 374;
	h3 = 298;
	h4 = 222;
	h5 = 149;
	h6 = 73;

	evento = new Event;

	if (!buffer.loadFromFile("resources/sounds/jump.wav"))
	{
		// Error...
	}

	snd_jump.setBuffer(buffer);
	snd_jump.setVolume(50);

	cargar_graficos();
}


void personaje::cargar_graficos()
{
	txt_personaje = new Texture;
	txt_personaje->loadFromFile("resources/images/jumper.png");
	spr_personaje = new Sprite(*txt_personaje);

	spr_personaje->setTexture(*txt_personaje);
	spr_personaje->setScale(0.7, 0.7);
	spr_personaje->setOrigin(23, 60); // origen en la parte inferior de la imagen
	spr_personaje->setPosition(posicion_x, posicion_y);
}


void personaje::actualizar_pos(Time* tiempo)
{
	/* 
		Calculamos la Posicion(distancia) = velocidad x tiempo
		La posicion en x esta limitada a los boundaries de la ventana.
	*/

	limite_izquierda = spr_personaje->getGlobalBounds().width;
	limite_derecha = 800 - spr_personaje->getGlobalBounds().width;;

	if ((spr_personaje->getPosition().x <= limite_derecha) && (spr_personaje->getPosition().x >= limite_izquierda))
	{
		posicion_x += velocidad_x * tiempo->asSeconds();
	}

	if (spr_personaje->getPosition().x > limite_derecha)
	{
		posicion_x = limite_derecha;
	}

	if (spr_personaje->getPosition().x < limite_izquierda)
	{
		posicion_x = limite_izquierda;
	}

	posicion_y += velocidad_y * tiempo->asSeconds();

	// limito la velocidad de caida para que el personaje no se acelere indefinidamente	
	if (velocidad_y > velocidad_yMax)
	{
		velocidad_y = 250;
	}

	// Para detectar si el personaje esta parado sobre alguna de las plataformas	
	if ((spr_personaje->getPosition().y == h0) || (spr_personaje->getPosition().y == h1) || (spr_personaje->getPosition().y == h2) || 
	    (spr_personaje->getPosition().y == h3) || (spr_personaje->getPosition().y == h4) || (spr_personaje->getPosition().y == h5) ||
		(spr_personaje->getPosition().y == h6))
	{
		esta_saltando = false;
	}

	// cuando el personaje esta en el aire, aplicamos la gravedad. Si esta sobre alguna de las plataformas, la velocidad en Y es cero.
	if ((!esta_saltando) && (spr_personaje->getPosition().y != h1) && (spr_personaje->getPosition().y != h2) && (spr_personaje->getPosition().y != h3)
		&& (spr_personaje->getPosition().y != h4) && (spr_personaje->getPosition().y != h5) && (spr_personaje->getPosition().y != h6) && !hit)
	{
		velocidad_y += gravedad;
	}

	// Si el personaje ha colisionado con un enemigo, activo la gravedad para devolverlo al piso 0.
	if (hit)
	{
		velocidad_y += gravedad;
	}

	// para evitar que el personaje caiga por debajo de la plataforma h0
	if (spr_personaje->getPosition().y > h0)
	{
		posicion_y = h0;
		velocidad_y = 0;
	}

	// evitamos que el personaje caiga por debajo de cada plataforma una vez alcanzada.
	if ((spr_personaje->getPosition().y > h2) && (spr_personaje->getPosition().y < h1) && velocidad_y >0 && !esta_saltando && !hit)
	{
		posicion_y = h1;
		velocidad_y = 0;
	}

	if ((spr_personaje->getPosition().y > h3) && (spr_personaje->getPosition().y < h2) && velocidad_y > 0 && !esta_saltando && !hit)
	{
		posicion_y = h2;
		velocidad_y = 0;
	}


	if ((spr_personaje->getPosition().y > h4) && (spr_personaje->getPosition().y < h3) && velocidad_y > 0 && !esta_saltando && !hit)
	{
		posicion_y = h3;
		velocidad_y = 0;
	}


	if ((spr_personaje->getPosition().y > h5) && (spr_personaje->getPosition().y < h4) && velocidad_y > 0 && !esta_saltando && !hit)
	{
		posicion_y = h4;
		velocidad_y = 0;
	}


	if ((spr_personaje->getPosition().y > h6) && (spr_personaje->getPosition().y < h5) && velocidad_y > 0 && !esta_saltando && !hit)
	{
		posicion_y = h5;
		velocidad_y = 0;
	}

	if ((spr_personaje->getPosition().y > -100) && (spr_personaje->getPosition().y < h6) && velocidad_y > 0 && !esta_saltando && !hit)
	{
		posicion_y = h6;
		velocidad_y = 0;
	}

	if (spr_personaje->getPosition().y == h0)
	{
		hit = false; // cuando el personaje vuelve al piso 0, pongo esta bandera en falso
	}

	// actualizamos la posicion del personaje
	spr_personaje->setPosition(posicion_x, posicion_y);
}



void personaje::actualizar_mov(Event& evento)
{
	// Eventos con el teclado

	if (evento.type == Event::KeyPressed)
	{
		// evitamos el doble salto. Verificamos si el personaje esta parado sobre h0
		if (Keyboard::isKeyPressed(Keyboard::Up) && !esta_saltando && posicion_y == h0 && !hit)
		{
			snd_jump.play();
			esta_saltando = true;
			velocidad_y = -450;
		}

		// evitamos el doble salto. Verificamos si el personaje esta parado sobre h1
		if (Keyboard::isKeyPressed(Keyboard::Up) && !esta_saltando && posicion_y == h1 && !hit)
		{
			snd_jump.play();
			esta_saltando = true;
			velocidad_y = -450;
		}

		// evitamos el doble salto. Verificamos si el personaje esta parado sobre h2
		if (Keyboard::isKeyPressed(Keyboard::Up) && !esta_saltando && posicion_y == h2 && !hit)
		{
			snd_jump.play();
			esta_saltando = true;
			velocidad_y = -450;
		}

		// evitamos el doble salto. Verificamos si el personaje esta parado sobre h3
		if (Keyboard::isKeyPressed(Keyboard::Up) && !esta_saltando && posicion_y == h3 && !hit)
		{
			snd_jump.play();
			esta_saltando = true;
			velocidad_y = -450;
		}

		// evitamos el doble salto. Verificamos si el personaje esta parado sobre h4
		if (Keyboard::isKeyPressed(Keyboard::Up) && !esta_saltando && posicion_y == h4 && !hit)
		{
			snd_jump.play();
			esta_saltando = true;
			velocidad_y = -450;
		}

		// evitamos el doble salto. Verificamos si el personaje esta parado sobre h5
		if (Keyboard::isKeyPressed(Keyboard::Up) && !esta_saltando && posicion_y == h5 && !hit)
		{
			snd_jump.play();
			esta_saltando = true;
			velocidad_y = -450;
		}

		// evitamos el doble salto. Verificamos si el personaje esta parado sobre h6
		if (Keyboard::isKeyPressed(Keyboard::Up) && !esta_saltando && posicion_y == h6 && !hit)
		{
			snd_jump.play();
			esta_saltando = true;
			velocidad_y = -325;
		}

		// movimiento a la derecha =>
		if (Keyboard::isKeyPressed(Keyboard::Right) && !hit)
		{
			velocidad_x = 170;
		}

		// movimiento a la izquierda <=
		if (Keyboard::isKeyPressed(Keyboard::Left) && !hit)
		{
			velocidad_x = -170;
		}

		// si presiono izquierda y derecha a la vez, el personaje no se mueve en el eje X  <= =>
		if ((Keyboard::isKeyPressed(Keyboard::Right)) && (Keyboard::isKeyPressed(Keyboard::Left)))
		{
			velocidad_x = 0;
		}
	}


	else if (evento.type == Event::KeyReleased)
	{
		// Al soltar la tecla de salto, se activa la gravedad afectando la velocidad en el eje y
		if ((evento.key.code == Keyboard::Up) && esta_saltando)
		{
			esta_saltando = false;
		}

		// Si dejamos de tocar las teclas de derecha o de izquierda, el personaje no se mueve
		if (evento.key.code == Keyboard::Right)
		{
			velocidad_x = 0;
		}

		if (evento.key.code == Keyboard::Left)
		{
			velocidad_x = 0;
		}
	}
}


Sprite personaje::get_sprite()
{
	return *spr_personaje;
}


void personaje::set_position(float x, float y)
{
	spr_personaje->setPosition(x, y);
}


void personaje::set_hitTrue()
{
	hit = true;
}

bool personaje::get_hitState()
{
	return hit;
}