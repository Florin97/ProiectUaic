#include "GameView.h"

GameView::GameView(SDL_Window *window, SDL_Surface *surface)
{
	this->window = window;
	this->screen = surface;
}
void GameView::displayGameInProgressMode(GameController* gameController, int balance, Hand dealerHand, Hand playerHand, Hand *playerSecondHand, Hand* currentHand) {
	clearShapes();
	
	Uint32 frontColor = SDL_MapRGB(screen->format, 255, 255, 255);//white
	Uint32 backColor = BUTTON_BROWN;

	int cardWidth = screen->w / 12;
	int cardHeight = screen->h / 5;

	int left = margin;
	vector<CardModel> dealerCards = dealerHand.getCards();
	for (vector<CardModel>::const_iterator it = dealerCards.begin(); it != dealerCards.end(); ++it) {
		CardModel cardModel = *it;
		Card card(cardModel.getCard(), frontColor, backColor, left, margin, cardWidth, cardHeight, cardModel.isCardVisible());
		cards.push_back(card);

		left += cardWidth + margin;
	}


	addBalanceText(balance);

	int top = addDealerHandInfo(gameController, dealerHand, cardHeight);

	top += margin + TEXT_HEIGHT;

	left = margin;
	vector<CardModel> playerCards = playerHand.getCards();
	for (vector<CardModel>::const_iterator it = playerCards.begin(); it != playerCards.end(); ++it) {
		CardModel cardModel = *it;

		Card playerCard1(cardModel.getCard(), frontColor, backColor, left, top, cardWidth, cardHeight);
		cards.push_back(playerCard1);

		left += cardWidth + margin;
	}
	

	//draw second hand
	if (playerSecondHand != NULL) {
		left += margin * 2;

		playerCards = playerSecondHand->getCards();
		for (vector<CardModel>::const_iterator it = playerCards.begin(); it != playerCards.end(); ++it) {
			CardModel cardModel = *it;

			Card playerCard1(cardModel.getCard(), frontColor, backColor, left, top, cardWidth, cardHeight);
			cards.push_back(playerCard1);

			left += cardWidth + margin;
		}
	}

	addHandValueText(top, cardHeight,playerHand, playerSecondHand, currentHand);

	addButtons(gameController);
	
	draw();
}
int GameView::addDealerHandInfo(GameController* gameController, Hand dealerHand, int cardHeight) {
	int top = margin * 2 + cardHeight;
	SDL_Rect bounds = { 0,top,screen->w, TEXT_HEIGHT };
	SDL_Color white = { 255, 255,255, 255 };
	char numstr[50];
	if (dealerHand.shouldShowHandValue()) {
		if (dealerHand.isHandBusted()) {
			sprintf_s(numstr, "Dealer Busted");
		}
		else {
			sprintf_s(numstr, "Dealer hand value: %d", dealerHand.getHandValue());
		}

		Text text(numstr, bounds, white, 25);
		texts.push_back(text);
	}


	return top;

}
void GameView::addHandValueText(int top, int cardHeight, Hand hand, Hand *playerSecondHand, Hand *currentHand) {

	char handText[200];
	
	sprintf_s(handText, "%s%sHand value: %d, (Bet: %d)", hand.getCurrentHandMarker(currentHand),hand.getStatusText(), hand.getHandValue(), hand.getBet());

	if (playerSecondHand != NULL) {
		sprintf_s(handText, "%s, || %s%sSecond Hand value: %d, (Bet: %d)", handText, playerSecondHand->getCurrentHandMarker(currentHand), playerSecondHand->getStatusText(), playerSecondHand->getHandValue(), playerSecondHand->getBet());
	}
	SDL_Rect handValueBounds = { 0,top + cardHeight,  screen->w, TEXT_HEIGHT };
	
	SDL_Color white = { 255, 255,255, 255 };
	Text handValueText(handText, handValueBounds, white, 25);
	texts.push_back(handValueText);
}
void GameView::addButtons(GameController* gameController) {

	vector<ButtonModel> buttonModels = gameController->getButtons();
	
	int buttonWidth = (screen->w - (MAX_BUTTONS + 1)*margin) / MAX_BUTTONS;
	int top = screen->h - BUTTON_HEIGHT - margin * 2 - TEXT_HEIGHT;

	int nrOfNotDisplayedButtons = MAX_BUTTONS - buttonModels.size();
	int left = (nrOfNotDisplayedButtons*(buttonWidth+margin))/2; //centrate buttons

	for (int i = 0; i < buttonModels.size(); i++) {
		int x = left+margin*(i + 1) + i*buttonWidth; 
		SDL_Rect rect = { x, top, buttonWidth, BUTTON_HEIGHT };

		ButtonModel buttonModel = buttonModels.at(i);
		Button button(buttonModel.getTag(), i, buttonModel.getLabel(), BUTTON_DEFAULT_COLOR, rect, 30);
		button.setGameController(gameController);
		buttons.push_back(button);

	}
}
void GameView::displayChooseBetMode(GameController* gameController, int balance) {
	
	clearShapes();
	
	checkedButtonPosition = DEFAULT_CHECK_BUTTON_POSITION;

	int nrButtons = 5;
	
	int buttonWidth = (screen->w - (nrButtons + 1)*margin) / nrButtons;//calculate width of button
	int top = screen->h - BUTTON_HEIGHT - margin*2 - TEXT_HEIGHT; //calculate height of button
	char *buttonTexts[] = { "1","5","25","100","DEAL" };  //text of buttons
	
	for (int i = 0; i < nrButtons; i++) { //create buttons
		int x = margin*(i + 1) + i*buttonWidth;  //calculate x for i button
		SDL_Rect rect = { x, top, buttonWidth, BUTTON_HEIGHT };//buttons area
		Uint32 color;
		int tag;
		if (i < nrButtons - 1) {
			color = BUTTON_GREEN;
			tag = TAG_BET_PRICE;
		}
		else {
			color = BUTTON_RED;
			tag = TAG_DEAL;
		}
		if (i == checkedButtonPosition) {
			color = BUTTON_GREEN_CHECKED;
		}
		Button button(tag, i, buttonTexts[i], color, rect); //create button
		button.setGameController(gameController); 
		buttons.push_back(button);

	}

	addBalanceText(balance);

	SDL_Rect bounds = { 0,0,screen->w, top};
	SDL_Color white = { 255, 255,255, 255 };

	Text text("BLACKJACK", bounds, white, 100, "KumarOne-Regular.ttf");
	texts.push_back(text);

	draw();
}
void GameView::addBalanceText(int balance) {
	SDL_Rect bounds = { 0,screen->h - TEXT_HEIGHT - margin,screen->w, TEXT_HEIGHT };
	SDL_Color white = { 255, 255,255, 255 };
	char numstr[21]; 
	sprintf_s(numstr, "Balance: %d", balance);
	Text text(numstr, bounds, white, 25);
	texts.push_back(text);

}
void GameView::checkButton(int buttonIndex) {
	buttons.at(checkedButtonPosition).setBackgroundColor(BUTTON_GREEN);
	buttons.at(buttonIndex).setBackgroundColor(BUTTON_GREEN_CHECKED);
	this->checkedButtonPosition = buttonIndex;
	draw();
}
void GameView::draw() {
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 69, 90, 100));

	for (vector<Card>::const_iterator it = cards.begin(); it != cards.end(); ++it) {
		Card card = *it;
		card.draw(screen);
	}

	for (vector<Button>::const_iterator it = buttons.begin(); it != buttons.end(); ++it) {
		Button button = *it;
		button.draw(screen);
	}
	for (vector<Text>::const_iterator it = texts.begin(); it != texts.end(); ++it) {
		Text text = *it;
		text.draw(screen);
	}
	
	SDL_UpdateWindowSurface(window);

}
void GameView::clearShapes() {
	cards.clear();
	buttons.clear();
	texts.clear();
}
void GameView::handleEvent(SDL_Event event) {
	for (vector<Button>::const_iterator it = buttons.begin(); it != buttons.end(); ++it) {
		Button button = *it;
		if (button.handleEvent(event)) {
			return;
		}
	}
}
void GameView::destroy() {

}
GameView::~GameView()
{

}
