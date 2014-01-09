/*
 * Point.cpp
 *
 *  Created on: Jan 3, 2014
 *      Author: jan-christoph
 */

#include "Point.h"

#include <cstdio>

Point::Point() {
	x = y = 0;
}

Point::Point(const Point & p) {
	x = p.x;
	y = p.y;
}

Point::Point(int a, int b) {
	x = a;
	y = b;
}

Point::~Point() {}

void Point::dump() {
	printf("(%d, %d)\t", x,y);
}

bool Point::operator ==(const Point p) const {
	return p.x == x && p.y == y;
}

bool Point::operator <(const Point p ) const {
	return x < p.x;
}
