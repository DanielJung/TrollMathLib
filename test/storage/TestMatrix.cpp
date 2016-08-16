#include <iostream>
#include <string.h>

#include <Matrix.h>

using namespace std;

int main(int argc, char* argv[]) {
    double vals[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

    auto mat = new Matrix<unsigned int, double>(3, 2, 0.0);
    memcpy(mat->getData(), vals, sizeof(double)*6);

    

    return 0;
}