#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

class Flee
{
public:
	Flee();
	~Flee();
	void kinematicFlee(sf::Vector2f playerPosition);
	float getNewOrientation(float currentOrientation, float velocity);
	float getRandom(int x, int y);
	void boundry(float x, float y);
	
	void update(sf::Vector2f playerPosition);
	void render(sf::RenderWindow & window);

private:
	float m_timeToTarget;
	float m_orientation;
	float m_rotation;
	float m_velocityF;
	float m_maxSpeed;
	float m_maxRotation;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::Vector2f m_velocity;
	sf::Vector2f m_position;
};
