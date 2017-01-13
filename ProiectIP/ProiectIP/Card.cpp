#include "Card.h"


Card::Card(const char *cardText, Uint32 frontColor, Uint32 backColor, int x, int y, int w, int h, bool isVisible) {
	this->frontColor = frontColor;
	this->backColor = backColor;
	this->width = w;
	this->height = h;
	this->isVisible = isVisible;

	createCardImage();
	

	//rect = image->clip_rect;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	SDL_Color blackColor = { 0, 0, 0, 255 };// culoare texte

	text = new Text(cardText, rect, blackColor); //obiect text
}
void Card::setVisible(bool isVisible) {
	this->isVisible = isVisible;
	createCardImage();
}

void Card::createCardImage() {
	image = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0); //create an image

	if(isVisible){
		SDL_FillRect(image, NULL, frontColor); // colorate the surface
	}
	else {
		SDL_FillRect(image, NULL, backColor);  //same shit here
	}
	
	
}
void Card::draw(SDL_Surface *screen) {
	SDL_BlitSurface(image, NULL, screen, &rect); //desenez imaginea
	if (isVisible) {
		text->draw(screen); //desenex text
	}
}


Card::~Card()
{
}
