#include <environment\Edge2D.h>

using namespace tf;
using namespace tf::env;

Edge2D::Edge2D(unsigned int ID, const std::vector<unsigned int>& VertexIDs) : 
	Edge(ID),
	mVertexIDs(VertexIDs) {

}

Edge2D::~Edge2D() {

}

const std::vector<unsigned int> Edge2D::getVertexIDs() const {
	return mVertexIDs;
}

void Edge2D::InitPointers(const IEnvironment& Environment) {
	mVertices = Environment.getVertices(mVertexIDs);
}