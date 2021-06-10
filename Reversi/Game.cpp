#include "Game.h"
#include <iostream>

// 鍵盤掃描碼
// 上:		72
// 下:		80
// 左:		75
// 右:		77
// <:		44
// >:		46
// Enter:	13
// Esc:		27
// w		119
// a		97
// s		115
// d		100
// space	32

#ifdef _CONSOLE_INFO_HANDLE_
CONSOLE_CURSOR_INFO cci;
HANDLE handle;
COORD cursorPosition;
#endif // _CONSOLE_INFO_HANDLE_


string Board[19] = {
		{"　　ａ　ｂ　ｃ　ｄ　ｅ　ｆ　ｇ　ｈ　"},
		{"　‧－－－－－－－－－－－－－－－‧"},
		{"１｜　｜　｜　｜　｜　｜　｜　｜　｜１"},
		{"　｜－＋－＋－＋－＋－＋－＋－＋－｜　"},
		{"２｜　｜　｜　｜　｜　｜　｜　｜　｜２"},
		{"　｜－＋－＋－＋－＋－＋－＋－＋－｜　"},
		{"３｜　｜　｜　｜　｜　｜　｜　｜　｜３"},
		{"　｜－＋－＋－＋－＋－＋－＋－＋－｜　"},
		{"４｜　｜　｜　｜　｜　｜　｜　｜　｜４"},
		{"　｜－＋－＋－＋－＋－＋－＋－＋－｜　"},
		{"５｜　｜　｜　｜　｜　｜　｜　｜　｜５"},
		{"　｜－＋－＋－＋－＋－＋－＋－＋－｜　"},
		{"６｜　｜　｜　｜　｜　｜　｜　｜　｜６"},
		{"　｜－＋－＋－＋－＋－＋－＋－＋－｜　"},
		{"７｜　｜　｜　｜　｜　｜　｜　｜　｜７"},
		{"　｜－＋－＋－＋－＋－＋－＋－＋－｜　"},
		{"８｜　｜　｜　｜　｜　｜　｜　｜　｜８"},
		{"　‧－－－－－－－－－－－－－－－‧　"},
		{"　　ａ　ｂ　ｃ　ｄ　ｅ　ｆ　ｇ　ｈ　　"}
};












string png1[10] = {
	{"　　　　　"},
	{"　　　　　"},
	{"██　　　"},
	{"　█　　　"},
	{"　　█　　"},
	{"　　██　"},
	{"　████"},
	{"███口█"},
	{"█口口口█"},
	{"　口口口　"},
};

string png2[10] = {
	{"　　　　　"},
	{"　█　　　"},
	{"　　　　　"},
	{"　　　　　"},
	{"　　█　　"},
	{"　███　"},
	{"█████"},
	{"█口口口█"},
	{"█口口口█"},
	{"　口口口　"},
};

string png3[10] = {
	{"　　　　　"},
	{"　　　█　"},
	{"　　██　"},
	{"　　█　　"},
	{"　█　　　"},
	{"███　　"},
	{"████　"},
	{"██口██"},
	{"█口口口█"},
	{"　口口口　"},
};

string png4[10] = {
	{"　　　█　"},
	{"　　　　　"},
	{"　　　　　"},
	{"　　　　　"},
	{"　██　　"},
	{"████　"},
	{"█████"},
	{"██口口█"},
	{"█口口口█"},
	{"　口口口　"},
};

#ifdef _GAME_MENU_
const string gameMenuOption[7] = {
		"▼＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝▼",
		"∥　　　　　→繼續遊戲　　　　　∥",
		"∥＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝∥",
		"∥　　　　　　儲存棋盤　　　　　∥",
		"∥＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝∥",
		"∥　　　　　　返回主選單　　　　∥",
		"▲＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝▲"
};
#endif // _GAME_MENU_

int chess[8][8];
int lastChess[8][8];
int lastlastChess[8][8];

