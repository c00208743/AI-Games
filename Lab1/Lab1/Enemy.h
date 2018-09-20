#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

class Enemy
{
public:
	Enemy();
	~Enemy();
	void update(double dt);
	void render(sf::RenderWindow & window);

private:
	sf::Vector2f m_position;
	sf::CircleShape m_enemy;
	sf::Vector2f m_velocity;
	int m_size;
};



