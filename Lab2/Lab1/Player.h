#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Player
{
public:
	Player();
	~Player();
	void update(double dt);
	void render(sf::RenderWindow & window);
	
private:

	sf::Vector2f m_position;
	sf::CircleShape m_shape;
	sf::Vector2f m_velocity;
	sf::Vector2f direction;
	int size;
	float orientation;
	float rotation;
	double speed;

	//Lab2
	sf::Texture texture;
	sf::Sprite sprite;

};
