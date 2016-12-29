#include "Text.h"


Text::Text(const char* text, SDL_Rect bounds, SDL_Color color, int fontSize) {
	font = TTF_OpenFont("Roboto-Black.ttf", fontSize);

	textSurface = TTF_RenderText_Solid(font, text, color);
	rect.x = (bounds.w - textSurface->w) / 2 + bounds.x;
	rect.y = (bounds.h - textSurface->h) / 2 + bounds.y;

}
void Text::draw(SDL_Surface *screen) {
	SDL_BlitSurface(textSurface, NULL, screen, &rect);
}
void Text::destroy() {

}



Text::~Text()
{
}
