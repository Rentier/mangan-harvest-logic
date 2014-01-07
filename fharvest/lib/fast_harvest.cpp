/*
 * fast_harvest.cpp
 *
 *  Created on: Jan 3, 2014
 *      Author: Jan-Christoph Klie
 */

#include <iostream>
#include <cstdio>

#include "fast_harvest.h"
#include "Harvester.h"
#include "Array3D.h"

using std::cout;
using std::endl;

void start_harvest(int *data, int x, int y, int steps, int number_of_robots) {
	cout << "C++ called from Python" << endl;
	cout << "For real!" << endl;
	Point goal(x,y);

	Array3D<int> arr(steps, number_of_robots, 2, data);	

	Harvester h(steps, number_of_robots, goal);
	h.load(arr);
	h.run();
	h.extract(&arr);
}
