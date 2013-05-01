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

	ART2Network();
	ART2Network(const ART2Network &art2network);
	ART2Network(dimension M, weight a, weight b, weight c, weight d, weight e, weight theta, weight rho);
	virtual ~ART2Network();

	ART2Network &operator=(const ART2Network &art2network);

	class Layer1 {
	public:
		Layer1(const ART2Network &parent);

	private:
		const ART2Network &parent;
	};

	class Layer2: public Maxnet {
	public:
		Layer2(const ART2Network &parent);

	private:
		const ART2Network &parent;
	};

	weight a;
	weight b;
	weight c;
	weight d;
	weight e;
	weight theta;
	weight rho;

	Layer1 F1;
	Layer2 F2;

private:

	void initZ();

	dimension input_dimension;
	weight_matrix z;

};

#endif /* ART2NETWORK_H_ */
