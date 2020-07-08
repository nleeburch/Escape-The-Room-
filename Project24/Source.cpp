#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

/*
5 rooms, a bunch of obstacles
when you get to the end of the room, you progress to the next one with a congratulations screen
if you get hit, you get a loser screen cuz youz a loza
obstacles are horizontal, vertical, and diagonal lasers, walls, spikes

I need some determination of where in the game someone is.
Title Screen: Start Game
Room 1,2,3,4,5,6
Game Over Screen
Win Screen
*/

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	// set the cursor visibility
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}

//gotoxy function, very helpful
void gotoxy(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord
	);
}

//gives things color
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//for arrays, probably very inefficient and memory demanding but helpful for what I know
const int M = 200;
//prototypes
int Menu(int x, int y);
int Room1();
int Room2();
int Room3();
int Room4();
void Shot(double s[M][M], int y, double r[M][M]);
void DeterminePlayerShot(double p[M], double s[M][M], int input);
void MovePlayerShot(double s[M][M], double r[M][M]);
void Movement(double p[M], int input, double r[M][M]);
void BuildTheWall(double w[M][M], int y, double r[M][M]);
void Build(double r[M][M], int y, int x);
void BuildAlpha(char a[M][M], double axy[M], int ay, int ax);
void AlphaMovement(double axy[M], double r[M][M]);
void AlphaCollision(double s[M][M], double axy[M], char A[M][M]);
int Collision(double p[M], int y, double s[M][M]);
int Lose();
int Win();
void WinGame();
void InputAcquisition(int input[2]);
class shot;

int main()
{
	ShowConsoleCursor(false);

	while (true)
	{
		int levelChoice = Menu(5, 3);
		switch (levelChoice)
		{
		case 1:
		{
			if (!Room1()) {
				continue;
			}
		}
		case 2:
		{
			if (!Room2()) {
				continue;
			}
		}
		case 3:
		{
			if (!Room3()) {
				continue;
			}
		}
		case 4:
		{
			if (!Room4()) {
				continue;
			}
		}
		case 5:
		{
			WinGame();
			continue;
		}
		default:
		{
			system("cls");
			cout << "nope try again please 1-4";
			cin.ignore();
			continue;
		}
		}
	}
}

int Menu(int x, int y)
{
	double menu[M][M] =
	{	  // 0         5        10        15        16      20        25
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}		// y=20
	};

	int a;
	gotoxy(0, 0);
	Build(menu, 21, 51);
	cin.ignore();
	gotoxy(x, y);
	cout << "W E L C O M E   T O   M I N E C R A F T " << endl;
	gotoxy(x, y + 1);
	cout << "           L E T ' S   P L A Y          " << endl;
	gotoxy(x, y + 2);
	cout << "            (use full screen)           ";
	gotoxy(x, y + 7);
	cout << "1. START THE GAME ALREADY!" << endl;
	gotoxy(x, y + 8);
	cout << "2. Start in Room 2 (cheater)" << endl;
	gotoxy(x, y + 9);
	cout << "3. Start in Room 3" << endl;
	gotoxy(x, y + 10);
	cout << "4. Start in Room 4" << endl;
	gotoxy(x, y + 12);
	cout << "So... whatchu wanna do?\t";
	cin >> a;
	Sleep(200);
	system("cls");
	gotoxy(20, 10);
	cout << "COUNTDOWN!";
	Sleep(1000);
	system("cls");
	gotoxy(20, 10);
	cout << "3!";
	Sleep(1000);
	system("cls");
	gotoxy(20, 10);
	cout << "2!";
	Sleep(1000);
	system("cls");
	gotoxy(20, 10);
	cout << "1!";
	Sleep(1000);
	system("cls");
	return a;
}

