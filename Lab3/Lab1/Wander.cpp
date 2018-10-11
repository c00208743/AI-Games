#include "Wander.h"
#include "Player.h"
#include "math.h"


#define M_PI   3.14159265358979323846264338327950288

Wander::Wander() :
	m_position(0, 0),
	m_velocity(0, 0),
	m_maxSpeed(0.5f)
{

	if (!m_font.loadFromFile("ALBA.TTF")) {
		//error
	}
	m_text.setFont(m_font);
	m_text.setFillColor(sf::Color::White);
	m_text.setCharacterSize(20);
	m_text.setString("Wander");
	
	if (!m_texture.loadFromFile("seek.png"))
	{
		// error...
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);

	m_velocity.x = getRandom(20, -10);
	m_velocity.y = getRandom(20, -10);
	m_sprite.setOrigin(128, 128);
}


Wander::~Wander()
{
}

void Wander::boundary(float x, float y)
{
	if (x > 2000)
	{
		m_position.x = 100;
	}
	if (x < 100)
	{
		m_position.x = 1900;
	}
	if (y < 100)
	{
		m_position.y = 1900;
	}
	if (y > 1900)
	{
		m_position.y = 100;
	}

}

void Wander::update(sf::Vector2f playerPosition, Player* player, std::vector<Enemy*> enemies)
{
	kinematicWander(playerPosition);
	repulseSteering(enemies);
	m_position = m_position + m_velocity;
	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_orientation);
	m_text.setPosition(m_position);
	boundary(m_sprite.getPosition().x, m_sprite.getPosition().y);
}

float Wander::getNewOrientation(float currentOrientation, float velocity)
{
	if (velocity >0)
	{
		return (std::atan2(-m_velocity.x, m_velocity.y) * 180.0 / M_PI);
	}
	else {
		return currentOrientation;
	}

}

float Wander::getRandom(int a, int b)
{
	srand(time(NULL));
	float randVal = rand() % a + b;
	return randVal;
}

sf::Vector2f Wander::getPosition()
{
	return m_sprite.getPosition();
}

sf::Vector2f Wander::getVelocity()
{
	return m_velocity;
}

void Wander::kinematicWander(sf::Vector2f playerPosition)
{
	m_velocity = playerPosition - m_position;

	//Get magnitude of vector
	m_velocityF = std::sqrt(m_velocity.x*m_velocity.x + m_velocity.y*m_velocity.y);

	//Normalize vector
	m_velocity.x = m_velocity.x / m_velocityF;
	m_velocity.y = m_velocity.y / m_velocityF;

	//get new orientation
	m_orientation = getNewOrientation(m_orientation, m_velocityF);

	//orientation = orientation + MaxRotation * random(-1, +1)
	m_orientation = m_orientation + maxRotation * getRandom(-1, 1);

	//Velocity = (-sin(orientation), cos(orientation))*maxSpeed
	m_velocity.x = (-sin(m_orientation))*m_maxSpeed;
	m_velocity.y = cos(m_orientation) *m_maxSpeed;
	

}

sf::Vector2f Wander::repulseSteering(std::vector<Enemy*> enemies)
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

sf::Vector2f Wander::normalise(sf::Vector2f norm)
{
	float length = sqrt((norm.x * norm.x) + (norm.y * norm.y));
	if (length != 0)
		return sf::Vector2f(norm.x / length, norm.y / length);
	else
		return norm;
}

void Wander::render(sf::RenderWindow & window)
{
	window.draw(m_sprite);
	window.draw(m_text);
}
