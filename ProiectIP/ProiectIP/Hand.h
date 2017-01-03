#pragma once
#include "CardModel.h"
#include <vector>
#include <iostream>
using namespace std;

class Hand
{
private:
	vector<CardModel> cards;
	int handValue;
	void computeHandValue();
public:
	vector<CardModel> getCards();
	void addCard(CardModel cardModel);
	int getHandValue();
	char* getHandText();
	void makeAllCardsVisible();
	void clearHand();
	Hand();
	~Hand();
};

