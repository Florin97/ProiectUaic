#include "Hand.h"



Hand::Hand()
{

}
int Hand::getBet() {
	return this->bet;
}
void Hand::setBet(int bet) {
	this->bet = bet;
}
bool Hand::isHandBusted() {
	return handStatus == HAND_BUSTED;
}
char* Hand::getCurrentHandMarker(Hand *currentHand) {
	if (currentHand == NULL) {
		return "";
	}
	if (this == currentHand) {
		return "> ";
	}
	return "";
}
char *Hand::getStatusText() {
	switch (handStatus) {
	case HAND_BUSTED:
		return "Hand Busted, ";
	case HAND_LOST:
		return "Hand lost, ";
	case HAND_PUSH:
		return "Push, ";
	case HAND_WON:
		return "Hand won, ";
	case HAND_DRAWING_CARDS:
	default:
		return "";

	}
}
CardModel Hand::removeSecondCard() {
	CardModel card = cards.at(1);
	cards.pop_back();
	return card;
}
void Hand::makeAllCardsVisible() {
	for (int i = 0; i < cards.size(); i++) {
		cards.at(i).setCardVisible();
	}
	showHandValue = true;
}
void Hand::computeHandValue() {
	int handValue = 0;
	int nrOfAces = 0;

	for (vector<CardModel>::const_iterator it = cards.begin(); it != cards.end(); ++it) {
		CardModel cardModel = *it;
		if (cardModel.isAce()) {
			nrOfAces++;
		}
		handValue += cardModel.getCardValue();
	}
	while (nrOfAces > 0 && handValue > 21) {
		handValue -= 10;
		nrOfAces--;
	}
	if (handValue > 21) {
		setHandStatus(HAND_BUSTED);
	}

	this->handValue = handValue;
}
void Hand::setStatusFromDealerHand(Hand dealerHand) {
	if (handStatus == HAND_BUSTED) {
		return;
	}
	if (dealerHand.getHandStatus() == HAND_BUSTED || dealerHand.getHandValue() < handValue) {
		setHandStatus(HAND_WON);
	}else if (dealerHand.getHandValue() == handValue) {
		setHandStatus(HAND_PUSH);
	}else{
		setHandStatus(HAND_LOST);
	}
	
}
bool Hand::handCanBeSplitted() {
	if (cards.size() != 2) {
		return false;
	}
	CardModel card1 = cards.at(0);
	CardModel card2 = cards.at(1);

	return card1.getCardValue() == card2.getCardValue();
}
int Hand::getHandValue() {
	return handValue;
}
void Hand::addCard(CardModel cardModel) {
	this->cards.push_back(cardModel);
	computeHandValue();
}
vector<CardModel> Hand::getCards() {
	return this->cards;
}
void Hand::clearHand() {
	handValue = 0;
	handStatus = HAND_DRAWING_CARDS;
	showHandValue = false;
	cards.clear();
}
int Hand::getHandStatus() {
	return handStatus;
}
void Hand::setHandStatus(int handStatus) {
	this->handStatus = handStatus;
}
bool Hand::shouldShowHandValue() {
	return showHandValue;
}
Hand::~Hand()
{
}
