/*
 * Array3D.cpp
 *
 *  Created on: Jan 3, 2014
 *      Author: jan-christoph
 */

#include <iostream>
#include "Array3D.h"

 using std::cout;
 using std::endl;

template<class T>
Array3D<T>::Array3D( int x,  int y,  int z, T *data) {
	xdim = x;
	ydim = y;
	zdim = z;
	buffer = data;
}

template<class T>
Array3D<T>::~Array3D() {}

template<class T>
int Array3D<T>::index(int x, int y,  int z) {
	return (x * ydim + y) * zdim + z;
}

template<class T>
T Array3D<T>::get( int x, int y, int z) {
	return buffer[index(x,y,z)];
}

template<class T>
void Array3D<T>::set( int x,  int y, int z ,T n) {
	buffer[index(x,y,z)] = n;
}

template<class T>
int Array3D<T>::x() {
	return xdim;
}

template<class T>
int Array3D<T>::y() {
	return ydim;
}

template<class T>
int Array3D<T>::z() {
	return zdim;
}

template<class T>
void Array3D<T>::dump() {
	for (int x = 0; x < xdim; x++) {
		for (int y = 0; y < ydim; y++) {
			for (int z = 0; z < zdim; z++) {				
				cout << get(x,y,z);
			}
			cout <<  endl;
		}
		cout <<  endl;
	}
}

template class Array3D<int>;
