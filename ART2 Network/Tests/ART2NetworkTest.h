/*
 * ART2NetworkTest.h
 *
 *  Created on: May 2, 2013
 *      Author: ah1411
 */

#ifndef ART2NETWORKTEST_H_
#define ART2NETWORKTEST_H_

#include <cassert>
#include <iostream>

#include "../ART2Network.h"

using namespace art2nn;
using namespace std;

void ART2NetworkTest() {
	ART2Network network(2, .2, 0, 0, .2, .001, .4, .3);

	input_vector a(2);
	a[0] = 1.0;
	a[1] = 1.0;
	assert(network(a) == 0);

	input_vector b(2);
	b[0] = 2.0;
	b[1] = 0.0;
	assert(network(b) == 1);

	input_vector c(2);
	c[0] = 1.2;
	c[1] = 1.0;
	assert(network(c) == 0);

	input_vector d(2);
	d[0] = -1.0;
	d[1] = 2.0;
	assert(network(d) == 2);
}


#endif /* ART2NETWORKTEST_H_ */
