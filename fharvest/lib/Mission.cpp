/*
 * Mission.cpp
 *
 *  Created on: Jan 8, 2014
 *      Author: Jan-Christoph Klie
 */

#include <iostream>
#include <cstdio>

#include "Mission.h"
#include "Array3D.h"
#include "Agent.h"

using std::cout;
using std::endl;

Mission::Mission() {
	h = NULL;
}

Mission::~Mission() {
	if(h != NULL) delete h;
}

void Mission::start(Agent agent, int *data, int x, int y, int steps, int number_of_robots) {
	cout << "C++ called from Python" << endl;
	Point goal(x,y);

	Array3D<int> * arr = new Array3D<int>(steps, number_of_robots, 2, data);
	h = new Harvester(arr, agent, goal);
	h->run();
}

int Mission::traveled() {
	return h->get_traveled();
}

double Mission::collected() {
	return h->get_collected();
}

