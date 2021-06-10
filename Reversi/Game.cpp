#include "Game.h"
#include <iostream>

// ��L���y�X
// �W:		72
// �U:		80
// ��:		75
// �k:		77
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
		{"�@�@��@��@��@��@��@��@��@��@"},
		{"�@�E�СССССССССССССССE"},
		{"���U�@�U�@�U�@�U�@�U�@�U�@�U�@�U�@�U��"},
		{"�@�U�СϡСϡСϡСϡСϡСϡСϡСU�@"},
		{"���U�@�U�@�U�@�U�@�U�@�U�@�U�@�U�@�U��"},
		{"�@�U�СϡСϡСϡСϡСϡСϡСϡСU�@"},
		{"���U�@�U�@�U�@�U�@�U�@�U�@�U�@�U�@�U��"},
		{"�@�U�СϡСϡСϡСϡСϡСϡСϡСU�@"},
		{"���U�@�U�@�U�@�U�@�U�@�U�@�U�@�U�@�U��"},
		{"�@�U�СϡСϡСϡСϡСϡСϡСϡСU�@"},
		{"���U�@�U�@�U�@�U�@�U�@�U�@�U�@�U�@�U��"},
		{"�@�U�СϡСϡСϡСϡСϡСϡСϡСU�@"},
		{"���U�@�U�@�U�@�U�@�U�@�U�@�U�@�U�@�U��"},
		{"�@�U�СϡСϡСϡСϡСϡСϡСϡСU�@"},
		{"���U�@�U�@�U�@�U�@�U�@�U�@�U�@�U�@�U��"},
		{"�@�U�СϡСϡСϡСϡСϡСϡСϡСU�@"},
		{"���U�@�U�@�U�@�U�@�U�@�U�@�U�@�U�@�U��"},
		{"�@�E�СССССССССССССССE�@"},
		{"�@�@��@��@��@��@��@��@��@��@�@"}
};












string png1[10] = {
	{"�@�@�@�@�@"},
	{"�@�@�@�@�@"},
	{"�i�i�@�@�@"},
	{"�@�i�@�@�@"},
	{"�@�@�i�@�@"},
	{"�@�@�i�i�@"},
	{"�@�i�i�i�i"},
	{"�i�i�i�f�i"},
	{"�i�f�f�f�i"},
	{"�@�f�f�f�@"},
};

string png2[10] = {
	{"�@�@�@�@�@"},
	{"�@�i�@�@�@"},
	{"�@�@�@�@�@"},
	{"�@�@�@�@�@"},
	{"�@�@�i�@�@"},
	{"�@�i�i�i�@"},
	{"�i�i�i�i�i"},
	{"�i�f�f�f�i"},
	{"�i�f�f�f�i"},
	{"�@�f�f�f�@"},
};

string png3[10] = {
	{"�@�@�@�@�@"},
	{"�@�@�@�i�@"},
	{"�@�@�i�i�@"},
	{"�@�@�i�@�@"},
	{"�@�i�@�@�@"},
	{"�i�i�i�@�@"},
	{"�i�i�i�i�@"},
	{"�i�i�f�i�i"},
	{"�i�f�f�f�i"},
	{"�@�f�f�f�@"},
};

string png4[10] = {
	{"�@�@�@�i�@"},
	{"�@�@�@�@�@"},
	{"�@�@�@�@�@"},
	{"�@�@�@�@�@"},
	{"�@�i�i�@�@"},
	{"�i�i�i�i�@"},
	{"�i�i�i�i�i"},
	{"�i�i�f�f�i"},
	{"�i�f�f�f�i"},
	{"�@�f�f�f�@"},
};

#ifdef _GAME_MENU_
const string gameMenuOption[7] = {
		"���ססססססססססססססס�",
		"���@�@�@�@�@���~��C���@�@�@�@�@��",
		"���ססססססססססססססס�",
		"���@�@�@�@�@�@�x�s�ѽL�@�@�@�@�@��",
		"���ססססססססססססססס�",
		"���@�@�@�@�@�@��^�D���@�@�@�@��",
		"���ססססססססססססססס�"
};
#endif // _GAME_MENU_

