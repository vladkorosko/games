#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <cmath>

using namespace std;

struct point
{
	int x;
	int y;

	void PrintPoint()
	{
		cout << "X = " << x << ' ';
		cout << "Y = " << y << "; ";
	}
};

struct place 
{
	point ourpoint;
	bool pl = 0;
	int shoot = 0;
	bool occupated = false;
};

struct gameboard 
{
	int number_of_fourfields_ship = 0;
	int number_of_threefields_ship = 0;
	int number_of_doublefields_ship = 0;
	int number_of_monoship = 0;
	vector<place> board;
	vector<vector<point>> ships;

	bool Game()
	{
		return (ships.size()>0);
	}

	void PrintBoardShips()
	{
		for (int i = 13; i <= 131; i++)
		{
			if (i % 12 != 0 && i % 12 != 11)
			{
				if ((i % 12) % 10 == 0)
				{
					cout << board[i].pl << "   ";
					cout << endl << endl;
				}
				else
					cout << board[i].pl << "   ";
			}
		}
	}

	void PrintBoardShoots()
	{
		for (int i = 13; i <= 131; i++)
		{
			if (i % 12 != 0 && i % 12 != 11)
			{
				if ((i % 12) % 10 == 0)
				{
					cout << board[i].shoot << "   ";
					cout << endl << endl;
				}
				else
					cout << board[i].shoot << "   ";
			}
		}
	}

	void PrintBoardOccupated()
	{
		for (int i = 1; i <= 144; i++)
		{
			if (i % 12 == 0)
			{
				cout << board[i - 1].occupated << "   ";
				cout << endl << endl;
			}
			else
				cout << board[i - 1].occupated << "   ";
		}
	}

	void PrintStats()
	{
		cout << "Number of fourfields ships is " << number_of_fourfields_ship << endl;
		cout << "Number of threefields ships is " << number_of_threefields_ship << endl;
		cout << "Number of doublefields ships is " << number_of_doublefields_ship << endl;
		cout << "Number of monoships is " << number_of_monoship << endl;
	}

	bool CheckGameboard()
	{
		bool res = true;
		if (number_of_doublefields_ship > 4 || number_of_fourfields_ship > 2 || number_of_monoship > 5 || number_of_threefields_ship > 3)
			res = false;
		return res;
	}

	void PrintShips()
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < ships[i].size(); j++)
				ships[i][j].PrintPoint();
			cout << endl;
		}
	}
};

struct ship {
	int len;
	point start;
	point finish;

	int Length()
	{
		if (start.x == finish.x)
			return abs(start.y - finish.y);
		else
			return abs(start.x - finish.x);
	}

	bool CorrectShip()
	{
		bool res = false;
		if ((len > 0 && len < 5) && ((start.x == finish.x && abs(start.y - finish.y) == len - 1) || (start.y == finish.y && abs(start.x - finish.x) == len - 1)))
			res = true;
		return res;
	}
};

void game();