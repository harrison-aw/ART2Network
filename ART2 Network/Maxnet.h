/*
 * Maxnet.h
 *
 *  Created on: Apr 29, 2013
 *      Author: ah1411
 */

#ifndef MAXNET_H_
#define MAXNET_H_

#include <cstddef>

class Maxnet {
public:
	typedef size_t index;

	typedef double input;
	typedef input *input_vector;

	typedef double weight;
	typedef weight *weight_vector;
	typedef weight_vector *weight_matrix;

	Maxnet();
	Maxnet(size_t node_count);
	Maxnet(size_t node_count, weight epsilon, weight theta);
	Maxnet(size_t node_count, weight epsilon, weight theta, input (&f)(weight));
	Maxnet(const Maxnet &maxnet);
	virtual ~Maxnet();

	Maxnet &operator=(const Maxnet &maxnet);
	void operator()(const input_vector x);  // iterates until winner chosen

	const input_vector output() const { return signal; }
	size_t getNodeCount() const { return node_count; }

	static input BASIC_SIGNAL_FUNC(weight x);

protected:
	weight net(index j) const;
	void iterate();

	size_t node_count;
	input (*f)(weight);
	weight_matrix W;  // connection weights

private:
	void initSignal();
	void initW(weight epsilon, weight theta);

	void setSignal(input_vector const I);

	input_vector signal;
};


/* Implementation */

#endif /* MAXNET_H_ */

