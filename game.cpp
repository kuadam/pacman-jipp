#include "game.h"


void game()
{
	//srand(time(NULL));
	//tworzenie okna
	sf::ContextSettings settings;
	sf::RenderWindow window(sf::VideoMode(1500, 800), "Pacman", sf::Style::Close);
	window.setFramerateLimit(240);

	//ikona
	sf::Image icon;
	if (!icon.loadFromFile("data/icon.png"))
	{
		std::cout << "Nie mozna wczytac ikony" << std::endl;
	}
	window.setIcon(32, 32, icon.getPixelsPtr());


	//tekst
	sf::Font t1;
	if (!t1.loadFromFile("data/t1.ttf"))
	{
		std::cout << "Nie mozna wczytac t1.ttf" << std::endl;
	}

	sf::Font t2;
	if (!t2.loadFromFile("data/t2.ttf"))
	{
		std::cout << "Nie mozna wczytac t2.ttf" << std::endl;
	}

	sf::Text wersja("v 1.2.1", t1, 30);
	wersja.setFillColor(sf::Color::Red);
	wersja.setPosition(10, window.getSize().y - wersja.getLocalBounds().height - 20);
	//Intro

	sf::Sound intro;
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("data/intro.wav"))
	{
		std::cout << "nie mozna wczytac intro.wav" << std::endl;
	}
	intro.setBuffer(buffer);

	//Mapa

	std::shared_ptr<Map> mapa = std::make_shared<Map>();

	//tekstura ducha
	std::shared_ptr<sf::Texture> duchTexture = std::make_shared<sf::Texture>();
	if (!duchTexture->loadFromFile("data/duch.png"))
	{
		std::cout << "Nie mozna wczytac tekstury ducha" << std::endl;
	}
	duchTexture->setSmooth(true);

	//sprite
	Pacman pacman;

	std::vector<Duch> duchy;

	for (int i = 0; i < 8; i++)
	{
		Duch temp;
		temp.setTexture(duchTexture);
		temp.setColor(i % 4);

		duchy.push_back(temp);
	}


	//licznik zyc
	std::string domyslne_life = "HP ";
	sf::Text life(domyslne_life + std::to_string(pacman.getHp()), t2, 40);
	life.setFillColor(sf::Color::Red);
	life.setPosition(1260, 0);

	//punkty
	std::string domyslen_pkt = "PKT ";
	sf::Text punkty("PKT " + std::to_string(pacman.getPkt()), t2, 40);
	punkty.setFillColor(sf::Color::Red);
	punkty.setPosition(1260, 40);

	//gameover
	sf::Text gameover("GameOver", t2, 380);
	gameover.setFillColor(sf::Color::Red);
	gameover.setPosition(window.getSize().x / 2 - gameover.getGlobalBounds().width / 2, window.getSize().y / 2 - gameover.getGlobalBounds().height);


	bool wygrana = false;
	bool restart = true;
	bool start = false;


	//---------------------------------------------------------------------------------------------------------------------------------------------
	//petla gry



	Menu menu(t1);
	menu.update(window);
	mapa->setLevel(menu.getLevel());

	sf::Clock clock;
	sf::Clock timer;

	intro.play();
	window.clear();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				pacman.setHp(3);
				pacman.changePkt(0);
				life.setString(domyslne_life + std::to_string(pacman.getHp()));

				for (int i = 0; i < duchy.size(); i++)
				{
					duchy[i].stop();
					duchy[i].setPosition(duchy[i].getStartPos());
				}
				pacman.stop();
				pacman.setPosition(pacman.getStartPos());

				menu.update(window);
				mapa->setLevel(menu.getLevel());
				clock.restart();
				timer.restart();

				for (int i = 0; i < duchy.size(); i++)
				{
					duchy[i].start();
				}
				pacman.start();
				intro.play();
				restart = true;
			}
		}
		//czas
		sf::Time time = clock.getElapsedTime();

		//update spritow
		pacman.update(time, mapa);
		punkty.setString("PKT " + std::to_string(pacman.getPkt()));
		if (pacman.czy_wrazliwy())
		{
			for (int i = 0; i < duchy.size(); i++)
			{
				duchy[i].ustaw_wrazliwosc(false);
				duchy[i].setTime(0);
			}
		}


		for (int i = 0; i < duchy.size(); i++)
		{
			duchy[i].update(time, mapa);
		}


		//cheaty
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			for (int i = 0; i < duchy.size(); i++)
			{
				duchy[i].ustaw_wrazliwosc(false);
				duchy[i].setTime(0);
			}

		}

		//kolizja pacmana z duchami

		for (int i = 0; i < duchy.size(); i++)
		{
			if (duchy[i].getRect().getGlobalBounds().contains(pacman.getRectCenter()))
			{
				std::cout << "kolizja ducha " << i << " i pacmana" << std::endl;
				if (duchy[i].czy_wrazliwy())
				{
					restart = true;
					intro.play();
					pacman.changeHp(-1);
					std::cout << pacman.getHp() << std::endl;
					life.setString(domyslne_life + std::to_string(pacman.getHp()));
					pacman.setPosition(pacman.getStartPos());
					for (int i = 0; i < duchy.size(); i++)
					{
						duchy[i].setPosition(duchy[i].getStartPos());
					}
				}
				else
				{
					pacman.changePkt(pacman.getPkt() + 10);
					punkty.setString(domyslen_pkt + std::to_string(pacman.getPkt()));
					duchy[i].zjedzony();
				}
			}
		}

		//czyszczenie okna
		clock.restart();

		window.clear();

		//renderowanie mapy

		mapa->draw(window);
		wygrana = true;
		for (int i = 0; i < mapa->mapaSizeY(); i++)
		{
			for (int j = 0; j < mapa->mapaSizeX(); j++)
			{
				if (mapa->Point(i, j) == 0 || mapa->Point(i, j) == 1)
				{
					wygrana = false;
					break;
				}
			}
		}

		//koniec gry
		if (pacman.getHp() == 0 || wygrana)
		{
			if (wygrana)
			{
				gameover.setString("Win");
				gameover.setFillColor(sf::Color::Green);
				gameover.setPosition(window.getSize().x / 2 - gameover.getGlobalBounds().width / 2, window.getSize().y / 2 - gameover.getGlobalBounds().height);
			}
			for (int i = 0; i < duchy.size(); i++)
			{
				duchy[i].setPosition(duchy[i].getStartPos());
				duchy[i].stop();
			}
			pacman.setPosition(pacman.getStartPos());
			pacman.stop();
			window.draw(gameover);

		}
		else
		{
			//renderowanie duchow
			for (auto x : duchy)
			{
				window.draw(x.getSprite());
			}

			//renderowanie pacmana 
			window.draw(pacman.getSprite());
		}


		window.draw(wersja);
		window.draw(life);
		window.draw(punkty);
		window.display();

		if (restart)
		{
			for (int i = 0; i < duchy.size(); i++)
			{
				duchy[i].stop();
			}
			pacman.stop();

			if (timer.getElapsedTime().asSeconds() > 1)
			{
				restart = false;

				for (int i = 0; i < duchy.size(); i++)
				{
					duchy[i].start();
				}
				pacman.start();
				timer.restart();
			}
		}
		else
		{
			timer.restart();
		}
	}
}