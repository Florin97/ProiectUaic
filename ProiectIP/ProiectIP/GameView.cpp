#include "GameView.h"



GameView::GameView(SDL_Window *window, SDL_Surface *surface)
{
	this->window = window;
	this->screen = surface;
	Uint32 frontColor = SDL_MapRGB(screen->format, 255, 255, 255);
	Uint32 backColor = SDL_MapRGB(screen->format, 230, 74, 25);
	Uint32 greenColor = SDL_MapRGB(screen->format, 205, 220, 57);
	int width = surface->w/7;
	int height = surface->h/4;

	/*
	Card card("A", frontColor, backColor, margin, margin, width, height);
	cards.push_back(card);

	Card card2("Q", frontColor, backColor, margin+width+10,margin, width, height, false);
	cards.push_back(card2);*/

	
}
void GameView::displayStartGameMode(void(*clickBetListener)(int), void(*clickDealListener)(int)) {
	
	Uint32 greenColor = SDL_MapRGB(screen->format, 205, 220, 57);
	Uint32 backColor = SDL_MapRGB(screen->format, 230, 74, 25);

	int nrButtons = 5;
	int buttonHeight = 100;
	int buttonWidth = (screen->w - (nrButtons + 1)*margin) / nrButtons;
	int top = screen->h - buttonHeight - margin;
	char *buttonTexts[] = { "1","5","25","100","Deal" };

	for (int i = 0; i < nrButtons; i++) {
		int x = margin*(i + 1) + i*buttonWidth;
		SDL_Rect rect = { x, top, buttonWidth, 100 };
		Uint32 color;
		if (i < nrButtons - 1) {
			color = greenColor;
		}
		else {
			color = backColor;
		}
		Button button(i, buttonTexts[i], color, rect);
		buttons.push_back(button);
	}
}

void GameView::draw() {
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 69, 90, 100));

	for (vector<Card>::const_iterator it = cards.begin(); it != cards.end(); ++it) {
		Card card = *it;
		card.draw(screen);
	}

	for (vector<Button>::const_iterator it = buttons.begin(); it != buttons.end(); ++it) {
		Button button = *it;
		button.draw(screen);
	}

	
	SDL_UpdateWindowSurface(window);

}

void GameView::destroy() {

}
GameView::~GameView()
{

}
