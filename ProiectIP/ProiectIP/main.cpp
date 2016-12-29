#include "SDL.h"
#include "SDL_ttf.h"
#include <iostream>
using namespace std;


class Text {
private:
	SDL_Rect rect = { 0,0,0,0 };
	TTF_Font *font;
	SDL_Surface *textSurface;
public:
	Text(const char* text, SDL_Rect bounds) {
		font = TTF_OpenFont("Roboto-Black.ttf", 30);
		SDL_Color color = { 255, 255,255, 255 };
		textSurface = TTF_RenderText_Solid(font, text, color);
		rect.x = (bounds.w - textSurface->w) / 2;
		rect.y = (bounds.h - textSurface->h) / 2;

	}
	void draw(SDL_Surface *screen) {
		SDL_BlitSurface(textSurface, NULL, screen, &rect);
	}
	void destroy() {

	}

};

class Card {
private:
	SDL_Surface *image;
	Text *text;
	SDL_Rect rect;

	int originX, originY;

	
public:
	Card(Uint32 backgroundColor, int x, int y, int w = 48, int h = 64) {
		image = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);

		SDL_FillRect(image, NULL, backgroundColor);

		rect = image->clip_rect;

		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;
		text = new Text("A", rect);
	}
	void update() {}
	void draw(SDL_Surface *screen) {
		SDL_BlitSurface(image, NULL, screen, &rect);
		text->draw(screen);
	}
	void destroy() {

	}
};


int main(int argc, char* args[]) {
	if (TTF_Init() == -1) {
		cout << "Font not initialized";
	}

	SDL_Init(SDL_INIT_EVERYTHING);


	SDL_Window *window;
	window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

	if (window == NULL) {
		cout << "No window" << SDL_GetError();
	}
	SDL_Surface* screen = SDL_GetWindowSurface(window);
	if (screen == NULL) cout << "errpr";

	Uint32 backgroundColor = SDL_MapRGB(screen->format, 0, 0, 255);
	Card card(backgroundColor, 0, 0);

	card.draw(screen);

	//Text text("A");
	//text.draw(screen);

	SDL_UpdateWindowSurface(window);

	SDL_Event event;
	bool running = true;

	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_MOUSEBUTTONUP) {
				cout << "event: click event" << event.type;
			}

			if (event.type == SDL_QUIT) {
				running = false;
				break;
			}
		}
	}
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}