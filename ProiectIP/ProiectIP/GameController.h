#pragma once
#include "GameView.h"

class GameController
{
private:
	GameView *gameView;

public:
	GameController(GameView *gameView);
	~GameController();

	void onClickBetListener(int buttonId);
	void onClickDealListener(int buttonId);
};

