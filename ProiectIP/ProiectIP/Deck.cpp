#include "Deck.h"
#include <math.h>
#include <stdlib.h>  
#include <time.h>

Deck::Deck()
{
	srand(time(NULL)); //for random to be different
}
CardModel Deck::drawCard() {
	int card = 0; // card
	do {
		card = rand() % NR_OF_CARDS; //draw random card
	} while (availableCards[card] == 0);//if i dont have any more cards, draw again
	availableCards[card]--;  //decrease card
	CardModel cardModel(cards[card], true, values[card]);//create a model card 
	return cardModel; //return the card

}
CardModel Deck::drawCard(int cardPos) { //manarie(to draw a card that i want)
	availableCards[cardPos]--;
	CardModel cardModel(cards[cardPos], true, values[cardPos]);
	return cardModel;
}
Deck::~Deck()
{
}
