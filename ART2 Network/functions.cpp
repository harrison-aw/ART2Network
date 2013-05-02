/*
 * functions.cpp
 *
 *  Created on: May 2, 2013
 *      Author: Tony
 */

#include "functions.h"

using namespace art2nn;

art2nn::signal SIMPLE_SIGNAL_FUNCTION(art2nn::signal x) {
	if (x > 0)
		return x;
	return 0;
}

art2nn::signal NONLINEAR_SIGNAL_FUNCTION(art2nn::param theta, art2nn::signal x) {
	if (theta >= x)
		return 2*theta*x*x/(x*x+theta*theta);
	return x;
}

art2nn::signal LINEAR_SIGNAL_FUNCTION(art2nn::param theta, art2nn::signal x) {
	if (theta >= x)
		return 0;
	return x;
}

art2nn::signal HEAVISIDE_SIGNAL_FUNCTION(art2nn::param d, art2nn::signal x) {
	if (x > 0)
		return d;
	return 0;
}

art2nn::signal_vector vectorApply(art2nn::signal_vector vector, art2nn::signal (*f)(art2nn::signal)) {
	art2nn::dimension n = vector.dim();
	art2nn::signal_vector new_vector(n);
	for (art2nn::index i = 0; i < n; ++i)
		new_vector[i] = f(vector[i]);
	return new_vector;
}

art2nn::signal_vector vectorApply(art2nn::signal_vector vector, art2nn::signal (*f)(art2nn::param, art2nn::signal), art2nn::param p) {
	art2nn::dimension n = vector.dim();
	art2nn::signal_vector new_vector(n);
	for (art2nn::index i = 0; i < n; ++i)
		new_vector[i] = f(p, vector[i]);
	return new_vector;
}



