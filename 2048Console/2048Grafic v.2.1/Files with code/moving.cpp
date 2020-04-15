#include"game.h"

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

void Move(int direction, vector<vector<int>>& table, int& score)
{
	bool generate_numbers = true;
	vector<vector<int>> a = table;
	switch (direction)
	{
	case 1:
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
	case 2:
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
	case 3:
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
	case 4:
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
		generate_numbers = false;
		break;
	}

	if (!EqualTables(table, a))
	{
		table = a;
		while (generate_numbers)
		{
			int x_pos = rand() % table.size();
			int y_pos = rand() % table.size();
			if (FreePlace(table, x_pos, y_pos))
			{
				table[x_pos][y_pos] = 2;
				generate_numbers = false;
				score += 2;
			}
		}
	}
}

bool HaveMoves(vector<vector<int>> a)
{
	bool res = true;
	int score = 0;
	vector<vector<int>> b = a;
	vector<vector<int>> c = a;
	vector<vector<int>> d = a;
	vector<vector<int>> e = a;
	Move(1, b, score);
	Move(2, c, score);
	Move(3, d, score);
	Move(4, e, score);
	if (EqualTables(a, b) && EqualTables(a, c) && EqualTables(a, d) && EqualTables(a, e))
		res = false;
	return res;
}
