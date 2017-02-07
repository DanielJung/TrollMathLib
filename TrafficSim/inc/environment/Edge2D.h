#pragma once

#include <graph\Edge.h>
#include <environment\IEnvironment.h>
#include <vector>

#include "Vertex2D.h"

namespace tf {
	namespace env {
		class Edge2D : public troll::graph::Edge<unsigned int> {
		public:
			Edge2D(unsigned int ID, const std::vector<unsigned int>& VertexIDs);
			virtual ~Edge2D();

			void InitPointers(const IEnvironment& Environment);

			const std::vector<unsigned int> getVertexIDs() const;
		protected:
			std::vector<unsigned int> mVertexIDs;
			std::vector<Vertex2D*> mVertices;
		};
	}
}