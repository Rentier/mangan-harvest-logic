/*
 * Harvester.h
 *
 *  Created on: Jan 2, 2014
 *      Author: Jan-Christoph Klie
 */

#ifndef HARVESTER_H_
#define HARVESTER_H_

#include <string>
#include <set>

#include "Point.h"
#include "Array3D.h"
#include "Agent.h"

using std::string;
using std::set;

const int MAX_DISTANCE = 200;

class Harvester {

	typedef void (Harvester::*AGENT_FN) ( int, int, int );

private:
	Point goal;
	int number_of_robots;
	int steps;
	Point *data;
	AGENT_FN agent;
	int traveled;
	set<Point> *collected_cells;

	inline int index(int, int);
	inline int taxicab_distance(Point, Point);
	inline double euclidean_distance(Point, Point);
	inline bool in_range(Point, int);
	inline bool legal_move(Point, int, int);
	void random_agent(int, int, int);
	void heuristic_agent(int, int, int);

public:
	Harvester(Agent, int, int, Point);
	virtual ~Harvester();

	void run();
	void load(Array3D<int>);
	void extract(Array3D<int> *);

	int get_traveled();
	double get_collected();

	void print_column(int);
	void print_finished(void);
	void print_harvest(void);

	void read_points(string);
};

#endif /* HARVESTER_H_ */
