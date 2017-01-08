#pragma once
#include "CardModel.h"
#include <vector>
#include <iostream>
using namespace std;

#define HAND_WON 1
#define HAND_LOST 2
#define HAND_BUSTED 3
#define HAND_DRAWING_CARDS 4
#define HAND_PUSH 5

class Hand
{
private:
	vector<CardModel> cards;
	int handValue;
	int handStatus = HAND_DRAWING_CARDS;
	bool showHandValue;
	void computeHandValue();
public:
	vector<CardModel> getCards();
	void addCard(CardModel cardModel);
	int getHandValue();
	void makeAllCardsVisible();
	void clearHand();
	bool shouldShowHandValue();
	int getHandStatus();
	void setHandStatus(int handStatus);
	void setStatusFromDealerHand(Hand dealerHand);
	Hand();
	~Hand();
};