namespace {
	int numberBlack = 0, numberWhite = 0;
	// Intent:顯示/隱藏 console 的游(光)標 cursor
	// Pre:傳入bool，true->顯示 / false->隱藏
	// Post:無
	void cursorVisiable(bool flag) {
		GetConsoleCursorInfo(handle, &cci);
		cci.bVisible = flag;
		SetConsoleCursorInfo(handle, &cci);
	}
	// Intent:設置console游(光)標cursor 位置
	// Pre:int [x]、[y]，左上角為(0,0)			/// (42,2)為棋盤內可移動的最左上角
	// Post:無
	void setConsoleCursorCoordinate(int x = 42, int y = 1) {
		cursorPosition.X = x;	cursorPosition.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
	}
	
	void printFireAnimation() {
		for (int j = 0; j < 10; j++) {
			
			for (int i = 0; i < 10; i++) {
				setConsoleCursorCoordinate(55, 10 + i);
				cout << png1[i] << "\n";
			}
			Sleep(100);
			for (int i = 0; i < 10; i++) {
				setConsoleCursorCoordinate(55, 10 + i);
				cout << png2[i] << "\n";
			}
			Sleep(100);
			for (int i = 0; i < 10; i++) {
				setConsoleCursorCoordinate(55, 10 + i);
				cout << png3[i] << "\n";
			}
			Sleep(100);
			for (int i = 0; i < 10; i++) {
				setConsoleCursorCoordinate(55, 10 + i);
				cout << png4[i] << "\n";
			}
			Sleep(100);
		}
	}

	void printBoard() {
		numberBlack = 0, numberWhite = 0;
		for (int i = 0; i < 16; i+=2) {
			for (int j = 0; j < 16; j+=2) {
				setConsoleCursorCoordinate(4 + 2 * j, 2+i);
				if (chess[i/2][j/2] == 0)
					cout << "　";
				else if (chess[i/2][j/2] == 1)
					cout << "○";
				else if (chess[i/2][j/2] == 2)
					cout << "●";
			}
		}
	}

	void printStatus() {
		numberBlack = 0;
		numberWhite = 0;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (chess[j][i] == 2) numberBlack++;
				if (chess[j][i] == 1)numberWhite++;
			}
		}
		setConsoleCursorCoordinate(44,2);
		cout << "● ： " << numberBlack << "　";
		setConsoleCursorCoordinate(44, 4);
		cout << "○ ： " << numberWhite << "　";
		
	}

	void printItem() {
		setConsoleCursorCoordinate(55, 2);
		cout << "＜ ： UNDO";
		setConsoleCursorCoordinate(55, 4);
		cout << "＞ ： REDO";
		setConsoleCursorCoordinate(44, 6);
		cout << "R：Restart　ESC：回主選單";
	}

	// 顯示yes no對話框
	bool showDialog(string msg, bool showOption = true) {
		setConsoleCursorCoordinate(42, 6);
		cout << "▼＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝▼";
		for (int i = 1; i <= 11; i++) {
			setConsoleCursorCoordinate(42, 6 + i);
			cout << "∥　　　　　　　　　　　　　　　∥";
			if (i == 3) {
				setConsoleCursorCoordinate(46, 6 + i);
				cout << msg;
			}
			else if (i == 8 && showOption) {
				setConsoleCursorCoordinate(60, 6 + i);
				cout << "是";
				setConsoleCursorCoordinate(68, 6 + i);
				cout << "否";
			}
		}
		setConsoleCursorCoordinate(42, 17);
		cout << "▲＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝▲";

		setConsoleCursorCoordinate(60, 14);
		if (!showOption)	cursorVisiable(false);
		int commandPress = 0, x = 60;
		while (commandPress = _getch())
		{
			if (showOption) {
				if (commandPress == KEYBOARD_LEFT || commandPress == KEYBOARD_A) {
					x -= 8;
				}
				else if (commandPress == KEYBOARD_RIGHT || commandPress == KEYBOARD_D) {
					x += 8;
				}
				else if (commandPress == KEYBOARD_ENTER || commandPress == KEYBOARD_SPACE) {
					if (x == 60) {
						return true;
					}
					else if (x == 68) {
						return false;
					}
				}
				else if (commandPress == KEYBOARD_ESCAPE) {
					return false;
				}
				x = (x > 68) ? 60 : x;
				x = (x < 60) ? 68 : x;
				setConsoleCursorCoordinate(x, 14);
			}
			else {
				if (commandPress == KEYBOARD_ESCAPE) menu->showMenu();
			}
		}
		return false;
	}
}


