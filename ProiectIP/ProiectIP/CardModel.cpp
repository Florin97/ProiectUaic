#include "CardModel.h"
#include <string.h>


CardModel::CardModel(char* card, bool isVisible, int cardValue)
{
	this->card = card;
	this->isVisible = isVisible;
	this->cardValue = cardValue;
}

int CardModel::getCardValue() {
	return this->cardValue;
}
void CardModel::setCardNotVisible() {
	this->isVisible = false;
}
void CardModel::setCardVisible() {
	this->isVisible = true;
}
bool CardModel::isCardVisible() {
	return isVisible;
}
bool CardModel::isAce() {
	if (strcmp(card, "A") == 0) {
		return true;
	}
	return false;
}
char* CardModel::getCard() {
	return this->card;
}
CardModel::~CardModel()
{
}
