#include "Hand.h"



Hand::Hand()
{
	//CardModel card1("A", false, 11);
	//this->cards.push_back(card1);

	//CardModel card2("Q", true, 10);
	//this->cards.push_back(card2);
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