int Room1()
{
	double room1[M][M] =
	{//	 0 1       5        10        15        20        25        30
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};
	//position
	double player[M] = { 5,19 };
	//c determines collision/death
	int	c = 1, input[2] = { 0,0 };
	//L,R are shot positions, I could include these attributes in classes but they are specific to the rooms
	double	L = 2, R = 28,
		//shots and their attributes, { x, y, dx, dy, c }
		Shots[M][M] =
	{
	{ L,5,1.7,0,0 },
	{ R,9,-1.1,0,0 },
	{ L,13,.8,0,0 },
	{ R,17,-.5,0,0 }
	};
	//Build Room1
	//build room function
	Build(room1, 21, 31);

	//Play Room1
	while (c == 1)
	{
		//this single function runs all of the shots
		Shot(Shots, 4, room1);
		//slows things down to human speed
		Sleep(51);
		//player input
		if (_kbhit())
		{
			//input acquisition and organization
			InputAcquisition(input);
			//validates the character as up, down, left, right with 224
			if (input[0] == 224)
				//Movement function takes input and moves the player according to it
				Movement(player, input[1], room1);
		}
		//gotoxy and render Player Icon
		gotoxy(player[0], player[1]);
		_putch('D');
		//collision with shot function
		c = Collision(player, 4, Shots);
		//if collision happens
		if (c == 0)
			//you lose!
			return c;
		//if you reach the "win" line
		else if (room1[int(player[1]) - 1][int(player[0])] == 2)
			//you win! move to the next stage
		{
			Win(); return 1;
		}
	}
}

int Room2()
{
	//Room 2
	double room2[M][M] =
	{	//     3                          17
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,2,2,2,1,1,1,1,1,1,1,1,1},
		{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},	// y=4, h1, h2
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},	// y=5,	d1, d2
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},	// y=8, d3, d4
		{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},	// y=9, h3, h4
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},	// y=10, d5, d6
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},	// y=18 d7, d8
		{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},	// y=19, h5, h6
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},	// y=20, d9, d10
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},	// y=29, d11, d12
		{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},	// y=30, h7, h8
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},	// y=31, d13, d14
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},	// y=39, d15, d16
		{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},	// y=40, h9, h10
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};
	//Initialize Room 2
	int c = 1, input[2] = { 0,0 };
	double player[M] = { 10,41 }, L = 3, R = 17,
		Shots[M][M] =
	{
		//Horizontal shots 1-10	{ x, y, dx, dy, c } c is a counter of "time"/number of iterations, implied as 0 when unassigned
		{ L,4,1.1,0  },
		{ R,4,-0.9,0 },
		{ L,9,1.4,0 },
		{ R,9,-1.2,0 },
		{ L,19,1.1,0 },
		{ R,19,-1.1,0 },
		{ L,30,1.4,0 },
		{ R,30,-0.8,0 },
		{ L,40,1.4,0  },
		{ R,40,-1.3,0 },

		//diagonal shots 1-16
		{ L,5,1,-1 },
		{ R,5,-1,-1 },
		{ L,8,1.6,1 },
		{ R,8,-1,1.6 },
		{ L,10,1.2,-1 },
		{ R,10,-1,-1.2 },
		{ L,18,1.4,1 },
		{ R,18,-1,1.4 },
		{ L,20,1.4,-1 },
		{ R,20,-1,-1.4 },
		{ L,29,1.2,1 },
		{ R,29,-1,1.2 },
		{ L,31,1.6,-1},
		{ R,31,-1,-1.6 },
		{ L,39,1,1 },
		{ R,39,-1,1 }
	};
	//Build Room 2
	Build(room2, 43, 21);
	//Play Room 2
	while (c == 1)
	{
		//this single function runs all of the shots
		Shot(Shots, 26, room2);
		//slows things down to human speed
		Sleep(51);
		//player input
		if (_kbhit())
		{
			//input acquisition and organization
			InputAcquisition(input);
			//validates the character as up, down, left, right with 224
			if (input[0] == 224)
				//Movement function takes input and moves the player according to it
				Movement(player, input[1], room2);
		}
		//gotoxy and render Player Icon
		gotoxy(player[0], player[1]);
		_putch('D');
		//collision with shot function
		c = Collision(player, 26, Shots);
		//if collision happens
		if (c == 0) {
			//you lose!
			return c;
		}
		//if you reach the "win" line
		else if (room2[int(player[1]) - 1][int(player[0])] == 2) {
			//you win! move to the next stage
			Win(); return 1;
		}
	}
}

