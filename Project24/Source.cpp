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
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void gotoxy(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord
	);
}	//gotoxy function, very helpful
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	//gives things color
const int M = 200;									//for arrays, probably very inefficient and memory demanding but helpful for what I know
int Menu(int x, int y);								//prototypes
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
void InputAcquisition(int input[2]);				//things get messy quick when you think of insane stuff
class shot;

int main()
{
	ShowConsoleCursor(false);
	int choice, c = 1;

	while (c == 1)
	{
		choice = Menu(5, 3);
		switch (choice)
		{
			case 1:
			{
				choice = Room1();
				if (choice == 0)
					continue;
			}
			case 2:
			{
				choice = Room2();
				if (choice == 0)
					continue;
			}
			case 3:
			{
				choice = Room3();
				if (choice == 0)
					continue;
			}
			case 4:
			{
				choice = Room4();
				if (choice == 0)
					continue;
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
	double player[M] = { 5,19 };	//position
	int	c = 1, input[2] = { 0,0 };	//c determines collision/death
	double	L = 2, R = 28,			//L,R are shot positions, I could include these attributes in classes but they are specific to the rooms
		Shots[M][M] = 
		{
		{ L,5,1.7,0,0 },			//shots and their attributes, { x, y, dx, dy, c }
		{ R,9,-1.1,0,0 },
		{ L,13,.8,0,0 },
		{ R,17,-.5,0,0 }
		};
	//Build Room1
	Build(room1, 21, 31);			//build room function
	//Play Room1
	while (c == 1)
	{
		Shot(Shots, 4, room1);									//this single function runs all of the shots
		Sleep(51);												//slows things down to human speed
		if (_kbhit())											//player input
		{
			InputAcquisition(input);							//input acquisition and organization
			if (input[0] == 224)								//validates the character as up, down, left, right with 224
				Movement(player, input[1], room1);				//Movement function takes input and moves the player according to it
		}
		gotoxy(player[0], player[1]);							//gotoxy and render Player Icon
		_putch('D');
		c = Collision(player, 4, Shots);						//collision with shot function
		if (c == 0)												//if collision happens
			return c;											//you lose!
		else if (room1[int(player[1]) - 1][int(player[0])] == 2)//if you reach the "win" line
		{Win(); return 2;}										//you win! move to the next stage
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
		{ L,4,1.1,0  },		//Horizontal shots 1-10	{ x, y, dx, dy, c } c is a counter of "time"/number of iterations, implied as 0 when unassigned
		{ R,4,-0.9,0 },	
		{ L,9,1.4,0 },		
		{ R,9,-1.2,0 },
		{ L,19,1.1,0 },		
		{ R,19,-1.1,0 },
		{ L,30,1.4,0 },		
		{ R,30,-0.8,0 },
		{ L,40,1.4,0  },	
		{ R,40,-1.3,0 },

		{ L,5,1,-1 },		//diagonal shots 1-16
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
		Shot(Shots, 26, room2);									//this single function runs all of the shots
		Sleep(51);												//slows things down to human speed
		if (_kbhit())											//player input
		{
			InputAcquisition(input);							//input acquisition and organization
			if (input[0] == 224)								//validates the character as up, down, left, right with 224
				Movement(player, input[1], room2);				//Movement function takes input and moves the player according to it
		}
		gotoxy(player[0], player[1]); 							//gotoxy and render Player Icon
		_putch('D');
		c = Collision(player, 26, Shots);						//collision with shot function
		if (c == 0)												//if collision happens
			return c;											//you lose!
		else if (room2[int(player[1]) - 1][int(player[0])] == 2)//if you reach the "win" line
		{Win(); return 3;}										//you win! move to the next stage
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
	double player[M] = { 2, 13 }, wall[M][M] =  {0,0};		//closing wall
	Build(room3, 25, 42);
	while (c == 1)
	{
		Sleep(17);											//slows things down to human speed
		if (_kbhit())										//player input
		{
			InputAcquisition(input);						//input acquisition and organization
			if (input[0] == 224)							//validates the character as up, down, left, right with 224
				Movement(player, input[1], room3);			//Movement function takes input and moves the player according to it
		}
		gotoxy(player[0], player[1]); 						//gotoxy and render Player Icon
		_putch('D');
		BuildTheWall(wall, 24, room3);						//builds the closing wall
		c = Collision(player, 1, wall);						//collision with wall function
		if (c == 0)											//if collision happens
			return c;										//you lose!
		if (room3[int(player[1]) - 1][int(player[0])] == 2) //if you reach the "win" line
		{Win(); return 4;}									//you win! move to the next stage
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
	//could create a struct of this to pair correlate height and width values
	//my god you would have to create so many variables for all the possble objects or hitboxes or whatever 
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
	double	Alphaxy[M] = { 18,10,-.5,.5,0,0,30 },	//Alphaxy[6] = 30
		Emptyxy[M] = { 0,0 },
		player[M] = { 2,13,1,1,0 },
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
	};						//player ammo
	//BUILD ROOM 4 LOOP
	Build(room4, 16, 31);
	//PLAY ROOM 4 LOOP
	while (c == 1)
	{
		Sleep(51);													//framerates
		BuildAlpha(Alpha, Alphaxy, 5, 4);							//build initial alpha
		Emptyxy[0] = Alphaxy[0], Emptyxy[1] = Alphaxy[1];			//allocate erase position
		if (counter == 0)											//specifically slows down movement of Alpha to a count of 2
		{	
			AlphaMovement(Alphaxy, room4);							//moves alpha coordinates
			BuildAlpha(Empty, Emptyxy, 5, 4);						//builds empty alpha or erases alpha before building it over it
		}
		counter++;													//manage speed of Alphabet with external counter
		if (counter == 2)												
			counter = 0;
		
		if (_kbhit())												//player input
		{
			InputAcquisition(input);								//input acquisition and organization								
			if (input[0] == 224)									//validates the character as up, down, left, right with 224
				Movement(player, input[1], room4);						
			else if (input[0] != 224)								//if its none of those then it must be w, a, s, or d
				DeterminePlayerShot(player, playershot, input[0]);	//Obvious function name is obvious
		}
		MovePlayerShot(playershot, room4);							//moves all the existing shots, maybe I should put alpha collision in there so they don't check at different times
		gotoxy(player[0], player[1]);								//go to xy
		_putch('D');												//Put 'D' at xy
		input[0] = 0, input[1] = 0;									//reset input values
		AlphaCollision(playershot, Alphaxy, Alpha);					//alpha collision function
		if ((player[1] >= Alphaxy[1]) && (player[1] <= (Alphaxy[1]) + 3 ) && (player[0] >= Alphaxy[0]) && (player[0] <= (Alphaxy[0]) + 4))
			{Lose(); return 0;}
		if (Alphaxy[6] < 1)
			{Win(); return 5;}
	}
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
		if ((r[int(s[i][1]) - int(s[i][3])][int(s[i][0]) + int(s[i][2])] == 1)
			|| (r[int(s[i][1] - s[i][3])][int(s[i][0] + s[i][2])] == 1)
			|| (r[int(s[i][1]) - int(s[i][3])][int(s[i][0]) + int(s[i][2])] == 2)
			|| (r[int(s[i][1] - s[i][3])][int(s[i][0] + s[i][2])] == 2)) {					//if the next position of the shot is 1 or 2
			gotoxy(s[i][0], s[i][1]);														//go to the current position of the shot
			cout << " ";																	//erase the 'sprite'
			s[i][0] -= (s[i][4] * s[i][2]), s[i][1] += (s[i][4] * s[i][3]), s[i][4] = 0;	//reset the x, y, and c values to 0
			}
		else {																				//so long as the next position of the shot is not 1
			gotoxy(s[i][0], s[i][1]);														//go to the current position of the shot
			cout << " ";																	//display a space
			s[i][0] += s[i][2], s[i][1] -= s[i][3], s[i][4]++;								//move the shot diagonally to the left and up, increment c
			}
		gotoxy(s[i][0], s[i][1]);															//go to the current position of the shot
		if (s[i][2] * s[i][3] > 0)															//determination of the sprite based on direction of velocity
			cout << "/";
		else if (s[i][2] * s[i][3] < 0)
			cout << "\\";
		else if (s[i][2] * s[i][3] == 0 && s[i][2] > 0)
			cout << ">";
		else if (s[i][2] * s[i][3] == 0 && s[i][2] < 0)
			cout << "<";
		else if (s[i][2] == 0)
			cout << "|";
	}
}

void BuildTheWall(double w[M][M], int y, double r[M][M])
{
	if (r[int(w[0][1]) + 1][int(w[0][0])] != 3 && r[int(w[0][1])][int(w[0][0]) + 1] != 3)	//so long as the next position of the wall is not 3, which will always be true, probably unnecessary
	{
		gotoxy(w[0][0], w[0][1]);		//go to the current coordinate of the wall
		cout << "|";					//display wall
		w[0][1]++;						//move its y position down by 1
		if (w[0][1] == y)				//once the wall hits the bottom of the room, or a certain amount y
		{
			gotoxy(w[0][0], w[0][1]);	//go to the current coordinate of the wall
			cout << "|";				//display wall
			w[0][1] = 0, w[0][0]++;		//reset y value to 0 and increase x value to the right by 1
		}
	}
}

void DeterminePlayerShot(double p[M], double s[M][M], int input)//player coordinates, player shots, input
{
	int i = 0;
														//{x, y, dx, dy, exist?}
	for (i; i < 10; i++)								//loop through all shots
	{
		if (s[i][4] == 0)								//if the shot does not exist yet
		{												//take the next input
			if (input == 119)							//if input is w
			{
				s[i][2] = 0;							//then dx = 0
				s[i][0] = p[0], s[i][1] = p[1];			//set the shot's starting coordinates to the player's current coordinates
				s[i][4] = 1;							//validate shot's existence
				break;
			}
			else if (input == 97)						//if input is a
			{
				s[i][2] = -s[i][2], s[i][3] = 0;		//then flip dx and dy = 0
				s[i][0] = p[0], s[i][1] = p[1];			//set the shot's starting coordinates to the player's current coordinates
				s[i][4] = 1;							//validate shot's existence
				break;
			}
			else if (input == 115)						//if input is s, i bet these need more to the conditions
			{
				s[i][2] = 0, s[i][3] = -s[i][3];		//then dx = 0 and flip dy
				s[i][0] = p[0], s[i][1] = p[1];			//set the shot's starting coordinates to the player's current coordinates
				s[i][4] = 1;							//validate shot's existence
				break;
			}
			else if (input == 100 || input == 13)		//if input is d
			{
				s[i][3] = 0;							//then dy = 0
				s[i][0] = p[0], s[i][1] = p[1];			//set the shot's starting coordinates to the player's current coordinates
				s[i][4] = 1;							//validate shot's existence
				break;
			}
		}
		if (i == 10)
			input = 0;
		//that did make it better kinda this sucks this is like really in depth code too so to solve it would require a lot of time and effort that I would rather put into reading
	}
}

void MovePlayerShot(double s[M][M], double r[M][M])//player shot array, room array
{
	for (int i = 0; i < 10; i++)														//loop through all 10 shots
	{
		if (s[i][4] == 1)																//if this shot exists
		{																				//then move it
			if ((r[int(s[i][1]) - int(s[i][3])][int(s[i][0]) + int(s[i][2])] == 1)
				|| (r[int(s[i][1] - s[i][3])][int(s[i][0] + s[i][2])] == 1)
				|| (r[int(s[i][1]) - int(s[i][3])][int(s[i][0]) + int(s[i][2])] == 2)
				|| (r[int(s[i][1] - s[i][3])][int(s[i][0] + s[i][2])] == 2))			//if the next position of the shot is 1 or 2
			{
				gotoxy(s[i][0], s[i][1]);												//go to the current position of the shot
				cout << " ";															//display a space
				s[i][3] = 1, s[i][2] = 1;												//reset the dx and dy values 
				s[i][4] = 0;															//extinguish shot's existence
			}
			else																		//so long as the next position of the shot is not 1 or 2
			{
				gotoxy(s[i][0], s[i][1]);												//go to the current position of the shot
				cout << " ";															//display a space
				s[i][0] += s[i][2], s[i][1] -= s[i][3];									//move the shot by dx and -dy
			}
			gotoxy(s[i][0], s[i][1]);													//go to the current position of the shot
			if (s[i][2] * s[i][3] == 0 && s[i][2] > 0)									//determination of sprite based on direction vector
				cout << ">";
			else if (s[i][2] * s[i][3] == 0 && s[i][2] < 0)
				cout << "<";
			else if (s[i][2] == 0 && s[i][3] > 0)
				cout << "^";
			else if (s[i][2] == 0 && s[i][3] < 0)
				cout << "v";
		}
	}
}

void Movement(double p[M], int input, double r[M][M])//player position, input, room array
{
		gotoxy(p[0], p[1]);							//go to current position
		cout << " ";								//display a space
		if (input == 72)
		{
			if (r[int(p[1]) - 1][int(p[0])] == 0)
				p[1]--;								//moves the character up a row
		}
		else if (input == 80)
		{
			if (r[int(p[1]) + 1][int(p[0])] == 0)
				p[1]++;								//moves the character down a row
		}
		else if (input == 77)
		{
			if (r[int(p[1])][int(p[0]) + 1] == 0)
				p[0]++;								//moves the character right a column
		}
		else if (input == 75)
		{
			if (r[int(p[1])][int(p[0]) - 1] == 0)
				p[0]--;								//moves the character left a column
		}
}

int Collision(double p[M], int y, double s[M][M])//player position, number of colliding objects, shot/wall array
{
	for (int i = 0; i < y; i++)								//loop through all colliding objects
	{
		if ((p[0] == int(s[i][0]) && p[1] == int(s[i][1])
			|| (p[0] == s[i][0]) && p[1] == s[i][1])
			|| (p[0] == int(s[i][0]) && p[1] == s[i][1])
			|| (p[0] == s[i][0]) && p[1] == int(s[i][1]))	//if the player has the same coordinates as the shot/wall
			return Lose();									//call the lose function
	}
	return 1;
}

//will have to build variables that hold the dimensions of Alpha as it changes
void AlphaCollision(double s[M][M], double axy[M], char A[M][M])//player shot, Alpha positions, Alpha array
{
	int i = 0;
	for (i; i < 10; i++)							//loop through number of shots
	{
		if (s[i][4] == 1)							//if the shot exists first and foremost
		{
			if ((s[i][1] >= axy[1])					
				&& (s[i][1] <= (axy[1]) + 3)		
				&& (s[i][0] >= axy[0])
				&& (s[i][0] <= (axy[0]) + 4))		//if the shot exists within the box of the array, aka hits the array
			{
				s[i][4] = 0;						//extinguish shot's existence
				A[int(axy[4])][int(axy[5])] = 0;	//erase the [axy[4]][axy[5]] position of Alpha
				axy[5]++;							//increment axy[5]to go down rows
				if (axy[5] == 6)					//once you reach the end of the row
					axy[4]++, axy[5] = 0;			//increment axy[4] and reset axy[5]
				gotoxy(s[i][0], s[i][1]);			//go to the immediate shot
				_putch(' ');						//clear its space
				axy[6]--;							//perhaps if the shot were a pointer of someshit then I could completely extinguish thoruhg deletion
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
	for (int i = 0; i < y; i++)				//simple nest for loop to build an array in the right order
	{
		for (int j = 0; j < x; j++)
		{
			if (r[i][j] == 1)
				cout << char(219);
			else if (r[i][j] == 0)
				cout << " ";
			else if (r[i][j] == 2)
				cout << "-";
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

	if (axy[2] > 0 && axy[3] > 0 && (r[int(axy[1] - axy[3])][int(axy[0] + axy[2]) + 6] == 0))			//if the direction is in Q1, and if the next position in that direction is 0
		axy[0] += axy[2], axy[1] -= axy[3];																//then go ahead and move the matrix in the direction of that vector
	else if(axy[2] < 0 && axy[3] > 0 && (r[int(axy[1] - axy[3])][int(axy[0] + axy[2]) - 1] == 0))		//if the direction is in Q2, and if the next position in that direction is 0
		axy[0] += axy[2], axy[1] -= axy[3];																//then go ahead and move the matrix in the direction of that vector															//then go ahead and move the matrix in the direction of that vector				
	else if (axy[2] < 0 && axy[3] < 0 && (r[int(axy[1] - axy[3]) + 4][int(axy[0] + axy[2]) - 1] == 0))	//if the direction is in Q3, and if the next position in that direction is 0															//and if the next position following the direction vector is 0 (this will require more conditions)
		axy[0] += axy[2], axy[1] -= axy[3];																//then go ahead and move the matrix in the direction of that vector
	else if (axy[2] > 0 && axy[3] < 0 && (r[int(axy[1] - axy[3]) + 4][int(axy[0] + axy[2]) + 6] == 0))	//if the direction is in Q4, and if the next position in that direction is 0
		axy[0] += axy[2], axy[1] -= axy[3];																//then go ahead and move the matrix in the direction of that vector
	else															//as long as the next position in the direction of the vector is not 0
	{
		if (axy[2] > 0 && axy[3] > 0)								//If Q1, (1,1)
		{
			if(r[int(axy[1] - axy[3])][int(axy[0])] != 0)			//if the position above is 1
			axy[3] = -axy[3];										//then change the sign of the y component
			else if (r[int(axy[1])][int(axy[0] + axy[2]) + 6] != 0)	//if the position to the right is 1
			axy[2] = -axy[2];										//then change the sign of the x component
		}
		else if (axy[2] < 0 && axy[3] > 0)							//If Q2, (-1,1)
		{
			if (r[int(axy[1] - axy[3])][int(axy[0])] != 0)			//if the position above is 1
				axy[3] = -axy[3];									//then change the sign of the y component
			else if (r[int(axy[1])][int(axy[0] + axy[2]) - 1] != 0)	//if the position to the left is 1
				axy[2] = -axy[2];									//then change the sign of the x component
		}
		else if (axy[2] < 0 && axy[3] < 0)							//If Q3, (-1,-1)
		{
			if (r[int(axy[1] - axy[3]) + 4][int(axy[0])] != 0)		//if the position below is 1
				axy[3] = -axy[3];									//then change the sign of the y component
			else if (r[int(axy[1])][int(axy[0] + axy[2]) - 1] != 0)	//if the position to the left is 1
				axy[2] = -axy[2];									//then change the sign of the x component
		}
		else if (axy[2] > 0 && axy[3] < 0)							//If Q4, (1,-1)
		{
			if (r[int(axy[1] - axy[3]) + 4][int(axy[0])] != 0)		//if the position below is 1
				axy[3] = -axy[3];									//then change the sign of the y component
			else if (r[int(axy[1])][int(axy[0] + axy[2]) + 6] != 0)	//if the position to the right is 1
				axy[2] = -axy[2];									//then change the sign of the x component
		}
	}																//circular motion
}

void InputAcquisition(int input[2])
{
	input[0] = _getch();
	if (input[0] == 224)		//if a movement key (up, down, left, right) is pressed, then grab the 2nd input
		input[1] = _getch();
	else						//otherwise, ignore the second input
		input[1] = 0;
}

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