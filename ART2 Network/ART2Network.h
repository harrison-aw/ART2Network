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
	typedef size_t node_index;
	typedef double *input;

	typedef double **weight_matrix;
	typedef double *weight_matrix_row;

	ART2Network(double a, double b, double c, double d, double e, double theta, double rho);
	virtual ~ART2Network();

	void iterate(input x);

protected:
	double w(node_index i, input I, double ui);
	double x(node_index i, double wi, double normw);
	double v(node_index i, double xi, double qi);
	double u(node_index i, double vi, double normv);
	double p(node_index i, double ui, double neti);
	double q(node_index i, double pi, double normp);

private:
	ART2Network() {};
	ART2Network(const ART2Network&) {};
	ART2Network operator=(const ART2Network&) {};

	double a;
	double b;
	double c;
	double d;
	double e;
	double theta;
	double rho;

	weight_matrix W;

};

#endif /* ART2NETWORK_H_ */