int Room3()
{
	double room3[M][M] =
	{//  0 1       5        10        15        20        25        30        35        40
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,1},
		{0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,0,1,1,1,1,0,1},
		{0,1,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1},
		{0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1},
		{0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1},	// y=5
		{0,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,0,1},
		{0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
		{0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1},
		{0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,1},
		{0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,0,1,0,1,0,1,0,1},	// y=10
		{0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,0,1,0,0,0,1},
		{0,1,0,1,0,1,0,0,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1},
		{0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,1,0,1,0,1},
		{0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1},
		{0,1,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1},	// y=15
		{0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,0,1},
		{0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1},
		{0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1},
		{0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,1,1,1},
		{0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1},	// y=20
		{0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
		{0,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,0,1,0,1},
		{0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}	// y=24
	};
	char k;
	int c = 1, input[2] = { 0,0 };
	//closing wall
	double player[M] = { 2, 13 }, wall[M][M] = { 0,0 };
	Build(room3, 25, 42);
	while (c == 1)
	{
		//slows things down to human speed
		Sleep(17);
		//player input
		if (_kbhit())
		{
			//input acquisition and organization
			InputAcquisition(input);
			//validates the character as up, down, left, right with 224
			if (input[0] == 224) {
				//Movement function takes input and moves the player according to it
				Movement(player, input[1], room3);
			}
		}
		//gotoxy and render Player Icon
		gotoxy(player[0], player[1]);
		_putch('D');
		//builds the closing wall
		BuildTheWall(wall, 24, room3);
		//collision with wall function
		c = Collision(player, 1, wall);
		//if collision happens
		if (c == 0) {
			//you lose!
			return c;
		}
		//if you reach the "win" line
		if (room3[int(player[1]) - 1][int(player[0])] == 2) {
			//you win! move to the next stage
			Win(); return 1;
		}
	}
}

int Room4()
{
	double room4[M][M] =
	{//  0         5        10        15        20          26		30
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},	// y=0
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},	// y=5
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},	// y=10
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}	// y=15
	};
	char Alpha[M][M] =
	{
			{'A','B','C','D','E','F'},
			{'G','H','I','J','K','L'},
			{'M','N','O','P','Q','R'},
			{'S','T','U','V','W','X'},
			{'Y','&','Z','!','?','.'}
	};
	char Empty[M][M] = {};
	//INITIALIZATION
	int c = 1, a = 0, input[2] = { 0,0 }, counter = 0;
	//		x  y  dx dy  c
	//Alphaxy[6] = 30
	double	Alphaxy[M] = { 18,10,-.5,.5,0,0,30 },
		Emptyxy[M] = { 0,0 },
		player[M] = { 2,13,1,1,0 },
		//player ammo
		playershot[M][M] =
	{
		{ 0,0,1,1,0 },
		{ 0,0,1,1,0 },
		{ 0,0,1,1,0 },
		{ 0,0,1,1,0 },
		{ 0,0,1,1,0 },
		{ 0,0,1,1,0 },
		{ 0,0,1,1,0 },
		{ 0,0,1,1,0 },
		{ 0,0,1,1,0 },
		{ 0,0,1,1,0 }
	};
	//BUILD ROOM 4 LOOP
	Build(room4, 16, 31);
	//PLAY ROOM 4 LOOP
	while (c == 1)
	{
		//framerates
		Sleep(51);
		//build initial alpha
		BuildAlpha(Alpha, Alphaxy, 5, 4);
		//allocate erase position
		Emptyxy[0] = Alphaxy[0], Emptyxy[1] = Alphaxy[1];
		//specifically slows down movement of Alpha to a count of 2
		if (counter == 0)
		{
			//moves alpha coordinates
			AlphaMovement(Alphaxy, room4);
			//builds empty alpha or erases alpha before building it over it
			BuildAlpha(Empty, Emptyxy, 5, 4);
		}
		//manage speed of Alphabet with external counter
		counter++;
		if (counter == 2)
			counter = 0;

		//player input
		if (_kbhit())
		{
			//input acquisition and organization
			InputAcquisition(input);
			//validates the character as up, down, left, right with 224
			if (input[0] == 224) {
				Movement(player, input[1], room4);
			}
			//if its none of those then it must be w, a, s, or d
			else if (input[0] != 224) {
				//Obvious function name is obvious
				DeterminePlayerShot(player, playershot, input[0]);
			}
		}
		//moves all the existing shots
		MovePlayerShot(playershot, room4);
		//go to xy
		gotoxy(player[0], player[1]);
		//Put 'D' at xy
		_putch('D');
		//reset input values
		input[0] = 0, input[1] = 0;
		//alpha collision function
		AlphaCollision(playershot, Alphaxy, Alpha);
		if ((player[1] >= Alphaxy[1]) && (player[1] <= (Alphaxy[1]) + 3) && (player[0] >= Alphaxy[0]) && (player[0] <= (Alphaxy[0]) + 4)) {
			Lose(); return 0;
		}
		if (Alphaxy[6] < 1) {
			Win(); return 1;
		}
	}
}

