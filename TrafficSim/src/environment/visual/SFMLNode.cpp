#include <environment\visual\SFMLNode.h>

using namespace tf;
using namespace tf::env;
using namespace tf::env::visual;

SFMLNode::SFMLNode(unsigned int ID, const std::vector<unsigned int> InEdgeIDs, const std::vector<unsigned int> OutEdgeIDs, double Radius, sf::Color Color) : 
	Node2D(ID, InEdgeIDs, OutEdgeIDs) {
	
}

SFMLNode::~SFMLNode() {
	mVertices.clear();
}

void SFMLNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	for (size_t i = 0; i < mVertices.size(); ++i) {
		target.draw(mVertices[i], states);
	}
}