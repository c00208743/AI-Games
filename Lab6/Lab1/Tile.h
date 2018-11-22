#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Tile
{
public:
	Tile(float x, float y, sf::Font &font);
	~Tile();
	void update();
	void render(sf::RenderWindow & window);

	int getId();
	void setCost(int m_cost);
	int getCost();
	void setRotation(int rot);
	
	sf::RectangleShape rect;
	int row = 50;
	int col = 50;
	float size = 25;
	int cost = 0;
	int id = 1;
	int rotation = 0;

private:
	sf::Vector2f m_position;
	sf::Text m_text;
	sf::RectangleShape vector;

};
