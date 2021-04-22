#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver;
const int width = 20;
const int height = width;
int tailX[100], tailY[100];
int nTail;
int x, y, fruitX, fruitY, score;

enum class eDirection
{
	STOP = 0,
	LEFT,
	RIGHT,
	UP,
	DOWN
};
eDirection dir;

void Setup()
{
	gameOver = false;
	dir = eDirection::STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}


void Draw()
{
	system("cls");
	for (int i = 0; i < width + 1; i++)
	{
		cout << "/";
	}
	cout << endl;


	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1)
			{
				cout << "/";
			}
			if (i == y && j == x)
			{
				cout << "0";
			}
			else if (i == fruitY && j == fruitX)
			{
				cout << "*";
			}
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						print = true;
						cout << "o";
					}
				}
				if (!print)
				{
					cout << " ";
				}
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width + 1; i++)
	{
		cout << "/";
	}
	cout << endl;

	cout << "Score: " << score << endl;
}


void Input() 
{
	if (_kbhit())
	{
		switch (_getch())
		{
			case 'a':
				dir = eDirection::LEFT;
				break;
			case 'd':
				dir = eDirection::RIGHT;
				break;
			case 'w':
				dir = eDirection::UP;
				break;
			case 's':
				dir = eDirection::DOWN;
				break;
			case 'x':
				gameOver = true;
				break;
		}
	}
}


void Logic(int &impassableWalls)
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)
	{
	case eDirection::LEFT:
		x--;
		break;
	case eDirection::RIGHT:
		x++;
		break;
	case eDirection::UP:
		y--;
		break;
	case eDirection::DOWN:
		y++;
		break;
	}

	if (impassableWalls == 2)
	{
		if (x > width - 2 || x < 0 || y > height - 1 || y < 0)
		{
			gameOver = true;
		}
	}

	if (x >= width -1)
	{
		x = 0;
	}
	else if (x < 0)
	{
		x = width - 2;
	}

	if (y >= height)
	{
		y = 0;
	}
	else if (y < 0)
	{
		y = height - 1;
	}

	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
		{
			gameOver = true;
		}
	}

	if (x == fruitX && fruitY == y)
	{
		score++;
		nTail++;

		fruitX = rand() % width;
		fruitY = rand() % height;
	}
}


int diff(int &difficulty)
{
	switch (difficulty)
	{
	case 1:
		return difficulty = 200;
	case 2:
		return difficulty = 100;
	case 3:
		return difficulty = 50;
	}
}


int main()
{
	setlocale(LC_ALL, "ru");


	int impassableWalls;
	int difficulty;

	cout << "Выберете режим игры:\n1.Стандартный\n2.Непроходимые стены\n";
	cin >> impassableWalls;

	cout << "Выберете уровень сложности:\n1.Легкий\n2.Средний\n3.Сложный\n";
	cin >> difficulty;

	difficulty = diff(difficulty);

	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic(impassableWalls);
		Sleep(difficulty);
	}

	return 0;
}