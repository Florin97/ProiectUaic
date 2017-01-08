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
CardModel Deck::drawCard(int cardPos) {
	availableCards[cardPos]--;
	CardModel cardModel(cards[cardPos], true, values[cardPos]);
	return cardModel;
}
Deck::~Deck()
{
}
