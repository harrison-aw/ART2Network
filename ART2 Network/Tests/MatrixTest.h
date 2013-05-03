/*
 * MatrixTest.h
 *
 *  Created on: May 1, 2013
 *      Author: Tony
 */

#ifndef MATRIXTEST_H_
#define MATRIXTEST_H_

#include <cassert>
#include <iostream>

#include "../Matrix.h"

using namespace art2nn;
using namespace std;

void MatrixTest() {
	cout << "Matrix default constructor" << endl;
	Matrix<double> a;
	cout << "Matrix copy constructor" << endl;
	Matrix<double> b(a);
	cout << "Matrix basic constructor" << endl;
	Matrix<double> c(5, 5);

	cout << "Matrix addition" << endl;
	c + c;
	cout << "Matrix subtraction" << endl;
	c - c;
	cout << "Matrix scalar left multiplication" << endl;
	5.0 * c;
	cout << "Matrix scalar right multiplication" << endl;
	c * 5.0;

	double array[] = {1, 2, 3, 4, 5};
	Vector<double> v(5, array);

	cout << "Matrix right vector multiplication" << endl;
	c * v;
	cout << "Matrix left vector multiplication" << endl;
	v * c;
	cout << "Matrix squaring" << endl;
	c * c;
	cout << "Matrix assignment" << endl;
	b = c;
	cout << "Matrix negation" << endl;
	-b;

	cout << "Matrix access" << endl;
	b(1, 1);
	cout << "Matrix modification" << endl;
	b(1, 1, 10);

	cout << "Matrix row retrieval" << endl;
	c.row(1);
	cout << "Matrix column retrieval" << endl;
	c.column(2);

	cout << "Matrix equality" << endl;
	c == c;
	cout << "Matrix not equal" << endl;
	c != c;

	/* Begin Testing */

	Matrix<double> m1(5, 5), m2(m1);

	cout << "Testing Matrix equality" << endl;
	assert(m1 == m2);

	cout << "Testing Matrix dimensions" << endl;
	dimension n = m1.col_dim();
	dimension m = m2.row_dim();
	assert(n == 5);
	assert(m == 5);

	cout << "Testing Matrix access/modification" << endl;
	for (unsigned int i = 0; i < n; ++i) {
		m1(i, i, 1.0);
		assert(m1(i, i) == 1.0);

		m2(0, i, array[i]);
	}

	cout << "Testing Matrix row retrieval";
	assert(m2.row(0) == v);
	cout << "Testing Matrix multiplication";
	assert(m1 * m2 == m2);
}


#endif /* MATRIXTEST_H_ */
