#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include <iostream>

int i, j, x, y, ok = 0;
struct
{
	int value;
	bool hidden = 1, flag = 0;
}map[18][32];
int resolutionX = 960, resolutionY = 640;
int number_of_bombs = 99;

void put_bomb()
{
	x = rand() % 16 + 1;
	y = rand() % 30 + 1;
	if (map[x][y].value == -1)
		put_bomb();
	else map[x][y].value = -1;
}

void check_value(int x1, int y1)
{
	std::cout << x1 << " " << y1 << std::endl;
	if (map[x1][y1].flag == 0)
		map[x1][y1].hidden = 0;
	
	if (map[x1][y1].value == 0)
	{
		if (x1 > 1)
		{
			if (y1 > 1  && map[x1 - 1][y1 - 1].hidden == 1)
				check_value(x1 - 1, y1 - 1);
			if (map[x1 - 1][y1].hidden == 1)
				check_value(x1 - 1, y1);
			if (y1 < 30 && map[x1 - 1][y1 + 1].hidden == 1)
				check_value(x1 - 1, y1 + 1);
		}
		if (y1 > 1 && map[x1][y1 - 1].hidden == 1)
			check_value(x1, y1 - 1);
		if (y1 < 30 && map[x1][y1 + 1].hidden == 1)
			check_value(x1, y1 + 1);
		if (x1 < 16)
		{
			if (y1 > 1 && map[x1 + 1][y1 - 1].hidden == 1)
				check_value(x1 + 1, y1 - 1);
			if (map[x1 + 1][y1].hidden == 1)
				check_value(x1 + 1, y1);
			if (y1 < 30 && map[x1 + 1][y1 + 1].hidden == 1)
				check_value(x1 + 1, y1 + 1);
		}
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(resolutionX, resolutionY), "Minesweeper");

	sf::Texture texture_bomb, texture_bomb_exploded, texture_flag, texture_unknown, texture_free, texture_1, texture_2, texture_3, texture_4, texture_5, texture_6, texture_7, texture_8;
	texture_bomb.loadFromFile("sprites/bomb.png");
	texture_bomb_exploded.loadFromFile("sprites/bomb_exploded.png");
	texture_flag.loadFromFile("sprites/flag.png");
	texture_unknown.loadFromFile("sprites/unknown.png");
	texture_free.loadFromFile("sprites/free.png");
	texture_1.loadFromFile("sprites/1_nearby.png");
	texture_2.loadFromFile("sprites/2_nearby.png");
	texture_3.loadFromFile("sprites/3_nearby.png");
	texture_4.loadFromFile("sprites/4_nearby.png");
	texture_5.loadFromFile("sprites/5_nearby.png");
	texture_6.loadFromFile("sprites/6_nearby.png");
	texture_7.loadFromFile("sprites/7_nearby.png");
	texture_8.loadFromFile("sprites/8_nearby.png");

	sf::Sprite sprite_bomb, sprite_bomb_exploded, sprite_flag, sprite_unknown, sprite_free, sprite_1, sprite_2, sprite_3, sprite_4, sprite_5, sprite_6, sprite_7, sprite_8;
	sprite_bomb.setTexture(texture_bomb);
	sprite_bomb_exploded.setTexture(texture_bomb_exploded);
	sprite_flag.setTexture(texture_flag);
	sprite_unknown.setTexture(texture_unknown);
	sprite_free.setTexture(texture_free);
	sprite_1.setTexture(texture_1);
	sprite_2.setTexture(texture_2);
	sprite_3.setTexture(texture_3);
	sprite_4.setTexture(texture_4);
	sprite_5.setTexture(texture_5);
	sprite_6.setTexture(texture_6);
	sprite_7.setTexture(texture_7);
	sprite_8.setTexture(texture_8);

	sf::Vector2i mouse_position;

	//window.setFramerateLimit(240);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			mouse_position = sf::Mouse::getPosition(window);
			mouse_position.x = mouse_position.x / 32 + 1;
			mouse_position.y = mouse_position.y / 32 + 1;
			if (mouse_position.x > 0 && mouse_position.x < 31 && mouse_position.y> 0 && mouse_position.y < 17)
			{
				//while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				//{
//
				//}
				if (ok == 0)
				{
					map[mouse_position.y - 1][mouse_position.x - 1].value = -1;
					map[mouse_position.y][mouse_position.x - 1].value = -1;
					map[mouse_position.y + 1][mouse_position.x - 1].value = -1;
					map[mouse_position.y - 1][mouse_position.x].value = -1;
					map[mouse_position.y][mouse_position.x].value = -1;
					map[mouse_position.y + 1][mouse_position.x].value = -1;
					map[mouse_position.y - 1][mouse_position.x + 1].value = -1;
					map[mouse_position.y][mouse_position.x + 1].value = -1;
					map[mouse_position.y + 1][mouse_position.x + 1].value = -1;

					srand(time(NULL));
					i = 0;
					while (i < number_of_bombs)
					{
						put_bomb();
						i++;
					}
					map[mouse_position.y - 1][mouse_position.x - 1].value = 0;
					map[mouse_position.y][mouse_position.x - 1].value = 0;
					map[mouse_position.y + 1][mouse_position.x - 1].value = 0;
					map[mouse_position.y - 1][mouse_position.x].value = 0;
					map[mouse_position.y][mouse_position.x].value = 0;
					map[mouse_position.y + 1][mouse_position.x].value = 0;
					map[mouse_position.y - 1][mouse_position.x + 1].value = 0;
					map[mouse_position.y][mouse_position.x + 1].value = 0;
					map[mouse_position.y + 1][mouse_position.x + 1].value = 0;

					for (x = 1; x <= 16; x++)
						for (y = 1; y <= 30; y++)
							if (map[x][y].value != -1)
							{
								if (map[x - 1][y - 1].value == -1)
									map[x][y].value++;
								if (map[x][y - 1].value == -1)
									map[x][y].value++;
								if (map[x + 1][y - 1].value == -1)
									map[x][y].value++;
								if (map[x - 1][y].value == -1)
									map[x][y].value++;
								if (map[x + 1][y].value == -1)
									map[x][y].value++;
								if (map[x - 1][y + 1].value == -1)
									map[x][y].value++;
								if (map[x][y + 1].value == -1)
									map[x][y].value++;
								if (map[x + 1][y + 1].value == -1)
									map[x][y].value++;
							}

					ok = 1;
				}

				check_value(mouse_position.y, mouse_position.x);
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			while (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{

			}
			mouse_position = sf::Mouse::getPosition(window);
			mouse_position.x = mouse_position.x / 32 + 1;
			mouse_position.y = mouse_position.y / 32 + 1;
			map[mouse_position.y][mouse_position.x].flag = 1 - map[mouse_position.y][mouse_position.x].flag;
		}

		for (x = 1; x <= 16; x++)
		{
			for (y = 1; y <= 30; y++)
			{
				switch (map[x][y].hidden)
				{
				case 1:
					switch (map[x][y].flag)
					{
					case 1:
						sprite_flag.setPosition(sf::Vector2f((y - 1) * 32, (x - 1) * 32));
						window.draw(sprite_flag);
						break;
					case 0:
						sprite_unknown.setPosition(sf::Vector2f((y - 1) * 32, (x - 1) * 32));
						window.draw(sprite_unknown);
						break;
					}
					break;
				case 0:
					switch (map[x][y].value)
					{
					case -1:
						sprite_bomb.setPosition(sf::Vector2f((y - 1) * 32, (x - 1) * 32));
						window.draw(sprite_bomb);
						break;
					case 0:
						sprite_free.setPosition(sf::Vector2f((y - 1) * 32, (x - 1) * 32));
						window.draw(sprite_free);
						break;
					case 1:
						sprite_1.setPosition(sf::Vector2f((y - 1) * 32, (x - 1) * 32));
						window.draw(sprite_1);
						break;
					case 2:
						sprite_2.setPosition(sf::Vector2f((y - 1) * 32, (x - 1) * 32));
						window.draw(sprite_2);
						break;
					case 3:
						sprite_3.setPosition(sf::Vector2f((y - 1) * 32, (x - 1) * 32));
						window.draw(sprite_3);
						break;
					case 4:
						sprite_4.setPosition(sf::Vector2f((y - 1) * 32, (x - 1) * 32));
						window.draw(sprite_4);
						break;
					case 5:
						sprite_5.setPosition(sf::Vector2f((y - 1) * 32, (x - 1) * 32));
						window.draw(sprite_5);
						break;
					case 6:
						sprite_6.setPosition(sf::Vector2f((y - 1) * 32, (x - 1) * 32));
						window.draw(sprite_6);
						break;
					case 7:
						sprite_7.setPosition(sf::Vector2f((y - 1) * 32, (x - 1) * 32));
						window.draw(sprite_7);
						break;
					case 8:
						sprite_8.setPosition(sf::Vector2f((y - 1) * 32, (x - 1) * 32));
						window.draw(sprite_8);
						break;
					default:
						break;
					}
					break;
				default:
					break;
				}
			}
		}
		window.display();
	}

	return 0;
}