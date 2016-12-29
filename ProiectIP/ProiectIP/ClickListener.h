#ifndef CLICK_LISTENER_H
#define CLICK_LISTENER_H

#include "GameController.h"

class GameController;

class ClickListener
{
private:
	GameController *gameController;
public:
	ClickListener(GameController *gameController);
	~ClickListener();
	void onClick(int tag, int id);
};
#endif

