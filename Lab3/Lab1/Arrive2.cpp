#include "Arrive2.h"

Arrive2::Arrive2() :
	m_position(1200, 1300),
	m_velocity(0, 0),
	m_maxSpeed(0.5f),
	m_maxRotation(20.0f),
	m_timeToTarget(100.0f),
	radius(200.0f),
	m_threshold(30.0f)
{

	if (!m_font.loadFromFile("ALBA.TTF")) {
		//error
	}
	m_text.setFont(m_font);
	m_text.setFillColor(sf::Color::White);
	m_text.setCharacterSize(20);
	m_text.setString("Arrive");

	if (!m_texture.loadFromFile("seek.png")) {
		//error
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
	m_velocity.x = getRandom(20, -10);
	m_velocity.y = getRandom(20, -10);

	m_sprite.setOrigin(128, 128);

}


Arrive2::~Arrive2()
{

}

float Arrive2::getNewOrientation(float currentOrientation, float velocity)
{
	if (velocity >0)
	{
		return (std::atan2(-m_velocity.x, m_velocity.y) * 180.0 / 3.141592653589793238463);
	}
	else {
		return currentOrientation;
	}

}

void Arrive2::boundary(float x, float y)
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

float Arrive2::getRandom(int a, int b)
{
	srand(time(NULL));
	float randVal = rand() % a + b;
	return randVal;
}

void Arrive2::kinematicSeek(sf::Vector2f playerPosition)
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
	m_orientation = m_orientation + 180;

}
void Arrive2::kinematicArrive(sf::Vector2f playerPosition)
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
		m_orientation = m_orientation + 180;
	}

}

sf::Vector2f Arrive2::repulseSteering(std::vector<Enemy*> enemies)
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

void Arrive2::collison(std::vector<Enemy*> enemies)
{
	for (int i = 0; i < enemies.size(); i++)
	{
		n_direction = enemies[i]->getPosition() - m_position;
		n_distance = std::sqrt(n_direction.x*n_direction.x + n_direction.y* n_direction.y);

		if (n_distance <= radius)
		{
			float dot = (m_velocity.x * n_direction.x) + (m_velocity.y * n_direction.y);
			float det = (m_velocity.x * n_direction.y) - (m_velocity.y * n_direction.x);

			float angle = atan2(det, dot);
			angle = (180 / 3.14) * angle;


			if (angle >= -m_threshold && angle <= m_threshold)
			{
				crash = true;
				m_velocity = -m_velocity;
				m_orientation = -m_orientation;
				//std::cout << "Collided Arrive" << std::endl;

			}

		}
		if (crash == true && n_distance > radius)
		{
			crash = false;
		}
	}
}


sf::Vector2f Arrive2::getPosition()
{
	return m_sprite.getPosition();
}
sf::Vector2f Arrive2::getVelocity()
{
	return m_velocity;
}
sf::Vector2f Arrive2::normalise(sf::Vector2f norm)
{
	float length = sqrt((norm.x * norm.x) + (norm.y * norm.y));
	if (length != 0)
		return sf::Vector2f(norm.x / length, norm.y / length);
	else
		return norm;
}

void Arrive2::update(sf::Vector2f playerPosition, Player* player, std::vector<Enemy*> enemies)
{
	//kinematicArrive(playerPosition);
	//repulseSteering(enemies);
	collison(enemies);
	if (crash == false)
	{
		kinematicArrive(playerPosition);
	}

	m_position = m_position + m_velocity;

	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_orientation);
	m_text.setPosition(m_position);

	boundary(m_sprite.getPosition().x, m_sprite.getPosition().y);
}


void Arrive2::render(sf::RenderWindow & window)
{

	window.draw(m_sprite);
	window.draw(m_text);
}