#pragma once

#include <SFML\Graphics.hpp>
#include <environment\Node2D.h>

namespace tf {
	namespace env {
		namespace visual {
			class SFMLNode : public sf::Drawable, public sf::Transformable, public Node2D {
			public:
				SFMLNode(unsigned int ID, const std::vector<unsigned int> InEdgeIDs, const std::vector<unsigned int> OutEdgeIDs, double Radius = 25.0f, sf::Color Color = sf::Color::Red);
				virtual ~SFMLNode();

				virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
			protected:
				std::vector<sf::CircleShape> mVertices;
			};
		}
	}
}