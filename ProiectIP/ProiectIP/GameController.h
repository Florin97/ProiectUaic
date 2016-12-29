#pragma once
#include "GameView.h"
#define TAG_BET_PRICE 1
#define TAG_DEAL 2

#define TAG_SPLIT 3
#define TAG_HIT 4
#define TAG_STAND 5
#define TAG_DOUBLE 6


class GameView;

class GameController
{
private:
	GameView *gameView;
	int balance = 1000;
	int betValues[4] = {1, 5, 25, 100};
	int currentBet = 5;

public:
	GameController(GameView *gameView);
	~GameController();

	void onClick(int tag, int buttonId);

	//click listeners
	void onClickBetPrice(int index);
	void onClickDeal();
};

