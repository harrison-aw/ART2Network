/*
 * Vector.h
 *
 *  Created on: May 1, 2013
 *      Author: ah1411
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include "nntypes.h"

namespace art2nn {

template<class T> class Vector;
template<class T> Vector<T> operator+(const Vector<T>&, const Vector<T>&);
template<class T> Vector<T> operator-(const Vector<T>&, const Vector<T>&);
template<class T> Vector<T> operator*(T, const Vector<T>&);
template<class T> Vector<T> operator*(const Vector<T>&, T);
template<class T> T operator*(const Vector<T>&, const Vector<T>&);

template<class T>
class Vector {
public:
	Vector();
	Vector(const Vector<T> &vector);
	explicit Vector(dimension n);
	virtual ~Vector();

	Vector<T> &operator=(const Vector<T> &vector);
	Vector<T> &operator+=(const Vector<T> &vector);
	Vector<T> &operator-=(const Vector<T> &vector);
	Vector<T> &operator*=(T scalar);
	Vector<T> operator-() const;
	T &operator[](index i);
	friend Vector<T> operator+<T>(const Vector<T> &left, const Vector<T> &left);
	//friend Vector<T> operator-<T>(const Vector<T> &left, const Vector<T> &left);
	friend Vector<T> operator*<T>(T left, const Vector<T> &right);
	friend Vector<T> operator*<T>(const Vector<T> &left, T right);
	friend T operator*<T>(const Vector<T> &left, const Vector<T> &right);

	T norm() const;

private:
	dimension n;
	T *coords;
};

template<class T>
Vector<T>::Vector():
	n(0), coords(NULL) {
}

template<class T>
Vector<T>::Vector(const Vector<T> &vector):
	n(vector.n) {
	coords = new T[n];
	for (index i = 0; i < n; ++i) {
		coords[i] = 0;
	}
}

template<class T>
Vector<T>::Vector(dimension n):
	n(n) {
	coords = new T[n];
	for (index i = 0; i < n; ++i) {
		coords[i] = 0;
	}
}

template<class T>
Vector<T>::~Vector() {
	if (coords != NULL)
		delete coords;
}

template<class T>
Vector<T> &Vector<T>::operator=(const Vector<T> &vector) {
	if (this != &vector) {
		delete coords;
		n = vector.n;
		coords = new T[n];
		for (index i = 0; i < n; ++i)
			coords[i] = vector.coords[i];
	}
	return *this;
}

template<class T>
Vector<T> &Vector<T>::operator+=(const Vector<T> &vector) {
	if (n != vector.n)
		throw dimension_error("vector dimensions must be equal to add");

	for (index i = 0; i < n; ++i) {
		coords[i] += vector.coords[i];
	}

	return *this;
}

template<class T>
Vector<T> &Vector<T>::operator-=(const Vector<T> &vector) {
	return *this += -vector;
}

template<class T>
Vector<T> Vector<T>::operator-() const {
	Vector negation(n);
	for (index i = 0; i < n; ++i)
		negation.coords[i] = -coords[i];
	return negation;
}

template<class T>
T &Vector<T>::operator[](index i) {
	if (i >= n)
		throw dimension_error("index beyond vector dimensions");
	return coords[i];
}

template<class T>
Vector<T> operator+(const Vector<T> &left, const Vector<T> &right) {
	if (left.n != right.n)
		throw dimension_error("cannot add vectors of different dimensions");
	Vector<T> sum(left);
	return sum += right;
}

template<class T>
Vector<T> operator-(const Vector<T> &left, const Vector<T> &right) {
	if (left.n != right.n)
		throw dimension_error("cannot subtract vectors of different dimensions");
	Vector<T> difference(left);
	return difference -= right;
}

template<class T>
Vector<T> &Vector<T>::operator*=(T scalar) {
	for (index i = 0; i < n; ++i)
		coords[i] = scalar * coords[i];
	return *this;
}

template<class T>
Vector<T> operator*<T>(T left, const Vector<T> &right) {
	Vector<T> product(right);
	return product *= left;
}
/*
template<class T>
Vector<T> operator*<T>(const Vector<T> &left, T right) {
	return right * left;
}

template<class T>
T operator*<T>(const Vector<T> &left, const Vector<T> &right) {
	if (left.n != right.n)
		throw dimension_error("cannot take the dot product of vectors of different dimensions");
	T product = 0.0;
	for (index i = 0; i < left.n; ++i)
		product += left[i] * right[i];
	return T;
}
*/

} /* namespace art2nn */
#endif /* VECTOR_H_ */
