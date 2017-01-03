#include "GameView.h"

GameView::GameView(SDL_Window *window, SDL_Surface *surface)
{
	this->window = window;
	this->screen = surface;
}
void GameView::displayGameInProgressMode(GameController* gameController, int balance, int currentBet, Hand dealerHand, Hand playerHand) {
	clearShapes();
	
	Uint32 frontColor = SDL_MapRGB(screen->format, 255, 255, 255);
	Uint32 backColor = BUTTON_BROWN;

	int width = screen->w / 12;
	int height = screen->h / 5;

	int left = margin;
	vector<CardModel> dealerCards = dealerHand.getCards();
	for (vector<CardModel>::const_iterator it = dealerCards.begin(); it != dealerCards.end(); ++it) {
		CardModel cardModel = *it;
		Card card(cardModel.getCard(), frontColor, backColor, left, margin, width, height, cardModel.isCardVisible());
		cards.push_back(card);

		left += width + margin;
	}


	addBalanceText(balance);

	int top = margin * 2 + height;
	SDL_Rect bounds = { 0,top,screen->w, BALANCE_HEIGHT };
	SDL_Color white = { 255, 255,255, 255 };
	char numstr[21]; // enough to hold all numbers up to 64-bits
	sprintf_s(numstr, "Bet: %d", currentBet);
	Text text(numstr, bounds, white, 25);
	texts.push_back(text);

	top += margin + BALANCE_HEIGHT;

	left = margin;
	vector<CardModel> playerCards = playerHand.getCards();
	for (vector<CardModel>::const_iterator it = playerCards.begin(); it != playerCards.end(); ++it) {
		CardModel cardModel = *it;

		Card playerCard1(cardModel.getCard(), frontColor, backColor, left, top, width, height);
		cards.push_back(playerCard1);

		left += width + margin;
	}
	

	addHandValueText(top, height,playerHand);

	addButtons(gameController);
	
	draw();
}
void GameView::addHandValueText(int top, int height, Hand hand) {
	int handValue = hand.getHandValue();
	char handText[30]; // enough to hold all numbers up to 64-bits
	if (handValue <= 21) {
		sprintf_s(handText, "Hand value: %d", handValue);
	}
	else {
		sprintf_s(handText, "Busted: %d", handValue);
	}

	SDL_Rect handValueBounds = { 0,top + height,  screen->w, BALANCE_HEIGHT };
	
	SDL_Color white = { 255, 255,255, 255 };
	Text handValueText(handText, handValueBounds, white, 25);
	texts.push_back(handValueText);
}
void GameView::addButtons(GameController* gameController) {

	vector<ButtonModel> buttonModels = gameController->getButtons();
	
	int buttonWidth = (screen->w - (MAX_BUTTONS + 1)*margin) / MAX_BUTTONS;
	int top = screen->h - BUTTON_HEIGHT - margin * 2 - BALANCE_HEIGHT;

	int nrOfNotDisplayedButtons = MAX_BUTTONS - buttonModels.size();
	int left = (nrOfNotDisplayedButtons*(buttonWidth+margin))/2;

	for (int i = 0; i < buttonModels.size(); i++) {
		int x = left+margin*(i + 1) + i*buttonWidth;
		SDL_Rect rect = { x, top, buttonWidth, BUTTON_HEIGHT };

		ButtonModel buttonModel = buttonModels.at(i);
		Button button(buttonModel.getTag(), i, buttonModel.getLabel(), BUTTON_DEFAULT, rect, 30);
		button.setListener(gameController);
		buttons.push_back(button);

	}
}
void GameView::displayStartGameMode(GameController* gameController, int balance) {
	
	clearShapes();
	
	checkedButtonPosition = DEFAULT_CHECK_BUTTON_POSITION;

	int nrButtons = 5;
	
	int buttonWidth = (screen->w - (nrButtons + 1)*margin) / nrButtons;
	int top = screen->h - BUTTON_HEIGHT - margin*2 - BALANCE_HEIGHT;
	char *buttonTexts[] = { "1","5","25","100","DEAL" };
	
	for (int i = 0; i < nrButtons; i++) {
		int x = margin*(i + 1) + i*buttonWidth;
		SDL_Rect rect = { x, top, buttonWidth, BUTTON_HEIGHT };
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
		Button button(tag, i, buttonTexts[i], color, rect);
		button.setListener(gameController);
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
	SDL_Rect bounds = { 0,screen->h - BALANCE_HEIGHT - margin,screen->w, BALANCE_HEIGHT };
	SDL_Color white = { 255, 255,255, 255 };
	char numstr[21]; // enough to hold all numbers up to 64-bits
	sprintf_s(numstr, "Balance:%d", balance);
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
