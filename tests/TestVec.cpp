#include <stdlib.h>
#include <iostream>

#include <storage/Vec.h>
#include <cblas.h>

using namespace std;
using namespace troll::storage;

unsigned long NumIt = 1000000;
unsigned long Inc = 500;

void TestVec();
void TestGetSize();
void TestGetData();
void TestAt();
void TestResize();
void TestSwap();
void TestScal();
void TestCopy();
void TestAxpy();
void TestDot();
void TestNrm2();
void TestAsum();
void TestIdaMax();

int main(int argc, char** argv) {
	cout << "Running TestVec()" << endl;
    TestVec();

	cout << "Running TestGetSize()" << endl;
    TestGetSize();

	cout << "Running TestGetData()" << endl;
    TestGetData();

	cout << "Running TestAt()" << endl;
    TestAt();

	cout << "Running TestResize()" << endl;
    TestResize();

	cout << "Running TestSwap()" << endl;
    TestSwap();

	cout << "Running TestScal()" << endl;
    TestScal();

	cout << "Running TestCopy()" << endl;
    TestCopy();

	cout << "Running TestAxpy()" << endl;
    TestAxpy();

	cout << "Running TestDot()" << endl;
    TestDot();

	cout << "Running TestNrm2()" << endl;
    TestNrm2();

	cout << "Running TestAsum()" << endl;
    TestAsum();

	cout << "Running TestIdaMax()" << endl;
    TestIdaMax();

	system("pause");
    return 0;
}

void TestVec() {
	const unsigned long Size = 100;
	double Val = 42.0;
	double Data[Size];
	for (unsigned long i = 0; i < Size; ++i) {
		Data[i] = (double)i;
	}

	auto* v1 = new Vec<unsigned long, double>(Size);
	assert(v1);
	assert(v1->getSize() == Size);
	assert(v1->getData());
	delete v1;

	auto* v2 = new Vec<unsigned long, double>(Size, Data);
	assert(v2);
	assert(v2->getSize() == Size);
	assert(v2->getData());
	for (unsigned long i = 0; i < Size; ++i) {
		assert(fabs(v2->getData()[i]-Data[i])<1e-15);
	}
	delete v2;
	
	auto* v3 = new Vec<unsigned long, double>(Size, Val);
	assert(v3);
	assert(v3->getSize() == Size);
	assert(v3->getData());
	for (unsigned long i = 0; i < Size; ++i) {
		assert(fabs(v3->getData()[i] - Val) < 1e-15);
	}
	delete v3;

	auto* v4 = new Vec<unsigned long, double>(Size, Data);
	auto* v5 = new Vec<unsigned long, double>(*v4);
	assert(v5);
	assert(v5->getSize() == v4->getSize());
	assert(v5->getData());
	for (unsigned long i = 0; i < Size; ++i) {
		assert(fabs(v4->getData()[i] - v5->getData()[i])<1e-15);
	}
	delete v4;
	delete v5;
}

void TestGetSize() {
	for (unsigned long i = Inc; i < NumIt; i += Inc) {
		auto* v1 = new Vec<unsigned long, double>(i);
		assert(v1);
		assert(v1->getSize() == i);
		v1->getData()[i - 1] = 0.0;
		delete v1;
	}
}

void TestGetData() {
	for (unsigned long i = Inc; i < NumIt; i += Inc) {
		double Val = (double)i;
		double* Data = new double[i];
		for (unsigned long j = 0; j < i; ++j) {
			Data[j] = (double)j;
		}

		auto* v1 = new Vec<unsigned long, double>(i, Data);
		auto* v2 = new Vec<unsigned long, double>(i, Val);

		for (unsigned long j = 0; j < i; ++j) {
			assert(fabs(v1->getData()[j] - Data[j])<1e-15);
			assert(fabs(v2->getData()[j] - Val) < 1e-15);
		}

		delete v1;
		delete v2;
		delete[] Data;
	}
}

void TestAt() {
	for (unsigned long i = Inc; i < NumIt; i += Inc) {
		double* Data = new double[i];
		for (unsigned long j = 0; j < i; ++j) {
			Data[j] = (double)j;
		}

		auto* v1 = new Vec<unsigned long, double>(i, Data);

		for (unsigned long j = 0; j < i; ++j) {
			assert(fabs(v1->getData()[j]-v1->at(j))<1e-15);
		}

		delete v1;
		delete[] Data;
	}
}

void TestResize() {
	auto* v1 = new Vec<unsigned long, double>(Inc);

	for (unsigned long i = 2*Inc; i < NumIt; i += Inc) {
		v1->Resize(i);
		assert(v1->getSize() == i);
		v1->at(i - 1) = 0.0;
	}

	delete v1;
}

