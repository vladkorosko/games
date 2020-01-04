#include "Header.h"
#include <iostream>
#include <vector>
#include <random>
#include <cmath>

using namespace std;

place FindPoint(gameboard player, point a)
{
	return player.board[a.x * 12 + a.y];
}

bool EqualPoint(point a, point b)
{
	bool res = true; 
	if (a.x != b.x || a.y != b.y)
		res = false;
	return res;
}

void UpdateStats(gameboard &player, int len)
{
	switch (len)
	{
	case 1:
		player.number_of_monoship--;
		break;
	case 2:
		player.number_of_doublefields_ship--;
		break;
	case 3:
		player.number_of_threefields_ship--;
		break;
	case 4:
		player.number_of_fourfields_ship--;
		break;
	default:
		break;
	}
}

void CheckShip(gameboard &player)
{
	for (int i = 0; i < player.ships.size(); i++)
	{
		bool res = true;
		for (int j = 0; j < player.ships[i].size(); j++)
		{
			if(FindPoint(player, player.ships[i][j]).shoot == 0)
				res = false;
		}
		if (res)
		{
			point StartPoint, FinishPoint;
			StartPoint = player.ships[i][0];
			FinishPoint = player.ships[i][player.ships[i].size() - 1];
			ship CreatedShip;
			CreatedShip.start = StartPoint;
			CreatedShip.finish = FinishPoint;
			int x = StartPoint.x;
			int y = StartPoint.y;
			if (CreatedShip.start.x == CreatedShip.finish.x)
			{
				for (int r = -1; r < 2; r++)
					for (int j = -1; j < CreatedShip.Length() + 2; j++)
						player.board[(x + r) * 12 + y + j].shoot = 1;
				for (int r = 0; r < CreatedShip.Length()+1; r++)
				{
					player.board[x * 12 + y + r].shoot = 3;
				}
			}
			if (CreatedShip.start.y == CreatedShip.finish.y)
			{
				for (int r = -1; r < 2; r++)
					for (int j = -1; j < CreatedShip.Length() + 2; j++)
						player.board[(x + j) * 12 + y + r].shoot = 1;
				for (int r = 0; r < CreatedShip.Length()+1; r++)
				{
					player.board[(x + r) * 12 + y].shoot = 3;
				}
			}
			UpdateStats(player, CreatedShip.Length()+1);
			player.ships.erase(player.ships.begin() + i);
		}
	}
}

point FindIndexOfPointShip(gameboard player, point a)
{
	point res;
	for (int i = 0; i < player.ships.size(); i++)
		for (int j = 0; j < player.ships[i].size(); j++)
			if (EqualPoint(player.ships[i][j], a))
			{
				res.x = i;
				res.y = j;
				return res;
				break;
			}
}

point CreatePoint(int x, int y)
{
	point a;
	a.x = x;
	a.y = y;
	return a;
}

void ChangeNumberOfShips(gameboard& player, int len)
{
	switch (len)
	{
	case 1:
		player.number_of_monoship++;
		break;
	case 2:
		player.number_of_doublefields_ship++;
		break;
	case 3:
		player.number_of_threefields_ship++;
		break;
	case 4:
		player.number_of_fourfields_ship++;
		break;
	default:
		break;
	}
}

bool CheckPlace(gameboard player, ship CreatedShip)
{
	bool res = true;
	int x1 = CreatedShip.start.x;
	int y1 = CreatedShip.start.y;
	if (CreatedShip.CorrectShip())
	{
		if (CreatedShip.start.x == CreatedShip.finish.x)
		{
			for (int j = 0; j < CreatedShip.len; j++)
				if (FindPoint(player, CreatePoint(x1, y1 + j)).occupated)
					res = false;
		}
		if (CreatedShip.start.y == CreatedShip.finish.y)
		{
			for (int j = 0; j < CreatedShip.len; j++)
				if (FindPoint(player, CreatePoint(x1 + j, y1)).occupated)
					res = false;
		}
	}
	return res;
}

bool CheckShip(int a, gameboard b)
{
	bool res = false;
	switch (a)
	{
	case 1:
		res = (b.number_of_monoship < 4);
		break;
	case 2:
		res = (b.number_of_doublefields_ship < 3);
		break;
	case 3:
		res = (b.number_of_threefields_ship < 2);
		break;
	case 4:
		res = (b.number_of_fourfields_ship < 1);
		break;
	default:
		break;
	}
	return res;
}

