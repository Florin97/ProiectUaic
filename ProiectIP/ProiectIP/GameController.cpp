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
	initialBet = betValues[buttonIndex];
	gameView->checkButton(buttonIndex);
}
void GameController::onClickDeal() {
	if (balance - initialBet < 0) {
		return;
	}
	mode = MODE_PLAYER_TURN;

	balance -= initialBet;
	
	this->playerSecondHand = NULL;
	this->deck = new Deck();

	CardModel firstCard = this->deck->drawCard();
	firstCard.setCardNotVisible();

	playerHand.addCard(this->deck->drawCard(0));
	playerHand.addCard(this->deck->drawCard(0));
	playerHand.setBet(initialBet);

	dealerHand.addCard(firstCard);
	dealerHand.addCard(this->deck->drawCard());

	//playerHand.addCard(this->deck->drawCard());
	//playerHand.addCard(this->deck->drawCard());

	currentHand = &playerHand;
	redrawGameInProgress();
}
void GameController::redrawGameInProgress() {
	gameView->displayGameInProgressMode(this, balance, dealerHand, playerHand, playerSecondHand, currentHand);
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
	bool balanceIsSmallerThanTheBet = this->balance < this->currentHand->getBet();
	for (int i = 0; i < 4; i++) {
		int tag = tags[i];
		if (tag == TAG_DOUBLE && balanceIsSmallerThanTheBet) {
			continue;
		}
		if (tag == TAG_SPLIT && (!this->playerHand.handCanBeSplitted() || balanceIsSmallerThanTheBet || this->playerSecondHand != NULL)) {
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

	updateBalanceWithHandValue(&playerHand);

	if (playerSecondHand != NULL) {
		updateBalanceWithHandValue(playerSecondHand);
	}

	mode = MODE_START_NEW_GAME;
	redrawGameInProgress();

}
void GameController::updateBalanceWithHandValue(Hand *hand) {
	hand->setStatusFromDealerHand(dealerHand);

	if (hand->getHandStatus() == HAND_WON) {
		balance += hand->getBet() * 2;
	}
	else if (hand->getHandStatus() == HAND_PUSH) {
		balance += hand->getBet();
	}
}
void GameController::switchToChooseBet() {
	mode = MODE_CHOOSE_BET;
	dealerHand.clearHand();
	playerHand.clearHand();

	gameView->displayStartGameMode(this, balance);
}
void GameController::onClickSplit() {
	
	this->playerSecondHand = new Hand();
	this->playerSecondHand->addCard(this->playerHand.removeSecondCard());

	this->playerHand.addCard(this->deck->drawCard());
	this->playerSecondHand->addCard(this->deck->drawCard());

	balance -= playerHand.getBet();
	this->playerSecondHand->setBet(playerHand.getBet());

	redrawGameInProgress();

}
bool GameController::shouldDisplayStartNewGame() {
	if (playerHand.isHandBusted() && playerSecondHand == NULL) {
		return true;
	}
	if (playerHand.isHandBusted() && playerSecondHand != NULL && playerSecondHand->isHandBusted()) {
		return true;
	}
	return false;
}
void GameController::switchToNextHand() {
	if (currentHand == &playerHand && playerSecondHand != NULL) {
		currentHand = playerSecondHand;
		redrawGameInProgress();
	} else {
		executeDealerAlgorithm();
	}
}
void GameController::drawCardForPlayer() {
	currentHand->addCard(this->deck->drawCard());

	redrawGameInProgress();

	if (shouldDisplayStartNewGame()) {
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
	switchToNextHand();
}
void GameController::onClickDouble() {
	this->balance -= currentHand->getBet();
	currentHand->setBet(currentHand->getBet() * 2);

	drawCardForPlayer();

	if (mode != MODE_START_NEW_GAME) {
		switchToNextHand();
	}
}

GameController::~GameController()
{
}
