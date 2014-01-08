/*
 * Point.h
 *
 *  Created on: Jan 3, 2014
 *      Author: jan-christoph
 */

#ifndef POINT_H_
#define POINT_H_

class Point {
private:

public:
	Point();
	Point(int, int);
	virtual ~Point();

	void dump();

	int x;
	int y;
};

#endif /* POINT_H_ */
