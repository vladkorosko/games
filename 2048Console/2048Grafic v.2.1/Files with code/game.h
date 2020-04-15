#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <string>
#include <time.h>
#include <conio.h>
#include <SFML/Graphics.hpp>

using namespace std;

sf::Color Colour(int n);

struct Tile
{
	sf::RectangleShape tile;

	void set_Tile(vector<vector<int>> table, int line, int column)
	{
		tile.setSize(sf::Vector2f(200, 200));
		tile.setFillColor(Colour(table[line][column]));
		tile.setPosition(100 + 200 * line, 200 * column);
	}
	/*
	void Print(sf::RenderWindow window)
	{
		window.draw(tile);
		window.draw(value);
	}*/
};

bool FreePlace(vector<vector<int>> a, int x, int y);
void Move(int direction, vector<vector<int>>& table, int& score);
bool HaveMoves(vector<vector<int>> a);
bool EqualTables(vector<vector<int>> a, vector<vector<int>> b);
bool Exit();

void game(int size);
void menu();