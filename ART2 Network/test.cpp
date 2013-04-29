/*
 * test.cpp
 *
 *  Created on: Apr 29, 2013
 *      Author: ah1411
 */

#include <iostream>

#include "Maxnet.h"

using namespace std;


template<class T>
void printArray(T *const array, int size) {
	for (int i = 0; i < size; ++i) {
		cout << "[" << i << "] " << array[i] << "\n";
	}
}

int main() {

	Maxnet<double, double> network(5);

	double input[] = {1.0, 7.0, 9.0, 2.0, 3.0};

	network(input);

	printArray<double>(input, 5);

	return 0;
}

