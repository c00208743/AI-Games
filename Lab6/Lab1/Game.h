#pragma once
#include "Tile.h"
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include <SFML/Graphics.hpp>
#include <string>     // std::string, std::to_string

class Game
{
public:
	Game();

	void run();

private:

	void update(double dt);
	void render();
	void processEvents();

	void checkTile();
	void costField();
	void vectorField();
	void restart();
	bool click = false;

	sf::RenderWindow m_window; // main SFML window
	//might need instance of tile
	static const int m_col = 50;
	static const int m_row = 50;
	static const int m_size = 25;
	Tile* m_grid[m_row][m_col];
	
	//recorded clicks 
	int mouseX = -2000;
	int mouseY = -2000;
	int mouseRX = -2000;
	int mouseRY = -2000;
	int middleX = -2000;
	int middleY = -2000;
	int tileX = -200;
	int tileY = -200;
	int rightMouseX = -2000;
	int rightMouseY = -2000;
	//cost field
	sf::Font m_font;
	sf::Text m_text;
	std::vector<sf::Text> v_text;	
	int index = 0;
	int ix = 0;
	int iy = 0;
	int costX = 0;
	int costY = 0;
	int realCost = 0;

	
};


