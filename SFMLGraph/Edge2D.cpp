#include "Edge2D.h"

using namespace troll;
using namespace troll::graph;

Edge2D::Edge2D(size_t ID, const interpolation::CubicSpline<size_t, double>& SplineX, const interpolation::CubicSpline<size_t, double>& SplineY, size_t NumPoints) : Edge(ID), mVertices(sf::LineStrip, NumPoints)
{
	double length = SplineX.getMax() - SplineX.getMin();
	for (auto i = 0; i < NumPoints; ++i) {
		double t = SplineX.getMin() + (double)(i)*length / (double)(NumPoints-1.0);
		double x = SplineX.Eval(t);
		double y = SplineY.Eval(t);
		mVertices[i] = sf::Vertex(sf::Vector2f((float)x, (float)y), sf::Color::Blue);
	}
}


Edge2D::~Edge2D()
{
}

void Edge2D::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mVertices, states);
}