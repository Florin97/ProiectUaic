#pragma once
#include "SDL.h"
#include <vector>
#include "Shape.h"
#include "Card.h"
#include "Button.h"


class GameView
{
private:
	SDL_Window *window;
	SDL_Surface *screen;
	vector<Card> cards;
	vector<Button> buttons;
	int margin = 10;
public:
	GameView(SDL_Window *window, SDL_Surface *surface);
	~GameView();

	void draw();
	void destroy();
	void displayStartGameMode(void(*clickBetListener)(int), void(*clickDealListener)(int));
};