Game::Game(string fileName)
{
	system("color F0");
	this->nowTurn = 0;
	// =====================初始化console控制元件=====================
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	cursorPosition.X = 0;	cursorPosition.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
	// =====================初始化console控制元件=====================
}

Game::~Game()
{
	
}

void Game::showMenu() {

	// 顯示gameMenu
	for (int i = 0; i < (sizeof(gameMenuOption) / sizeof(gameMenuOption[0])); i++) {
		setConsoleCursorCoordinate(42, 5 + i);
		cout << gameMenuOption[i];
	}
	// 宣告gameMenu 專屬console座標 int [y]
	int commandPress, y = 6;
	// 設定console座標位置，從(54,6)開始繪製
	setConsoleCursorCoordinate(54, 6);
	cursorVisiable(false);
	while (commandPress = _getch())
	{
		if (commandPress == KEYBOARD_UP || commandPress == KEYBOARD_W) {
			y -= 2;
		}
		else if (commandPress == KEYBOARD_DOWN || commandPress == KEYBOARD_S) {
			y += 2;
		}
		else if (commandPress == KEYBOARD_ENTER || commandPress == KEYBOARD_SPACE) {
			if (y == 6) {
				cursorVisiable(true);
				//this->freshGameConsole();
				//printBoardNoSpace(this->boardStatus, 42, 1);
				break;
			}
			else if (y == 8) {
				//儲存遊戲
			}
			else if (y == 10) {
				if (menu != NULL) {
					system("cls");
					this->~Game();
					menu->showMenu();
				}
			}
		}
		else if (commandPress == KEYBOARD_ESCAPE) {
			cursorVisiable(true);
			//this->freshGameConsole();
			//printBoardNoSpace(this->boardStatus, 42, 1);
			break;
		}
		y = (y > 10) ? 6 : y;
		y = (y < 6) ? 10 : y;
		cout << "　\b\b";
		setConsoleCursorCoordinate(54, y);
		cout << "→\b\b";
	}
}


void Game::gameStart() 
{
	// 清空console
	system("cls");
	// 設置視窗大小
	SMALL_RECT windowSize = { 0,0,80, 20 };
	SetConsoleWindowInfo(handle, TRUE, &windowSize);

	PlaySound("Sounds/Produce.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	// 繪製遊戲畫面
	for (int i = 0; i < 19; i++) {
		cout << Board[i] << endl;
	}
	printItem();
	setConsoleCursorCoordinate(44, 8);
	cout << "棋盤載入中...";
	printFireAnimation();
	//棋盤初始化
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			chess[i][j] = 0;
		}
	}
	chess[3][3] = 1; chess[4][4] = 1;
	chess[3][4] = 2; chess[4][3] = 2;
	printBoard();
	printStatus();

	// 顯示提示
	this->showHint();
	this->showWhoTurn();


	// 將畫面往上拉，若不將光標位置y提至0的話，console畫面將會往下一點
	setConsoleCursorCoordinate(0, 0);

	// 顯示光標(Cursor)
	cursorVisiable(true);

	int commandPress,x = 4, y = 2;
	// 設定console座標位置，從(4,2)開始繪製
	setConsoleCursorCoordinate(4, 2);

	while (commandPress = _getch())
	{
		if (commandPress == KEYBOARD_UP) {
			y -= 2;
		}
		else if (commandPress == KEYBOARD_DOWN) {
			y += 2;
		}
		else if (commandPress == KEYBOARD_LEFT) {
			x -= 4;
		}

		else if (commandPress == KEYBOARD_RIGHT) {
			x += 4;
		}
		else if (commandPress == KEYBOARD_LEFT_SHIFT) {
			undo();
		}
		else if (commandPress == KEYBOARD_RIGHT_SHIFT) {
			redo();
		}
		else if (commandPress == KEYBOARD_R) {
			restart();
		}
		else if (commandPress == KEYBOARD_ESCAPE) {
			menu->showMenu();
		}
		else if (commandPress == KEYBOARD_ENTER) {
			mciSendString("play \"Sounds/下棋聲.mp3\" ", NULL, 0, 0);
			//SAVE 
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					lastChess[i][j] = chess[i][j];
				}
			}
			setConsoleCursorCoordinate(x, y);
			if (this->nowTurn == 0) {
				chess[(y - 2) / 2][x / 4 - 1] = 2;
				process(x / 4 - 1, (y - 2) / 2);
			}
			else if (this->nowTurn == 1) {
				chess[(y - 2) / 2][x / 4 - 1] = 1;
				process(x / 4 - 1, (y - 2) / 2);
			}
			printBoard();
			printStatus();
			this->nowTurn = (this->nowTurn == 0) ? 1 : 0;
			this->showHint();
			this->showWhoTurn();
			if (isEnd()) {
				if (numberBlack > numberWhite)showDialog("黑色贏了！", false);
				else if (numberWhite > numberBlack)showDialog("白色贏了！", false);
				else showDialog("平手　　", false);
			}
			
		}
		y = (y > 16) ? 2 : y;
		y = (y < 2) ? 2 : y;
		x = (x > 34) ? 4 : x;
		x = (x < 4) ? 4 : x;
		//cout << "\a";
		setConsoleCursorCoordinate(x, y);
	}
}

