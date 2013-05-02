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
	Vector<double> a, b;

	assert(a==b);

	double array[] = {1, 2, 3, 4, 5};
	Vector<double> d(5, array);
	Vector<double> c(d);

	assert(d == c);

	d += d;
	c *= 2;

	assert(d == c);

	d -= c;

	assert(d + c == c);

	d - c;
	d + c;
	5.0 * d;
	d * 5.0;
	d * c;

	a = d;

	a += d;
	a -= d;
	a *= 10;
	-a;
	a[1];

	a.norm();
	a.project(2);
	a.project(10);
}


#endif /* VECTORTEST_H_ */
