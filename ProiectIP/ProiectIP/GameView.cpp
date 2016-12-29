#include "GameView.h"

GameView::GameView(SDL_Window *window, SDL_Surface *surface)
{
	this->window = window;
	this->screen = surface;
}
void GameView::displayGameInProgressMode(GameController* gameController, int balance, int currentBet, char *dealerCard[], char *playerCard[]) {
	clearShapes();
	
	Uint32 frontColor = SDL_MapRGB(screen->format, 255, 255, 255);
	Uint32 backColor = BUTTON_BROWN;

	int width = screen->w / 7;
	int height = screen->h / 4;

	Card card(dealerCard[0], frontColor, backColor, margin, margin, width, height);
	cards.push_back(card);

	Card card2(dealerCard[1], frontColor, backColor, margin + width + 10, margin, width, height, false);
	cards.push_back(card2);

	addBalanceText(balance);

	int top = margin * 2 + height;
	SDL_Rect bounds = { 0,top,screen->w, BALANCE_HEIGHT };
	SDL_Color white = { 255, 255,255, 255 };
	char numstr[21]; // enough to hold all numbers up to 64-bits
	sprintf_s(numstr, "Bet: %d", currentBet);
	Text text(numstr, bounds, white, 25);
	texts.push_back(text);

	top += margin + BALANCE_HEIGHT;
	Card playerCard1(playerCard[0], frontColor, backColor, margin, top, width, height);
	cards.push_back(playerCard1);

	Card playerCard2(playerCard[1], frontColor, backColor, margin + width + 10, top, width, height);
	cards.push_back(playerCard2);

	addButtons(gameController);
	
	draw();
}
void GameView::addButtons(GameController* gameController) {
	int nrButtons = 4;
	
	int buttonWidth = (screen->w - (nrButtons + 1)*margin) / nrButtons;
	int top = screen->h - BUTTON_HEIGHT - margin * 2 - BALANCE_HEIGHT;
	char *buttonTexts[] = { "SPLIT","HIT","STAND","DOUBLE"};
	int tags[] = { TAG_SPLIT, TAG_HIT, TAG_STAND, TAG_DOUBLE };

	for (int i = 0; i < nrButtons; i++) {
		int x = margin*(i + 1) + i*buttonWidth;
		SDL_Rect rect = { x, top, buttonWidth, BUTTON_HEIGHT };

		Button button(tags[i], i, buttonTexts[i], BUTTON_DEFAULT, rect, 30);
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
