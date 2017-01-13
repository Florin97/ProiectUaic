#include "Text.h"


Text::Text(const char* text, SDL_Rect bounds, SDL_Color color, int fontSize, char* fontType) {
	font = TTF_OpenFont(fontType, fontSize); //create font

	textSurface = TTF_RenderText_Solid(font, text, color); //draw text surface
	rect.x = (bounds.w - textSurface->w) / 2 + bounds.x; //centrate text on bounds
	rect.y = (bounds.h - textSurface->h) / 2 + bounds.y;

}
void Text::draw(SDL_Surface *screen) {
	SDL_BlitSurface(textSurface, NULL, screen, &rect); //draw text 
}
void Text::destroy() {

}



Text::~Text()
{
}
