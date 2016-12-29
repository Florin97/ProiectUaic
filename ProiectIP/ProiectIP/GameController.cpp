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
	case TAG_SPLIT:
		onClickSplit();
		break;
	case TAG_HIT:
		onClickHit();
		break;
	case TAG_STAND:
		onClickStand();
		break;
	case TAG_DOUBLE:
		onClickDouble();
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
void GameController::onClickSplit() {

}
void GameController::onClickHit() {
}
void GameController::onClickStand() {

}
void GameController::onClickDouble() {

}

GameController::~GameController()
{
}
