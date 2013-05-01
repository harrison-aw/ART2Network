/*
 * test.cpp
 *
 *  Created on: Apr 29, 2013
 *      Author: ah1411
 */

#include <iostream>

#include "Maxnet.h"
#include "ART2Network.h"

using namespace std;


template<class T>
void printArray(T *const array, int size) {
	for (int i = 0; i < size; ++i) {
		cout << "[" << i << "] " << array[i] << "\n";
	}
}

int main() {

	Maxnet network(5);

	double input[] = {1.0, 7.0, 20.0, 2.0, 3.0};

	network(input);

	printArray<double>(network.output(), 5);


	ART2Network test;

	return 0;
}

