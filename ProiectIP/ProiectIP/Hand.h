#pragma once
#include "CardModel.h"
#include <vector>
#include <iostream>
using namespace std;

class Hand
{
private:
	vector<CardModel> cards;
public:
	vector<CardModel> getCards();
	void addCard(CardModel cardModel);
	int getHandValue();
	char* getHandText();
	void makeAllCardsVisible();
	Hand();
	~Hand();
};

