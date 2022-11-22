#include <iostream>
#include <SFML\Graphics.hpp>

void drawGraph(sf::RenderWindow* window, std::vector<std::pair<int64_t, int64_t>>* coord);

float scale{ 0.9 };


int main()
{
	sf::Font font;
	font.loadFromFile("JAi_____.ttf");

	sf::Text text("", font, 20);
	text.setFillColor(sf::Color::Black);

	std::cout << "Entrer un nombre entier initial : ";
	int64_t nb{ 0 };
	std::cin >> nb;

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Conjecture de Syracude");
	window.setFramerateLimit(0);

	while (window.isOpen())	{
		sf::Event event;


		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Up) {

				}
				else if (event.key.code == sf::Keyboard::Down) {

				}
			if (event.type == sf::Event::MouseWheelMoved) {
				if (event.key.code == 1) {
					scale *= 1.01;
					if (scale > 0.95)
						scale = 0.95;
				}
				else {
					scale /= 1.01;
					if (scale < 0.8)
						scale = 0.8;
				}
			}
		}

		std::vector<std::pair<int64_t, int64_t>> coord;

		int64_t it{ 0 };
		int64_t n{ nb };

		coord.push_back(std::make_pair(it, n));

		while (n != 1) {
			it++;
			if (n % 2 == 0)
				n /= 2;
			else
				n = 3 * n + 1;

			coord.push_back(std::make_pair(it, n));
		}

		text.setString(std::to_string(nb));

		window.clear(sf::Color::White);
		drawGraph(&window, &coord);
		window.draw(text);
		window.display();

		nb++;
	}

	return 0;
}


void drawGraph(sf::RenderWindow* window, std::vector<std::pair<int64_t, int64_t>>* coord)
{
	std::vector<std::pair<double, double>> tabPt;

	int64_t ymax{ 0 };
	int64_t xmax{ 0 };

	for (auto const pair : *coord)
		if (pair.second > ymax)
			ymax = pair.second;
		else if (pair.first > xmax)
			xmax = pair.first;


	for (auto const pair : *coord) {
		std::pair<double, double> p{ double(pair.first) / double(xmax), double(pair.second) / double(ymax) };
		p.first *= (1280 * scale);
		p.second *= (720 * scale);
		tabPt.push_back(p);
	}

	sf::CircleShape pt(4);
	pt.setOrigin(pt.getRadius() / 2.f, pt.getRadius() / 2.f);
	pt.setFillColor(sf::Color::Red);

	for (auto const pair : tabPt) {
		pt.setPosition(pair.first, -pair.second);
		pt.move((1280 - 1280 * scale) / 2.f, 720 - (720 - (720 * scale)) / 2.f);

		window->draw(pt);
	}
}

