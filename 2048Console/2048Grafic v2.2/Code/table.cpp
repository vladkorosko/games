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

bool have_file(string path)
{
	ifstream file(path);
	return file.good();
}

void quick_sort(vector<int>& a, int first, int last)
{
	int x = a[first];
	int i = first, j = last;
	do
	{
		while (a[i] > x)
			i++;
		while (a[j] < x)
			j--;
		if (i <= j)
		{
			if (i < j)
				swap(a[i], a[j]);
			i++;
			j--;
		}
	} while (i <= j);
	if (first < j)
		quick_sort(a, first, j);
	if (last > i)
		quick_sort(a, i, last);
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

void End_game(sf::RenderWindow& window, int score)
{
	vector<int> scores;
	if (have_file("score.txt"))
	{
		ifstream file("score.txt");
		int number;
		file >> number;
		while (number)
		{
			int points;
			file >> points;
			scores.push_back(points);
			number--;
		}
		file.close();
	}

	scores.push_back(score);
	quick_sort(scores, 0, scores.size() - 1);

	if (scores.size() > 10)
	{
		scores.erase(scores.begin());
	}

	ofstream fout("score.txt");
	fout << scores.size() << endl;
	for (int i = 0; i < scores.size(); i++)
		fout << scores[i] << endl;

	fout.close();
	
	bool cont = true;
	while (cont)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				cont = false;
		}

		window.clear();

		sf::Text text1;
		sf::Font font;
		font.loadFromFile("bold.ttf");
		text1.setCharacterSize(100);
		text1.setFont(font);
		text1.setFillColor(sf::Color::Red);
		text1.setStyle(sf::Text::Bold);

		string text = "Game over";
		text1.setString(text);
		text1.setPosition(500 - 55 * text.size()/2, 100);
		window.draw(text1);

		text = "Score: " + to_string(score);
		text1.setString(text);
		text1.setFillColor(sf::Color::Blue);
		text1.setPosition(500 - 50 * text.size() / 2, 300);
		window.draw(text1);

		text = "Press Esc to go to the Menu.";
		text1.setString(text);
		text1.setCharacterSize(60);
		text1.setFillColor(sf::Color::Green);
		text1.setPosition(70, 500);
		window.draw(text1);

		window.display();
	}

	menu(window);
}

void game(int size, sf::RenderWindow &window)
{
	ofstream fout("Last_game.txt");
	srand(time(NULL));
	vector<vector<int>> prev_a(size, (vector<int>(size, 0)));
	vector<vector<int>> a(size, (vector<int> (size, 0)));
	a[rand() % a.size()][rand() % a.size()] = 2;
	prev_a = a;
	vector<Tile> Tiles;
	int score = 2;
	int prev_score = 2;
	Tiles = Make_Table(a);
	bool cont = true;
	while (cont && HaveMoves(a))
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				if (Exit())
				{
					cont = false;
					for (int i = 0; i < size * size; i++)
						fout << a[i/4][i%4] << endl;
					fout << score << endl;
					menu(window);
				}
			if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S))
			{
				prev_a = a;
				prev_score = score;
				Move(4, a, score);
			}
			if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W))
			{
				prev_a = a;
				prev_score = score;
				Move(3, a, score);
			}
			if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A))
			{
				prev_a = a;
				prev_score = score;
				Move(1, a, score);
			}
			if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D))
			{
				prev_a = a;
				prev_score = score;
				Move(2, a, score);
			}
			if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::BackSpace || event.key.code == sf::Keyboard::Z))
			{
				a = prev_a;
				score = prev_score;
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
		for (int i = 0; i < Tiles.size(); i++)
		{
			window.draw(Tiles[i].tile);
		}
		for (int i = 0; i < a.size();i++)
			for (int j = 0; j < a.size(); j++)
			{
				text1.setString(to_string(a[i][j]));
				text1.setPosition(300 + 200 * i - to_string(a[i][j]).length() * 15, 50 + j * 200 + 15);
				window.draw(text1);
			}
		text1.setCharacterSize(20);
		text1.setString("Score: " + to_string(score));
		text1.setPosition(0,0);
		window.draw(text1);

		window.display();
	}

	End_game(window, score);
	fout.close();
}

