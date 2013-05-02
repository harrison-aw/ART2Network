/*
 * ART2Network.h
 *
 *  Created on: Apr 29, 2013
 *      Author: Tony
 */

#ifndef ART2NETWORK_H_
#define ART2NETWORK_H_

#include "nntypes.h"
#include "Maxnet.h"

namespace art2nn {

class ART2Network {
public:
	class Layer1;
	class Layer2;
	class Vigilance;

	ART2Network(dimension input_dimension, param a, param b, param c, param d, param e, param theta, param rho);
	virtual ~ART2Network();

	index operator()(const input_vector &I);

	friend class Layer1;
	friend class Layer2;
	friend class Vigilance;

	class Layer1 {
	public:
		Layer1(const ART2Network &parent);

		void zeroInput();

		signal_vector operator()(const input_vector I);

		friend class Vigilance;
	private:
		void initVectors();

		const ART2Network &parent;

		signal_vector p;
		signal_vector q;
		signal_vector u;
		signal_vector v;
		signal_vector w;
		signal_vector x;
	};

	class Layer2: public Maxnet {
	public:
		Layer2(const ART2Network &parent);

		friend class Vigilance;
	private:
		const ART2Network *parent;
	};

	class Vigilance {
	public:
		Vigilance(const ART2Network &parent);

		const weight_vector operator()();

	private:
		const ART2Network *parent;

		signal_vector r;
	};

protected:
	weight_matrix weight_deltas();

private:
	dimension input_dimension;

	param a;
	param b;
	param c;
	param d;
	param e;
	param theta;
	param rho;

	signal (*f)(param, signal);
	signal (*g)(param, signal);

	weight_matrix W;

	Layer1 F1;
	Layer2 F2;
}; /* class ART2Network */

} /* namespace art2nn */

#endif /* ART2NETWORK_H_ */

