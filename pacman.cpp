#include "pacman.h"
#include "losuj.h"

Pacman::Pacman()
{
	rect_.setSize(sf::Vector2f(48, 48));
	rect_.setFillColor(sf::Color::Blue);
	if (!texture_->loadFromFile("data/pac.png"))
	{
		std::cout << "Nie mozna wczytac tekstury pacmana" << std::endl;

	}
	texture_->setSmooth(true);
	sprite_.setTexture(*texture_);
	sprite_.setTextureRect(sf::IntRect(0, 0, 48, 48));
	rect_.setPosition(pozycja_startowa_);
	sprite_.setPosition(rect_.getPosition());
	lastTileX_ = rect_.getPosition().x / 50;
	lastTileY_ = rect_.getPosition().y / 50;
}


void Pacman::update(sf::Time time, std::shared_ptr<Map> mapa)
{
	//predkosc ruchu z uwzglednieniem czasu
	float tempSpeed = speed_*time.asMilliseconds();

	//animacja postaci
	licznik_++;
	if (licznik_ > 20 * time.asMilliseconds())
	{
		otwarty_ = !otwarty_;
		licznik_ = 0;
	}

	//Wybor kierunku poruszania
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		kierunek_ = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		kierunek_ = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		kierunek_ = 2;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		kierunek_ = 3;
	}



	//kolizja

	sf::Vector2f punkt = { this->getRectCenter().x/50,this->getRectCenter().y/50 };
	int PunktX1 = 0, PunktX2 = 0, PunktY1 = 0, PunktY2 = 0;
	{
		if (kierunek_ == 0)
		{
			PunktX1 = rect_.getPosition().x / 50;
			PunktY1 = rect_.getPosition().y / 50;

			PunktX2 = (rect_.getPosition().x + rect_.getLocalBounds().width) / 50;
			PunktY2 = PunktY1;
			if (kierunek_ != poprzedni_kierunek_)
			{
				if (mapa->Point(PunktY1 - 1, PunktX1) != 2 && mapa->Point(PunktY2 - 1, PunktX2) != 2)//klocek nad nie jest sciana
				{
					poprzedni_kierunek_ = kierunek_;
				}
			}
		}
		else if (kierunek_ == 1)
		{
			PunktX1 = rect_.getPosition().x / 50;
			PunktY1 = (rect_.getPosition().y + rect_.getLocalBounds().height) / 50;

			PunktX2 = (rect_.getPosition().x + rect_.getLocalBounds().width) / 50;
			PunktY2 = PunktY1;
			if (kierunek_ != poprzedni_kierunek_) {
				if (mapa->Point(PunktY1 + 1, PunktX1) != 2 && mapa->Point(PunktY2 + 1, PunktX2) != 2)//klocek pod nie jest sciana
				{
					poprzedni_kierunek_ = kierunek_;
				}
			}
		}
		else if (kierunek_ == 2)
		{
			PunktX1 = rect_.getPosition().x / 50;
			PunktY1 = rect_.getPosition().y / 50;

			PunktX2 = PunktX1;
			PunktY2 = (rect_.getPosition().y + rect_.getLocalBounds().height) / 50;
			if (kierunek_ != poprzedni_kierunek_) {
				if (mapa->Point(PunktY1, PunktX1 - 1) != 2 && mapa->Point(PunktY2, PunktX2 - 1) != 2)//klocek po lewo nie jest sciana
				{
					poprzedni_kierunek_ = kierunek_;
				}
			}
		}
		else if (kierunek_ == 3)
		{
			PunktX1 = (rect_.getPosition().x + rect_.getLocalBounds().width) / 50;
			PunktY1 = (rect_.getPosition().y) / 50;

			PunktX2 = PunktX1;
			PunktY2 = (rect_.getPosition().y + rect_.getLocalBounds().height) / 50;
			if (kierunek_ != poprzedni_kierunek_) {
				if (mapa->Point(PunktY1, PunktX1 + 1) != 2 && mapa->Point(PunktY2, PunktX2 + 1) != 2)//klocek po prawo nie jest sciana
				{
					poprzedni_kierunek_ = kierunek_;
				}
			}
		}
	}
	
	//zbieranie punktow
	{
		if (mapa->Point(punkt.y, punkt.x) == 0)
		{
			mapa->zebrano_punkt(punkt.y, punkt.x);
			pkt_++;
			wrazliwosc_ = false;

		}
		else if (mapa->Point(punkt.y, punkt.x) == 1)
		{
			mapa->zebrano_punkt(punkt.y, punkt.x);
			pkt_ += 2;
			wrazliwosc_ = true;
		}
	}

	//ruch w 4 kierunkach
	{
		if (poprzedni_kierunek_ == 0)
		{
			PunktX1 = rect_.getPosition().x / 50;
			PunktY1 = (rect_.getPosition().y + rect_.getLocalBounds().height) / 50;
			if (mapa->Point(PunktY1 - 1, PunktX1) != 2)//klocek nie nad jest sciana
			{
				sprite_.setTextureRect(sf::IntRect(otwarty_ * 48, 48 * 3, 48, 48));
				rect_.move(0, -tempSpeed);
			}


		}

		else if (poprzedni_kierunek_ == 1)
		{
			PunktX1 = rect_.getPosition().x / 50;
			PunktY1 = rect_.getPosition().y / 50;
			if (mapa->Point(PunktY1 + 1, PunktX1) != 2)//klocek pod nie jest sciana
			{
				sprite_.setTextureRect(sf::IntRect(otwarty_ * 48, 48, 48, 48));
				rect_.move(0, tempSpeed);
			}


		}

		else if (poprzedni_kierunek_ == 2)
		{
			PunktX1 = (rect_.getPosition().x + rect_.getLocalBounds().width) / 50;
			PunktY1 = (rect_.getPosition().y) / 50;
			if (mapa->Point(PunktY1, PunktX1 - 1) != 2)//klocek po lewo nie jest sciana
			{
				sprite_.setTextureRect(sf::IntRect(otwarty_ * 48, 48 * 2, 48, 48));
				rect_.move(-tempSpeed, 0);
			}
		}

		else if (poprzedni_kierunek_ == 3)
		{
			PunktX1 = rect_.getPosition().x / 50;
			PunktY1 = rect_.getPosition().y / 50;
			if (mapa->Point(PunktY1, PunktX1 + 1) != 2)//klocek po prawo nie jest sciana
			{
				sprite_.setTextureRect(sf::IntRect(otwarty_ * 48, 0, 48, 48));
				rect_.move(tempSpeed, 0);
			}
		}
	}
	
	//przemiszczenie sprita w miejsce rect
	sprite_.setPosition(rect_.getPosition());

}

void Pacman::changeHp(int n)
{
	hp_ += std::move(n);
}

void Pacman::changePkt(int n)
{
	pkt_ = std::move(n);
}

void Pacman::setPosition(sf::Vector2f pos)
{
	rect_.setPosition(std::move(pos));
	sprite_.setPosition(rect_.getPosition());
}


