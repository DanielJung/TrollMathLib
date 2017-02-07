#include <environment\Node2D.h>

using namespace tf;
using namespace tf::env;

Node2D::Node2D(unsigned int ID, const std::vector<unsigned int> InEdgeIDs, const std::vector<unsigned int> OutEdgeIDs) :
	Node(ID),
	mInEdgeIDs(InEdgeIDs),
	mOutEdgeIDs(OutEdgeIDs) {

}

Node2D::~Node2D() {

}

const std::vector<unsigned int> Node2D::getInEdgeIDs() const {
	return mInEdgeIDs;
}

const std::vector<unsigned int> Node2D::getOutEdgeIDs() const {
	return mOutEdgeIDs;
}

void Node2D::InitPointers(const IEnvironment& Environment) {
	mInEdges = Environment.getEdges(mInEdgeIDs);
	mOutEdges = Environment.getEdges(mOutEdgeIDs);
}