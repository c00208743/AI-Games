#pragma once
#include "Player.h"
#include "Wander.h"
#include "Seek.h"
#include "Flee.h"
#include "Pursue.h"
#include "Arrive.h"
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();

	void run();

private:

	void update(double dt);
	void render();
	void processEvents();

	sf::RenderWindow m_window; // main SFML window
	Player* m_player;
	/*Wander* m_wander;
	Seek *m_seek;
	Flee *m_flee;
	Pursue *m_pursue;*/
	std::vector<Enemy*> enemies;

};


