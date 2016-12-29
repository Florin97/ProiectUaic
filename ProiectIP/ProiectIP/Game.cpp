#include "Game.h"



Game::Game(SDL_Window *window, SDL_Surface *surface)
{
	this->window = window;
	this->screen = surface;
	Uint32 frontColor = SDL_MapRGB(screen->format, 255, 255, 255);
	Uint32 backColor = SDL_MapRGB(screen->format, 230, 74, 25);
	int width = surface->w/7;
	int height = surface->h/4;

	Card card("A", frontColor, backColor, margin, margin, width, height);
	cards.push_back(card);

	Card card2("Q", frontColor, backColor, margin+width+10,margin, width, height, false);
	cards.push_back(card2);
}


void Game::draw() {
	for (vector<Card>::const_iterator it = cards.begin(); it != cards.end(); ++it) {
		Card card = *it;
		card.draw(screen);
	}

}

void Game::destroy() {

}
Game::~Game()
{

}
