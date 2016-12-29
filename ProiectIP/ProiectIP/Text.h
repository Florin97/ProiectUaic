#pragma once
#include "Shape.h"
class Text : public Shape
{
private:
	SDL_Rect rect = { 0,0,0,0 };
	TTF_Font *font;
	SDL_Surface *textSurface;
public:
	Text(const char* text, SDL_Rect bounds, SDL_Color color = { 255, 255,255, 255 });
	~Text();

	void draw(SDL_Surface * screen);
	void destroy();
};


