/*
 * ART2Network.cpp
 *
 *  Created on: Apr 29, 2013
 *      Author: Tony
 */

#include "ART2Network.h"


/* Constructors */

ART2Network::ART2Network():
	a(0), b(0), c(0), d(0), e(0), theta(0), rho(1), F1(*this), F2(*this), input_dimension(0), z(NULL) {

}

ART2Network::ART2Network(dimension input_dimension, weight a, weight b, weight c, weight d, weight e, weight theta, weight rho):
	a(a), b(b), c(c), d(d), e(e), theta(theta), rho(rho), F1(*this), F2(*this), input_dimension(input_dimension), z(NULL) {
}

ART2Network::~ART2Network() {
	size_t N = F2.getNodeCount();
	if (z != NULL) {
		for (index j = 0; j < N; ++j) {
			delete z[j];
		}
		delete z;
	}
}


/** Layer1 **/

ART2Network::Layer1::Layer1(const ART2Network &parent):
	parent(parent) {
}


/** Layer 2 **/

ART2Network::Layer2::Layer2(const ART2Network &parent):
	Maxnet(), parent(parent) {
}
