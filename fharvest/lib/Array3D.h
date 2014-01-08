/*
 * Array3D.h
 *
 *  Created on: Jan 3, 2014
 *      Author: jan-christoph
 */

#ifndef ARRAY3D_H_
#define ARRAY3D_H_

template<class T>
class Array3D {
private:
	T * buffer;
	int xdim;
	int ydim;
	int zdim;

	int index(int,int,int);

public:
	Array3D(int, int, int, T *);
	virtual ~Array3D();

	T get(int, int, int);
	void set(int, int, int ,T);

	int x();
	int y();
	int z();
	void dump();

};


#endif /* ARRAY3D_H_ */
