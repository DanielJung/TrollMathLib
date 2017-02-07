#pragma once

#include <graph\Edge.h>
#include <storage\Vec.h>
#include <interpolation\CubicSpline.h>
#include <vector>
#include <SFML\Graphics.hpp>

namespace troll {
	namespace graph {
		class Edge2D : public Edge<size_t>, public sf::Drawable
		{
		public:
			Edge2D(size_t ID, const interpolation::CubicSpline<size_t, double>& SplineX, const interpolation::CubicSpline<size_t, double>& SplineY, size_t NumPoints = 100);
			virtual ~Edge2D();

			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		private:
			sf::VertexArray mVertices;
		};


	}
}
