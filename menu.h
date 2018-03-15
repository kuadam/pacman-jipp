#pragma once
#include <SFML/Graphics.hpp>

class Menu
{
	sf::Font font_;
	std::vector<sf::Text> tekst_;
	std::vector<sf::Text> tekst_s_;
	bool start_ = false;
	int wybrany_ = 0;
	int level_ = 1; // 1-1lvl 2-2lvl
	bool restart_ = false;

public:
	Menu(sf::Font &font);
	void update(sf::RenderWindow& window);

	int getLevel() const { return level_; }
	bool restart() const { return restart_; }
	void setRestartFalse() { restart_ = false; }
};