void Shot(double s[M][M], int y, double r[M][M])	//shots array, number of shots, room array
{
	/*
			   0,1
		-1,1\	|	/1,1
		-1,0<		>1,0
		-1,-1/	|	\1,-1
			   0,-1
		  {x,y,dx,dy,c} c is a counter of "time"/number of iterations
	*/
	//absolutely beautiful
	for (int i = 0; i < y; i++)						//move through the number of shots
	{
		//if the next position of the shot is 1 or 2
		if ((r[int(s[i][1]) - int(s[i][3])][int(s[i][0]) + int(s[i][2])] == 1)
			|| (r[int(s[i][1] - s[i][3])][int(s[i][0] + s[i][2])] == 1)
			|| (r[int(s[i][1]) - int(s[i][3])][int(s[i][0]) + int(s[i][2])] == 2)
			|| (r[int(s[i][1] - s[i][3])][int(s[i][0] + s[i][2])] == 2)) {
			//go to the current position of the shot
			gotoxy(s[i][0], s[i][1]);
			//erase the 'sprite'
			cout << " ";
			//reset the x, y, and c values to 0
			s[i][0] -= (s[i][4] * s[i][2]), s[i][1] += (s[i][4] * s[i][3]), s[i][4] = 0;
		}
		//so long as the next position of the shot is not 1
		else {
			//go to the current position of the shot
			gotoxy(s[i][0], s[i][1]);
			//display a space
			cout << " ";
			//move the shot diagonally to the left and up, increment c
			s[i][0] += s[i][2], s[i][1] -= s[i][3], s[i][4]++;
		}
		//go to the current position of the shot
		gotoxy(s[i][0], s[i][1]);
		//determination of the sprite based on direction of velocity
		if (s[i][2] * s[i][3] > 0) {
			cout << "/";
		}
		else if (s[i][2] * s[i][3] < 0) {
			cout << "\\";
		}
		else if (s[i][2] * s[i][3] == 0 && s[i][2] > 0) {
			cout << ">";
		}
		else if (s[i][2] * s[i][3] == 0 && s[i][2] < 0) {
			cout << "<";
		}
		else if (s[i][2] == 0) {
			cout << "|";
		}
	}
}

void BuildTheWall(double w[M][M], int y, double r[M][M])
{
	//so long as the next position of the wall is not 3, which will always be true, probably unnecessary
	if (r[int(w[0][1]) + 1][int(w[0][0])] != 3 && r[int(w[0][1])][int(w[0][0]) + 1] != 3)
	{
		//go to the current coordinate of the wall
		gotoxy(w[0][0], w[0][1]);
		//display wall
		cout << "|";
		//move its y position down by 1
		w[0][1]++;
		//once the wall hits the bottom of the room, or a certain amount y
		if (w[0][1] == y)
		{
			//go to the current coordinate of the wall
			gotoxy(w[0][0], w[0][1]);
			//display wall
			cout << "|";
			//reset y value to 0 and increase x value to the right by 1
			w[0][1] = 0, w[0][0]++;
		}
	}
}

//player coordinates, player shots, input
void DeterminePlayerShot(double p[M], double s[M][M], int input)
{
	int i = 0;
	//{x, y, dx, dy, exist?}

	//loop through all shots
	for (i; i < 10; i++)
	{
		//if the shot does not exist yet
		if (s[i][4] == 0) {
			//take the next input
			//if input is w
			if (input == 119) {
				//then dx = 0
				s[i][2] = 0;
				//set the shot's starting coordinates to the player's current coordinates
				s[i][0] = p[0], s[i][1] = p[1];
				//validate shot's existence
				s[i][4] = 1;
				break;
			}
			//if input is a
			else if (input == 97) {
				//then flip dx and dy = 0
				s[i][2] = -s[i][2], s[i][3] = 0;
				//set the shot's starting coordinates to the player's current coordinates
				s[i][0] = p[0], s[i][1] = p[1];
				//validate shot's existence
				s[i][4] = 1;
				break;
			}
			//if input is s, i bet these need more to the conditions
			else if (input == 115) {
				//then dx = 0 and flip dy
				s[i][2] = 0, s[i][3] = -s[i][3];
				//set the shot's starting coordinates to the player's current coordinates
				s[i][0] = p[0], s[i][1] = p[1];
				//validate shot's existence
				s[i][4] = 1;
				break;
			}
			//if input is d
			else if (input == 100 || input == 13) {
				//then dy = 0
				s[i][3] = 0;
				//set the shot's starting coordinates to the player's current coordinates
				s[i][0] = p[0], s[i][1] = p[1];
				//validate shot's existence
				s[i][4] = 1;
				break;
			}
		}
		if (i == 10)
			input = 0;
	}
}

