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
class Maxnet {
public:
	typedef size_t node_index;

	typedef input *input_vector;

	typedef weight *weight_vector;
	typedef weight_vector *weight_matrix;

	Maxnet(size_t node_count);
	Maxnet(size_t node_count, weight epsilon, weight theta);
	Maxnet(const Maxnet<input, weight> &maxnet);
	virtual ~Maxnet();

	void iterate(input_vector x) const;     // steps through a single iteration
	void operator()(input_vector x) const;  // iterates until winner chosen

	size_t getNodeCount() const { return node_count; }

protected:
	weight net(node_index j, input_vector const x) const;
	input f(weight x) const;  // node activation function
	weight w(node_index j, node_index i) const;

	size_t get_node_count() const { return node_count; };
	void set_node_count(size_t node_count) { this->node_count = node_count; }
	weight_matrix const get_W() const { return W;}
	void set_W(weight_matrix W) { this->W = W; }
	void set_W(node_index j, node_index i, weight wji) { W[j][i] = wji; };

private:
	Maxnet() {};
	Maxnet<input, weight> operator=(const Maxnet<input, weight> &maxnet) {};

	void init_W(weight epsilon, weight theta);

	size_t node_count;
	weight_matrix W;  // connection weights

};


/* Implementation */

template<class input, class weight>
Maxnet<input, weight>::Maxnet(size_t node_count):
	node_count(node_count) {
	init_W(1.0/node_count, 1.0);
}

template<class input, class weight>
Maxnet<input, weight>::Maxnet(size_t node_count, weight epsilon, weight theta):
	node_count(node_count) {
	init_W(epsilon, theta);
}

template<class input, class weight>
Maxnet<input, weight>::Maxnet(const Maxnet<input, weight> &maxnet) {
	node_count = maxnet.node_count;

	W = new weight_vector[node_count];

	for (node_index j = 0; j < node_count; ++j) {
		W[j] = new weight[node_count];

		for (node_index i = 0; i < node_count; ++i) {
			W[j][i] = maxnet.W[j][i];
		}
	}
}

template<class input, class weight>
Maxnet<input, weight>::~Maxnet() {
	for (node_index j = 0; j < node_count; ++j) {
		delete W[j];
	}

	delete W;
}

template<class input, class weight>
void Maxnet<input, weight>::iterate(input_vector x) const {

	double temp[node_count];

	for (node_index j = 0; j < node_count; ++j) {
		temp[j] = f(net(j, x));
	}

	for (node_index j = 0; j < node_count; ++j) {
		x[j] = temp[j];
	}
}

template<class input, class weight>
void Maxnet<input, weight>::operator()(input_vector x) const {
	unsigned non_zero_count;

	do {
		iterate(x);

		non_zero_count = 0;
		for (node_index j = 0; j < node_count; ++j) {
			if (x[j] > 0) ++non_zero_count;
		}
	} while (non_zero_count > 1);
}

template<class input, class weight>
weight Maxnet<input, weight>::net(node_index j, input_vector const x) const {
	double net = 0.0;

	for (node_index i = 0; i < node_count; ++i) {
		net += w(j, i) * x[i];
	 }

	return net;
}

template<class input, class weight>
input Maxnet<input, weight>::f(weight net) const {
	if (net > 0.0) {
		return net;
	}
	return 0.0;
}

template<class input, class weight>
weight Maxnet<input, weight>::w(node_index j, node_index i) const {
	return W[j][i];
}

template<class input, class weight>
void Maxnet<input, weight>::init_W(weight epsilon, weight theta) {
	W = new weight_vector[node_count];

	for (node_index j = 0; j < node_count; ++j) {
		W[j] = new weight[node_count];

		for (node_index i = 0; i < node_count; ++i) {
			if (j != i) W[j][i] = -epsilon;
			else W[j][i] = theta;
		}
	}
}

#endif /* MAXNET_H_ */
