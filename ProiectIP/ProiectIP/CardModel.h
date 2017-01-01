#pragma once
class CardModel
{
private:
	bool isVisible;
	char* card;
	int cardValue;
public:
	int getCardValue();
	bool isAce();
	bool isCardVisible();
	void setCardNotVisible();
	char* getCard();
	CardModel(char* card, bool isVisible, int cardValue);
	~CardModel();
};

