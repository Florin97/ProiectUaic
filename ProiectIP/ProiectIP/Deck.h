#pragma once
#define NR_OF_CARDS 13
#include "CardModel.h"

class Deck
{
private:
	char *cards[NR_OF_CARDS] = { "2","3","4","5","6","7","8","9","10","J","Q","K","A" }; //card char
	int values[NR_OF_CARDS] = {2,3,4,5,6,7,8,9,10,10,10,10,11};//card value
	int availableCards[NR_OF_CARDS] = {4,4,4,4,4,4,4,4,4,4,4,4,4};//card available
public:
	CardModel drawCard();
	//only for testing
	CardModel drawCard(int cardPos);
	Deck(); //constructor
	~Deck(); //destructor
};

