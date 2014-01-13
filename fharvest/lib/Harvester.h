/*
 * Harvester.h
 *
 *  Created on: Jan 2, 2014
 *      Author: Jan-Christoph Klie
 */

#ifndef HARVESTER_H_
#define HARVESTER_H_

#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <set>
#include <string>
#include <cstdlib> // abs
#include <limits>
#include <map>
#include <algorithm>

#include "Point.h"
#include "Array3D.h"
#include "Agent.h"
#include "Direction.h"

using std::set;
using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::vector;
using std::remove_copy_if;

const int MAX_DISTANCE = 200;
const double EDGE_AREA = (4-M_PI) / 16.;
const double CIRCLE_AREA = M_PI / 4.;

class Harvester {

	typedef void (Harvester::*AGENT_FN) ( int, int );

private:
	int number_of_robots;
	int steps;
	int traveled;
	Point goal;
	Point *robots;
	Array3D<int> * data;
	AGENT_FN agent;

	set<Point> *collected_cells;
	set<Point> *collected_edges_upper_left;
	set<Point> *collected_edges_upper_right;
	set<Point> *collected_edges_lower_left;
	set<Point> *collected_edges_lower_right;

	inline int taxicab_distance(Point, Point);
	inline double euclidean_distance(Point, Point);
	inline bool in_range(Point);
	inline bool legal_move(Point, int);
	inline bool is_harvested(Point p);
	vector<Point> get_valid_neighbours(Point, int);
	void update_collected(Point, Point);
	void random_agent(int, int);
	void heuristic_agent(int, int);
	vector<Point> choose_unharvested_move(vector<Point>);
 	vector<Point> choose_max_density_move(Point, int, vector<Point>);
 	vector<Point> choose_max_distance_move(Point, int, vector<Point>);

public:
	Harvester(Array3D<int> *, Agent, Point);
	virtual ~Harvester();

	void run();
	void load();
	void extract(Array3D<int> *);

	int get_traveled();
	int get_visited();
	double get_collected();

	void print_robot(int, int);
	void print_finished(void);
	void print_harvest(void);

	void read_points(string);
};

#endif /* HARVESTER_H_ */
