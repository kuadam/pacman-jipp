#pragma once
#include <SFML/Graphics.hpp>
#include  "postac.h"
#include <iostream>
#include "map.h"
#include "SFML/Audio.hpp"

class Pacman :Postac
{
private:
	sf::Vector2f pozycja_startowa_ = sf::Vector2f(601, 451);

	bool otwarty_ = 0;
	int hp_ = 3;
	int pkt_ = 0;


	int poprzedni_kierunek_ = 0;
	int kierunek_ = 2;	// gora 0 dol 1 lewo 2 prawo 3

public:
	Pacman();

	sf::Sprite getSprite() const { return sprite_; }
	sf::RectangleShape getRect() const { return rect_; }

	int getHp() const { return hp_; };
	void changeHp(int n);
	void setHp(int n) { hp_ = std::move(n); }

	int getPkt() const { return pkt_; };
	void changePkt(int n);

	int getDirection() const { return kierunek_; }

	sf::Vector2f getStartPos() const { return pozycja_startowa_; }
	void setPosition(sf::Vector2f pos);

	sf::Vector2f getRectCenter() const { return sf::Vector2f(rect_.getPosition().x + rect_.getGlobalBounds().width / 2, rect_.getPosition().y + rect_.getGlobalBounds().height / 2); }

	bool czy_wrazliwy() const { return wrazliwosc_; }

	void stop() { speed_ = 0; }
	void start() { speed_ = default_speed_; }
	void update(sf::Time time, std::shared_ptr<Map> mapa);
};
