#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Player.h"

class Pursue
{
public:
	Pursue();
	~Pursue();
	float getNewOrientation(float currentOrientation, float velocity);
	void kinematicSeek(sf::Vector2f playerPosition);
	void kinematicArrive(sf::Vector2f playerPosition);
	void boundary(float x, float y);
	float getRandom(int x, int y);
	void update(sf::Vector2f playerPosition, Player* player);
	void render(sf::RenderWindow & window);
	//Lab3
	void pursue(Player* player);


private:
	float m_timeToTarget;
	float m_orientation;
	float m_rotation;
	float m_velocityF;
	float m_maxSpeed;
	float m_maxRotation;
	float distance;
	float speed;
	float maxTimePrediction;
	float timePrediction;
	sf::Vector2f m_velocity;
	sf::Vector2f m_position;

	//Lab3 
	sf::Vector2f direction;
	sf::Vector2f newTarget;

	Player* player;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
};