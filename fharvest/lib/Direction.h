/*
 * Direction.h
 *
 *  Created on: Jan 10, 2014
 *      Author: Jan-Christoph Klie
 */

#ifndef DIRECTION_H_
#define DIRECTION_H_

#include <cassert>

#include "Point.h"

enum Direction {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NONE
};

Direction get_movement_direction(Point, Point);

#endif /* DIRECTION_H_ */
