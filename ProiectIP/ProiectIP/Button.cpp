#include "Button.h"



Button::Button(const char*buttonText, Uint32 backgroundColor, SDL_Rect rect)
{
	this->backgroundColor = backgroundColor;
	this->rect = rect;

	this->image = SDL_CreateRGBSurface(0, rect.w, rect.h, 32, 0, 0, 0, 0);
	SDL_FillRect(image, NULL, backgroundColor);

	text = new Text(buttonText, rect);
}
void Button::draw(SDL_Surface *screen) {
	SDL_BlitSurface(image, NULL, screen, &rect);
	
	text->draw(screen);
	
}
bool handleEvent(SDL_Event event) {
	return false;
}
void Button::destroy() {

}

Button::~Button()
{
}
