#include "duch.h"

Duch::Duch()
{
	rect_.setSize(sf::Vector2f(48, 48));
	rect_.setFillColor(sf::Color::Green);
	rect_.setPosition(pozycja_startowa_);
	sprite_.setPosition(rect_.getPosition());
	lastTileX_ = rect_.getPosition().x / 50;
	lastTileY_ = rect_.getPosition().y / 50;
	czas_.restart();
	zjedz_clock_.restart();
	wrazliwy_clock_.restart();
}

void Duch::setPosition(sf::Vector2f pos)
{
	rect_.setPosition(std::move(pos));
	sprite_.setPosition(rect_.getPosition());
	wrazliwosc_ = true;
}

void Duch::setColor(int kolor)
{
	kolor_ = std::move(kolor);
	sprite_.setTextureRect(sf::IntRect(2 * 48, 48 * kolor_, 48, 48));
}

void Duch::zjedzony()
{
	this->setPosition(pozycja_startowa_);
	zjedzony_ = true;
}

void Duch::setTexture(std::shared_ptr<sf::Texture> texture)
{
	texture_ = texture;
	sprite_.setTexture(*texture_);
}

void Duch::update(sf::Time time, std::shared_ptr<Map> mapa)
{
	//predkosc ruchu z uwzglednieniem czasu
	float tempSpeed = speed_*time.asMilliseconds();

	// kolizja z mapa
	int PunktX1, PunktY1;
	{
		if (kierunek_ == 0)
		{
			PunktX1 = rect_.getPosition().x / 50;
			PunktY1 = (rect_.getPosition().y + rect_.getLocalBounds().height) / 50;

			if (lastTileX_ != PunktX1 || lastTileY_ != PunktY1)
			{
				if (mapa->Point(PunktY1, PunktX1 - 1) != 2 && mapa->Point(PunktY1, PunktX1 + 1) != 2) //klocki po lewej i prawej nie sa scianami
				{
					if (mapa->Point(PunktY1 - 1, PunktX1) != 2)//klocek nad nie jest sciana
					{
						kierunek_ = losuj3(0, 2, 3); //wybor kierunku dol lewo prawo
					}
					else
					{
						kierunek_ = losuj3(1, 2, 3);
					}
				}
				else if (mapa->Point(PunktY1, PunktX1 - 1) != 2) //klocek po lewej nie jest sciana
				{
					if (mapa->Point(PunktY1 - 1, PunktX1) != 2)//klocek nad nie jest sciana
					{
						kierunek_ = losuj(0, 2);
					}
					else
					{
						kierunek_ = 2;
					}
				}
				else if (mapa->Point(PunktY1, PunktX1 + 1) != 2) //klocek po prawej nie jest sciana
				{
					if (mapa->Point(PunktY1 - 1, PunktX1) != 2)//klocek nad nie jest sciana
					{
						kierunek_ = losuj(0, 3);
					}
					else
					{
						kierunek_ = 3;
					}

				}
				else if (mapa->Point(PunktY1, PunktX1 - 1) == 2 && mapa->Point(PunktY1, PunktX1 + 1) == 2 && mapa->Point(PunktY1 - 1, PunktX1) == 2)//zaulek
				{
					kierunek_ = 1;
				}
				lastTileX_ = PunktX1;
				lastTileY_ = PunktY1;
			}
		}

		else if (kierunek_ == 1)
		{
			PunktX1 = rect_.getPosition().x / 50;
			PunktY1 = rect_.getPosition().y / 50;
			if (lastTileX_ != PunktX1 || lastTileY_ != PunktY1)
			{
				if (mapa->Point(PunktY1, PunktX1 - 1) != 2 && mapa->Point(PunktY1, PunktX1 + 1) != 2) //klocki po lewej i prawej nie sa scianami
				{
					if (mapa->Point(PunktY1 + 1, PunktX1) != 2)//klocek pod nie jest sciana
					{
						kierunek_ = losuj3(1, 2, 3); //wybor kierunku gora lewo prawo
					}
					else
					{
						kierunek_ = losuj3(0, 2, 3);
					}
				}
				else if (mapa->Point(PunktY1, PunktX1 - 1) != 2) //klocek po lewej nie jest sciana
				{
					if (mapa->Point(PunktY1 + 1, PunktX1) != 2)//klocek pod nie jest sciana
					{
						kierunek_ = losuj(1, 2);
					}
					else
					{
						kierunek_ = 2;
					}
				}
				else if (mapa->Point(PunktY1, PunktX1 + 1) != 2) //klocek po prawej nie jest sciana
				{
					if (mapa->Point(PunktY1 + 1, PunktX1) != 2)//klocek pod nie jest sciana
					{
						kierunek_ = losuj(1, 3);
					}
					else
					{
						kierunek_ = 3;
					}

				}
				else if (mapa->Point(PunktY1, PunktX1 - 1) == 2 && mapa->Point(PunktY1, PunktX1 + 1) == 2 && mapa->Point(PunktY1 + 1, PunktX1) == 2)//zaulek
				{
					kierunek_ = 0;
				}
				lastTileX_ = PunktX1;
				lastTileY_ = PunktY1;
			}

		}

		else if (kierunek_ == 2)
		{
			PunktX1 = (rect_.getPosition().x + rect_.getLocalBounds().width) / 50;
			PunktY1 = (rect_.getPosition().y) / 50;
			if (lastTileX_ != PunktX1 || lastTileY_ != PunktY1)
			{
				if (mapa->Point(PunktY1 - 1, PunktX1) != 2 && mapa->Point(PunktY1 + 1, PunktX1) != 2) //klock nad i pod nie sa scianami
				{
					if (mapa->Point(PunktY1, PunktX1 - 1) != 2)//klocek po lewo nie jest sciana
					{
						kierunek_ = losuj3(2, 0, 1); //wybor kierunku lewo dol gora
					}
					else
					{
						kierunek_ = losuj3(3, 0, 1);
					}
				}
				else if (mapa->Point(PunktY1 + 1, PunktX1) != 2) //klocek po pod nie jest sciana
				{
					if (mapa->Point(PunktY1, PunktX1 - 1) != 2)//klocek po lewo nie jest sciana
					{
						kierunek_ = losuj(2, 1);
					}
					else
					{
						kierunek_ = 1;
					}
				}
				else if (mapa->Point(PunktY1 - 1, PunktX1) != 2) //klocek nad nie jest sciana
				{
					if (mapa->Point(PunktY1, PunktX1 - 1) != 2)//klocek po lewo nie jest sciana
					{
						kierunek_ = losuj(2, 0);
					}
					else
					{
						kierunek_ = 0;
					}

				}
				else if (mapa->Point(PunktY1 - 1, PunktX1) == 2 && mapa->Point(PunktY1 + 1, PunktX1) == 2 && mapa->Point(PunktY1, PunktX1 - 1) == 2)//zaulek
				{
					kierunek_ = 3;
				}
				lastTileX_ = PunktX1;
				lastTileY_ = PunktY1;
			}
		}

		else if (kierunek_ == 3)
		{
			PunktX1 = rect_.getPosition().x / 50;
			PunktY1 = rect_.getPosition().y / 50;

			if (lastTileX_ != PunktX1 || lastTileY_ != PunktY1)
			{
				if (mapa->Point(PunktY1 - 1, PunktX1) != 2 && mapa->Point(PunktY1 + 1, PunktX1) != 2) //klocki  nad i pod nie sa scianami
				{
					if (mapa->Point(PunktY1, PunktX1 + 1) != 2)//klocek po prawo nie jest sciana
					{
						kierunek_ = losuj3(3, 0, 1); //wybor kierunku prawo dol gora
					}
					else
					{
						kierunek_ = losuj3(2, 0, 1);
					}
				}
				else if (mapa->Point(PunktY1 + 1, PunktX1) != 2) //klocek po pod nie jest sciana
				{
					if (mapa->Point(PunktY1, PunktX1 + 1) != 2)//klocek po prawo nie jest sciana
					{
						kierunek_ = losuj(3, 1);
					}
					else
					{
						kierunek_ = 1;
					}
				}
				else if (mapa->Point(PunktY1 - 1, PunktX1) != 2) //klocek nad nie jest sciana
				{
					if (mapa->Point(PunktY1, PunktX1 + 1) != 2)//klocek po prawo nie jest sciana
					{
						kierunek_ = losuj(3, 0);
					}
					else
					{
						kierunek_ = 0;
					}

				}
				else if (mapa->Point(PunktY1 - 1, PunktX1) == 2 && mapa->Point(PunktY1 + 1, PunktX1) == 2 && mapa->Point(PunktY1, PunktX1 + 1) == 2)//zaulek
				{
					kierunek_ = 2;
				}
				lastTileX_ = PunktX1;
				lastTileY_ = PunktY1;
			}
		}
	}

	//poruszanie
	{
		if (wrazliwosc_ == true) {
			if (kierunek_ == 0)
			{
				sprite_.setTextureRect(sf::IntRect(2 * 48, 48 * kolor_, 48, 48));
				rect_.move(0, -tempSpeed);
			}

			else if (kierunek_ == 1)
			{
				sprite_.setTextureRect(sf::IntRect(3 * 48, 48 * kolor_, 48, 48));
				rect_.move(0, tempSpeed);
			}

			else if (kierunek_ == 2)
			{
				sprite_.setTextureRect(sf::IntRect(1 * 48, 48 * kolor_, 48, 48));
				rect_.move(-tempSpeed, 0);
			}

			else if (kierunek_ == 3)
			{
				sprite_.setTextureRect(sf::IntRect(0 * 48, 48 * kolor_, 48, 48));
				rect_.move(tempSpeed, 0);
			}
			czas_.restart();
		}
		else //Wrazliwosc na pacmana
		{
			sprite_.setTextureRect(sf::IntRect(kolor_wrazliwosci * 48, 48 * 4, 48, 48));
			if (czas_.getElapsedTime().asSeconds()>5)
			{
				wrazliwosc_ = true;
				czas_.restart();
				kolor_wrazliwosci = 0;
			}
			if (czas_.getElapsedTime().asSeconds() > 3)
			{
				if (wrazliwy_clock_.getElapsedTime().asMilliseconds()>500)
				{
					kolor_wrazliwosci = !kolor_wrazliwosci;
					wrazliwy_clock_.restart();
				}
				
			}
			else
			{
				wrazliwy_clock_.restart();
			}


			if (kierunek_ == 0)
			{
				rect_.move(0, -tempSpeed / 2);
			}

			else if (kierunek_ == 1)
			{
				rect_.move(0, tempSpeed / 2);
			}

			else if (kierunek_ == 2)
			{
				rect_.move(-tempSpeed / 2, 0);
			}

			else if (kierunek_ == 3)
			{
				rect_.move(tempSpeed / 2, 0);
			}
		}
	}
	if (zjedzony_)
	{
		this->stop();
		if (zjedz_clock_.getElapsedTime().asSeconds()>2)
		{
			this->start();
			zjedzony_ = false;
			zjedz_clock_.restart();
		}
	}
	else
	{
		zjedz_clock_.restart();
	}

	sprite_.setPosition(rect_.getPosition());
}