void PlaceShip(gameboard &player, ship CreatedShip)
{
	int x1 = CreatedShip.start.x;
	int y1 = CreatedShip.start.y;
	vector<point> b;
	if (CreatedShip.len == 1)
	{
		for (int i = -1; i < 2; i++)
			for (int j = -1; j < 2; j++)
				player.board[(x1 + i) * 12 + y1 + j].occupated = true;
		player.board[x1 * 12 + y1].pl = 1;
		b.push_back(CreatePoint(x1, y1));
	}
	else
	{
		if (CreatedShip.start.x == CreatedShip.finish.x)
		{
			for (int i = -1; i < 2; i++)
				for (int j = -1; j < CreatedShip.len + 1; j++)
					player.board[(x1 + i) * 12 + y1 + j].occupated = true;
			for (int i = 0; i < CreatedShip.len; i++)
			{
				b.push_back(CreatePoint(x1, y1 + i));
				player.board[x1 * 12 + y1 + i].pl = 1;
			}
		}
		if (CreatedShip.start.y == CreatedShip.finish.y)
		{
			for (int i = -1; i < 2; i++)
				for (int j = -1; j < CreatedShip.len + 1; j++)
					player.board[(x1 + j) * 12 + y1 + i].occupated = true;
			for (int i = 0; i < CreatedShip.len; i++)
			{
				b.push_back(CreatePoint(x1 + i, y1));
				player.board[(x1 + i) * 12 + y1].pl = 1;
			}
		}
	}
	player.ships.push_back(b);

}

void fill(gameboard &a)
{
	int statement = 10;
	while (statement)
	{   
		a.PrintBoardShips();
		//a.PrintBoardOccupated();
		a.PrintStats();

		ship CreatedShip;
		point StartPoint, FinishPoint;

		cout << "Enter the length of ship." << endl;
		int len;
		cin >> len;
		cout << "Enter the coordinates of start (x,y)." << endl;
		cin >> StartPoint.x >> StartPoint.y;
		cout << "Enter the coordinates of finish (x,y)." << endl;
		cin >> FinishPoint.x >> FinishPoint.y;

		CreatedShip.finish = FinishPoint;
		CreatedShip.start = StartPoint;
		CreatedShip.len = len;

		bool st1 = CreatedShip.CorrectShip();
		bool st2 = CheckShip(len, a);
		bool st3 = CheckPlace(a, CreatedShip);
		
		if (st1 && st2 && st3)
		{
			PlaceShip(a, CreatedShip);
			ChangeNumberOfShips(a, len);
			statement--;
		}
		else cout << "Something wrong. Try again." << endl;
	}
	system("cls");
}

void fight(gameboard &FirstPlayer, gameboard &SecondPlayer)
{
	int i = 0;
	while (FirstPlayer.Game() && SecondPlayer.Game())
	{
		bool res = true;
		if (i % 2)
		{
			while (res && FirstPlayer.Game())
			{
				FirstPlayer.PrintBoardShoots();
				FirstPlayer.PrintStats();
				cout << "Second Player. Please enter the coordinates of point which you want to shoot." << endl;
				int x, y;
				cin >> x >> y;
				place a;
				if (!(FirstPlayer.board[12 * x + y].shoot))
				{
					if (FirstPlayer.board[12 * x  + y].pl)
					{
						cout << "You hit the ship!" << endl;
						FirstPlayer.board[12 * x + y].shoot = 2;
						CheckShip(FirstPlayer);
					}
					else
					{
						FirstPlayer.board[12 * x + y].shoot = 1;
						res = false;
						cout << "You miss." << endl;
						i++;
					}
				}
				else
					cout << "You shoot this point before. Try again" << endl;
			}
		}
		else
		{
			while (res && SecondPlayer.Game())
			{
				SecondPlayer.PrintBoardShoots();
				SecondPlayer.PrintStats();
				cout << "First Player. Please enter the coordinates of point which you want to shoot." << endl;
				int x, y;
				cin >> x >> y;
				place a;
				if (!(SecondPlayer.board[12 * x + y].shoot))
				{
					if (SecondPlayer.board[12 * x + y].pl)
					{
						cout << "You hit the ship!" << endl;
						SecondPlayer.board[12 * x + y].shoot = 2;
						CheckShip(SecondPlayer);
					}
					else
					{
						SecondPlayer.board[12 * x + y].shoot = 1;
						res = false;
						cout << "You miss." << endl;
						i++;
					}
				}
				else
					cout << "You shoot this point before. Try again" << endl;
			}
		}

	}
}


void game()
{
	gameboard player_1;
	gameboard player_2;
	vector<place> a(144);
	for (int i = 0; i < 144; i++)
	{
		a[i].ourpoint.x = i / 12;
		a[i].ourpoint.y = i % 12;
	}

	player_1.board = a;
	player_2.board = a;

	fill(player_1);
	player_1.PrintShips();
	cout << "Now the second player. Enter 2 for continue." << endl;
	int pause;
	cin >> pause;
	fill(player_2);
	cout << "Let`s start" << endl;

	fight(player_1, player_2);

	if (player_1.Game())
		cout << "The First player is winner!" << endl;
	if(player_2.Game())
		cout << "The Second player is winner!" << endl;
}