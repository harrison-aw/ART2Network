/*
 * test.cpp
 *
 *  Created on: Apr 29, 2013
 *      Author: ah1411
 */


#include "Tests/VectorTest.h"
#include "Tests/MatrixTest.h"
#include "Tests/MaxnetTest.h"
#include "Tests/ART2NetworkTest.h"

int main() {

	VectorTest();
	MatrixTest();
	MaxnetTest();
	ART2NetworkTest();

	return 0;
}

