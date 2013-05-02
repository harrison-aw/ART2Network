/*
 * MatrixTest.h
 *
 *  Created on: May 1, 2013
 *      Author: Tony
 */

#ifndef MATRIXTEST_H_
#define MATRIXTEST_H_

#include "../Matrix.h"

using namespace art2nn;

bool MatrixTest() {
	Matrix<double> a;
	Matrix<double> b(a);
	Matrix<double> c(5, 5);

	c + c;
	c - c;
	5.0 * c;
	c * 5.0;

	double array[] = {1, 2, 3, 4, 5};
	Vector<double> v(5, array);

	c * v;
	v * c;
	c * c;
	b = c;
	-b;

	b(1, 1);
	b(1, 1, 10);

	c.row(1);
	c.column(2);


	return true;
}


#endif /* MATRIXTEST_H_ */
