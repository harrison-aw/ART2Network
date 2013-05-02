/*
 * VectorTest.h
 *
 *  Created on: May 1, 2013
 *      Author: ah1411
 */

#ifndef VECTORTEST_H_
#define VECTORTEST_H_

#include <iostream>

#include "../Vector.h"

using namespace art2nn;

bool VectorTest() {
	double array[5] = {1, 2, 3, 4, 5};

	Vector<double> a;
	Vector<double> b(a);
	Vector<double> c(5);
	Vector<double> d(5, array);

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

	return true;
}


#endif /* VECTORTEST_H_ */
