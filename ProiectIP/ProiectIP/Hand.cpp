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
int Hand::getHandValue() {
	int handValue = 0;
	bool handContainsAce = false;

	cout << "computing ";
	for (vector<CardModel>::const_iterator it = cards.begin(); it != cards.end(); ++it) {
		CardModel cardModel = *it;
		if (cardModel.isAce()) {
			handContainsAce = true;
		}
		handValue += cardModel.getCardValue();
	}
	if (handContainsAce && handValue > 21) {
		handValue -= 10;
	}
	cout << "random: "+handValue;
	return handValue;
}
void Hand::addCard(CardModel cardModel) {
	this->cards.push_back(cardModel);
}
vector<CardModel> Hand::getCards() {
	return this->cards;
}

Hand::~Hand()
{
}