void Game::computerGameStart()
{
	// 清空console
	system("cls");
	// 設置視窗大小
	SMALL_RECT windowSize = { 0,0,80, 20 };
	SetConsoleWindowInfo(handle, TRUE, &windowSize);

	PlaySound("Sounds/Produce.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	// 繪製遊戲畫面
	for (int i = 0; i < 19; i++) {
		cout << Board[i] << endl;
	}

	setConsoleCursorCoordinate(44, 6);
	cout << "R：Restart　ESC：回主選單";

	//棋盤初始化
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			chess[i][j] = 0;
		}
	}
	chess[3][3] = 1; chess[4][4] = 1;
	chess[3][4] = 2; chess[4][3] = 2;
	printBoard();
	printStatus();

	// 顯示提示
	this->showHint();


	// 將畫面往上拉，若不將光標位置y提至0的話，console畫面將會往下一點
	setConsoleCursorCoordinate(0, 0);

	// 顯示光標(Cursor)
	cursorVisiable(true);

	int commandPress, x = 4, y = 2;
	// 設定console座標位置，從(4,2)開始繪製
	setConsoleCursorCoordinate(4, 2);

	while (commandPress = _getch())
	{
		if (commandPress == KEYBOARD_UP) {
			y -= 2;
		}
		else if (commandPress == KEYBOARD_DOWN) {
			y += 2;
		}
		else if (commandPress == KEYBOARD_LEFT) {
			x -= 4;
		}

		else if (commandPress == KEYBOARD_RIGHT) {
			x += 4;
		}
		else if (commandPress == KEYBOARD_LEFT_SHIFT) {
			undo();
		}
		else if (commandPress == KEYBOARD_RIGHT_SHIFT) {
			redo();
		}
		else if (commandPress == KEYBOARD_R) {
			restart();
		}
		else if (commandPress == KEYBOARD_ESCAPE) {
			menu->showMenu();
		}
		else if (commandPress == KEYBOARD_ENTER) {
			mciSendString("play \"Sounds/下棋聲.mp3\" ", NULL, 0, 0);
			//SAVE 
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					lastChess[i][j] = chess[i][j];
				}
			}
			setConsoleCursorCoordinate(x, y);
			if (this->nowTurn == 0) {
				chess[(y - 2) / 2][x / 4 - 1] = 2;
				process(x / 4 - 1, (y - 2) / 2);
			}
			printBoard();
			printStatus();
			this->nowTurn = 1;
			this->showHint();
			this->nowTurn = 0;
			
			setConsoleCursorCoordinate(44, 8);
			cout << "電腦正在思考中...";
			printFireAnimation();
			mciSendString("play \"Sounds/下棋聲.mp3\" ", NULL, 0, 0);
			int a = computerThinking();
			chess[a % 10][a / 10] = 1;
			process( a / 10, a % 10);
			setConsoleCursorCoordinate(44, 8);
			cout << "　　　　　　　　　";
			printBoard();
			printStatus();
			if (isEnd()) {
				if (numberBlack > numberWhite)showDialog("黑色贏了！", false);
				else if (numberWhite > numberBlack)showDialog("白色贏了！", false);
				else showDialog("平手　　", false);
			}
			this->showHint();
			
		}
		y = (y > 16) ? 2 : y;
		y = (y < 2) ? 2 : y;
		x = (x > 34) ? 4 : x;
		x = (x < 4) ? 4 : x;
		//cout << "\a";
		setConsoleCursorCoordinate(x, y);
	}
}

