/*
 * MaxnetTest.h
 *
 *  Created on: May 2, 2013
 *      Author: Tony
 */

#ifndef MAXNETTEST_H_
#define MAXNETTEST_H_

#include <iostream>
#include <cassert>

#include "../Maxnet.h"
#include "../nnfunctions.h"

using namespace art2nn;
using namespace std;

void MaxnetTest() {
	cout << "Maxnet default constructor" << endl;
	Maxnet a;
	cout << "Maxnet copy constructor" << endl;
	Maxnet b(a);
	cout << "Maxnet basic constructor" << endl;
	Maxnet c(5);
	cout << "Maxnet extended constructor" << endl;
	Maxnet d(5, .5, .5);
	cout << "Maxnet full constructor" << endl;
	Maxnet e(5, .5, .5, &SIMPLE_SIGNAL_FUNCTION);

	cout << "Maxnet assignment" << endl;
	b = c;

	input array[] = {1, 2, 3, 4, 5};
	input_vector I(5, array);

	cout << "Maxnet operation" << endl;
	b(I);

	cout << "Maxnet output" << endl;
	b.output();
	cout << "Maxnet node count" << endl;
	b.getNodeCount();

	cout << "Testing Maxnet operation" << endl;
	assert(b.output()[4] > 0.0);
	for (int i = 0; i < 4; ++i) {
		assert(b.output()[i] == 0.0);
	}
}


#endif /* MAXNETTEST_H_ */
