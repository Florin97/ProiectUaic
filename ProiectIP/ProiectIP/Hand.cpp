#include "Hand.h"



Hand::Hand()
{

}
char* Hand::getHandText() {
	int handValue = getHandValue();
	char numstr[30]; // enough to hold all numbers up to 64-bits
	if (handValue <= 21) {
		sprintf_s(numstr, "Hand value: %d", handValue);
	}
	else {
		sprintf_s(numstr, "Busted: %d", handValue);
	}
	return numstr;
}
void Hand::makeAllCardsVisible() {
	for (int i = 0; i < cards.size(); i++) {
		cards.at(i).setCardVisible();
	}
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
	this->handValue = handValue;
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
	cards.clear();
}
Hand::~Hand()
{
}
