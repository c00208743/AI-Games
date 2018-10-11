#include "Game.h"

/// <summary>
/// @author JM
/// @version 1.0
/// 
/// </summary>

// Updates per milliseconds
static double const MS_PER_UPDATE = 10.0;

Game::Game()
	: m_window(sf::VideoMode(2000, 2000), "SFML Playground")

{
	m_window.setVerticalSyncEnabled(true);

	m_player = new Player();

	Enemy* m_wander = new Wander();
	Enemy* m_seek = new Seek();
	Enemy* m_flee = new Flee();
	Enemy* m_pursue = new Pursue();
	Enemy* m_arrive = new Arrive();

	enemies.push_back(m_wander);
	enemies.push_back(m_seek);
	enemies.push_back(m_flee);
	enemies.push_back(m_arrive);
	enemies.push_back(m_arrive);
	enemies.push_back(m_pursue);

}


/// <summary>
/// Main game entry point - runs untfil user quits.
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Int32 lag = 0;

	while (m_window.isOpen())
	{
		sf::Time dt = clock.restart();

		lag += dt.asMilliseconds();

		processEvents();

		while (lag > MS_PER_UPDATE)
		{
			update(MS_PER_UPDATE);
			lag -= MS_PER_UPDATE;
		}
		update(MS_PER_UPDATE);

		render();
	}
}



/// <summary>
/// @brief Check for events
/// 
/// Allows window to function and exit. 
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		
	}
}

/// <summary>
/// Method to handle all game updates
/// </summary>
/// <param name="time">update delta time</param>
void Game::update(double dt)
{
	sf::Time deltaTime;
	m_player->update(dt);


	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->update(m_player->getPosition(), m_player, enemies);
	}
}


/// <summary>
/// @brief draw the window for the game.
/// 
/// draw buttons and text on left side
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0));
	m_player->render(m_window);
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->render(m_window);
	}
	m_window.display();
}

