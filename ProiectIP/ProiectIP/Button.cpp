#include "Button.h"



Button::Button(int tag, int index, const char*buttonText, Uint32 backgroundColor, SDL_Rect rect, int textSize)
{	
	this->tag = tag;
	this->index = index;
	this->backgroundColor = backgroundColor;
	this->rect = rect;

	this->image = SDL_CreateRGBSurface(0, rect.w, rect.h, 32, 0, 0, 0, 0); //create surface
	SDL_FillRect(image, NULL, backgroundColor);  //create collor of the surface

	SDL_Color whiteColor = { 255, 255,255, 255 };

	text = new Text(buttonText, rect, whiteColor, textSize); //create text
}
void Button::draw(SDL_Surface *screen) { 
	SDL_BlitSurface(image, NULL, screen, &rect);// draw background
	
	text->draw(screen);//draw text
	
}
bool Button::handleEvent(SDL_Event event) {
	int x = event.button.x;
	int y = event.button.y;
	if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h) {//use coordonates of click event and check if is in the button area
		gameController->onClick(tag, index);
		return true;
	}
	return false;
}
void Button::setGameController(GameController* gameController) { //set game controller
	this->gameController = gameController;
}
void Button::setBackgroundColor(Uint32 backgroundColor) {  //collor selected button
	this->backgroundColor = backgroundColor;
	this->image = SDL_CreateRGBSurface(0, rect.w, rect.h, 32, 0, 0, 0, 0);
	SDL_FillRect(image, NULL, backgroundColor);
}
void Button::destroy() {

}

Button::~Button()
{
}
