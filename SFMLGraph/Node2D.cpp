#include "Node2D.h"

using namespace troll::graph;

Node2D::Node2D(size_t ID, sf::Vector2f Pos) : Node(ID), sf::CircleShape(25.0f)
{
	setOrigin(getRadius(), getRadius());
	setPosition(Pos);
	setFillColor(sf::Color::Red);
}


Node2D::~Node2D()
{
}
