#include "Tile.h"
#include <iostream>
#include "math.h"


#define M_PI   3.14159265358979323846264338327950288

Tile::Tile(float x, float y, sf::Font &font) :
	m_position(x, y)
{

	m_text.setFont(font);

	m_text.setString("");
	m_text.setFillColor(sf::Color::Black);
	m_text.setPosition(x, y);
	m_text.setCharacterSize(10);

	rect.setSize(sf::Vector2f(size, size));
	rect.setOutlineColor(sf::Color::Red);
	rect.setOutlineThickness(1);
	rect.setPosition(x, y);

	vector.setSize(sf::Vector2f(1, 1));
	vector.setOutlineColor(sf::Color::Black);
	vector.setFillColor(sf::Color::Black);
	vector.setOutlineThickness(1);
	vector.setPosition(x - (size/2), y - (size/2) );



}

Tile::~Tile()
{
	
}

/// <summary>
/// Update the tile object
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Tile::update()
{
	if (id == 2) {
		//start
		rect.setFillColor(sf::Color::Red);
	}
	else if (id == 3) {
		//end
		rect.setFillColor(sf::Color::Green);
	}
	else if (id == 4) {
		//wall
		rect.setFillColor(sf::Color::Blue);
	}
}

void Tile::render(sf::RenderWindow & window)
{ 
	window.draw(rect);
	window.draw(m_text);
	window.draw(vector);
}

int Tile::getId()
{
	return id;
}

void Tile::setCost(int m_cost)
{
	cost = m_cost;
	m_text.setString(std::to_string(cost));

}

int Tile::getCost()
{
	return cost;

}
void Tile::setRotation(int rot)
{
	rotation = rot;
	vector.setRotation(rotation);
	vector.setSize(sf::Vector2f(12.5f, 1));
}
