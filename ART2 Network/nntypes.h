/*
 * types.h
 *
 *  Created on: May 1, 2013
 *      Author: ah1411
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <cstddef>
#include <stdexcept>

namespace art2nn {

typedef size_t index;
typedef size_t dimension;

class dimension_error: public std::length_error {
public:
	explicit dimension_error(const std::string &what_arg): std::length_error(what_arg) {};
};

} /* namespace art2nn */

#endif /* TYPES_H_ */
