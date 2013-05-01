/*
 * Maxnet.cpp
 *
 *  Created on: Apr 30, 2013
 *      Author: Tony
 */

#include "Maxnet.h"


/* Friends */

Maxnet::input Maxnet::BASIC_SIGNAL_FUNC(weight x) {
	if (x >= 0)
		return x;
	return 0;
}


/* Constructors */

Maxnet::Maxnet():
	node_count(0), f(BASIC_SIGNAL_FUNC) {
	initSignal();
	initW(1.0, 1.0);
}


Maxnet::Maxnet(size_t node_count):
	node_count(node_count), f(&BASIC_SIGNAL_FUNC) {
	initSignal();
	initW(1.0/node_count, 1.0);
}


Maxnet::Maxnet(size_t node_count, weight epsilon, weight theta):
	node_count(node_count), f(&BASIC_SIGNAL_FUNC) {
	initSignal();
	initW(epsilon, theta);
}

Maxnet::Maxnet(const Maxnet &maxnet):
	node_count(maxnet.node_count), f(maxnet.f) {

	signal = new input[node_count];
	for (index i = 0; i < node_count; ++i)
		signal[i] = maxnet.signal[i];

	W = new weight_vector[node_count];
	for (index j = 0; j < node_count; ++j) {
		W[j] = new weight[node_count];
		for (index i = 0; i < node_count; ++i)
			W[j][i] = maxnet.W[j][i];
	}
}


/* Destructor */

Maxnet::~Maxnet() {
	delete signal;

	for (index j = 0; j < node_count; ++j)
		delete W[j];
	delete W;
}


/* Operators */

Maxnet &Maxnet::operator=(const Maxnet &maxnet) {
	if (node_count != maxnet.node_count) {
		delete signal;
		for (index i = 0; i < node_count; ++i)
			delete W[i];
		delete W;

		signal = new input[maxnet.node_count];
		W = new weight_vector[maxnet.node_count];
		for (index i = 0; i < maxnet.node_count; ++i)
			W[i] = new weight[maxnet.node_count];
	}

	node_count = maxnet.node_count;
	f = maxnet.f;
	for (index j = 0; j < node_count; ++j) {
		signal[j] = maxnet.signal[j];
		for (index i = 0; i < node_count; ++i)
			W[j][i] = maxnet.W[j][i];
	}

	return *this;
}

void Maxnet::operator()(input_vector const I) {
	unsigned int non_zero_count;

	setSignal(I);

	do {
		iterate();

		non_zero_count = 0;
		for (index j = 0; j < node_count; ++j) {
			if (signal[j] > 0)
				++non_zero_count;
		}
	} while (non_zero_count > 1);
}


/* Methods */

Maxnet::weight Maxnet::net(index j) const {
	weight net = 0;
	for (index i = 0; i < node_count; ++i)
		net += W[j][i] * signal[i];
	return net;
}


void Maxnet::iterate() {
	input temp[node_count];
	for (index j = 0; j < node_count; ++j)
		temp[j] = f(net(j));
	for (index j = 0; j < node_count; ++j)
		signal[j] = temp[j];
}


void Maxnet::initSignal() {
	signal = new input[node_count];
	for (index i = 0; i < node_count; ++i)
		signal[0] = 0;
}


void Maxnet::initW(weight epsilon, weight theta) {
	W = new weight_vector[node_count];

	for (index j = 0; j < node_count; ++j) {
		W[j] = new weight[node_count];

		for (index i = 0; i < node_count; ++i) {
			if (j != i)
				W[j][i] = -epsilon;
			else
				W[j][i] = theta;
		}
	}
}


void Maxnet::setSignal(input_vector const I) {
	for (index i = 0; i < node_count; ++i)
		signal[i] = I[i];
}