void TestSwap() {
	for (unsigned long i = Inc; i < NumIt; i += Inc) {
		double* Data1 = new double[i];
		double* Data2 = new double[i];
		for (unsigned long j = 0; j < i; ++j) {
			Data1[j] = (double)j;
			Data2[j] = (double)j+10.0;
		}

		auto* v1 = new Vec<unsigned long, double>(i, Data1);
		auto* v2 = new Vec<unsigned long, double>(i, Data2);

		v1->Swap(*v2);
		for (unsigned long j = 0; j < i; ++j) {
			assert(fabs(v1->getData()[j] - Data2[j])<1e-15);
			assert(fabs(v2->getData()[j] - Data1[j])<1e-15);
		}

		v2->Swap(*v1);
		for (unsigned long j = 0; j < i; ++j) {
			assert(fabs(v1->getData()[j] - Data1[j])<1e-15);
			assert(fabs(v2->getData()[j] - Data2[j])<1e-15);
		}

		delete v1;
		delete v2;
		delete[] Data1;
		delete[] Data2;
	}
}

void TestScal() {
	for (unsigned long i = Inc; i < NumIt; i += Inc) {
		double Alpha = (double)i / (double)NumIt;
		double* Data = new double[i];
		for (unsigned long j = 0; j < i; ++j) {
			Data[j] = (double)j;
		}

		auto* v1 = new Vec<unsigned long, double>(i, Data);

		v1->Scal(Alpha);
		cblas_dscal(i, Alpha, Data, 1);

		for (unsigned long j = 0; j < i; ++j) {
			assert(fabs(v1->getData()[j] - Data[j])<1e-15);
		}

		delete v1;
		delete[] Data;
	}
}

void TestCopy() {
	for (unsigned long i = Inc; i < NumIt; i += Inc) {
		double* Data = new double[i];
		for (unsigned long j = 0; j < i; ++j) {
			Data[j] = (double)j;
		}

		auto* v1 = new Vec<unsigned long, double>(i, Data);
		auto* v2 = new Vec<unsigned long, double>(i);

		v2->Copy(*v1);
		for (unsigned long j = 0; j < i; ++j) {
			assert(fabs(v1->getData()[j] - v2->getData()[j])<1e-15);
		}

		delete v1;
		delete v2;
		delete[] Data;
	}
}

void TestAxpy() {
	for (unsigned long i = Inc; i < NumIt; i += Inc) {
		double Alpha = (double)i / (double)NumIt;
		double* Data1 = new double[i];
		double* Data2 = new double[i];
		for (unsigned long j = 0; j < i; ++j) {
			Data1[j] = (double)j;
			Data2[j] = (double)j + 10.0;
		}

		auto* v1 = new Vec<unsigned long, double>(i, Data1);
		auto* v2 = new Vec<unsigned long, double>(i, Data2);

		v1->Axpy(Alpha, *v2);
		cblas_daxpy(i, Alpha, Data2, 1, Data1, 1);

		for (unsigned long j = 0; j < i; ++j) {
			assert(fabs(v1->getData()[j] - Data1[j])<1e-15);
		}

		delete v1;
		delete v2;
		delete[] Data1;
		delete[] Data2;
	}
}

void TestDot() {
	for (unsigned long i = Inc; i < NumIt; i += Inc) {
		double* Data1 = new double[i];
		double* Data2 = new double[i];
		for (unsigned long j = 0; j < i; ++j) {
			Data1[j] = (double)j;
			Data2[j] = (double)j + 10.0;
		}

		auto* v1 = new Vec<unsigned long, double>(i, Data1);
		auto* v2 = new Vec<unsigned long, double>(i, Data2);

		double d1 = v1->Dot(*v2);
		double d2 = cblas_ddot(i, Data1, 1, Data2, 1);
		assert(fabs(d1 - d2) < 1e-15);

		delete v1;
		delete v2;
		delete[] Data1;
		delete[] Data2;
	}
}

void TestNrm2() {
	for (unsigned long i = Inc; i < NumIt; i += Inc) {
		double* Data = new double[i];
		for (unsigned long j = 0; j < i; ++j) {
			Data[j] = (double)j;
		}

		auto* v1 = new Vec<unsigned long, double>(i, Data);

		double d1 = v1->Nrm2();
		double d2 = cblas_dnrm2(i, Data, 1);
		assert(fabs(d1 - d2) < 1e-15);

		delete v1;
		delete[] Data;
	}
}

void TestAsum() {
	for (unsigned long i = Inc; i < NumIt; i += Inc) {
		double* Data = new double[i];
		for (unsigned long j = 0; j < i; ++j) {
			Data[j] = (double)j;
		}

		auto* v1 = new Vec<unsigned long, double>(i, Data);

		double d1 = v1->Asum();
		double d2 = cblas_dasum(i, Data, 1);
		assert(fabs(d1 - d2) < 1e-15);

		delete v1;
		delete[] Data;
	}
}

void TestIdaMax() {
	for (unsigned long i = Inc; i < NumIt; i += Inc) {
		double* Data = new double[i];
		for (unsigned long j = 0; j < i; ++j) {
			Data[j] = (double)j;
		}

		auto* v1 = new Vec<unsigned long, double>(i, Data);

		unsigned long d1 = v1->Idamax();
		unsigned long d2 = cblas_idamax(i, Data, 1);
		assert(d1==d2);

		delete v1;
		delete[] Data;
	}
}
