#include "puerta.h"


puerta::puerta() // constructor
{
	cargar_graficos();
}


void puerta::cargar_graficos()
{
	txt_puerta = new Texture;
	txt_puerta->loadFromFile("resources/images/puerta.png");

	spr_puerta = new Sprite(*txt_puerta);
	spr_puerta->setTexture(*txt_puerta);
	spr_puerta->setOrigin(14.5, 48); // origen abajo en la parte inferior de la imagen
	spr_puerta->setPosition(400, 73);
}

Sprite puerta::get_sprite()
{
	return *spr_puerta;
}


