#include <iostream>
#include <SFML\Graphics.hpp>

#include "Node2D.h"
#include "Edge2D.h"

using namespace std;
using namespace troll;
using namespace sf;

int main() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Traffic", sf::Style::Default, settings);

	graph::Node2D n1(1, sf::Vector2f(100.0, 100.0));
	graph::Node2D n2(2, sf::Vector2f(100.0, 300.0));
	graph::Node2D n3(3, sf::Vector2f(100.0, 500.0));
	graph::Node2D n4(4, sf::Vector2f(700.0, 300.0));

	vector<double> t = { 1.0, 2.0, 3.0 };

	vector<double> w1x = { 100.0, 50.0, 100.0 };
	vector<double> w1y = { 100.0, 200.0, 300.0 };

	vector<double> w2x = { 100.0, 400.0, 700.0 };
	vector<double> w2y = { 300.0, 200.0, 300.0 };

	storage::Vec<size_t, double> v = { 1.0, 2.0, 3.0 };

	interpolation::CubicSpline<size_t, double> s1x;
	interpolation::CubicSpline<size_t, double> s1y;
	s1x.ComputeCrs(storage::Vec<size_t, double>(t), storage::Vec<size_t, double>(w1x));
	s1y.ComputeCrs(storage::Vec<size_t, double>(t), storage::Vec<size_t, double>(w1y));

	interpolation::CubicSpline<size_t, double> s2x;
	interpolation::CubicSpline<size_t, double> s2y;
	s2x.ComputeCrs(storage::Vec<size_t, double>(t), storage::Vec<size_t, double>(w2x));
	s2y.ComputeCrs(storage::Vec<size_t, double>(t), storage::Vec<size_t, double>(w2y));


	graph::Edge2D e1(1, s1x, s1y, 100);
	graph::Edge2D e2(2, s2x, s2y, 100);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Cyan);

		window.draw(n1);
		window.draw(n2);
		window.draw(n3);
		window.draw(n4);

		window.draw(e1);
		window.draw(e2);

		window.display();
	}
}