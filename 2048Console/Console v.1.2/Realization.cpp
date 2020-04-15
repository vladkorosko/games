#include "../../2048/2048/Functions.h"
bool FreePlace(vector<vector<int>> a, int x, int y)
{
	bool res = true;
	if (a[x][y] > 0)
		res = false;
	return res;
}

bool AllZeroHeightUp(vector<vector<int>> a, int i, int k)
{
	int res = 0;
	for (int j = k; j < a.size(); j++)
		res += a[j][i];
	return(res != 0);
}

bool AllZeroHeightDown(vector<vector<int>> a, int i, int k)
{
	int res = 0;
	for (int j = k; j >= 0; j--)
		res += a[j][i];
	return(res != 0);
}

bool AllZeroLengthUp(vector<vector<int>> a, int i, int k)
{
	int res = 0;
	for (int j = k; j < a.size(); j++)
		res += a[i][j];
	return(res != 0);
}

bool AllZeroLengthDown(vector<vector<int>> a, int i, int k)
{
	int res = 0;
	for (int j = k; j >= 0; j--)
		res += a[i][j];
	return(res != 0);
}

bool EqualTables(vector<vector<int>> a, vector<vector<int>> b)
{
	bool res = true;
	for (int i = 0; i < a.size(); i++)
		for (int j = 0; j < a.size(); j++)
			if (a[i][j] != b[i][j])
				res = false;
	return res;
}

void Color(int n)
{
	if (n == 0)
		cout << white;
	else 
	{
		while (n / 32 > 0)
		{
			n /= 32;
		}
		switch (n)
		{
		case 1:
			cout << blue;
			break;
		case 2:
			cout << red;
			break;
		case 4:
			cout << yellow;
			break;
		case 8:
			cout << green;
			break;
		case 16:
			cout << light_blue;
			break;
		}
	}
}

void PrintTable(vector<vector<int>> &a)
{
	system("cls");
	for (int i = 0; i < a.size(); i++)
	{
		for (int j = 0; j < a.size(); j++)
		{
			Color(a[i][j]);
			cout << a[i][j] << "    ";
		}
		cout << endl << endl;
	}

}

void Move(char s, vector<vector<int>> &a)
{
	switch (s)
	{
	case 'w':
		for (int i = 0; i < a.size(); i++)
		{
			for (int j = 0; j < a.size() - 1; j++)
				if (a[j][i] == 0 && AllZeroHeightUp(a, i, j))
					while (a[j][i] == 0)
					{
						for (int k = j + 1; k < a.size(); k++)
							a[k - 1][i] = a[k][i];
						a[a.size() - 1][i] = 0;
					}
			for (int j = 0; j < a.size() - 1; j++)
				if (a[j][i] == a[j + 1][i])
				{
					a[j][i] *= 2;
					for (int k = j + 1; k < a.size() - 1; k++)
						a[k][i] = a[k + 1][i];
					a[a.size() - 1][i] = 0;
				}
		}
		break;
	case 's':
		for (int i = 0; i < a.size(); i++)
		{
			for (int j = a.size() - 1; j > 0; j--)
				if (a[j][i] == 0 && AllZeroHeightDown(a, i, j))
					while (a[j][i] == 0)
					{
						for (int k = j; k > 0; k--)
							a[k][i] = a[k - 1][i];
						a[0][i] = 0;
					}
			for (int j = a.size() - 1; j > 0; j--)
				if (a[j][i] == a[j - 1][i])
				{
					a[j][i] *= 2;
					for (int k = j - 1; k > 0; k--)
						a[k][i] = a[k - 1][i];
					a[0][i] = 0;
				}
		}
		break;
	case 'a':
		for (int i = 0; i < a.size(); i++)
		{
			for (int j = 0; j < a.size() - 1; j++)
				if (a[i][j] == 0 && AllZeroLengthUp(a, i, j))
					while (a[i][j] == 0)
					{
						for (int k = j + 1; k < a.size(); k++)
							a[i][k - 1] = a[i][k];
						a[i][a.size() - 1] = 0;
					}
			for (int j = 0; j < a.size() - 1; j++)
				if (a[i][j] == a[i][j + 1])
				{
					a[i][j] *= 2;
					for (int k = j + 1; k < a.size() - 1; k++)
						a[i][k] = a[i][k + 1];
					a[i][a.size() - 1] = 0;
				}
		}
		break;
	case 'd':
		for (int i = 0; i < a.size(); i++)
		{
			for (int j = a.size() - 1; j > 0; j--)
			{
				if (a[i][j] == 0 && AllZeroLengthDown(a, i, j))
					while (a[i][j] == 0)
					{
						for (int k = j; k > 0; k--)
							a[i][k] = a[i][k - 1];
						a[i][0] = 0;
					}
			}
			for (int j = a.size() - 1; j > 0; j--)
			{
				if (a[i][j] == a[i][j - 1])
				{
					a[i][j] *= 2;
					for (int k = j - 1; k > 0; k--)
						a[i][k] = a[i][k - 1];
					a[i][0] = 0;
				}
			}
		}
		break;
	default:
		cout << "No such move." << endl;
		break;
	}
}

bool HaveMoves(vector<vector<int>> a)
{
	bool res = true;
	vector<vector<int>> b = a;
	vector<vector<int>> c = a;
	vector<vector<int>> d = a;
	vector<vector<int>> e = a;
	Move('w', b);
	Move('s', c);
	Move('a', d);
	Move('d', e);
	if (EqualTables(a, b) && EqualTables(a,c) && EqualTables(a, d) && EqualTables(a, e))
		res = false;
	return res;
}

void game(int size)
{
	srand(time(NULL));
	vector<vector<int>> a(size, vector<int>(size, 0));
	a[rand() % a.size()][rand() % a.size()] = 2;
	a[rand() % a.size()][rand() % a.size()] = 2;
	a[rand() % a.size()][rand() % a.size()] = 4;
	PrintTable(a);
	int score = 8;
	while (HaveMoves(a))
	{
		bool res2 = true;
		bool res1 = true;
		while (res1)
		{
			int key;
			cout << white;
			key = _getch();
			cout << white;
			vector<vector<int>> b = a;
			Move((char) key, b);
			if (!(EqualTables(a, b)))
			{
				a = b;
				res1 = false;
			}
		}
		while (res2)
		{
			int x = rand() % a.size();
			int y = rand() % a.size();
			if (FreePlace(a, x, y))
			{
				a[x][y] = 2;
				score += 2;
				PrintTable(a);
				res2 = false;
			}
		}
	}
	cout << blue;
	cout << "Game over." << endl;
	cout << "Your final score is " << score << endl;
}