void prev_game(int size, sf::RenderWindow& window)
{
	vector<vector<int>> a(size, (vector<int>(size, 0)));
	int score = 0;
	bool is_file = have_file("Last_game.txt");
	if (is_file)
	{
		ifstream fin("Last_game.txt");
		for (int i = 0; i < size * size; i++)
			fin >> a[i / 4][i % 4];
		fin >> score;
		fin.close();
	}

	vector<vector<int>> prev_a = a;
	int prev_score = score;
	ofstream fout("Last_game.txt");
	srand(time(NULL));
	vector<Tile> Tiles;
	Tiles = Make_Table(a);
	bool cont = true;
	while (cont && HaveMoves(a))
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				if (Exit())
				{
					cont = false;
					for (int i = 0; i < size * size; i++)
						fout << a[i / 4][i % 4] << endl;
					fout.close();
					menu(window);
				}
			if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S))
			{
				prev_a = a;
				prev_score = score;
				Move(4, a, score);
			}
			if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W))
			{
				prev_a = a;
				prev_score = score;
				Move(3, a, score);
			}
			if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A))
			{
				prev_a = a;
				prev_score = score;
				Move(1, a, score);
			}
			if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D))
			{
				prev_a = a;
				prev_score = score;
				Move(2, a, score);
			}
			if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::BackSpace || event.key.code == sf::Keyboard::Z))
			{
				a = prev_a;
				score = prev_score;
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
		for (int i = 0; i < Tiles.size(); i++)
		{
			window.draw(Tiles[i].tile);
		}
		for (int i = 0; i < a.size(); i++)
			for (int j = 0; j < a.size(); j++)
			{
				text1.setString(to_string(a[i][j]));
				text1.setPosition(300 + 200 * i - to_string(a[i][j]).length() * 15, 50 + j * 200 + 15);
				window.draw(text1);
			}
		text1.setCharacterSize(20);
		text1.setString("Score: " + to_string(score));
		text1.setPosition(0, 0);
		window.draw(text1);

		window.display();
	}

	if (score == 0)
		game(size, window);
	else
		End_game(window, score);
}

void show_scores(sf::RenderWindow& window)
{
	vector<int> scores;
	if (have_file("score.txt"))
	{
		ifstream file("score.txt");
		int number;
		file >> number;
		while (number)
		{
			int points;
			file >> points;
			scores.push_back(points);
			number--;
		}
		file.close();
	}

	bool cont = true;
	while (cont && scores.size())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed ||
				(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				cont = false;
		}

		window.clear();

		sf::Text text1;
		sf::Font font;
		font.loadFromFile("bold.ttf");
		text1.setCharacterSize(100);
		text1.setFont(font);
		text1.setFillColor(sf::Color::Green);
		text1.setStyle(sf::Text::Bold);

		string text = "You records:";
		text1.setString(text);
		text1.setPosition(500 - 50 * text.size() / 2, 0);
		window.draw(text1);

		text1.setCharacterSize(50);
		for (int i = 0; i < scores.size(); i++)
		{
			text = "Score: " + to_string(scores[i]);
			text1.setString(text);
			text1.setFillColor(sf::Color::Blue);
			text1.setPosition(400 * (i%2 + 1) - 50 * text.size() / 2, 100 * (i/2 + 1));
			window.draw(text1);
		}

		text = "Press Esc to go to the Menu.";
		text1.setString(text);
		text1.setCharacterSize(60);
		text1.setFillColor(sf::Color::Green);
		text1.setPosition(70, 600);
		window.draw(text1);

		window.display();
	}

	menu(window);
}