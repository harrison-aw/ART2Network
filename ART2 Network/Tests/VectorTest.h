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
	Vector<double> a;
	Vector<double> b(a);
	Vector<double> c(10);

	a = c;
	c += c;
	c -= a;

	for (art2nn::index i = 0; i < 10; ++i) {
		c[i] = i + 1.0;
		std::cout << c[i] << " ";
	}
	std::cout << std::endl;

	b = c;

	b *= 2;

	std::cout << c * b << std::endl;

	return true;
}


#endif /* VECTORTEST_H_ */
