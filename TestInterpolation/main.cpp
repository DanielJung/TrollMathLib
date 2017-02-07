#include <iostream>

#include <interpolation\CubicSpline.h>

#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace troll;

int main(int argc, char** argv) {

	int N = 5;
	vector<double> dx(N);
	vector<double> dy(N);
	for (int i = 0; i < N; ++i) {
		dx[i] = (double)(i) / (double)(N);
		dy[i] = sin(dx[i]);
	}

	storage::Vec<int, double> x(N, dx.data());
	storage::Vec<int, double> y(N, dy.data());

	interpolation::CubicSpline<int, double> spline;

	//auto t0 = std::chrono::high_resolution_clock::now();
	spline.ComputeCrs(x, y);
	//auto t1 = std::chrono::high_resolution_clock::now();
	//std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << std::endl;

	system("pause");
	return 0;
}