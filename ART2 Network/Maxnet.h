/*
 * Maxnet.h
 *
 *  Created on: Apr 29, 2013
 *      Author: ah1411
 */

#ifndef MAXNET_H_
#define MAXNET_H_

#include <cstddef>

template<class input_type, class weight_type>
class Maxnet {
public:
	typedef input_type *input;
	typedef size_t node_index;

	typedef weight_type **weight_matrix;
	typedef weight_type *weight_matrix_row;

	Maxnet(size_t node_count);
	Maxnet(size_t node_count, weight_type epsilon, weight_type theta);
	Maxnet(const Maxnet<input_type, weight_type> &maxnet);
	virtual ~Maxnet();

	void iterate(input x) const;     // steps through a single iteration
	void operator()(input x) const;  // iterates until winner chosen

protected:
	weight_type net(node_index j, input const x) const;
	input_type f(weight_type x) const;  // node activation function
	weight_type w(node_index j, node_index i) const;

	size_t get_node_count() const { return node_count; };
	weight_matrix const get_W() const { return W;}
	void set_W(node_index j, node_index i, weight_type wji) { W[j][i] = wji; };

private:
	Maxnet(): node_count(0), W(NULL) {};
	Maxnet<input_type, weight_type> operator=(const Maxnet<input_type, weight_type> &maxnet) { return *this; };

	void init_W(weight_type epsilon, weight_type theta);

	size_t node_count;
	weight_matrix W;  // connection weights

};


/* Implementation */

template<class input_type, class weight_type>
Maxnet<input_type, weight_type>::Maxnet(size_t node_count):
	node_count(node_count) {
	init_W(1.0/node_count, 1.0);
}

template<class input_type, class weight_type>
Maxnet<input_type, weight_type>::Maxnet(size_t node_count, weight_type epsilon, weight_type theta):
	node_count(node_count) {
	init_W(epsilon, theta);
}

template<class input_type, class weight_type>
Maxnet<input_type, weight_type>::Maxnet(const Maxnet<input_type, weight_type> &maxnet) {
	node_count = maxnet.node_count;

	W = new weight_matrix_row[node_count];

	for (node_index j = 0; j < node_count; ++j) {
		W[j] = new weight_type[node_count];

		for (node_index i = 0; i < node_count; ++i) {
			W[j][i] = maxnet.W[j][i];
		}
	}
}

template<class input_type, class weight_type>
Maxnet<input_type, weight_type>::~Maxnet() {
	for (node_index j = 0; j < node_count; ++j) {
		delete W[j];
	}

	delete W;
}

template<class input_type, class weight_type>
void Maxnet<input_type, weight_type>::iterate(input x) const {

	double temp[node_count];

	for (node_index j = 0; j < node_count; ++j) {
		temp[j] = f(net(j, x));
	}

	for (node_index j = 0; j < node_count; ++j) {
		x[j] = temp[j];
	}
}

template<class input_type, class weight_type>
void Maxnet<input_type, weight_type>::operator()(input x) const {
	unsigned non_zero_count;

	do {
		iterate(x);

		non_zero_count = 0;
		for (node_index j = 0; j < node_count; ++j) {
			if (x[j] > 0) ++non_zero_count;
		}
	} while (non_zero_count > 1);
}

template<class input_type, class weight_type>
weight_type Maxnet<input_type, weight_type>::net(node_index j, input const x) const {
	double net = 0.0;

	for (node_index i = 0; i < node_count; ++i) {
		net += w(j, i) * x[i];
	 }

	return net;
}

template<class input_type, class weight_type>
input_type Maxnet<input_type, weight_type>::f(weight_type net) const {
	if (net > 0.0) {
		return net;
	}
	return 0.0;
}

template<class input_type, class weight_type>
weight_type Maxnet<input_type, weight_type>::w(node_index j, node_index i) const {
	return W[j][i];
}

template<class input_type, class weight_type>
void Maxnet<input_type, weight_type>::init_W(weight_type epsilon, weight_type theta) {
	W = new weight_matrix_row[node_count];

	for (node_index j = 0; j < node_count; ++j) {
		W[j] = new weight_type[node_count];

		for (node_index i = 0; i < node_count; ++i) {
			if (j != i) W[j][i] = -epsilon;
			else W[j][i] = theta;
		}
	}
}

#endif /* MAXNET_H_ */
