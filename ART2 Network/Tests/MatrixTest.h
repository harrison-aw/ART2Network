/*
 * MatrixTest.h
 *
 *  Created on: May 1, 2013
 *      Author: Tony
 */

#ifndef MATRIXTEST_H_
#define MATRIXTEST_H_

#include <cassert>

#include "../Matrix.h"

using namespace art2nn;

void MatrixTest() {
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

	c == c;
	c != c;

	/* Begin Testing */

	Matrix<double> m1(5, 5), m2(m1);

	assert(m1 == m2);

	dimension n = m1.col_dim();
	dimension m = m2.row_dim();
	assert(n == 5);
	assert(m == 5);

	for (unsigned int i = 0; i < n; ++i) {
		m1(i, i, 1.0);
		assert(m1(i, i) == 1.0);

		m2(0, i, array[i]);
	}

	assert(m2.row(0) == v);
	assert(m1 * m2 == m2);

}


#endif /* MATRIXTEST_H_ */
