#pragma once
#include "Shape.h"
#include "Text.h"
class Card :public Shape
{
private:
	SDL_Surface *image;
	Text *text;
	SDL_Rect rect;
	bool isVisible;
	Uint32 frontColor;
	Uint32 backColor;
	int width;
	int height;

	void createCardImage();
public:
	Card(const char *cardText, Uint32 frontColor, Uint32 backColor, int x, int y, int w, int h, bool isVisible=true);
	~Card();

	void setVisible(bool isVisible);
	void draw(SDL_Surface *screen);
	void destroy();

};

