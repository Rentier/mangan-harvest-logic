/*
 * Direction.cpp
 *
 *  Created on: Jan 10, 2014
 *      Author: jan-christoph
 */

#include "Direction.h"

Direction get_movement_direction(Point origin, Point next) {
	int dx  = origin.x - next.x;
	int dy  = origin.y - next.y;

	if(dx == 0 && dy == 0) {
		return NONE;
	}

	if(dx == 0) {
		assert(dy == -1 || dy == 1);
		return dy == 1 ? UP : DOWN;
	} else { // dy == 0
		assert( dy == 0);
		assert( dx == -1 || dx == 1);
		return dy == 1 ? RIGHT : LEFT;
	}
}
