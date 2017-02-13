#include <iostream>
#include "TVector.h"

int main() {
	int n = 0;
	std::cout << "Enter number of elements:" << std::endl << "> ";
	std::cin >> n;
	
	double * doubles = new double[n];
	for (int i = 0; i < n; i++) {
		doubles[i] = rand() / 100.;
	}

	TVector vector = TVector();
	vector = TVector(doubles, n);
	vector = vector + doubles; // Vector + double * = Vector

	for (int i = 0; i < n * 2; i++) {
		std::cout << vector[i] << " ";
	}

	delete[] doubles;

	system("pause");
	return 0;
}