int Game::computerThinking()
{
	int zero = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (isSuccess(j, i, 1) && chess[i][j] == 0) {
				zero++;
			}
			if (zero == 1) return 10 * j + i; //都找第一個可以的位子
		}
	}

}

void Game::process(int x,int y)
{
	int change = 0, smaller;
	int firstSamePosition = 0;
	bool flag;
	//search up
	if (y != 0) {
		for (int i = y - 1; i >= 0; i--) {
			if (chess[i][x] == 0) {
				change = 0;
				break;
			}
			if (chess[i][x] == chess[y][x]) {
				firstSamePosition = i;
				change = 1;
				break;
			}
		}
		if (change == 1) {
			for (int i = firstSamePosition; i <= y; i++) {
				chess[i][x] = chess[y][x];
			}
			//printBoard();
		}
		change = 0;
	}
	//search down
	if (y != 7) {
		for (int i = y + 1; i <= 7; i++) {
			if (chess[i][x] == 0) {
				change = 0;
				break;
			}
			if (chess[i][x] == chess[y][x]) {
				firstSamePosition = i;
				change = 1;
				break;
			}
		}
		if (change == 1) {
			for (int i = y; i <= firstSamePosition; i++) {
				chess[i][x] = chess[y][x];
			}
			//printBoard();
		}
		change = 0;
	}
	//search left
	if (x != 0) {
		for (int i = x - 1; i >= 0; i--) {
			if (chess[y][i] == 0) {
				change = 0;
				break;
			}
			if (chess[y][i] == chess[y][x]) {
				firstSamePosition = i;
				change = 1;
				break;
			}
		}
		if (change == 1) {
			for (int i = firstSamePosition; i <= x; i++) {
				chess[y][i] = chess[y][x];
			}
			//printBoard();
		}
		change = 0;
	}
	//search right
	if (x != 7) {
		for (int i = x + 1; i <= 7; i++) {
			if (chess[y][i] == 0) {
				change = 0;
				break;
			}
			if (chess[y][i] == chess[y][x]) {
				firstSamePosition = i;
				change = 1;
				break;
			}
		}
		if (change == 1) {
			for (int i = x; i <= firstSamePosition; i++) {
				chess[y][i] = chess[y][x];
			}
			//printBoard();
		}
		change = 0;
	}
	//search 右上
	if (x != 7 && y != 0) {
		smaller = (7 - x) < y ? (7 - x) : y;
		for (int i = 1; i <= smaller; i++) {
			if (chess[y - i][x + i] == 0) {
				change = 0;
				break;
			}
			if (chess[y - i][x + i] == chess[y][x]) {
				firstSamePosition = i;
				change = 1;
				break;
			}
		}
		if (change == 1) {
			for (int i = 1; i <= firstSamePosition; i++) {
				chess[y - i][x + i] = chess[y][x];
			}
			//printBoard();
		}
		change = 0;
	}
	//search 左下
	if (x != 0 && y != 7) {
		smaller = x < (7 - y) ? x : (7 - y);
		for (int i = 1; i <= smaller; i++) {
			if (chess[y + i][x - i] == 0) {
				change = 0;
				break;
			}
			if (chess[y + i][x - i] == chess[y][x]) {
				firstSamePosition = i;
				change = 1;
				break;
			}
		}
		if (change == 1) {
			for (int i = 1; i <= firstSamePosition; i++) {
				chess[y + i][x - i] = chess[y][x];
			}
			//printBoard();
		}
		change = 0;
	}
	//search 左上
	if (x != 0 && y != 0) {
		smaller = x < y ? x : y;
		for (int i = 1; i <= smaller; i++) {
			if (chess[y - i][x - i] == 0) {
				change = 0;
				break;
			}
			if (chess[y - i][x - i] == chess[y][x]) {
				firstSamePosition = i;
				change = 1;
				break;
			}
		}
		if (change == 1) {
			for (int i = 1; i <= firstSamePosition; i++) {
				chess[y - i][x - i] = chess[y][x];
			}
			//printBoard();
		}
		change = 0;
	}
	//search 右下
	if (x != 7 && y != 7) {
		smaller = (7 - x) < (7 - y) ? (7 - x) : (7 - y);
		for (int i = 1; i <= smaller; i++) {
			if (chess[y + i][x + i] == 0) {
				change = 0;
				break;
			}
			if (chess[y + i][x + i] == chess[y][x]) {
				firstSamePosition = i;
				change = 1;
				break;
			}
		}
		if (change == 1) {
			for (int i = 1; i <= firstSamePosition; i++) {
				chess[y + i][x + i] = chess[y][x];
			}
			//printBoard();
		}
		change = 0;
	}
}

