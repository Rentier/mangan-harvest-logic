/*
 * Point.h
 *
 *  Created on: Jan 3, 2014
 *      Author: jan-christoph
 */

#ifndef POINT_H_
#define POINT_H_

 #include <inttypes.h>

class Point {
private:

public:
	Point();
	Point(int32_t, int32_t);
	virtual ~Point();

	void dump();

	int32_t x;
	int32_t y;
};

#endif /* POINT_H_ */
