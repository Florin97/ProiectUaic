#pragma once
#include "Shape.h"
#include "Text.h"
class Card :public Shape
{
private:
	SDL_Surface *image;
	Text *text;
	SDL_Rect rect;

public:
	Card(Uint32 backgroundColor, int x, int y, int w = 48, int h = 64);
	~Card();

	void draw(SDL_Surface *screen);
	void destroy();
};

