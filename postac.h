#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class Postac
{
protected:
	sf::RectangleShape rect_;
	sf::Sprite sprite_;
	std::shared_ptr<sf::Texture> texture_ = std::make_shared<sf::Texture>();

	int licznik_ = 0;
	int kierunek_ = 0;// gora 0 dol 1 lewo 2 prawo 3
	float default_speed_ = 0.2;
	float speed_ = default_speed_;
	bool wrazliwosc_ = true;

	int lastTileX_;
	int lastTileY_;
};
