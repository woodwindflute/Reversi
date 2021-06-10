#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include <string>
#include <algorithm>
#include "MainMenu.h"
#include <iomanip>
#include <fstream>
#include <mmsystem.h>
#pragma comment(lib,"Winmm.lib")

#define KEYBOARD_UP 72
#define KEYBOARD_DOWN 80
#define KEYBOARD_LEFT 75
#define KEYBOARD_RIGHT 77
#define KEYBOARD_LEFT_SHIFT 44
#define KEYBOARD_RIGHT_SHIFT 46
#define KEYBOARD_ENTER 13
#define KEYBOARD_ESCAPE 27

#define KEYBOARD_W 119
#define KEYBOARD_A 97
#define KEYBOARD_S 115
#define KEYBOARD_R 114
#define KEYBOARD_D 100
#define KEYBOARD_SPACE 32

using namespace std;

typedef pair<int, int> COORDINATE;


#ifndef _CHESS_CHINESE_
#define _CHESS_CHINESE_
extern const string chessChinese[15];
#endif // !_CHESS_CHINESE_

#ifndef _CELAR_BOARD_
#define _CELAR_BOARD_
extern const string clearBoard[21][18];
#endif // !_CELAR_BOARD_

#ifndef _CONSOLE_INFO_HANDLE_
#define _CONSOLE_INFO_HANDLE_
extern CONSOLE_CURSOR_INFO cci;
extern HANDLE handle;
extern COORD cursorPosition;
#endif // !_CONSOLE_INFO_HANDLE_

#ifndef _GAME_MENU_
#define _GAME_MENU_
extern const string gameMenuOption[7];
#endif // !_GAME_MENU_

#ifndef _LEFT_RIGHT_SPACE_
#define _LEFT_RIGHT_SPACE_
extern const string leftSpace[21];
extern const string rightSpace[21];
#endif // !_LEFT_RIGHT_SPACE_

//static CONSOLE_SCREEN_BUFFER_INFO csbi;

#ifndef _GAME_H_
#define _GAME_H_
class Game
{
public:
	Game(string);
	~Game();
	void gameStart();
	void computerGameStart();
	int computerThinking();
	void process(int,int);
	void showMenu();
	void showHint();
	void showList();
	void showWhoTurn();
	bool isEnd();
	void undo();
	void redo();
	void restart();
	bool isSuccess(int, int, int);
	int nowTurn;
};
#endif // !_GAME_H_