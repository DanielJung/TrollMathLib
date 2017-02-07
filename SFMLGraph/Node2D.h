#pragma once

#include <graph\Node.h>
#include <SFML\Graphics.hpp>

namespace troll {
	namespace graph {
		class Node2D : public Node<size_t>, public sf::CircleShape {
		public:
			Node2D(size_t ID, sf::Vector2f Pos);
			virtual ~Node2D();

		private:
		};
	}
}