//player shot array, room array
void MovePlayerShot(double s[M][M], double r[M][M])
{
	//loop through all 10 shots
	for (int i = 0; i < 10; i++)
	{
		//if this shot exists
		//then move it
		if (s[i][4] == 1) {
			//if the next position of the shot is 1 or 2
			if ((r[int(s[i][1]) - int(s[i][3])][int(s[i][0]) + int(s[i][2])] == 1)
				|| (r[int(s[i][1] - s[i][3])][int(s[i][0] + s[i][2])] == 1)
				|| (r[int(s[i][1]) - int(s[i][3])][int(s[i][0]) + int(s[i][2])] == 2)
				|| (r[int(s[i][1] - s[i][3])][int(s[i][0] + s[i][2])] == 2)) {
				//go to the current position of the shot
				gotoxy(s[i][0], s[i][1]);
				//display a space
				cout << " ";
				//reset the dx and dy values 
				s[i][3] = 1, s[i][2] = 1;
				//extinguish shot's existence
				s[i][4] = 0;
			}
			//so long as the next position of the shot is not 1 or 2
			else {
				//go to the current position of the shot
				gotoxy(s[i][0], s[i][1]);
				//display a space
				cout << " ";
				//move the shot by dx and -dy
				s[i][0] += s[i][2], s[i][1] -= s[i][3];
			}
			//go to the current position of the shot
			gotoxy(s[i][0], s[i][1]);
			//determination of sprite based on direction vector
			if (s[i][2] * s[i][3] == 0 && s[i][2] > 0) {
				cout << ">";
			}
			else if (s[i][2] * s[i][3] == 0 && s[i][2] < 0) {
				cout << "<";
			}
			else if (s[i][2] == 0 && s[i][3] > 0) {
				cout << "^";
			}
			else if (s[i][2] == 0 && s[i][3] < 0) {
				cout << "v";
			}
		}
	}
}

//player position, input, room array
void Movement(double p[M], int input, double r[M][M])
{
	//go to current position
	gotoxy(p[0], p[1]);
	//display a space
	cout << " ";
	if (input == 72) {
		if (r[int(p[1]) - 1][int(p[0])] == 0) {
			//moves the character up a row
			p[1]--;
		}
	}
	else if (input == 80) {
		if (r[int(p[1]) + 1][int(p[0])] == 0) {
			//moves the character down a row
			p[1]++;
		}
	}
	else if (input == 77) {
		if (r[int(p[1])][int(p[0]) + 1] == 0) {
			//moves the character right a column
			p[0]++;
		}
	}
	else if (input == 75) {
		if (r[int(p[1])][int(p[0]) - 1] == 0) {
			//moves the character left a column
			p[0]--;
		}
	}
}

//player position, number of colliding objects, shot/wall array
int Collision(double p[M], int y, double s[M][M])
{
	//loop through all colliding objects
	for (int i = 0; i < y; i++)
	{
		//if the player has the same coordinates as the shot/wall
		if ((p[0] == int(s[i][0]) && p[1] == int(s[i][1])
			|| (p[0] == s[i][0]) && p[1] == s[i][1])
			|| (p[0] == int(s[i][0]) && p[1] == s[i][1])
			|| (p[0] == s[i][0]) && p[1] == int(s[i][1])) {
			//call the lose function
			return Lose();
		}
	}
	return 1;
}

//player shot, Alpha positions, Alpha array
void AlphaCollision(double s[M][M], double axy[M], char A[M][M])
{
	int i = 0;
	//loop through number of shots
	for (i; i < 10; i++)
	{
		//if the shot exists first and foremost
		if (s[i][4] == 1)
		{
			//if the shot exists within the box of the array, aka hits the array
			if ((s[i][1] >= axy[1])
				&& (s[i][1] <= (axy[1]) + 3)
				&& (s[i][0] >= axy[0])
				&& (s[i][0] <= (axy[0]) + 4)) {
				//extinguish shot's existence
				s[i][4] = 0;
				//erase the [axy[4]][axy[5]] position of Alpha
				A[int(axy[4])][int(axy[5])] = 0;
				//increment axy[5]to go down rows
				axy[5]++;
				//once you reach the end of the row
				if (axy[5] == 6) {
					//increment axy[4] and reset axy[5]
					axy[4]++, axy[5] = 0;
				}
				//go to the immediate shot
				gotoxy(s[i][0], s[i][1]);
				//clear its space
				_putch(' ');
				axy[6]--;
			}
		}
	}
}

