#include <iostream>

#include<integration\NewtonCotes.h>

using namespace std;

double f2(double x) {
	double a = 2.0;
	double b = 3.0;
	double c = 4.0;
	double d = 5.0;
	return sqrt(a*x*x*x + b*x*x + c*x + d);
}

double f1(double x) {
	return cos(x);
}

int main(int argc, char** argv) {

	double a = 0.0;
	double b = 5.0;

	int N = 10000;

	double res1 = troll::integration::NewtonCotes<int, double>(f2, a, b, N, troll::integration::Method::Trapezoid);
	double res2 = troll::integration::NewtonCotes<int, double>(f2, a, b, N, troll::integration::Method::Simpson);
	double res3 = troll::integration::NewtonCotes<int, double>(f2, a, b, N, troll::integration::Method::Pulcherrima);
	double res4 = troll::integration::NewtonCotes<int, double>(f2, a, b, N, troll::integration::Method::Milne);
	double res5 = troll::integration::GaussianQuadrature<int, double>(f2, a, b, 1, troll::integration::GaussPolynom::Legendre);
	double res6 = troll::integration::GaussianQuadrature<int, double>(f2, a, b, 2, troll::integration::GaussPolynom::Legendre);
	double res7 = troll::integration::GaussianQuadrature<int, double>(f2, a, b, 3, troll::integration::GaussPolynom::Legendre);
	double res8 = troll::integration::GaussianQuadrature<int, double>(f2, a, b, 4, troll::integration::GaussPolynom::Legendre);
	const unsigned int Nch = 20;
	double rescheb[Nch];
	for (int i = 0; i < Nch; ++i) {
		rescheb[i] = troll::integration::GaussianQuadrature<int, double>(f2, a, b, i+1, troll::integration::GaussPolynom::Chebyshev);
	}
	
	cout << "Trapezoid: " << res1 << endl;
	cout << "Simpson: " << res2 << endl;
	cout << "Pulcherrima: " << res3 << endl;
	cout << "Milne: " << res4 << endl;
	cout << "Legendre n=1: " << res5 << endl;
	cout << "Legendre n=2: " << res6 << endl;
	cout << "Legendre n=3: " << res7 << endl;
	cout << "Legendre n=4: " << res8 << endl;
	for (int i = 0; i < Nch; ++i) {
		cout << "Chebychev n=" << i+1 << ": " << rescheb[i] << endl;
	}

	system("pause");
	return 0;
}