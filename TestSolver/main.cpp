#include <iostream>
#include <vector>

#include <solver/cg.h>
#include <solver\jacobi.h>
#include <storage\COOMat.h>
#include <storage\Vec.h>
#include <storage\DiagCRSMat.h>

using namespace std;
using namespace troll;

int main(int argc, char** argv) {
	cout << "Hello World" << endl;

	vector<double> data = { 2.0, 1.0, 1.0, 4.0, 1.0, 1.0, 4.0, 1.0, 1.0, 2.0 };
	vector<int> rows = { 0, 0, 1, 1, 1, 2, 2, 2, 3, 3 };
	vector<int> cols = { 0, 1, 0, 1, 2, 1, 2, 3, 2, 3 };

	vector<double> diag = { 2.0, 4.0, 4.0, 2.0 };
	vector<double> crsdata = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };
	vector<int> crscols = { 1, 0, 2, 1, 3, 2 };
	vector<int> crsrowptr = { 0, 1, 3, 5, 6 };

	auto mat = new storage::COOMat<int, double>(4, 4, data, rows, cols);
	auto crsmat = new storage::DiagCRSMat<int, double>(4, 4, storage::Vec<int, double>(diag), storage::Vec<int, double>(crsdata), storage::Vec<int, int>(crsrowptr), storage::Vec<int, int>(crscols));
	auto vec = new storage::Vec<int, double>(4, 3.0);
	auto x0 = new storage::Vec<int, double>(4, 1.0);
	auto x1 = new storage::Vec<int, double>(4, 1.0);
	cout << *mat << endl;
	cout << *crsmat << endl;
	cout << *vec << endl;

	solver::cg<int, double>(*mat, *vec, *x0, 1e-10, 1000);
	solver::jacobi<int, double>(*crsmat, *vec, *x1, 1e-10, 1000);
	cout << "Solution 1: " << endl;
	cout << *x0 << endl;
	cout << "Solution 2: " << endl;
	cout << *x1 << endl;

	system("pause");

	delete mat;
	delete vec;
	delete x0;
	return 0;
}