int chess[8][8];
int lastChess[8][8];
int lastlastChess[8][8];

namespace {
	int numberBlack = 0, numberWhite = 0;
	// Intent:���/���� console ����(��)�� cursor
	// Pre:�ǤJbool�Atrue->��� / false->����
	// Post:�L
	void cursorVisiable(bool flag) {
		GetConsoleCursorInfo(handle, &cci);
		cci.bVisible = flag;
		SetConsoleCursorInfo(handle, &cci);
	}
	// Intent:�]�mconsole��(��)��cursor ��m
	// Pre:int [x]�B[y]�A���W����(0,0)			/// (42,2)���ѽL���i���ʪ��̥��W��
	// Post:�L
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
					cout << "�@";
				else if (chess[i/2][j/2] == 1)
					cout << "��";
				else if (chess[i/2][j/2] == 2)
					cout << "��";
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
		cout << "�� �G " << numberBlack << "�@";
		setConsoleCursorCoordinate(44, 4);
		cout << "�� �G " << numberWhite << "�@";
		
	}

	void printItem() {
		setConsoleCursorCoordinate(55, 2);
		cout << "�� �G UNDO";
		setConsoleCursorCoordinate(55, 4);
		cout << "�� �G REDO";
		setConsoleCursorCoordinate(44, 6);
		cout << "R�GRestart�@ESC�G�^�D���";
	}

	// ���yes no��ܮ�
	bool showDialog(string msg, bool showOption = true) {
		setConsoleCursorCoordinate(42, 6);
		cout << "���ססססססססססססססס�";
		for (int i = 1; i <= 11; i++) {
			setConsoleCursorCoordinate(42, 6 + i);
			cout << "���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@��";
			if (i == 3) {
				setConsoleCursorCoordinate(46, 6 + i);
				cout << msg;
			}
			else if (i == 8 && showOption) {
				setConsoleCursorCoordinate(60, 6 + i);
				cout << "�O";
				setConsoleCursorCoordinate(68, 6 + i);
				cout << "�_";
			}
		}
		setConsoleCursorCoordinate(42, 17);
		cout << "���ססססססססססססססס�";

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
	// =====================��l��console�����=====================
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	cursorPosition.X = 0;	cursorPosition.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
	// =====================��l��console�����=====================
}

Game::~Game()
{
	
}

void Game::showMenu() {

	// ���gameMenu
	for (int i = 0; i < (sizeof(gameMenuOption) / sizeof(gameMenuOption[0])); i++) {
		setConsoleCursorCoordinate(42, 5 + i);
		cout << gameMenuOption[i];
	}
	// �ŧigameMenu �M��console�y�� int [y]
	int commandPress, y = 6;
	// �]�wconsole�y�Ц�m�A�q(54,6)�}�lø�s
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
				//�x�s�C��
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
		cout << "�@\b\b";
		setConsoleCursorCoordinate(54, y);
		cout << "��\b\b";
	}
}


