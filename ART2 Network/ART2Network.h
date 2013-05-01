/*
 * ART2Network.h
 *
 *  Created on: Apr 29, 2013
 *      Author: Tony
 */

#ifndef ART2NETWORK_H_
#define ART2NETWORK_H_

#include <cstddef>

#include "Maxnet.h"

class ART2Network {
public:
	typedef size_t index;
	typedef size_t dimension;

	typedef double input;
	typedef input *input_vector;

	typedef double weight;
	typedef weight *weight_vector;
	typedef weight_vector *weight_matrix;
	typedef const weight *const *const_weight_matrix;

	ART2Network();
	ART2Network(const ART2Network &art2network);
	ART2Network(dimension input_dimension, weight a, weight b, weight c, weight d, weight e, weight theta, weight rho);
	virtual ~ART2Network();

	ART2Network &operator=(const ART2Network &art2network);

	const_weight_matrix weights() const { return W; }

	// Network signal functions
	static weight NONLINEAR_SIGNAL_FUNC(weight theta, weight x);
	static weight LINEAR_SIGNAL_FUNC(weight theta, weight x);

	static double norm(double *vector, dimension m);

	class Layer1 {
	public:
		Layer1();
		Layer1(ART2Network &parent);

		const weight_vector operator()(const input_vector I);
		const weight_vector operator()(const input_vector I, const weight_vector y, dimension y_dimension);

		void setParent(const ART2Network &parent);

		void zeroInput();
		const weight_vector output() const { return p; }

	private:
		weight feedback(index i, weight_vector const y, dimension y_dimension);
		void iterate(const input_vector I, const weight_vector y, dimension y_dimension);

	public:
		void initVectors();

		const ART2Network *parent;

		weight_vector p;
		weight_vector q;
		weight_vector u;
		weight_vector v;
		weight_vector w;
		weight_vector x;
	};

	class Layer2: public Maxnet {
	public:
		Layer2();
		Layer2(const ART2Network &parent);

	private:
		const ART2Network *parent;
	};

	weight a;
	weight b;
	weight c;
	weight d;
	weight e;
	weight theta;
	weight rho;

private:
	dimension input_dimension;
	weight_matrix W;
	weight (*f)(weight, weight);
public:
	Layer1 F1;
	Layer2 F2;
};

#endif /* ART2NETWORK_H_ */
