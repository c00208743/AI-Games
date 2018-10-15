#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Enemy.h"

class Wander : public Enemy
{
public:
	Wander();
	~Wander();
	void update(sf::Vector2f playerPosition, Player* player, std::vector<Enemy*> enemies);
	void render(sf::RenderWindow & window);
	void boundary(float x, float y);
	void kinematicWander(sf::Vector2f playerPosition);
	float getNewOrientation(float currentOrientation, float velocity);
	float getRandom(int x, int y);
	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	sf::Vector2f repulseSteering(std::vector<Enemy*> enemies);
	sf::Vector2f normalise(sf::Vector2f norm);
	void collison(std::vector<Enemy*> enemies);


private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	float m_velocityF;
	float m_orientation;
	float m_maxSpeed;
	int m_size;
	double speed = 0.3;
	double maxRotation = 180;

	//Lab2
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Font m_font;
	sf::Text m_text;

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
	float radius;
	float relativeSpeed = 0;
	float maxAcceleration = 3;
	double timeToCollision = 0;
	double minSeparation = 0;

	//cone of vision
	sf::Vector2f n_direction;
	float n_orientation;
	double n_distance = 0;
	float m_threshold;
	bool crash = false;
};



