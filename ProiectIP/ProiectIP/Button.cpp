#include "Button.h"



Button::Button(int index, const char*buttonText, Uint32 backgroundColor, SDL_Rect rect)
{
	this->index = index;
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
bool Button::handleEvent(SDL_Event event) {
	int x = event.button.x;
	int y = event.button.y;
	if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h) {
		if (clickListener != NULL) {
			clickListener(index);
		}
		return true;
	}
	return false;
}
void Button::destroy() {

}

Button::~Button()
{
}