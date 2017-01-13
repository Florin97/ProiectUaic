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
	SDL_Surface *image; //background of the button
	Text *text;
	SDL_Rect rect; //area of the button
	Uint32 backgroundColor;
	GameController *gameController; //for sending mouse click event

	int index; //for controller
	int tag;   //same
public:
	Button(int tag, int index, const char*text, Uint32 backgroundColor, SDL_Rect rect, int textSize = 40);
	~Button();

	bool handleEvent(SDL_Event event);
	void draw(SDL_Surface *screen);
	void destroy();
	void setGameController(GameController* gameController);
	void setBackgroundColor(Uint32 backgroundColor);
};

