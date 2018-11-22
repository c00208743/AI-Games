#include "Game.h"
#include <list>

/// <summary>
/// @author JM
/// @version 1.0
/// 
/// </summary>

// Updates per milliseconds
static double const MS_PER_UPDATE = 10.0;

Game::Game()
	: m_window(sf::VideoMode(1250, 1250), "SFML Playground")

{
	m_window.setVerticalSyncEnabled(true);

	if (!m_font.loadFromFile("ALBA.TTF")) {
		//error
	}

	for (int i = 0; i < m_col; i++)
	{
		for (int j = 0; j < m_row; j++)
		{
			int random = rand() % 15 + 1;
			m_grid[j][i] = new Tile(i * m_size, j*m_size, m_font);
			if (random == 1) {
				m_grid[j][i]->id = 4;
			}
			if (i == 0) {
				m_grid[j][i]->id = 4;
			}
			if (j == 0) {
				m_grid[j][i]->id = 4;
			}
			if (i == 49) {
				m_grid[j][i]->id = 4;
			}
			if (j == 49) {
				m_grid[j][i]->id = 4;
			}
		}
	}
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

		if (event.type == sf::Event::MouseButtonPressed) {

			if (event.mouseButton.button == sf::Mouse::Left)
			{
				std::cout << "Click" << std::endl;
				//std::cout << "mouse x: " << event.mouseButton.x << std::endl;
				//std::cout << "mouse y: " << event.mouseButton.y << std::endl;
				mouseX = event.mouseButton.x;
				mouseY = event.mouseButton.y;
				checkTile();

			}
			if (event.mouseButton.button == sf::Mouse::Right)
			{
				std::cout << "Right Click" << std::endl;
				mouseRX = event.mouseButton.x;
				mouseRY = event.mouseButton.y;
				checkTile();
				//costfield();
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
			{
				std::cout << "Middle Click" << std::endl;
				middleX = event.mouseButton.x;
				middleY = event.mouseButton.y;
				checkTile();
			}
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			restart();
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
	srand(time(NULL));
	for (int i = 0; i < m_col; i++)
	{
		for (int j = 0; j < m_row; j++)
		{
			m_grid[i][j]->update();
		}

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
	for (int i = 0; i < m_col; i++)
	{
		for (int j = 0; j < m_row; j++)
		{
			m_grid[i][j]->render(m_window);
		}

	}
	for (int i = 0; i < v_text.size(); i++) {
		m_window.draw(v_text[i]);
	}
	m_window.display();
}

/// <summary>
/// 
/// </summary>
void Game::checkTile()
{
	for (int i = 0; i < m_col; i++)
	{
		for (int j = 0; j < m_row; j++)
		{
			//m_grid[j][i] = new Tile(i * m_size, j*m_size);
			if (mouseX > i* m_size && mouseX < (i * m_size) + m_size
				&& mouseY > j* m_size && mouseY < (j * m_size) + m_size) {
				if (click == false) {
					ix = i;
					iy = j;
					costField();
					vectorField();
					//picked
					m_grid[j][i]->id = 2;
					m_grid[j][i]->setCost(0);
					click = true;
				}

			}

			
			if (mouseRX > i* m_size && mouseRX < (i * m_size) + m_size
				&& mouseRY > j* m_size && mouseRY < (j * m_size) + m_size) {

				m_grid[j][i]->id = 3;
				std::cout << "mouse x: " << i << std::endl;
				std::cout << "mouse y: " << j << std::endl;
			}
			if (middleX > i* m_size && middleX < (i * m_size) + m_size
				&& middleY > j* m_size && middleY < (j * m_size) + m_size) {

				m_grid[j][i]->id = 4;
				m_grid[j][i]->setCost(999);
				std::cout << "mouse x: " << i << std::endl;
				std::cout << "mouse y: " << j << std::endl;
			}

		}
	}
}

/// <summary>
/// 
/// </summary>
void Game::costField()
{

	for (int i = 0; i < m_col; i++)
	{
		for (int j = 0; j < m_row; j++)
		{

			//if wall
			if (m_grid[j][i]->id == 4) {
				m_grid[j][i]->setCost(999);
			}


			if (m_grid[j][i]->id == 1) {
				costX = ix - i;
				costY = iy - j;
				realCost = costX + costY;


				////index == ix , iy
				if (ix> i && iy> j) {
					realCost = costX + costY;
				}
				if (ix < i && iy< j) {
					realCost = costX + costY;
				}

				//index == ix , iy
				if (ix> i && iy< j) {
					realCost = costX - costY;
				}
				if (ix < i && iy> j) {
					realCost = costX - costY;
				}


				if (realCost == 0 && costX > costY) {
					realCost = costX *2;
				}
				if (realCost == 0 && costX < costY) {
					realCost = costY *2;
				}

				if (realCost < 0) {
					realCost = realCost * -1;
				}

				m_grid[j][i]->setCost(realCost);
				//
				int heatMap=0;
				heatMap = realCost * 5;
				if (heatMap > 255) {
					heatMap = 255;
				}
				m_grid[j][i]->rect.setFillColor(sf::Color(255, heatMap, 255));
			}
			

		}
	}
}
/// <summary>
/// 
/// </summary>
void Game::vectorField()
{
	for (int i = 0; i < m_col; i++)
	{
		for (int j = 0; j < m_row; j++)
		{
			if (m_grid[i][j]->id == 1) {
				//vector
				int up = 0;
				int down = 0;
				int right = 0;
				int left = 0;


				//get cost in four directions
				up = m_grid[i - 1][j]->getCost();
				right = m_grid[i][j + 1]->getCost();
				down = m_grid[i + 1][j]->getCost();
				left = m_grid[i][j - 1]->getCost();

				//first four direction
				if (up < down && up < left && up < right) {
					m_grid[i][j]->setRotation(270);
				}
				if (left < down && left < up && left <right) {
					m_grid[i][j]->setRotation(180);
				}
				if (down < up && down < left && down < right) {
					m_grid[i][j]->setRotation(90);
				}
				if (right < up && right < left && right < down) {
					m_grid[i][j]->setRotation(0);
				}

				// some values are the same 
				costX = ix - i;
				costY = iy - j;
				realCost = costX + costY;


				////index == ix , iy
				if (ix> i && iy> j) {
					if (left == up) {
						if (down >= right) {
							m_grid[i][j]->setRotation(0);
						}
						else
						{
							m_grid[i][j]->setRotation(90);
						}
					}
				}
				if (ix < i && iy< j) {
					if (right == down) {
						if (up >= left) {
							m_grid[i][j]->setRotation(180);
						}
						else {
							m_grid[i][j]->setRotation(90);
						}
						
					}
				}

				////index == ix , iy
				if (ix> i && iy< j) {
					if (right == up ) {
						if (up >= left) {
							m_grid[i][j]->setRotation(180);
						}
						else {
							m_grid[i][j]->setRotation(270);
						}
					}
				}

				if (ix < i && iy> j) {
					if (left == down ) {
						if (up >= right) {
							m_grid[i][j]->setRotation(0);
						}
						else {
							m_grid[i][j]->setRotation(270);
						}
						
					}
				}
			}

		}
	}
}
/// <summary>
/// 
/// </summary>
void Game::restart()
{
	click = false;
	std::cout << "restart" << std::endl;
	for (int i = 0; i < m_col; i++)
	{
		for (int j = 0; j < m_row; j++)
		{
			m_grid[j][i]->id = 1;
		}
	}

	for (int i = 0; i < m_col; i++)
	{
		for (int j = 0; j < m_row; j++)
		{
			int random = rand() % 15 + 1;
			m_grid[j][i] = new Tile(i * m_size, j*m_size, m_font);
			if (random == 1) {
				m_grid[j][i]->id = 4;
			}
			if (i == 0) {
				m_grid[j][i]->id = 4;
			}
			if (j == 0) {
				m_grid[j][i]->id = 4;
			}
			if (i == 49) {
				m_grid[j][i]->id = 4;
			}
			if (j == 49) {
				m_grid[j][i]->id = 4;
			}
		}
	}
}


