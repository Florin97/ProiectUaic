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
	
	this->deck = new Deck();

	CardModel firstCard = this->deck->drawCard();
	firstCard.setCardNotVisible();

	dealerHand.addCard(firstCard);
	dealerHand.addCard(this->deck->drawCard());

	playerHand.addCard(this->deck->drawCard());
	playerHand.addCard(this->deck->drawCard());

	redrawGameInProgress();
}
void GameController::redrawGameInProgress() {
	gameView->displayGameInProgressMode(this, balance, currentBet, dealerHand, playerHand);
}
vector<ButtonModel> GameController::getButtons() {
	vector<ButtonModel> buttons;
	//TODO add buttons
	char *buttonTexts[] = { "SPLIT","HIT","STAND","DOUBLE" };
	int tags[] = { TAG_SPLIT, TAG_HIT, TAG_STAND, TAG_DOUBLE };
	for (int i = 0; i < 4; i++) {
		ButtonModel button(buttonTexts[i], tags[i]);
		buttons.push_back(button);
	}
	return buttons;
}
void GameController::executeDealerALgorithm() {
	dealerHand.makeAllCardsVisible();
	redrawGameInProgress();

	while (dealerHand.getHandValue() < 17) {
		
		SDL_Delay(1000);
		dealerHand.addCard(this->deck->drawCard());
		redrawGameInProgress();

	}


}
void GameController::onClickSplit() {

}
void GameController::onClickHit() {
	playerHand.addCard(this->deck->drawCard());
	redrawGameInProgress();
}
void GameController::onClickStand() {
	executeDealerALgorithm();
}
void GameController::onClickDouble() {

}

GameController::~GameController()
{
}
