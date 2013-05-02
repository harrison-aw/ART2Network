/*
 * ART2Network.cpp
 *
 *  Created on: Apr 29, 2013
 *      Author: Tony
 */

#include "functions.h"
#include "ART2Network.h"

using namespace art2nn;

ART2Network::ART2Network(dimension input_dimension, param a, param b, param c, param d, param e, param theta, param rho):
	input_dimension(input_dimension),
	a(a), b(b), c(c), d(d), e(e), theta(theta), rho(rho),
	f(LINEAR_SIGNAL_FUNCTION), g(HEAVISIDE_SIGNAL_FUNCTION),
	F1(*this), F2(*this) {
}

ART2Network::~ART2Network() {
}


/** Layer1 **/

ART2Network::Layer1::Layer1(const ART2Network &parent):
	parent(parent),
	p(parent.input_dimension),
	q(parent.input_dimension),
	u(parent.input_dimension),
	v(parent.input_dimension),
	w(parent.input_dimension),
	x(parent.input_dimension) {
}

signal_vector ART2Network::Layer1::operator()(input_vector I) {
	signal_vector temp_p(u + parent.W * vectorApply(parent.F2.output(), parent.g, parent.theta));
	signal_vector temp_q(p * (parent.e + p.norm()));
	signal_vector temp_u(v * (parent.e + v.norm()));
	signal_vector temp_v(vectorApply(x, parent.f, parent.theta) + parent.b * vectorApply(q, parent.f, parent.theta));
	signal_vector temp_w(I + parent.a * u);
	signal_vector temp_x(w * (parent.e + w.norm()));

	p = temp_p;
	q = temp_q;
	u = temp_u;
	v = temp_v;
	w = temp_w;
	x = temp_x;

	return p;
}

void ART2Network::Layer1::zeroInput() {
	dimension m = parent.input_dimension;
	for (index i = 0; i < m; ++i)
		p[i] = q[i] = u[i] = v[i] = w[i] = x[i] = 0.0;
}