int Win()
{
	Sleep(500);
	gotoxy(5, 25);
	cout << "Noice!";
	Sleep(1000);
	_getch();
	cin.ignore();
	Sleep(500);
	system("cls");
	return 1;
}

int Lose()
{
	double menu[M][M] =
	{ // 0         5        10        15        16      20        25
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}		// y=20
	};

	Sleep(1000);
	system("cls");
	Build(menu, 21, 51);
	gotoxy(10, 10);
	cout << "GAME OVER GET OUT OF HERE" << endl << endl;
	Sleep(2000);
	_getch();
	system("cls");
	Sleep(500);
	return 0;
}

void WinGame()
{
	double menu[M][M] =
	{ // 0         5        10        15        16      20        25
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}		// y=20
	};
	Sleep(1000);
	system("cls");
	Build(menu, 21, 51);
	gotoxy(10, 10);
	cout << "Congratulations you won now get a job" << endl;
	Sleep(2000);
	_getch();
	system("cls");
	Sleep(500);
}

void Build(double r[M][M], int y, int x)
{
	//simple nest for loop to build an array in the right order
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			if (r[i][j] == 1) {
				//rectangle character that outlines the room
				cout << char(219);
			}
			else if (r[i][j] == 0) {
				cout << " ";
			}
			else if (r[i][j] == 2) {
				cout << "-";
			}
		}
		cout << endl;
	}
}

void BuildAlpha(char a[M][M], double axy[M], int ay, int ax)
{
	for (int i = 0; i <= ay; i++)
	{
		for (int j = 0; j <= ax; j++)
		{
			gotoxy(axy[0] + i, axy[1] + j);
			cout << a[j][i];
		}
	}
}

void AlphaMovement(double axy[M], double r[M][M])
{
	/*
	Check if the next position is open
	Move Alpha xy in direction of the vector
	If you hit the top, go down, if you hit the bottom, go up
	If you hit the west wall, go east, if you hit the east wall, go west
	Alphaxy[4] = { 30,10,-.5,.5 }
					y - 1
				x-1	{'A','B','C','D','E','F'},x + 6
					{'G','H','I','J','K','L'},
					{'M','N','O','P','Q','R'},
					{'S','T','U','V','W','X'},
					{'Y','&','Z','!','?','.'}
					y + 5					  x + 6 , y + 5


					|
					|
			Q2		|		Q1
					|
		------------|------------
					|
			Q3		|		Q4
					|
					|
	*/

	//if the direction is in Q1, and if the next position in that direction is 0
	if (axy[2] > 0 && axy[3] > 0 && (r[int(axy[1] - axy[3])][int(axy[0] + axy[2]) + 6] == 0)) {
		//then go ahead and move the matrix in the direction of that vector
		axy[0] += axy[2], axy[1] -= axy[3];
	}
	//if the direction is in Q2, and if the next position in that direction is 0
	else if (axy[2] < 0 && axy[3] > 0 && (r[int(axy[1] - axy[3])][int(axy[0] + axy[2]) - 1] == 0)) {
		//then go ahead and move the matrix in the direction of that vector				
		axy[0] += axy[2], axy[1] -= axy[3];
	}
	//if the direction is in Q3, and if the next position in that direction is 0											
	else if (axy[2] < 0 && axy[3] < 0 && (r[int(axy[1] - axy[3]) + 4][int(axy[0] + axy[2]) - 1] == 0)) {
		//then go ahead and move the matrix in the direction of that vector
		axy[0] += axy[2], axy[1] -= axy[3];
	}
	//if the direction is in Q4, and if the next position in that direction is 0
	else if (axy[2] > 0 && axy[3] < 0 && (r[int(axy[1] - axy[3]) + 4][int(axy[0] + axy[2]) + 6] == 0)) {
		//then go ahead and move the matrix in the direction of that vector
		axy[0] += axy[2], axy[1] -= axy[3];
	}
	//as long as the next position in the direction of the vector is not 0
	else {
		//If Q1, (1,1)
		if (axy[2] > 0 && axy[3] > 0) {
			//if the position above is 1
			if (r[int(axy[1] - axy[3])][int(axy[0])] != 0) {
				//then change the sign of the y component
				axy[3] = -axy[3];
			}
			//if the position to the right is 1
			else if (r[int(axy[1])][int(axy[0] + axy[2]) + 6] != 0) {
				//then change the sign of the x component
				axy[2] = -axy[2];
			}
		}
		//If Q2, (-1,1)
		else if (axy[2] < 0 && axy[3] > 0) {
			//if the position above is 1
			if (r[int(axy[1] - axy[3])][int(axy[0])] != 0) {
				//then change the sign of the y component
				axy[3] = -axy[3];
			}
			//if the position to the left is 1
			else if (r[int(axy[1])][int(axy[0] + axy[2]) - 1] != 0) {
				//then change the sign of the x component
				axy[2] = -axy[2];
			}
		}
		//If Q3, (-1,-1)
		else if (axy[2] < 0 && axy[3] < 0) {
			//if the position below is 1
			if (r[int(axy[1] - axy[3]) + 4][int(axy[0])] != 0) {
				//then change the sign of the y component
				axy[3] = -axy[3];
			}
			//if the position to the left is 1
			else if (r[int(axy[1])][int(axy[0] + axy[2]) - 1] != 0) {
				//then change the sign of the x component
				axy[2] = -axy[2];
			}
		}
		//If Q4, (1,-1)
		else if (axy[2] > 0 && axy[3] < 0) {
			//if the position below is 1
			if (r[int(axy[1] - axy[3]) + 4][int(axy[0])] != 0) {
				//then change the sign of the y component
				axy[3] = -axy[3];
			}
			//if the position to the right is 1
			else if (r[int(axy[1])][int(axy[0] + axy[2]) + 6] != 0) {
				//then change the sign of the x component
				axy[2] = -axy[2];
			}
		}
		//circular motion
	}
}

