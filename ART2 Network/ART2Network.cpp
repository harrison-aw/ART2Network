/*
 * ART2Network.cpp
 *
 *  Created on: Apr 29, 2013
 *      Author: Tony
 */

#include "ART2Network.h"

ART2Network::ART2Network(dimension input_dimension, weight a, weight b, weight c, weight d, weight e, weight theta, weight rho):
	input_dimension(input_dimension), a(a), b(b), c(c), d(d), e(e), theta(theta), rho(rho), Z(NULL) {
}

ART2Network::~ART2Network() {
}


/* Layer 1 */

ART2Network::Layer1::Layer1(const ART2Network &parent):
	parent(parent) {

	p = new weight[input_dimension];
	q = new weight[input_dimension];
	u = new weight[input_dimension];
	v = new weight[input_dimension];
	w = new weight[input_dimension];
	x = new weight[input_dimension];

	zeroInput();
}

ART2Network::weight_vector ART2Network::Layer1::feedforward(const input_vector const &I) {
	this->I = I;
}

ART2Network::weight_vector const ART2Network::Layer1::output() const {
	return p;
}

void ART2Network::Layer1::zeroInput() {
	for (index i = 0; i < input_dimension; ++i) {
		p[i] = q[i] = u[i] = v[i] = w[i] = x[i] = 0.0;
	}
}

void ART2Network::Layer1::update_p() {

	weight (&g)(weight) = parent.g;
	weight_matrix const z = parent.weights();
	weight_vector const y = parent.F2.output();

	size_t node_count = parent.F2.getNodeCount();

	for (index i = 0; i < input_dimension; ++i) {
		weight feedback = 0.0;
		for (index j = 0; j < 0; ++j) {
			feedback += g(y[j]) * z[j][i];
		}
		p[i] = u[i] + a * feedback;
	}
}
