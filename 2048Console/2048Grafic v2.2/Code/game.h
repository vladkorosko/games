#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <random>
#include <string>
#include <time.h>
#include <conio.h>
#include <sys/stat.h>
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
		tile.setPosition(200 + 200 * line, 200 * column);
	}
};

bool FreePlace(vector<vector<int>> a, int x, int y);
void Move(int direction, vector<vector<int>>& table, int& score);
bool HaveMoves(vector<vector<int>> a);
bool EqualTables(vector<vector<int>> a, vector<vector<int>> b);
bool Exit();

void game(int size, sf::RenderWindow& window);
void prev_game(int size, sf::RenderWindow& window);
void show_scores(sf::RenderWindow& window);
void menu(sf::RenderWindow &window);