#include "GameController.h"


GameController::GameController(GameView *gameView)
{
	this->gameView = gameView;

	gameView->displayStartGameMode(this, balance);
}
bool GameController::shouldShowGameResult() {
	return mode == MODE_START_NEW_GAME;
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
	case TAG_START_NEW_GAME:
		onClickStartNewGame();
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
	if (balance - currentBet < 0) {
		return;
	}
	mode = MODE_PLAYER_TURN;

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

	if (mode == MODE_DEALER_TURN) {
		return buttons;
	}

	if (mode == MODE_START_NEW_GAME) {
		ButtonModel startNewGame("START", TAG_START_NEW_GAME);
		buttons.push_back(startNewGame);
		return buttons;
	}

	int nrButtons;
	//TODO add buttons
	char *buttonTexts[] = { "SPLIT","HIT","STAND","DOUBLE" };
	int tags[] = { TAG_SPLIT, TAG_HIT, TAG_STAND, TAG_DOUBLE };
	bool balanceIsSmallerThanTheBet = this->balance < this->currentBet;
	for (int i = 0; i < 4; i++) {
		int tag = tags[i];
		if (tag == TAG_DOUBLE && balanceIsSmallerThanTheBet) {
			continue;
		}
		if (tag == TAG_SPLIT && (!this->playerHand.handCanBeSplitted() || balanceIsSmallerThanTheBet)) {
			continue;
		}
		ButtonModel button(buttonTexts[i], tag);
		buttons.push_back(button);
	}
	return buttons;
}
void GameController::executeDealerAlgorithm() {
	mode = MODE_DEALER_TURN;

	dealerHand.makeAllCardsVisible();
	redrawGameInProgress();

	while (dealerHand.getHandValue() < 17) {
		
		SDL_Delay(1000);
		dealerHand.addCard(this->deck->drawCard());
		redrawGameInProgress();
	}
	playerHand.setStatusFromDealerHand(dealerHand);

	if (playerHand.getHandStatus() == HAND_WON) {
		balance += this->currentBet * 2;
	}
	else if (playerHand.getHandStatus() == HAND_PUSH) {
		balance += this->currentBet;
	}

	mode = MODE_START_NEW_GAME;
	redrawGameInProgress();

}
void GameController::switchToChooseBet() {
	mode = MODE_CHOOSE_BET;
	dealerHand.clearHand();
	playerHand.clearHand();

	gameView->displayStartGameMode(this, balance);
}
void GameController::onClickSplit() {

}
void GameController::drawCardForPlayer() {
	playerHand.addCard(this->deck->drawCard());

	redrawGameInProgress();

	if (playerHand.getHandValue() > 21) {
		mode = MODE_START_NEW_GAME;
		redrawGameInProgress();
	}
}
void GameController::onClickHit() {
	drawCardForPlayer();
}
void GameController::onClickStartNewGame() {
	switchToChooseBet();
}
void GameController::onClickStand() {
	executeDealerAlgorithm();
}
void GameController::onClickDouble() {
	this->balance -= currentBet;
	currentBet += currentBet;
	drawCardForPlayer();

	if (mode != MODE_START_NEW_GAME) {
		executeDealerAlgorithm();
	}
}

GameController::~GameController()
{
}
