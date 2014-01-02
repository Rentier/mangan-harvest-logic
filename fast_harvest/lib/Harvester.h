/*
 * Harvester.h
 *
 *  Created on: Jan 2, 2014
 *      Author: jan-christoph
 */

#ifndef HARVESTER_H_
#define HARVESTER_H_

#include <string>

#include "Point.h"

using std::string;

class Harvester {

private:
	Point goal;
	int number_of_robots;
	int mission_time;
	int steps;
	Point *data;

	inline int index(int, int);
	inline int taxicab_distance(Point, Point);
	void random_agent(int, int, int);


public:
	void run(void);
	void print_harvest(void);
	void print_finished(void);
	void read_points(string);

	Harvester(int t, int n, Point);
	virtual ~Harvester();

};

#endif /* HARVESTER_H_ */
