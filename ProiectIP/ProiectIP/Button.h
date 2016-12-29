#pragma once
#include "Shape.h"
#include "Text.h"

class Button :public Shape
{
private:
	SDL_Surface *image;
	Text *text;
	SDL_Rect rect;
	Uint32 backgroundColor;
	void(*clickListener)(int);
	int index;

public:
	Button(int index, const char*text, Uint32 backgroundColor, SDL_Rect rect);
	~Button();

	bool handleEvent(SDL_Event event);
	void draw(SDL_Surface *screen);
	void destroy();
};

