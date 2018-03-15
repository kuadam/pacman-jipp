#include "map.h"


Map::Map()
{
	if (!texture_->loadFromFile("data/map.png"))
	{
		std::cout << "Nie mozna wczytac tekstury mapy" << std::endl;
	}
	tile_.setTexture(*texture_);
	tile_.setTextureRect(sf::IntRect(50, 0, 50, 50));
}

void Map::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < mapa_->size(); i++)
	{
		for (int j = 0; j < (*mapa_)[i].size(); j++)
		{
			tile_.setPosition(j * 50, i * 50);
			if ((*mapa_)[i][j] != -1)
			{
				tile_.setTextureRect(sf::IntRect(50 * (*mapa_)[i][j], 0, 50, 50));
				window.draw(tile_);
			}
		}
	}
}

void Map::setLevel(const int &lvl)
{
	if(lvl==1)
	{
		mapa_= std::make_shared<std::vector<std::vector<int>>>(uklad_mapy_);
	}
	else if (lvl == 2)
	{
		mapa_ = std::make_shared<std::vector<std::vector<int>>>(uklad_mapy2_);
	}
}

void Map::setPositionTile(int x, int y)
{
	tile_.setPosition(std::move(x),std::move(y));
}

void Map::TileTextureRect(sf::IntRect x)
{
	tile_.setTextureRect(std::move(x));
}

void Map::zebrano_punkt( int x, int y)
{
		(*mapa_)[x][y] = -1;
}

