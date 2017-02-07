#include <iostream>
#include <SFML\Graphics.hpp>
#include <rapidjson\document.h>

#include <environment\Environment.h>


using namespace std;
using namespace sf;
using namespace tf;
using namespace rapidjson;

int main() {

	env::Environment Environment("C:\\Users\\danie\\Documents\\TrollMathLib\\TrafficSim\\testmap2.json");
	cout << "Loaded Environment: " << Environment.getName() << ", Version: " << Environment.getVersion() << endl;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(800, 600), "TrafficSim", sf::Style::Default, settings);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Green);

		window.display();
	}

	return 0;
}