#include "game.h"

sf::Color Colour(int n)
{
	if (n == 0)
		return sf::Color::White;
	else
	{
		while (n / 32 > 0)
		{
			n /= 32;
		}
		switch (n)
		{
		case 1:
			return sf::Color::Black;
			break;
		case 2:
			return sf::Color::Red;
			break;
		case 4:
			return sf::Color::Yellow;
			break;
		case 8:
			return sf::Color::Green;
			break;
		case 16:
			return sf::Color::Blue;
			break;
		}
	}
}

vector<Tile> Make_Table(vector<vector<int>> a)
{
	vector<Tile> Tiles;
	for (int i = 0; i < a.size(); i++)
		for (int j = 0; j < a.size(); j++)
		{
			Tile current_tile;
			current_tile.set_Tile(a, i, j);
			Tiles.push_back(current_tile);
		}
	return Tiles;
}

bool Exit()
{
	sf::RenderWindow window(sf::VideoMode(400, 200), "EXIT");
	int position = 1;
	bool res = false;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				window.close();
			if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A))
			{
				if (position == 1)
					position = 2;
				else position--;
			}
			if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D))
			{
				if (position == 2)
					position = 1;
				else position++;
			}
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
				switch (position)
				{
				case 1:
					window.close();
					res = true;
					break;
				case 2:
					window.close();
					res = false;
					break;
				}
		}
		window.clear();
		sf::Text text;
		sf::Font font;
		font.loadFromFile("bold.ttf");
		text.setCharacterSize(20);
		text.setFont(font);
		text.setFillColor(sf::Color::Blue);
		text.setStyle(sf::Text::Bold);
		text.setString("Do you want to left game?");
		text.setPosition(70, 30);

		sf::Text yes = text, no = text;
		switch (position)
		{
		case 1:
			yes.setFillColor(sf::Color::Yellow);
			yes.setStyle(sf::Text::Underlined);
			break;
		case 2:
			no.setFillColor(sf::Color::Yellow);
			no.setStyle(sf::Text::Underlined);
			break;
		}

		sf::RectangleShape rect;
		rect.setSize(sf::Vector2f(400, 200));
		rect.setFillColor(sf::Color::Green);
		rect.setPosition(0, 0);
		window.draw(rect);
		window.draw(text);
		
		yes.setPosition(30, 160);
		no.setPosition(330, 160);
		yes.setString("Yes");
		no.setString("No");
		window.draw(yes);
		window.draw(no);
		window.display();
	}
	return res;
}

void game(int size)
{
	srand(time(NULL));
	vector<vector<int>> a(size, (vector<int> (size, 0)));
	vector<Tile> Tiles;
	sf::RenderWindow window(sf::VideoMode(1000, 800), "2048");
	a[rand() % size][rand() % size] = 4;
	a[rand() % size][rand() % size] = 2;
	a[rand() % size][rand() % size] = 2;
	int score = 8;
	Tiles = Make_Table(a);
	while (window.isOpen() && HaveMoves(a))
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				if (Exit())
					window.close();
			if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S))
			{
				Move(4, a, score);
			}
			if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W))
			{
				Move(3, a, score);
			}
			if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A))
			{
				Move(1, a, score);
			}
			if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D))
			{
				Move(2, a, score);
			}
		}
		window.clear();
		Tiles = Make_Table(a);
		sf::Text text1;
		sf::Font font;
		font.loadFromFile("bold.ttf");
		text1.setCharacterSize(50);
		text1.setFont(font);
		text1.setFillColor(sf::Color::White);
		text1.setStyle(sf::Text::Bold);
		text1.setPosition(400, 110);
		for (int i = 0; i < Tiles.size(); i++)
		{
			window.draw(Tiles[i].tile);
		}
		for (int i = 0; i < a.size();i++)
			for (int j = 0; j < a.size(); j++)
			{
				text1.setString(to_string(a[i][j]));
				text1.setPosition(200 + 200 * i - to_string(a[i][j]).length() * 15, 50 + j * 200 + 15);
				window.draw(text1);
			}

		window.display();
		
	}
	window.close();
}