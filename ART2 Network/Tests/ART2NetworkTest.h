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
	cout << "before" << endl;
	ART2Network a(2, .2, 0, 0, .2, .001, .4, .3);
	cout << "after" << endl;

	input_vector I(2);
	I[0] = 1.0;
	I[1] = 1.0;

	assert(a(I) == 1);
}


#endif /* ART2NETWORKTEST_H_ */
