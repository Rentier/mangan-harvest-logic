/*
 * Array3D.h
 *
 *  Created on: Jan 3, 2014
 *      Author: jan-christoph
 */

#ifndef ARRAY3D_H_
#define ARRAY3D_H_

#include <inttypes.h>

template<class T>
class Array3D {
private:
	T * buffer;
	int32_t xdim;
	int32_t ydim;
	int32_t zdim;

	int32_t index(int32_t,int32_t,int32_t);

public:
	Array3D(int32_t, int32_t, int32_t, T *);
	virtual ~Array3D();

	T get(int32_t, int32_t, int32_t);
	void set(int32_t, int32_t, int32_t ,T);

	int32_t x();
	int32_t y();
	int32_t z();
	void dump();

};


#endif /* ARRAY3D_H_ */
