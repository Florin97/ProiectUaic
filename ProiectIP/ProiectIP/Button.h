#pragma once
#include "Shape.h"
#include "Text.h"
#include "GameController.h"
#include <iostream>
using namespace std;
class GameController;

class Button :public Shape
{
private:
	SDL_Surface *image;
	Text *text;
	SDL_Rect rect;
	Uint32 backgroundColor;
	GameController *gameController;

	int index;
	int tag;
public:
	Button(int tag, int index, const char*text, Uint32 backgroundColor, SDL_Rect rect);
	~Button();

	bool handleEvent(SDL_Event event);
	void draw(SDL_Surface *screen);
	void destroy();
	void setListener(GameController* gameController);
	void setBackgroundColor(Uint32 backgroundColor);
};

