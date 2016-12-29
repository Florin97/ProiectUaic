#ifndef GAME_VIEW_H
#define GAME_VIEW_H
#include "SDL.h"
#include <vector>
#include "Shape.h"
#include "Card.h"
#include "Button.h"

#define BUTTON_GREEN SDL_MapRGB(screen->format, 104, 159, 56)
#define BUTTON_RED SDL_MapRGB(screen->format, 230, 74, 25)
#define BUTTON_GREEN_CHECKED SDL_MapRGB(screen->format, 205, 220, 57)
#define DEFAULT_CHECK_BUTTON_POSITION 1
#define BALANCE_HEIGHT 50

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
public:
	GameView(SDL_Window *window, SDL_Surface *surface);
	~GameView();

	void draw();
	void destroy();
	void displayStartGameMode(GameController* gameController, int balance);
	void displayGameInProgressMode(GameController* gameController, int balance, int currentBet, char *dealerCard[], char *playerCard[]);
	void handleEvent(SDL_Event event);
	void checkButton(int buttonIndex);
};
#endif
