#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Player.h"
#include "Enemy.h"

class Pursue : public Enemy
{
public:
	Pursue();
	~Pursue();
	float getNewOrientation(float currentOrientation, float velocity);
	void kinematicSeek(sf::Vector2f playerPosition);
	void kinematicArrive(sf::Vector2f playerPosition);
	void boundary(float x, float y);
	float getRandom(int x, int y);
	void update(sf::Vector2f playerPosition, Player* player, std::vector<Enemy*> enemies);
	void render(sf::RenderWindow & window);
	//Lab3
	void pursue(Player* player);
	 sf::Vector2f getPosition();
	 sf::Vector2f getVelocity();
	 sf::Vector2f repulseSteering(std::vector<Enemy*> enemies);
	 sf::Vector2f normalise(sf::Vector2f norm);


private:
	float m_timeToTarget;
	float m_orientation;
	float m_rotation;
	float m_velocityF;
	float m_maxSpeed;
	float m_maxRotation;
	float m_distance;
	float speed;
	float maxTimePrediction;
	float timePrediction;
	sf::Vector2f m_velocity;
	sf::Vector2f m_position;
	sf::Font m_font;
	sf::Text m_text;

	//Lab3 
	sf::Vector2f direction;
	sf::Vector2f newTarget;

	Player* player;
	sf::Sprite m_sprite;
	sf::Texture m_texture;

	//cone of vision
	//double shortestTime = std::numeric_limits<double>::infinity();
	double shortestTime = 2000;
	sf::Vector2f firstTarget;
	sf::Vector2f firstRelativePos;
	sf::Vector2f firstRelativeVel;
	sf::Vector2f relativePos;
	sf::Vector2f relativeVel;
	sf::Vector2f steering;
	double firstMinSeparation = 0;
	double firstDistance = 0;
	double distance = 0;
	float radius = 300;
	float relativeSpeed = 0;
	float maxAcceleration = 3;
	double timeToCollision = 0;
	double minSeparation = 0;
};