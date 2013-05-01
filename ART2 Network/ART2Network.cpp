/*
 * ART2Network.cpp
 *
 *  Created on: Apr 29, 2013
 *      Author: Tony
 */

#include <cmath>
#include <iostream>

#include "ART2Network.h"

using namespace std;


/* Static */

ART2Network::weight ART2Network::NONLINEAR_SIGNAL_FUNC(weight theta, weight x) {
	if (theta >= x)
		return 2*theta*x*x/(x*x+theta*theta);
	return x;
}


ART2Network::weight ART2Network::LINEAR_SIGNAL_FUNC(weight theta, weight x) {
	if (theta >= x)
		return 0;
	return x;
}


ART2Network::weight ART2Network::HEAVISIDE_STEP_FUNC(weight d, weight x) {
	if (x > 0)
		return d;
	return 0;
}


ART2Network::weight ART2Network::norm(const weight_vector v, dimension m) {
	weight sum = 0.0;
	for (index i = 0; i < m; ++i) {
		sum += v[i] * v[i];
	}
	return sqrt(sum);
}

ART2Network::weight ART2Network::dotProduct(const weight_vector a, const weight_vector b, dimension m) {
	weight product = 0.0;
	for (index i = 0; i < m; ++i)
		product += a[i] * b[i];
	return product;
}


/* Constructors */

ART2Network::ART2Network():
	a(0), b(0), c(0), d(0), e(0), theta(0), rho(0), input_dimension(0), W(NULL), f(LINEAR_SIGNAL_FUNC), g(HEAVISIDE_STEP_FUNC), F1(*this), F2(*this) {
}


ART2Network::ART2Network(dimension input_dimension, weight a, weight b, weight c, weight d, weight e, weight theta, weight rho):
	a(a), b(b), c(c), d(d), e(e), theta(theta), rho(rho), input_dimension(input_dimension), W(NULL), f(LINEAR_SIGNAL_FUNC), g(HEAVISIDE_STEP_FUNC), F1(*this), F2(*this) {
}


ART2Network::~ART2Network() {
	size_t N = F2.getNodeCount();
	if (W != NULL) {
		for (index j = 0; j < N; ++j) {
			delete W[j];
		}
		delete W;
	}
}


/* Operators */



/** Layer1 **/

ART2Network::Layer1::Layer1():
	parent(NULL) {
	p = q = u = v = w = x = NULL;
}


ART2Network::Layer1::Layer1(ART2Network &parent):
	parent(&parent) {
	initVectors();
}


const ART2Network::weight_vector ART2Network::Layer1::operator()(const input_vector I) {
	iterate(I, NULL, 0);
	return p;
}


const ART2Network::weight_vector ART2Network::Layer1::operator()(const input_vector I, const weight_vector y, dimension y_dimension) {
	iterate(I, y, y_dimension);
	return p;
}


void ART2Network::Layer1::setParent(const ART2Network &parent) {
	this->parent = &parent;

	if (p != NULL) delete p;
	if (q != NULL) delete q;
	if (u != NULL) delete u;
	if (v != NULL) delete v;
	if (w != NULL) delete w;
	if (x != NULL) delete x;

	initVectors();
}


void ART2Network::Layer1::zeroInput() {
	dimension m = parent->input_dimension;
	for (index i = 0; i < m; ++i)
		p[i] = q[i] = u[i] = v[i] = w[i] = x[i] = 0.0;
}


ART2Network::weight ART2Network::Layer1::feedback(index i, const weight_vector y, dimension y_dimension) {
	weight feedback = 0.0;
	const_weight_matrix W = parent->weights();

	if (y_dimension > 0 && y != NULL) {
		for (index j = 0; j < y_dimension; ++i) {
			if (y[j] > 0.0)
				feedback += parent->d * W[i][j];
		}
	}

	return feedback;
}


void ART2Network::Layer1::iterate(const input_vector I, const weight_vector y, dimension y_dimension) {
	dimension m = parent->input_dimension;

	enum vector_index {P, Q, U, V, W, X, VECTOR_COUNT};
	weight_vector temp[VECTOR_COUNT];
	for (index i = 0; i < VECTOR_COUNT; ++i)
		temp[i] = new weight[m];

	weight a = parent->a;
	weight b = parent->b;
	weight e = parent->e;
	weight theta = parent->theta;
	weight (&f)(weight, weight) = *parent->f;

	weight norm_p = ART2Network::norm(p, m);
	weight norm_v = ART2Network::norm(v, m);
	weight norm_w = ART2Network::norm(w, m);

	const weight_vector g_y = parent->F2.gated_output();

	for (index i = 0; i < m; ++i) {
		temp[P][i] = u[i] + feedback(i, y, y_dimension);
		temp[Q][i] = p[i] / (e + norm_p);
		temp[U][i] = v[i] / (e + norm_v);
		temp[V][i] = f(theta, x[i]) + b * f(theta, q[i]);
		temp[W][i] = I[i] + a * u[i];
		temp[X][i] = w[i] / (e + norm_w);
	}

	for (index i = 0; i < m; ++i) {
		p[i] = temp[P][i];
		q[i] = temp[Q][i];
		u[i] = temp[U][i];
		v[i] = temp[V][i];
		w[i] = temp[W][i];
		x[i] = temp[X][i];
	}
}


void ART2Network::Layer1::initVectors() {
	dimension m = parent->input_dimension;

	p = new weight[m];
	q = new weight[m];
	u = new weight[m];
	v = new weight[m];
	w = new weight[m];
	x = new weight[m];

	for (index i = 0; i < m; ++i)
		p[i] = q[i] = u[i] = v[i] = w[i] = x[i] = 0.0;
}


/** Layer 2 **/

ART2Network::Layer2::Layer2():
	Maxnet(), parent(NULL) {
}


ART2Network::Layer2::Layer2(const ART2Network &parent):
	Maxnet(), parent(&parent) {
}
