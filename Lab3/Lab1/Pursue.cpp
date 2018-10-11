#include "Pursue.h"

Pursue::Pursue() :
	m_position(500, 500),
	m_velocity(0, 0),
	m_maxSpeed(1.0f),
	m_maxRotation(20.0f),
	m_timeToTarget(100.0f),
	maxTimePrediction(250.0f)
{

	if (!m_texture.loadFromFile("seek.png")) {
		//error
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
	m_sprite.setScale(0.4, 0.4);
	m_velocity.x = getRandom(20, -10);
	m_velocity.y = getRandom(20, -10);

	m_sprite.setOrigin(m_position.x - (m_sprite.getTextureRect().width / 2), m_position.y - (m_sprite.getTextureRect().height / 2));

}


Pursue::~Pursue()
{

}

float Pursue::getNewOrientation(float currentOrientation, float velocity)
{
	if (velocity >0)
	{
		return (std::atan2(-m_velocity.x, m_velocity.y) * 180.0 / 3.141592653589793238463);
	}
	else {
		return currentOrientation;
	}

}

void Pursue::boundary(float x, float y)
{
	if (x > 2100)
	{
		m_position.x = -100;
	}
	if (x < -100)
	{
		m_position.x = 2100;
	}
	if (y < -100)
	{
		m_position.y = 2100;
	}
	if (y > 2100)
	{
		m_position.y = -100;
	}

}

float Pursue::getRandom(int a, int b)
{
	srand(time(NULL));
	float randVal = rand() % a + b;
	return randVal;
}

void Pursue::kinematicSeek(sf::Vector2f playerPosition)
{
	m_velocity = playerPosition - m_position;
	//Get magnitude of vector
	m_velocityF = std::sqrt(m_velocity.x*m_velocity.x + m_velocity.y* m_velocity.y);

	//Normalize vector
	m_velocity.x = m_velocity.x / m_velocityF;
	m_velocity.y = m_velocity.y / m_velocityF;

	m_velocity.x = m_velocity.x * m_maxSpeed;
	m_velocity.y = m_velocity.y * m_maxSpeed;

	m_orientation = getNewOrientation(m_orientation, m_velocityF);

}

void Pursue::kinematicArrive(sf::Vector2f playerPosition)
{
	//Get magnitude of vector
	m_velocityF = std::sqrt(m_velocity.x*m_velocity.x + m_velocity.y* m_velocity.y);

	m_velocity = playerPosition - m_position;

	if (m_velocityF >= 0)
	{
		m_velocity = m_velocity / m_timeToTarget;

		if (m_velocityF > m_maxSpeed) {

			//Normalize vector
			m_velocity.x = m_velocity.x / m_velocityF;
			m_velocity.y = m_velocity.y / m_velocityF;
			m_velocity = m_velocity * m_maxSpeed;

		}

		m_orientation = getNewOrientation(m_orientation, m_velocityF);
	}

}

void Pursue::pursue(Player* player)
{
	direction = player->getPosition() -m_position;
	distance = std::sqrt(direction.x*direction.x + direction.y* direction.y);
	speed = std::sqrt(m_velocity.x*m_velocity.x + m_velocity.y* m_velocity.y);
	//std::cout << maxTimePrediction << std::endl;

	if (speed <= distance / maxTimePrediction )
	{
		timePrediction = maxTimePrediction;
	}
	else {
		timePrediction = distance / speed;
	}
	
	newTarget = player->getPosition() + player->getVelocity() * timePrediction;
	
	//kinematicSeek(newTarget);
	kinematicArrive(newTarget);
}

sf::Vector2f Pursue::getPosition()
{
	return m_sprite.getPosition();
}
sf::Vector2f Pursue::getVelocity()
{
	return m_velocity;
}

void Pursue::update(sf::Vector2f playerPosition, Player* player, std::vector<Enemy*> enemies)
{
	pursue(player);

	m_position = m_position + m_velocity;

	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_orientation);

	boundary(m_sprite.getPosition().x, m_sprite.getPosition().y);
}


void Pursue::render(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}