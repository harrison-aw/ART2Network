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

using namespace art2nn;

void MaxnetTest() {
	Maxnet a();
	Maxnet b(5);

	input array[] = {1, 2, 3, 4, 5};
	input_vector I(5, array);

	b(I);

	Maxnet c(b);
}


#endif /* MAXNETTEST_H_ */
