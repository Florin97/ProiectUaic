#pragma once
#include "SDL.h"
#include <vector>
#include "Shape.h"
#include "Card.h"
#include "Button.h"

class Game
{
private:
	SDL_Window *window;
	SDL_Surface *screen;
	vector<Card> cards;
	vector<Button> buttons;
	int margin = 10;

public:
	Game(SDL_Window *window, SDL_Surface *surface);
	~Game();

	void draw();
	void destroy();
};