void InputAcquisition(int input[2])
{
	input[0] = _getch();
	//if a movement key (up, down, left, right) is pressed, then grab the 2nd input
	if (input[0] == 224)
		input[1] = _getch();
	//otherwise, ignore the second input
	else
		input[1] = 0;
}

//ignore, this is for Nick later
/*
int Room5()
{
	//pacman
	double room5[M][M] =
	{//	 0         5        10        15        20        25
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},	//y=3
		{1,3,3,3,3,3,3,3,3,3,3,3,3,1,1,3,3,3,3,3,3,3,3,3,3,3,3,1},
		{1,3,1,1,1,1,3,1,1,1,1,1,3,1,1,3,1,1,1,1,1,3,1,1,1,1,3,1},	//y=5
		{1,3,1,1,1,1,3,1,1,1,1,1,3,1,1,3,1,1,1,1,1,3,1,1,1,1,3,1},
		{1,3,1,1,1,1,3,1,1,1,1,1,3,1,1,3,1,1,1,1,1,3,1,1,1,1,3,1},
		{1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1},
		{1,3,1,1,1,1,3,1,1,3,1,1,1,1,1,1,1,1,3,1,1,3,1,1,1,1,3,1},
		{1,3,1,1,1,1,3,1,1,3,3,3,3,1,1,3,3,3,3,1,1,3,1,1,1,1,3,1},	//y=10
		{1,3,3,3,3,3,3,1,1,1,1,1,0,1,1,0,1,1,1,1,1,3,3,3,3,3,3,1},
		{1,1,1,1,1,1,3,1,1,1,1,1,0,1,1,0,1,1,1,1,1,3,1,1,1,1,1,1},
		{0,0,0,0,0,1,3,1,1,0,0,0,0,0,0,0,0,0,0,1,1,3,1,0,0,0,0,0},
		{0,0,0,0,0,1,3,1,1,0,1,1,1,0,0,1,1,1,0,1,1,3,1,0,0,0,0,0},
		{1,1,1,1,1,1,3,1,1,0,1,0,0,0,0,0,0,1,0,1,1,3,1,1,1,1,1,1},
		{0,0,0,0,0,0,3,0,0,0,1,0,0,0,0,0,0,1,0,0,0,3,0,0,0,0,0,0},	//y=16
		{1,1,1,1,1,1,3,1,1,0,1,1,1,1,1,1,1,1,0,1,1,3,1,1,1,1,1,1},
		{0,0,0,0,0,1,3,1,1,0,0,0,0,0,0,0,0,0,0,1,1,3,1,0,0,0,0,0},
		{0,0,0,0,0,1,3,1,1,0,1,1,1,1,1,1,1,1,0,1,1,3,1,0,0,0,0,0},
		{1,1,1,1,1,1,3,1,1,0,1,1,1,1,1,1,1,1,0,1,1,3,1,1,1,1,1,1},	//y=20
		{1,3,3,3,3,3,3,3,3,3,3,3,3,1,1,3,3,3,3,3,3,3,3,3,3,3,3,1},
		{1,3,1,1,1,1,3,1,1,1,1,1,3,1,1,3,1,1,1,1,1,3,1,1,1,1,3,1},
		{1,3,1,1,1,1,3,1,1,1,1,1,3,1,1,3,1,1,1,1,1,3,1,1,1,1,3,1},
		{1,3,3,3,1,1,3,3,3,3,3,3,3,0,0,3,3,3,3,3,3,3,1,1,3,3,3,1},
		{1,1,1,3,1,1,3,1,1,3,1,1,1,1,1,1,1,1,3,1,1,3,1,1,3,1,1,1},	//y=25
		{1,1,1,3,1,1,3,1,1,3,1,1,1,1,1,1,1,1,3,1,1,3,1,1,3,1,1,1},
		{1,3,3,3,3,3,3,1,1,3,3,3,3,1,1,3,3,3,3,1,1,3,3,3,3,3,3,1},
		{1,3,1,1,1,1,1,1,1,1,1,1,3,1,1,3,1,1,1,1,1,1,1,1,1,1,3,1},
		{1,3,1,1,1,1,1,1,1,1,1,1,3,1,1,3,1,1,1,1,1,1,1,1,1,1,3,1},
		{1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},	//y=32
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	};
	double player[M] = { 24,14,0 },
		ghosts[M][M] =
	{					//x,y,dx,dy,c
		{21,8,1,1,1},
		{26,8,1,1,1},
		{21,21,1,1,1},
		{21,6,1,1,1},
	};
	int	c = 1, input[2] = { 0,0 };
	//Build Room1
	Build(room5, 28, 34);
	//Play Room5
	while (c == 1)
	{
		Sleep(51);										//These are all fine and working well
		if (_kbhit())
		{
			InputAcquisition(input);
			if (input[0] == 224)										//validates the character as up, down, left, right with 224
				Movement(player, input[1], room5);						//perhaps I need to pass through a line with getline because arrow keys produce two values rather than one (i.e. a line) or I need an input validation function that holds values in an array and checks to see what values to pass through
		}
		gotoxy(player[0], player[1]);
		_putch('D');
		if ()
			return c;
		else if (player[3] == 244)
		{Win(); return 6;}
	}
}*/

