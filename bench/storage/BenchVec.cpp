#include <cstdlib>
#include <iostream>
#include <chrono>

#include <omp.h>
#include <storage/Vec.h>
#include <cblas.h>

using namespace std;
using namespace troll::storage;

const unsigned long MaxIt = 100000000;
const unsigned long NumIt = 100;
const unsigned long Inc = 5000000;

void BenchScal();
void BenchCopy();
void BenchAxpy();
void BenchDot();
void BenchNrm2();
void BenchAsum();
void BenchIdamax();

unsigned long Scal[MaxIt / Inc - 1];

#define USE_BLAS	1
#define USE_TROLL	2
#define USE_TROLL_1	3

#define VERSION USE_TROLL_1

int main(int argc, char** argv) {
#if VERSION==USE_BLAS
		cout << "USING BLAS" << endl;
#elif VERSION==USE_TROLL
		cout << "USING TROLL" << endl;
#elif VERSION==USE_TROLL_1
	cout << "USING TROLL_1" << endl;
#endif
	printf("Size\t Scal\n");

	BenchScal();

	for (unsigned long i = 1; i < MaxIt/Inc; ++i) {
		printf("%5lu %10lu\n", i*Inc, Scal[i - 1]);
	}

	system("pause");
	return 0;
}

void BenchScal() {
	for (unsigned long i = Inc; i < MaxIt; i += Inc) {
		double Alpha = (double)i / (double)MaxIt;
		double* Data = new double[i];
		for (unsigned long j = 0; j < i; ++j) {
			Data[j] = (double)j;
		}

		auto* v = new Vec<blasint, double>(i, Data);

		auto t0 = std::chrono::high_resolution_clock::now();
		for (unsigned long j = 0; j < NumIt; ++j) {
#if VERSION==USE_BLAS
			cblas_dscal(i, Alpha, Data, 1);
#elif VERSION==USE_TROLL
			v->Scal(Alpha);
#elif VERSION==USE_TROLL_1
			v->Scal_1(Alpha);
#endif
		}
		auto t1 = std::chrono::high_resolution_clock::now();
		
		Scal[i/Inc-1] = chrono::duration_cast<chrono::microseconds>(t1 - t0).count();
		
		delete[] Data;
		delete v;
	}
}

void BenchCopy() {

}

void BenchAxpy() {

}

void BenchDot() {

}

void BenchNrm2() {

}

void BenchAsum() {

}

void BenchIdamax() {

}