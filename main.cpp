#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>
#include <sstream>


const int width = 600;
const int height = 600;

const int addwidth = 200;
const int addheight = 600;

const int screenwidth = width + addwidth;
const int screenheight = height;

const int col = width / 10;
const int row = height / 10;
int cur[col][row] = { 0 };
int next[col][row];

int population = 0;

bool paused = false;

float speed = 0.005;

sf::String toString(sf::Int64 integer)
{
	std::ostringstream os;
	os << "Population: "<< integer;
	return os.str();
}

void popString(sf::Text t, sf::RenderWindow& win)
{
	t.setString(toString(population));
	win.draw(t);
}

void init()
{
	for (int x = 0; x < col; x++)
	{
		for (int y = 0; y < row; y++)
		{
			int num = rand() % 2;
			cur[x][y] = num;
		}
	}
}

void update()
{
	for (int x = 0; x < col; x++)
	{
		for (int y = 0; y < row; y++)
		{
			int neighbours = 0;

			if (cur[x - 1][y] == 1)
			{
				neighbours++;
			}
			if (cur[x + 1][y] == 1)
			{
				neighbours++;
			}
			if (cur[x][y + 1] == 1)
			{
				neighbours++;
			}
			if (cur[x][y - 1] == 1)
			{
				neighbours++;
			}
			if (cur[x + 1][y + 1] == 1)
			{
				neighbours++;
			}
			if (cur[x + 1][y - 1] == 1)
			{
				neighbours++;
			}
			if (cur[x - 1][y - 1] == 1)
			{
				neighbours++;
			}
			if (cur[x - 1][y + 1] == 1)
			{
				neighbours++;
			}

			if (cur[x][y] == 1)
			{
				if (neighbours >= 2 && neighbours <= 3)
				{
					next[x][y] = 1;
				}
				if (neighbours < 2)
				{
					next[x][y] = 0;
				}
				if (neighbours > 3)
				{
					next[x][y] = 0;
				}

			}
			if (cur[x][y] == 0)
			{
				if (neighbours == 3)
				{
					next[x][y] = 1;
				}
			}

		
		}
	}
	for (int x = 0; x < col; x++)
	{
		for (int y = 0; y < row; y++)
		{
			cur[x][y] = next[x][y];
		}
	}
}

void draw(sf::RenderWindow& win)
{
	for (int x = 0; x < col; x++)
	{
		for (int y = 0; y < row; y++)
		{
			sf::Color color;
			
			sf::RectangleShape shape;
			shape.setSize(sf::Vector2f(10, 10));
			if (cur[x][y] == 0)
			{
				color = sf::Color::White;
			}
			if (cur[x][y] == 1)
			{
				color = sf::Color::Black;
			}
			shape.setFillColor(color);
			shape.setPosition(x * 10, y * 10);
			win.draw(shape);

			if (cur[x][y] == 1)
			{
				population++;
			}
		}
	}
	
}



int main()
{
	sf::RenderWindow window(sf::VideoMode(screenwidth, screenheight), "window");

	sf::Font font;

	if (!font.loadFromFile("Fonts/arial.ttf"))
	{
		std::cout << "Font not loaded" << std::endl;
	}

	sf::Text poptext;
	poptext.setFont(font);
	poptext.setFillColor(sf::Color::White);
	poptext.setPosition(sf::Vector2f(width, 0));
	poptext.setCharacterSize(24);

	sf::Text pausetext;
	pausetext.setFont(font);
	pausetext.setFillColor(sf::Color::White);
	pausetext.setPosition(sf::Vector2f(width + 50, 550));
	pausetext.setCharacterSize(24);
	pausetext.setString("P to pause");

	sf::Text clearcells;
	clearcells.setFont(font);
	clearcells.setFillColor(sf::Color::White);
	clearcells.setPosition(sf::Vector2f(width + 50, 520));
	clearcells.setCharacterSize(24);
	clearcells.setString("C to clear");

	sf::Text gentext;
	gentext.setFont(font);
	gentext.setFillColor(sf::Color::White);
	gentext.setPosition(sf::Vector2f(width + 20, 490));
	gentext.setCharacterSize(24);
	gentext.setString("G to generate");

	sf::Text speedtext;
	speedtext.setFont(font);
	speedtext.setFillColor(sf::Color::White);
	speedtext.setPosition(sf::Vector2f(width, 460));
	speedtext.setCharacterSize(24);
	speedtext.setString("Change speed + -");

	sf::Vector2u gsize;
	sf::Image graph;

	sf::Clock clock;
	clock.restart();


	init();
	

	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				window.close();
			}
			if (e.type == sf::Event::KeyPressed)
			{
				if (e.key.code == sf::Keyboard::P)
				{
					paused = !paused;
				}
				if (e.key.code == sf::Keyboard::G)
				{
					init();
				}
				if (e.key.code == sf::Keyboard::C)
				{
					for (int x = 0; x < col; x++)
					{
						for (int y = 0; y < row; y++)
						{
							cur[x][y] = 0;
							next[x][y] = 0;
						}
					}
				}
				if (e.key.code == sf::Keyboard::Add)
				{
					if (speed > 0.005)
					{
						speed -= 0.05;
					}
				}
				if (e.key.code == sf::Keyboard::Subtract)
				{
					speed += 0.05;
				}
			}
			if (e.type == sf::Event::MouseButtonPressed)
			{
				if (e.mouseButton.button == sf::Mouse::Left)
				{
					if (cur[int(sf::Mouse::getPosition(window).x / 10)][int(sf::Mouse::getPosition(window).y / 10)] == 0)
					{
						cur[int(sf::Mouse::getPosition(window).x / 10)][int(sf::Mouse::getPosition(window).y / 10)] = 1;
					}
				}
				if (e.mouseButton.button == sf::Mouse::Right)
				{
					if (cur[int(sf::Mouse::getPosition(window).x / 10)][int(sf::Mouse::getPosition(window).y / 10)] == 1)
					{
						cur[int(sf::Mouse::getPosition(window).x / 10)][int(sf::Mouse::getPosition(window).y / 10)] = 0;
					}
				}
			}

		}
		sf::Time time = clock.getElapsedTime();
		if (time.asSeconds() >= speed)
		{
			window.clear();
			if (!paused)
			{
				update();
			}
			draw(window);
			clock.restart();
			popString(poptext, window);
			population = 0;
			window.draw(pausetext);
			window.draw(clearcells);
			window.draw(gentext);
			window.draw(speedtext);
			graph.create(gsize.x, gsize.y, sf::Color::Black);
			window.display();
		}
	}

		
	
}