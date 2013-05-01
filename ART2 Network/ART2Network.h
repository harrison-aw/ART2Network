/*
 * ART2Network.h
 *
 *  Created on: Apr 29, 2013
 *      Author: Tony
 */

#ifndef ART2NETWORK_H_
#define ART2NETWORK_H_

#include <cstddef>

class ART2Network {
public:
	typedef size_t index;
	typedef size_t dimension;

	typedef double input;
	typedef input *input_vector;

	typedef double weight;
	typedef weight *weight_vector;
	typedef weight_vector *weight_matrix;

	class Layer1 {
	public:
		Layer1(const ART2Network &parent);

	private:
		const ART2Network &parent;
	};

	class Layer2 {
	public:
		Layer2(const ART2Network &parent);
	private:
		weight_vector output;
	};

	ART2Network(dimension M, weight a, weight b, weight c, weight d, weight e, weight theta, weight rho);
	virtual ~ART2Network();

	void iterate(input x);


private:
	ART2Network() {};
	ART2Network(const ART2Network &art2network) {};
	ART2Network &operator=(const ART2Network&) {};

	double a;
	double b;
	double c;
	double d;
	double e;
	double theta;
	double rho;

	weight_matrix z;

};

#endif /* ART2NETWORK_H_ */
