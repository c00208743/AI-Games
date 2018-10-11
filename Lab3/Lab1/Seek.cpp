#include "Seek.h"

Seek::Seek() :
	m_position(800, 500),
	m_velocity(0, 0),
	m_maxSpeed(0.5f),
	m_maxRotation(20.0f),
	m_timeToTarget(100.0f)
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


Seek::~Seek()
{

}

float Seek::getNewOrientation(float currentOrientation, float velocity)
{
	if (velocity >0)
	{
		return (std::atan2(-m_velocity.x, m_velocity.y) * 180.0 / 3.141592653589793238463);
	}
	else {
		return currentOrientation;
	}

}

void Seek::boundary(float x, float y)
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

float Seek::getRandom(int a, int b)
{
	srand(time(NULL));
	float randVal = rand() % a + b;
	return randVal;
}

void Seek::kinematicSeek(sf::Vector2f playerPosition)
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
void Seek::kinematicArrive(sf::Vector2f playerPosition)
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

sf::Vector2f Seek::repulseSteering(std::vector<Enemy*> enemies)
{
	firstTarget = sf::Vector2f(NULL, NULL);
	for (int i = 0; i < enemies.size(); i++)
	{
		//relativePos = target.position - character.position
		relativePos = enemies[i]->getPosition() - m_position;
		//relativeVel = target.velocity - character.velocity
		relativeVel = enemies[i]->getVelocity() - m_velocity;
		//relativeSpeed = relativeVel.length()
		relativeSpeed = std::sqrt(relativeVel.x*relativeVel.x + relativeVel.y* relativeVel.y);

		//timeToCollision = (relativePos . relativeVel) / (relativeSpeed * relativeSpeed)
		timeToCollision = ((relativePos.x * relativeVel.x) + (relativePos.y * relativeVel.y)) / (relativeSpeed * relativeSpeed);

		// distance = relativePos.length()
		distance = std::sqrt(relativePos.x*relativePos.x + relativePos.y* relativePos.y);
		//minSeparation = distance – relativeSpeed * shortestTime
		minSeparation = distance - (relativeSpeed * shortestTime);

		if (minSeparation > 2 * radius) {

			if (timeToCollision > 0 && timeToCollision < shortestTime) {
				shortestTime = timeToCollision;
				firstTarget = enemies[i]->getPosition();
				firstMinSeparation = minSeparation;
				firstDistance = distance;
				firstRelativePos = relativePos;
				firstRelativeVel = relativeVel;
			}
		}

		
	}
	if (firstTarget == sf::Vector2f(NULL, NULL)) {
		return sf::Vector2f();
		//break;
	}
		
	if (firstMinSeparation <= 0 || distance <2 * radius)
	{
		relativePos = firstTarget - m_position;
		std::cout << "dirk" << std::endl;
	}
	else {
		relativePos.x = firstRelativePos.x + firstRelativeVel.x * shortestTime;
		relativePos.y = firstRelativePos.y + firstRelativeVel.y * shortestTime;
	}

	normalise(relativePos);
	steering = relativePos * maxAcceleration;
	return steering;
}

sf::Vector2f Seek::getPosition()
{
	return m_sprite.getPosition();
}
sf::Vector2f Seek::getVelocity()
{
	return m_velocity;
}
sf::Vector2f Seek::normalise(sf::Vector2f norm)
{
	float length = sqrt((norm.x * norm.x) + (norm.y * norm.y));
	if (length != 0)
		return sf::Vector2f(norm.x / length, norm.y / length);
	else
		return norm;
}

void Seek::update(sf::Vector2f playerPosition, Player* player, std::vector<Enemy*> enemies)
{
	kinematicArrive(playerPosition);
	repulseSteering(enemies);

	m_position = m_position + m_velocity;

	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_orientation);

	boundary(m_sprite.getPosition().x, m_sprite.getPosition().y);
}


void Seek::render(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}