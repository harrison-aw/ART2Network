/*
 * Maxnet.h
 *
 *  Created on: Apr 29, 2013
 *      Author: ah1411
 */

#ifndef MAXNET_H_
#define MAXNET_H_

#include <cstddef>

template<class input, class weight>
input BASIC_MAXNET_SIGNAL_FUNC(weight x) {
	if (x >= 0) {
		return x;
	}
	return 0;
}

template<class input, class weight>
class Maxnet {
public:
	typedef size_t index;

	typedef input *input_vector;

	typedef weight *weight_vector;
	typedef weight_vector *weight_matrix;

	Maxnet(size_t node_count);
	Maxnet(size_t node_count, weight epsilon, weight theta);
	Maxnet(size_t node_count, weight epsilon, weight theta, input (&f)(weight));
	virtual ~Maxnet();

	void operator()(input_vector const x);  // iterates until winner chosen

	input_vector const output() const { return signal; }

protected:
	weight net(index j) const;
	void iterate();

	size_t node_count;
	input (&f)(weight);
	weight_matrix W;  // connection weights

private:
	Maxnet() {};
	Maxnet<input, weight> &operator=(const Maxnet<input, weight> &) {};
	Maxnet(const Maxnet<input, weight> &maxnet) {};

	void initSignal();
	void initW(weight epsilon, weight theta);

	void setSignal(input_vector const I);

	input_vector signal;
};


/* Implementation */

template<class input, class weight>
Maxnet<input, weight>::Maxnet(size_t node_count):
	node_count(node_count), f(BASIC_MAXNET_SIGNAL_FUNC<input, weight>) {
	initSignal();
	initW(1.0/node_count, 1.0);
}

template<class input, class weight>
Maxnet<input, weight>::Maxnet(size_t node_count, weight epsilon, weight theta):
	node_count(node_count), f(BASIC_MAXNET_SIGNAL_FUNC<input, weight>) {
	initSignal();
	initW(epsilon, theta);
}

template<class input, class weight>
Maxnet<input, weight>::~Maxnet() {
	delete signal;

	for (index j = 0; j < node_count; ++j) {
		delete W[j];
	}
	delete W;
}

template<class input, class weight>
void Maxnet<input, weight>::operator()(input_vector const I) {
	unsigned int non_zero_count;

	setSignal(I);

	do {
		iterate();

		non_zero_count = 0;
		for (index j = 0; j < node_count; ++j) {
			if (signal[j] > 0) ++non_zero_count;
		}
	} while (non_zero_count > 1);
}

template<class input, class weight>
weight Maxnet<input, weight>::net(index j) const {
	weight net = 0;

	for (index i = 0; i < node_count; ++i) {
		net += W[j][i] * signal[i];
	 }

	return net;
}

template<class input, class weight>
void Maxnet<input, weight>::iterate() {
	input temp[node_count];

	for (index j = 0; j < node_count; ++j) {
		temp[j] = f(net(j));
	}

	for (index j = 0; j < node_count; ++j) {
		signal[j] = temp[j];
	}
}

template<class input, class weight>
void Maxnet<input, weight>::initSignal() {
	signal = new input[node_count];

	for (index i = 0; i < node_count; ++i) {
		signal[0] = 0;
	}
}

template<class input, class weight>
void Maxnet<input, weight>::initW(weight epsilon, weight theta) {
	W = new weight_vector[node_count];

	for (index j = 0; j < node_count; ++j) {
		W[j] = new weight[node_count];

		for (index i = 0; i < node_count; ++i) {
			if (j != i) W[j][i] = -epsilon;
			else W[j][i] = theta;
		}
	}
}

template<class input, class weight>
void Maxnet<input, weight>::setSignal(input_vector const I) {
	for (index i = 0; i < node_count; ++i) {
		signal[i] = I[i];
	}
}

#endif /* MAXNET_H_ */
