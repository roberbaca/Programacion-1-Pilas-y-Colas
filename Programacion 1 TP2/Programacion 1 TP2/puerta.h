#pragma once
#include "SFML\Graphics.hpp"
#include "SFML/Audio.hpp"

using namespace std;
using namespace sf;

class puerta
{

public:

	puerta();
	void cargar_graficos();
	Sprite get_sprite();

private:
	Sprite* spr_puerta;
	Texture* txt_puerta;
};

