/*
 * test.cpp
 *
 *  Created on: Apr 29, 2013
 *      Author: ah1411
 */

#include <iostream>

#include "Maxnet.h"
#include "ART2Network.h"

#define STATE cout << "p: "; printArray<double>(test.F1.p, 5); cout << "q: "; printArray<double>(test.F1.q, 5); cout << "u: "; printArray<double>(test.F1.u, 5); cout << "v: ";	printArray<double>(test.F1.v, 5); cout << "w: "; printArray<double>(test.F1.w, 5); cout << "x: "; printArray<double>(test.F1.x, 5);

using namespace std;


template<class T>
void printArray(T *const array, int size) {
	cout << '[';
	for (int i = 0; i < size; ++i) {
		cout << array[i];
		if ((i + 1) != size) {
			cout << ", ";
		}
	}
	cout << ']' << endl;
}

int main() {

	Maxnet network(5);

	double input[] = {1.0, 7.0, 20.0, 2.0, 3.0};

	network(input);

	printArray<double>(network.output(), 5);


	ART2Network test(5, 1.0, 0.0, 0.0, 1.0, 0.000001, 0.5, 0.5);

	test.F1(input);
	test.F1(input);
	test.F1(input);
	test.F1(input);
	STATE

	test.F1(input);
	STATE

	test.F1(input);
	STATE

	test.F1(input);
	STATE
	test.F1(input);
	STATE
	test.F1(input);
	STATE



	return 0;
}

