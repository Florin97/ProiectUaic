#ifndef SHAPE_H
#define SHAPE_H

#include "SDL.h"
#include "SDL_ttf.h"
#include <iostream>
using namespace std;

class Shape {
public:
	virtual void destroy();
	virtual void draw(SDL_Surface *screen);
};

#endif
