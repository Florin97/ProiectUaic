#ifndef GAME_VIEW_H
#define GAME_VIEW_H
#include "SDL.h"
#include <vector>
#include "CardModel.h"
#include "Shape.h"
#include "Card.h"
#include "Button.h"
#include "Hand.h"

#define BUTTON_GREEN SDL_MapRGB(screen->format, 104, 159, 56)
#define BUTTON_RED SDL_MapRGB(screen->format, 230, 74, 25)
#define BUTTON_GREEN_CHECKED SDL_MapRGB(screen->format, 205, 220, 57)
#define BUTTON_BROWN SDL_MapRGB(screen->format, 121, 85, 72)
#define BUTTON_DEFAULT SDL_MapRGB(screen->format, 97, 97, 97)
#define DEFAULT_CHECK_BUTTON_POSITION 1
#define BALANCE_HEIGHT 50
#define BUTTON_HEIGHT 100

class Button;
class GameController;

class GameView
{
private:
	SDL_Window *window;
	SDL_Surface *screen;
	vector<Card> cards;
	vector<Button> buttons;
	vector<Text> texts;
	int margin = 10;
	int checkedButtonPosition;

	void clearShapes();
	void addBalanceText(int balance);
	void addButtons(GameController* gameController);
	void addHandValueText(int top, int height, Hand hand);
public:
	GameView(SDL_Window *window, SDL_Surface *surface);
	~GameView();

	void draw();
	void destroy();
	void displayStartGameMode(GameController* gameController, int balance);
	void displayGameInProgressMode(GameController* gameController, int balance, int currentBet, Hand dealerHand, Hand playerHand);
	void handleEvent(SDL_Event event);
	void checkButton(int buttonIndex);
};
#endif
