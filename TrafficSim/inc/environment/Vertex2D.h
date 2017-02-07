#pragma once

namespace tf {
	namespace env {
		class Vertex2D {
		public:
			Vertex2D(unsigned int ID, double X, double Y);
			virtual ~Vertex2D();

			unsigned int getID() const;
			double getX() const;
			double getY() const;
		protected:
			unsigned int mID;
			double mX;
			double mY;
		};
	}
}