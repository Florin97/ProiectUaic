#pragma once
#include "GameView.h"
#include "Hand.h"
#include "Deck.h"
#include "ButtonModel.h"

#define TAG_BET_PRICE 1
#define TAG_DEAL 2

#define TAG_SPLIT 3
#define TAG_HIT 4
#define TAG_STAND 5
#define TAG_DOUBLE 6
#define TAG_START_NEW_GAME 7

#define MODE_CHOOSE_BET 1
#define MODE_PLAYER_TURN 2
#define MODE_DEALER_TURN 3
#define MODE_START_NEW_GAME 4

#define MAX_BUTTONS 5

class GameView;

class GameController
{
private:
	GameView *gameView;
	int balance = 1000;
	int betValues[4] = {1, 5, 25, 100};
	int currentBet = 5;
	Deck *deck;
	Hand dealerHand;
	Hand playerHand;
	int mode = MODE_CHOOSE_BET;
public:
	GameController(GameView *gameView);
	~GameController();

	void redrawGameInProgress();
	void onClick(int tag, int buttonId);
	void executeDealerALgorithm();
	void switchToChooseBet();

	//click listeners
	void onClickBetPrice(int index);
	void onClickDeal();
	void onClickSplit();
	void onClickHit();
	void onClickStand();
	void onClickDouble();
	void onClickStartNewGame();
	vector<ButtonModel> getButtons();
};