bool Game::isSuccess(int x, int y,int turn)
{
	
	int change = 0, smaller;
	int firstSamePosition = 0;
	bool flag;
	//search up
	if (y != 0) {
		for (int i = y - 1; i >= 0; i--) {
			if (chess[i][x] == 0) {
				change = 0;
				break;
			}
			if (chess[i][x] == (turn==0?2:1)) {
				firstSamePosition = i;
				change = 1;
				break;
			}
		}
		if (change == 1) {
			for (int i = firstSamePosition; i < y - 1; i++) {
				return true;
			}
			//printBoard();
		}
		change = 0;
	}
	//search down
	if (y != 7) {
		for (int i = y + 1; i <= 7; i++) {
			if (chess[i][x] == 0) {
				change = 0;
				break;
			}
			if (chess[i][x] == (turn == 0 ? 2 : 1)) {
				firstSamePosition = i;
				change = 1;
				break;
			}
		}
		if (change == 1) {
			for (int i = y + 1; i < firstSamePosition; i++) {
				return true;
			}
			//printBoard();
		}
		change = 0;
	}
	//search left
	if (x != 0) {
		for (int i = x - 1; i >= 0; i--) {
			if (chess[y][i] == 0) {
				change = 0;
				break;
			}
			if (chess[y][i] == (turn == 0 ? 2 : 1)) {
				firstSamePosition = i;
				change = 1;
				break;
			}
		}
		if (change == 1) {
			for (int i = firstSamePosition; i < x - 1; i++) {
				return true;
			}
			//printBoard();
		}
		change = 0;
	}
	//search right
	if (x != 7) {
		for (int i = x + 1; i <= 7; i++) {
			if (chess[y][i] == 0) {
				change = 0;
				break;
			}
			if (chess[y][i] == (turn == 0 ? 2 : 1)) {
				firstSamePosition = i;
				change = 1;
				break;
			}
		}
		if (change == 1) {
			for (int i = x + 1; i < firstSamePosition; i++) {
				return true;
			}
			//printBoard();
		}
		change = 0;
	}
	//search 右上
	if (x != 7 && y != 0) {
		smaller = (7 - x) < y ? (7 - x) : y;
		for (int i = 1; i <= smaller; i++) {
			if (chess[y - i][x + i] == 0) {
				change = 0;
				break;
			}
			if (chess[y - i][x + i] == (turn == 0 ? 2 : 1)) {
				firstSamePosition = i;
				change = 1;
				break;
			}
		}
		if (change == 1) {
			for (int i = 1; i < firstSamePosition; i++) {
				return true;
			}
			//printBoard();
		}
		change = 0;
	}
	//search 左下
	if (x != 0 && y != 7) {
		smaller = x < (7 - y) ? x : (7 - y);
		for (int i = 1; i <= smaller; i++) {
			if (chess[y + i][x - i] == 0) {
				change = 0;
				break;
			}
			if (chess[y + i][x - i] == (turn == 0 ? 2 : 1)) {
				firstSamePosition = i;
				change = 1;
				break;
			}
		}
		if (change == 1) {
			for (int i = 1; i < firstSamePosition; i++) {
				return true;
			}
			//printBoard();
		}
		change = 0;
	}
	//search 左上
	if (x != 0 && y != 0) {
		smaller = x < y ? x : y;
		for (int i = 1; i <= smaller; i++) {
			if (chess[y - i][x - i] == 0) {
				change = 0;
				break;
			}
			if (chess[y - i][x - i] == (turn == 0 ? 2 : 1)) {
				firstSamePosition = i;
				change = 1;
				break;
			}
		}
		if (change == 1) {
			for (int i = 1; i < firstSamePosition; i++) {
				return true;
			}
			//printBoard();
		}
		change = 0;
	}
	//search 右下
	if (x != 7 && y != 7) {
		smaller = (7 - x) < (7 - y) ? (7 - x) : (7 - y);
		for (int i = 1; i <= smaller; i++) {
			if (chess[y + i][x + i] == 0) {
				change = 0;
				break;
			}
			if (chess[y + i][x + i] == (turn == 0 ? 2 : 1)) {
				firstSamePosition = i;
				change = 1;
				break;
			}
		}
		if (change == 1) {
			for (int i = 1; i < firstSamePosition; i++) {
				return true;
			}
			//printBoard();
		}
		change = 0;
	}
	return false;
}