void Game::gameStart() 
{
	// �M��console
	system("cls");
	// �]�m�����j�p
	SMALL_RECT windowSize = { 0,0,80, 20 };
	SetConsoleWindowInfo(handle, TRUE, &windowSize);

	PlaySound("Sounds/Produce.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	// ø�s�C���e��
	for (int i = 0; i < 19; i++) {
		cout << Board[i] << endl;
	}
	printItem();
	setConsoleCursorCoordinate(44, 8);
	cout << "�ѽL���J��...";
	printFireAnimation();
	//�ѽL��l��
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			chess[i][j] = 0;
		}
	}
	chess[3][3] = 1; chess[4][4] = 1;
	chess[3][4] = 2; chess[4][3] = 2;
	printBoard();
	printStatus();

	// ��ܴ���
	this->showHint();
	this->showWhoTurn();


	// �N�e�����W�ԡA�Y���N���Ц�my����0���ܡAconsole�e���N�|���U�@�I
	setConsoleCursorCoordinate(0, 0);

	// ��ܥ���(Cursor)
	cursorVisiable(true);

	int commandPress,x = 4, y = 2;
	// �]�wconsole�y�Ц�m�A�q(4,2)�}�lø�s
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
			mciSendString("play \"Sounds/�U���n.mp3\" ", NULL, 0, 0);
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
				if (numberBlack > numberWhite)showDialog("�¦�Ĺ�F�I", false);
				else if (numberWhite > numberBlack)showDialog("�զ�Ĺ�F�I", false);
				else showDialog("����@�@", false);
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
	// �M��console
	system("cls");
	// �]�m�����j�p
	SMALL_RECT windowSize = { 0,0,80, 20 };
	SetConsoleWindowInfo(handle, TRUE, &windowSize);

	PlaySound("Sounds/Produce.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	// ø�s�C���e��
	for (int i = 0; i < 19; i++) {
		cout << Board[i] << endl;
	}

	setConsoleCursorCoordinate(44, 6);
	cout << "R�GRestart�@ESC�G�^�D���";

	//�ѽL��l��
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			chess[i][j] = 0;
		}
	}
	chess[3][3] = 1; chess[4][4] = 1;
	chess[3][4] = 2; chess[4][3] = 2;
	printBoard();
	printStatus();

	// ��ܴ���
	this->showHint();


	// �N�e�����W�ԡA�Y���N���Ц�my����0���ܡAconsole�e���N�|���U�@�I
	setConsoleCursorCoordinate(0, 0);

	// ��ܥ���(Cursor)
	cursorVisiable(true);

	int commandPress, x = 4, y = 2;
	// �]�wconsole�y�Ц�m�A�q(4,2)�}�lø�s
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
			mciSendString("play \"Sounds/�U���n.mp3\" ", NULL, 0, 0);
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
			cout << "�q�����b��Ҥ�...";
			printFireAnimation();
			mciSendString("play \"Sounds/�U���n.mp3\" ", NULL, 0, 0);
			int a = computerThinking();
			chess[a % 10][a / 10] = 1;
			process( a / 10, a % 10);
			setConsoleCursorCoordinate(44, 8);
			cout << "�@�@�@�@�@�@�@�@�@";
			printBoard();
			printStatus();
			if (isEnd()) {
				if (numberBlack > numberWhite)showDialog("�¦�Ĺ�F�I", false);
				else if (numberWhite > numberBlack)showDialog("�զ�Ĺ�F�I", false);
				else showDialog("����@�@", false);
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
			if (zero == 1) return 10 * j + i; //����Ĥ@�ӥi�H����l
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
	//search �k�W
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
	//search ���U
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
	//search ���W
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
	//search �k�U
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
	//search �k�W
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
	//search ���U
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
	//search ���W
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
	//search �k�U
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
				cout << "�E";
			}
		}
	}
}

void Game::showList()
{
	setConsoleCursorCoordinate(0, 0);
	cout<<"���ססססססססססססססס�\n";
	cout<<"���@�@�@�@���@��ܢҢݡ@�@�@�@�@��\n";
	cout<<"���ססססססססססססססס�\n";
	cout<<"���@�@�@�@�@�@�@���ޡ@�@�@�@�@�@��\n";
	cout<<"���ססססססססססססססס�\n";
	cout<<"���@�@�@�@�@�@�����{���@�@�@�@�@��\n";
	cout<<"���ססססססססססססססס�"  ;
	// �]�w��l���Ц�m
	int commandPress = 0, y = 1;
	setConsoleCursorCoordinate(14, 1);

	// ���å���
	cursorVisiable(false);

	// ���б���
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
				showDialog("�ĤG��", false);
			}
			else if (y == 5) {
				exit(1);
			}
		}

		if (y < 1)	y = 5;
		if (y > 5)	y = 1;

		/*cout << "\b\b�@";
		cursorPosition.Y = y;
		SetConsoleCursorPosition(handle, cursorPosition);
		cout << "\b\b��";*/
	}
}

void Game::showWhoTurn()
{
	if (nowTurn == 0) {
		setConsoleCursorCoordinate(44,8);
		cout << "�{�b���� �¦� �U�ѡC";
	}
	else {
		setConsoleCursorCoordinate(44,8);
		cout << "�{�b���� �զ� �U�ѡC";
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
	//�ѽL��l��
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

	// ��ܴ���
	this->showHint();
}
