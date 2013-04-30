/*
 * ART2Network.h
 *
 *  Created on: Apr 29, 2013
 *      Author: Tony
 */

#ifndef ART2NETWORK_H_
#define ART2NETWORK_H_

#include <cmath>
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

	ART2Network(dimension input_dimension, weight a, weight b, weight c, weight d, weight e, weight theta, weight rho);
	virtual ~ART2Network();

	void iterate(input_vector I);


	weight_matrix const weights() const { return z; };

	weight a;
	weight b;
	weight c;
	weight d;
	weight e;
	weight theta;
	weight rho;

	weight (&f)(weight);
	weight (&g)(weight);

	template<class scalar>
	static scalar norm(scalar *vector, dimension n) {
		scalar sum = 0.0;
		for (index i = 0; i < n; ++i) {
			sum += vector[i] * vector[i];
		}

		return sqrt(sum);
	}

protected:

	class Layer1 {
	public:
		Layer1(const ART2Network &parent);

		weight_vector feedforward(const input_vector const &I);
		weight_vector feedback(const weight_vector const &Y);

		weight_vector const output() const;

	private:
		void zeroInput();

		void update_p();
		void update_q();
		void update_u();
		void update_v();
		void update_w();
		void update_x();

		const ART2Network &parent;

		input_vector const &I;

		weight_vector p;
		weight_vector q;
		weight_vector u;
		weight_vector v;
		weight_vector w;
		weight_vector x;

	};

	class Layer2: public Maxnet<input, weight> {
	public:
		Layer2();
		virtual ~Layer2();

		weight_vector const output();
	};

public:
	Layer1 F1;
	Layer2 F2;

private:
	ART2Network() {};
	ART2Network(const ART2Network& art2network) {};
	ART2Network operator=(const ART2Network &art2network) {};

	dimension input_dimension;

	weight_matrix z;
};

#endif /* ART2NETWORK_H_ */