void Game::showHint() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (isSuccess(j, i,nowTurn)&&chess[i][j]==0) {
				setConsoleCursorCoordinate(4 + 4 * j, 2 + 2 * i);
				cout << "‧";
			}
		}
	}
}

void Game::showList()
{
	setConsoleCursorCoordinate(0, 0);
	cout<<"▼＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝▼\n";
	cout<<"∥　　　　→　ＵＮＤＯ　　　　　∥\n";
	cout<<"∥＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝∥\n";
	cout<<"∥　　　　　　　２Ｐ　　　　　　∥\n";
	cout<<"∥＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝∥\n";
	cout<<"∥　　　　　　結束程式　　　　　∥\n";
	cout<<"▲＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝▲"  ;
	// 設定初始光標位置
	int commandPress = 0, y = 1;
	setConsoleCursorCoordinate(14, 1);

	// 隱藏光標
	cursorVisiable(false);

	// 光標控制
	while (commandPress = _getch())
	{
		if (commandPress == 72 || commandPress == 119)	y -= 2;
		if (commandPress == 80 || commandPress == 115)	y += 2;

		if (commandPress == 13 || commandPress == 32) {
			if (y == 1) {
				undo();
				break;
			}
			else if (y == 3) {
				showDialog("第二個", false);
			}
			else if (y == 5) {
				exit(1);
			}
		}

		if (y < 1)	y = 5;
		if (y > 5)	y = 1;

		/*cout << "\b\b　";
		cursorPosition.Y = y;
		SetConsoleCursorPosition(handle, cursorPosition);
		cout << "\b\b→";*/
	}
}

void Game::showWhoTurn()
{
	if (nowTurn == 0) {
		setConsoleCursorCoordinate(44,8);
		cout << "現在輪到 黑色 下棋。";
	}
	else {
		setConsoleCursorCoordinate(44,8);
		cout << "現在輪到 白色 下棋。";
	}
}

bool Game::isEnd() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (isSuccess(j, i, nowTurn) && chess[i][j] == 0) {
				setConsoleCursorCoordinate(4 + 4 * j, 2 + 2 * i);
				return 0;
			}
		}
	}
	return 1;
}

void Game::undo()
{
	nowTurn = (nowTurn + 1) % 2;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			lastlastChess[i][j] = chess[i][j];
		}
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			chess[i][j] = lastChess[i][j];
		}
	}
	printBoard();
	printStatus();
	showHint();
}

void Game::redo()
{
	nowTurn = (nowTurn + 1) % 2;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			chess[i][j] = lastlastChess[i][j];
		}
	}
	printBoard();
	printStatus();
	showHint();
}

void Game::restart()
{
	//棋盤初始化
	nowTurn = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			chess[i][j] = 0;
		}
	}
	chess[3][3] = 1; chess[4][4] = 1;
	chess[3][4] = 2; chess[4][3] = 2;
	printBoard();
	printStatus();

	// 顯示提示
	this->showHint();
}
