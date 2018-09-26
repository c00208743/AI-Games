#pragma once
#include "Player.h"
#include "Enemy.h"
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
	Enemy* m_enemy;

};


