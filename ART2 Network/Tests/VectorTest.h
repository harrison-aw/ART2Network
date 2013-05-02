/*
 * VectorTest.h
 *
 *  Created on: May 1, 2013
 *      Author: ah1411
 */

#ifndef VECTORTEST_H_
#define VECTORTEST_H_

#include <cassert>

#include "../Vector.h"

using namespace art2nn;

void VectorTest() {
	double array[] = {1, 2, 3, 4, 5};

	Vector<double> a;
	Vector<double> b(a);
	Vector<double> c(5);
	Vector<double> d(5, array);

	d - c;
	d + c;
	1.0 * d;
	d * 1.0;
	d / 2.0;

	d * d;

	d == d;
	d != c;

	c = d;
	c += d;
	c -= d;
	c *= 2.0;
	c /= 1.5;
	-c;
	c[1];
	c[2] = 10;

	c.norm();
	c.project(2);

	c.dim();


	/* Begin Testing */

	Vector<double> nullv, v1(5, array), v2(v1), v3(5), v4(4);

	assert(nullv.dim() == 0);
	assert(nullv.norm() == 0);
	assert(nullv == -nullv);
	assert(nullv - nullv == nullv);

	assert(v1 == v2);
	assert(v1 + v1 == 2.0 * v2);
	assert(v1 - v2 == v3);
	assert(v1 == 2.0 * v2 / 2.0);
	assert(v1 - v1 / 2.0 == v1 + -(v1/2.0));

	assert(v3.project(4) == v4);
	assert(v4.project(5) == v3);
	assert(v4.dim() == 4);
}


#endif /* VECTORTEST_H_ */
