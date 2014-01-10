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
	Point(const Point&);
	Point(int, int);
	virtual ~Point();

	int x;
	int y;

	void dump();
	bool operator <(const Point) const;

};

#endif /* POINT_H_ */
