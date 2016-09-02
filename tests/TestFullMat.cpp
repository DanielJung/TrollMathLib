#include <stdlib.h>
#include <iostream>
#include <omp.h>

#include <storage/FullMat.h>
#include <storage\Vec.h>
#include <cblas.h>

using namespace std;
using namespace troll::storage;

unsigned long MaxIt = 10000;
unsigned long Inc = 500;

void TestFullMat();
void TestAt();
void TestResize();
void TestScal();
void TestGemv();


int main(int argc, char** argv) {
	cout << "Running TestFullMat()" << endl;
	TestFullMat();

	cout << "Running TestAt()" << endl;
	TestAt();

	cout << "Running TestResize()" << endl;
	TestResize();

	cout << "Running TestScal()" << endl;
	TestScal();

	cout << "Running TestGemv()" << endl;
	TestGemv();

	system("pause");
	return 0;
}

void TestFullMat() {
	unsigned long numRows = 100;
	unsigned long numCols = 80 + rand() % 40;
	double Val = 42.0;

	double* Data = new double[numRows*numCols];
	for (unsigned long i = 0; i < numRows*numCols; ++i) {
		Data[i] = (double)(i%numRows);
	}

	auto* m1 = new FullMat<unsigned long, double>(numRows, numCols);
	assert(m1);
	assert(m1->getNumRows() == numRows);
	assert(m1->getNumCols() == numCols);
	assert(m1->isRowMajor());
	delete m1;

	auto* m2 = new FullMat<unsigned long, double>(numRows, numCols, Val);
	assert(m2);
	assert(m2->getNumRows() == numRows);
	assert(m2->getNumCols() == numCols);
	assert(m2->isRowMajor());
	for (unsigned long i = 0; i < numRows; ++i) {
		for (unsigned long j = 0; j < numCols; ++j) {
			assert(fabs(m2->get(i, j) - Val) < 1e-15);
		}
	}
	delete m2;

	auto* m3 = new FullMat<unsigned long, double>(numRows, numCols, Data);
	assert(m3);
	assert(m3->getNumRows() == numRows);
	assert(m3->getNumCols() == numCols);
	assert(m3->isRowMajor());
	assert(m2->isRowMajor());
	for (unsigned long i = 0; i < numRows; ++i) {
		for (unsigned long j = 0; j < numCols; ++j) {

		}
	}

	delete[] Data;
}

void TestAt() {

}

void TestResize() {

}

void TestScal() {

}

void TestGemv() {
	for (unsigned long i = Inc; i < MaxIt; i += Inc) {
		unsigned long numRows = i;
		unsigned long numCols = i- Inc/2+rand()% Inc;

		double* Data = new double[numRows*numCols];
		for (unsigned long i = 0; i < numRows*numCols; ++i) {
			Data[i] = (double)(i%numRows)/(double)MaxIt;
		}
		double* Vec = new double[numCols];
		for (unsigned long i = 0; i < numCols; ++i) {
			Vec[i] = (double)(i) / (double)(MaxIt);
		}

		double Alpha = (double)i / (double)MaxIt;
		double Beta = 1.0 - Alpha;

		auto* m = new FullMat<unsigned long, double>(numRows, numCols, Data);
		auto* v = new troll::storage::Vec<unsigned long, double>(numCols, Vec);

		auto* yData = new double[numRows];
		for (unsigned long i = 0; i < numRows; ++i) {
			yData[i] = 0.0;
		}
		auto* y = new troll::storage::Vec<unsigned long, double>(numRows, yData);

		m->Gemv(Alpha, *v, Beta, *y);

		cblas_dgemv(CblasRowMajor, CblasNoTrans, numRows, numCols, Alpha, Data, numCols, Vec, 1, Beta, yData, 1);

		double a1 = y->Nrm2();
		double a2 = cblas_dnrm2(numRows, yData, 1);
		
		assert(fabs((a1 - a2)/a2) < 1e-10);

		delete y;
		delete[] yData;
		delete v;
		delete m;
		delete[] Data;
		delete[] Vec;
	}
}