#include <iostream>

#include <vector>

#include <graph\Graph.h>
#include <graph\Node.h>
#include <graph\Edge.h>

using namespace std;
using namespace troll;


int main() {

	graph::Node<size_t> n1(1);
	graph::Node<size_t> n2(2);
	graph::Node<size_t> n3(3);
	graph::Node<size_t> n4(4);

	graph::Edge<size_t> e1(1);
	graph::Edge<size_t> e2(2);
	graph::Edge<size_t> e3(3);

	vector<graph::INode<size_t>*> nodes = { &n1, &n2, &n3, &n4 };
	vector<graph::Edge<size_t>*> edges = { &e1, &e2, &e3 };

	vector<size_t> vals = { 1, 2, 3, 1, 2, 3 };
	vector<size_t> rows = { 0, 1, 2, 3, 3, 3 };
	vector<size_t> cols = { 3, 3, 3, 0, 1, 2};

	storage::Vec<size_t, size_t> v1(vals);
	storage::Vec<size_t, size_t> v2(rows);
	storage::Vec<size_t, size_t> v3(cols);

	storage::COOMat<size_t, size_t> adj((size_t)4, (size_t)4, v1, v2, v3);

	cout << adj << endl;

	system("pause");
	return 0;
}