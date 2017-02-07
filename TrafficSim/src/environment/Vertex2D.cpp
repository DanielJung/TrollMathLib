#include <environment\Vertex2D.h>

using namespace tf;
using namespace tf::env;

Vertex2D::Vertex2D(unsigned int ID, double X, double Y) : 
	mID(ID),
	mX(X),
	mY(Y) {

}

Vertex2D::~Vertex2D() {

}

unsigned int Vertex2D::getID() const {
	return mID;
}

double Vertex2D::getX() const {
	return mX;
}

double Vertex2D::getY() const {
	return mY;
}