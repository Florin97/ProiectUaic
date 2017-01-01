#include "Deck.h"
#include <math.h>
#include <stdlib.h>  
#include <time.h>

Deck::Deck()
{
	srand(time(NULL));
}
CardModel Deck::drawCard() {
	int card = 0;
	do {
		card = rand() % NR_OF_CARDS;
	} while (availableCards[card] == 0);
	availableCards[card]--;
	CardModel cardModel(cards[card], true, values[card]);
	return cardModel;

}

Deck::~Deck()
{
}
