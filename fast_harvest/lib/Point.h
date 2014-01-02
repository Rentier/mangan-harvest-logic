/*
 * point.h
 *
 *  Created on: Jan 2, 2014
 *      Author: Jan-Christoph Klie
 */

#ifndef POINT_H_
#define POINT_H_

#include <cstdio>

struct Point {
	int x;
	int y;

	Point(int u, int v) : x(u), y(v) {}
	Point() : x(0), y(0) {}

	void print() {
		printf("(%d, %d)\t", x,y);
	}
};


#endif /* POINT_H_ */
