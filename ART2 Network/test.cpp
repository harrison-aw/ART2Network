/*
 * test.cpp
 *
 *  Created on: Apr 29, 2013
 *      Author: ah1411
 */

#include <iostream>

#include "Tests/VectorTest.h"
#include "Tests/MatrixTest.h"
#include "Tests/MaxnetTest.h"
#include "Tests/ART2NetworkTest.h"

using namespace std;

int main() {

	cout << "VectorTest:" << endl;
	VectorTest();
	cout << "MatrixTest:" << endl;
	MatrixTest();
	cout << "MaxnetTest:" << endl;
	MaxnetTest();
	cout << "ART2NetworkTest:" << endl;
	ART2NetworkTest();

	return 0;
}

