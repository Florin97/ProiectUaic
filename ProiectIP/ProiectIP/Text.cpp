#include "Text.h"


Text::Text(const char* text, SDL_Rect bounds) {
	font = TTF_OpenFont("Roboto-Black.ttf", 30);
	SDL_Color color = { 255, 255,255, 255 };
	textSurface = TTF_RenderText_Solid(font, text, color);
	rect.x = (bounds.w - textSurface->w) / 2;
	rect.y = (bounds.h - textSurface->h) / 2;

}
void Text::draw(SDL_Surface *screen) {
	SDL_BlitSurface(textSurface, NULL, screen, &rect);
}
void Text::destroy() {

}



Text::~Text()
{
}
