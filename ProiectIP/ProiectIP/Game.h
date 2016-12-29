#pragma once
#include "SDL.h"
#include <vector>
#include "Shape.h"
#include "Card.h"

class Game
{
private:
	SDL_Window *window;
	SDL_Surface *screen;
	vector<Card> cards;
	int margin = 10;
public:
	Game(SDL_Window *window, SDL_Surface *surface);
	~Game();

	void draw();
	void destroy();
};

