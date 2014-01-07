/*
 * Harvester.h
 *
 *  Created on: Jan 2, 2014
 *      Author: Jan-Christoph Klie
 */

#ifndef HARVESTER_H_
#define HARVESTER_H_

#include <string>
#include <inttypes.h>

#include "Point.h"
#include "Array3D.h"



using std::string;

const int32_t MAX_DISTANCE = 200;

class Harvester {

private:
	Point goal;
	int32_t number_of_robots;
	int32_t steps;
	Point *data;

	inline int32_t index(int32_t, int32_t);
	inline int32_t taxicab_distance(Point, Point);
	inline bool in_range(Point, int32_t);
	inline bool legal_move(Point, int32_t, int32_t);
	void random_agent(int32_t, int32_t, int32_t);

public:
	void run(void);
	void load(Array3D<int32_t>);
	void extract(Array3D<int32_t> *);
	void print_column(int32_t);
	void print_finished(void);
	void print_harvest(void);

	void read_points(string);

	Harvester(int32_t t, int32_t n, Point);
	virtual ~Harvester();

};

#endif /* HARVESTER_H_ */
