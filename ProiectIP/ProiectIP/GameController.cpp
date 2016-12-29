#include "GameController.h"


GameController::GameController(GameView *gameView)
{
	this->gameView = gameView;
	void(*click)(int) = (this->onClickBetListener);

	gameView->displayStartGameMode(click, click);
}

void GameController::onClickBetListener(int buttonId) {
}
void GameController::onClickDealListener(int buttonId) {
}

GameController::~GameController()
{
}
