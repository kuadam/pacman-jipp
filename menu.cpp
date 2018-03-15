#include "menu.h"
#include <iostream>

Menu::Menu(sf::Font &font)
{
	font_ = font;
	sf::Text text("Wybierz level", font_, 50);
	text.setFillColor(sf::Color::Cyan);
	tekst_s_.push_back(text);

	//text.setString("kuadam");

	text.setFillColor(sf::Color::White);
	text.setString("Level 1");
	tekst_.push_back(text);

	text.setString("Level 2");
	tekst_.push_back(text);

	text.setString("Wyjdz");
	tekst_.push_back(text);
}

void Menu::update(sf::RenderWindow & window)
{
	while (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
	while (!start_)
	{
		window.clear();
		tekst_s_[0].setPosition(window.getSize().x / 2 - tekst_s_[0].getGlobalBounds().width / 2, 200); //wybor
		window.draw(tekst_s_[0]);

		tekst_[0].setPosition(window.getSize().x / 2 - tekst_[0].getGlobalBounds().width - 20, 260);//1
		window.draw(tekst_[0]);
		tekst_[1].setPosition(window.getSize().x / 2 + 20, 260);//2
		window.draw(tekst_[1]);

		tekst_[2].setPosition(window.getSize().x / 2 - tekst_[2].getGlobalBounds().width / 2, 380); //wyjdz
		window.draw(tekst_[2]);

		tekst_[wybrany_].setOutlineThickness(3);
		tekst_[wybrany_].setOutlineColor(sf::Color::Red);

		for (int i = 0; i < tekst_.size(); i++)
		{
			if (i != wybrany_)
			{
				tekst_[i].setOutlineThickness(0);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))// poruszanie po mneu
		{
			if (wybrany_ == 0)
			{
				wybrany_ = tekst_.size() - 1;
			}
			else
			{
				wybrany_--;
			}
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))//poruszanie po menu
		{
			if (wybrany_ == tekst_.size() - 1)
			{
				wybrany_ = 0;
			}
			else
			{
				wybrany_++;
			}
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))//wybor
		{
			switch (wybrany_)
			{
			case 0:
			{
				level_ = 1;
				start_ = true;
				break;
			}
			case 1:
			{
				level_ = 2;
				start_ = true;
				break;
			}
			case 2: {
				exit(0);
				break;
			}
			}
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Return));
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
				start_ = true;
			}
		}
		window.display();
	}
	start_ = false;
	restart_ = true;
}
