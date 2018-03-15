#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include  "postac.h"
#include <memory>
#include "losuj.h"
#include "map.h"

class Duch :Postac
{
	int kolor_;
	bool kolor_wrazliwosci = 0;
	sf::Vector2f pozycja_startowa_ = sf::Vector2f(600, 350);

	float default_speed_ = 0.22;
	float speed_ = default_speed_;

	int timer_ = 0;
	bool zjedzony_ = false;

	sf::Clock czas_;
	sf::Clock zjedz_clock_;
	sf::Clock wrazliwy_clock_;
public:
	Duch();
	void setTexture(std::shared_ptr<sf::Texture> texture);

	sf::Sprite getSprite() const { return sprite_; }
	sf::RectangleShape getRect() const { return rect_; }
	
	sf::Vector2f getStartPos() const { return pozycja_startowa_; }
	void setPosition(sf::Vector2f pos);
	
	void setColor(int kolor);

	bool czy_wrazliwy() const { return wrazliwosc_; }
	void ustaw_wrazliwosc(bool wrazliwosc) { wrazliwosc_ = std::move(wrazliwosc); }
	void zjedzony();

	void setTime(int x) { czas_.restart(); };
	void stop() { speed_ = 0; }
	void start() { speed_ = default_speed_; }

	void update(sf::Time time, std::shared_ptr<Map> mapa);
};
