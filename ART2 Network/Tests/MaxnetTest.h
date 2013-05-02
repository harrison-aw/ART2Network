/*
 * MaxnetTest.h
 *
 *  Created on: May 2, 2013
 *      Author: Tony
 */

#ifndef MAXNETTEST_H_
#define MAXNETTEST_H_

#include <cassert>

#include "../Maxnet.h"
#include "../nnfunctions.h"

using namespace art2nn;

void MaxnetTest() {
	Maxnet a;
	Maxnet b(5);
	Maxnet c(5, .5, .5);
	Maxnet d(5, .5, .5, SIMPLE_SIGNAL_FUNCTION);

	a = b;

	input array[] = {1, 2, 3, 4, 5};
	input_vector I(5, array);

	b(I);

	b.output();
	b.getNodeCount();

	assert(b.output()[4] > 0.0);
	for (int i = 0; i < 4; ++i) {
		assert(b.output()[i] == 0.0);
	}
}


#endif /* MAXNETTEST_H_ */