//genius code for nick later
/*
void DetermineGhosts(double g[M][M], double r[M][M], double p[M])
{
	//loop through the ghosts in the array that exist
	//if 1, then based on position and relative information around the ghost, pick a direction and set 1 => 2
	//if 0, then count a certain number of function calls until the ghost respawns
	for (int i = 0; i < 4; i++)
	{
		if (g[i][4] == 0)
		{
			g[i][5]++;
			if (g[i][5] == 8)
			{
				g[i][4] = 1;
				g[i][5] = 0;
			}
		}
		if (g[i][4] == 1)
		{
			//if the ratio of y/x is > 1, then move towards the player in the y direction
			//if the ratio of y/x is  < 1, then move towards the player in the x direction
		}
	}
}

//need to build
void MoveGhosts(double g[M][M], double r[M][M])
{
	/*
	loop through ghosts array with existence set to 2
	if the next position of the ghost is open, then move it on into the next position
	if that location is closed, set 2 => 1 so it will run through the determine function

	m = (p(y) - g(y))/((p(x) - g(x)))
	if m > 1
	check the left and right for the next open position
	whichever is the shorter distance, move towards there
	if m < 1
	do the same but up and down instead of left and right
	if m = 1
	perform both functions and compare all four values


	for (int i = 0; i < 4; i++)
	{
		if (g[i][1] == 1)
		{
			if(r[int(g[i][1]) - dy][int(g[i][0]) + dx]


		}
	}


}*/