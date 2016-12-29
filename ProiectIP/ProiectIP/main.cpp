#include "SDL.h"
#include "SDL_ttf.h"
#include "GameView.h"
#include "GameController.h"
#include <iostream>
using namespace std;




int main(int argc, char* args[]) {
	if (TTF_Init() == -1) {
		cout << "Font not initialized";
	}

	SDL_Init(SDL_INIT_EVERYTHING);


	SDL_Window *window;
	window = SDL_CreateWindow("Blackjack", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

	if (window == NULL) {
		cout << "No window" << SDL_GetError();
	}
	SDL_Surface* screen = SDL_GetWindowSurface(window);
	if (screen == NULL) cout << "errpr";
	
	GameView gameView(window, screen);
	new GameController(&gameView);
	gameView.draw();

	//Text text("A");
	//text.draw(screen);

	//SDL_UpdateWindowSurface(window);

	SDL_Event event;
	bool running = true;

	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_MOUSEBUTTONUP) {

				cout << "event: click event" << event.type;
				
				//SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
			//	SDL_UpdateWindowSurface(window);
			}

			if (event.type == SDL_QUIT) {
				running = false;
				break;
			}
		}
	}
	gameView.destroy();

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}