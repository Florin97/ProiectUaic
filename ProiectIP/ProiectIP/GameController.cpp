#include "GameController.h"


GameController::GameController(GameView *gameView)
{
	this->gameView = gameView;

	gameView->displayStartGameMode(this, balance);
}

void GameController::onClick(int tag, int buttonIndex) {
	switch (tag)
	{
	case TAG_BET_PRICE:
		onClickBetPrice(buttonIndex);
		break;
	case TAG_DEAL:
		onClickDeal();
		break;
	default:
		break;
	}
}

void GameController::onClickBetPrice(int buttonIndex) {
	currentBet = betValues[buttonIndex];
	gameView->checkButton(buttonIndex);
}
void GameController::onClickDeal() {
	balance -= currentBet;
	char *dealerCards[] = {"J", "Q"};
	char *playerCards[] = { "K", "A" };

	gameView->displayGameInProgressMode(this, balance, currentBet,  dealerCards, playerCards);
}


GameController::~GameController()
{
}
