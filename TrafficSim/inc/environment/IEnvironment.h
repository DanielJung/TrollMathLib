#pragma once

#include <vector>

namespace tf {
	namespace env {
		class Vertex2D;
		class Edge2D;
		class Node2D;

		class IEnvironment {
		public:
			virtual Vertex2D* getVertex(unsigned int ID) const = 0;
			virtual const std::vector<Vertex2D*> getVertices(const std::vector<unsigned int>& IDs) const = 0;
			virtual std::vector<Vertex2D*> getAllVertices() const = 0;
			
			virtual Edge2D* getEdge(unsigned int ID) const = 0;
			virtual const std::vector<Edge2D*> getEdges(const std::vector<unsigned int>& IDs) const = 0;
			virtual const std::vector<Edge2D*> getAllEdges() const = 0;

			virtual Node2D* getNode(unsigned int ID) const = 0;
			virtual const std::vector<Node2D*> getNodes(const std::vector<unsigned int>& IDs) const = 0;
			virtual const std::vector<Node2D*> getAllNodes() const = 0;
		};
	}
}