#include "nodo.h"

nodo::nodo(Vector2f coord, string colorShell)
{
	coordenadas = coord;
	colorNodo = colorShell;

	cargar_graficos();
}


void nodo::dibujar(RenderWindow& ventana)
{
	ventana.draw(*spr_shell);
}

void nodo::cargar_graficos()
{
	txt_shell = new Texture;
	txt_shell->loadFromFile("resources/images/shell_" + colorNodo + ".png");
	spr_shell = new Sprite(*txt_shell);
	spr_shell->setTexture(*txt_shell);
	spr_shell->setOrigin(15, 24); // origen abajo en la parte inferior de la imagen
	spr_shell->setPosition(coordenadas);
}


void nodo::set_texture(string textura)
{
	txt_shell->loadFromFile(textura);
}


Sprite nodo::get_sprite()
{
	return *spr_shell;
}


void nodo::mover(int velocidad) // con esta funcion se mueve los shell
{
	float x, y;
	x = spr_shell->getPosition().x;
	y = spr_shell->getPosition().y;

	spr_shell->setPosition(x+velocidad,y);
}

float nodo::get_positionX()
{
	return spr_shell->getPosition().x;
}


void nodo::set_position(Vector2f coord)
{
	spr_shell->setPosition(coord);
}


String nodo::get_color()
{
	return colorNodo;
}