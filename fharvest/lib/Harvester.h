/*
 * Harvester.h
 *
 *  Created on: Jan 2, 2014
 *      Author: Jan-Christoph Klie
 */

#ifndef HARVESTER_H_
#define HARVESTER_H_

#include <string>

#include "Point.h"
#include "Array3D.h"

using std::string;

const int MAX_DISTANCE = 200;

class Harvester {

private:
	Point goal;
	int number_of_robots;
	int steps;
	Point *data;

	inline int index(int, int);
	inline int taxicab_distance(Point, Point);
	inline bool in_range(Point, int);
	inline bool legal_move(Point, int, int);
	void random_agent(int, int, int);

public:
	void run(void);
	void load(Array3D<int>);
	void extract(Array3D<int> *);
	void print_column(int);
	void print_finished(void);
	void print_harvest(void);

	void read_points(string);

	Harvester(int t, int n, Point);
	virtual ~Harvester();

};

#endif /* HARVESTER_H_ */
