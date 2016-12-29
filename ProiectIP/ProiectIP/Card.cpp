#include "Card.h"


Card::Card(Uint32 backgroundColor, int x, int y, int w, int h) {
	image = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);

	SDL_FillRect(image, NULL, backgroundColor);

	rect = image->clip_rect;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	text = new Text("A", rect);
}

void Card::draw(SDL_Surface *screen) {
	SDL_BlitSurface(image, NULL, screen, &rect);
	text->draw(screen);
}
void Card::destroy() {

}

Card::~Card()
{
}
