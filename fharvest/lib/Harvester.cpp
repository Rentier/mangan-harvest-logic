/*
 * Harvester.cpp
 *
 *  Created on: Jan 2, 2014
 *      Author: jan-christoph
 */

#include "Harvester.h"

#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#include <cstdlib> // abs


using std::cout;
using std::endl;
using std::ifstream;
using std::vector;

/*     n=0 n=1 n=2
 * t=0
 * t=1
 * t=2
 * t=3
 */


Harvester::Harvester(Agent a, int t, int n, Point g) {
	number_of_robots = n;
	steps = t;
	goal = g;	

	traveled = 0;
	collected_cells = new set<Point>();
	data = new Point[steps * number_of_robots];

	switch (a) {
	case HEURISTIC:
		agent = &Harvester::heuristic_agent;
		cout << "Heuristic agent " << endl;
		break;
	case RANDOM:
	default:
		agent = &Harvester::random_agent;
		cout << "Random agent " << endl;
	}
}

Harvester::~Harvester() {
	delete[] data;
}

/*
 * ###
 * # Private
 * ###
 */

/*!
 * @function 	Harvester::index
 * @abstract	Maps 2D coords to 1D index for accessing data buffer
 * @param		t	X coord
 * @param		n	Y coord
 * @return		1D index
 */
int Harvester::index(int t, int n) {
	return t * number_of_robots + n;
}

int Harvester::taxicab_distance(Point u, Point v) {
	return abs(u.x - v.x) + abs(u.y - v.y);
}

/*! @function 	Harvester::in_euclidean_range
 *  @abstract	Computes the eucldiean distance between two points
 *  @discussion I pray for the FSQRT assembly instruction, as alternative to
 *  			to comparing with the squared distance
 */
double Harvester::euclidean_distance(Point u, Point v) {
	int dx = u.x - v.x;
	int dy = u.y - v.y;
	return sqrt( dx*dx +dy*dy );
}

/*!
 * @function 	Harvester::in_range
 * @abstract 	Compute whether point is in range of at least one other
 * @discussion	A point is considered in range when it has a distance of
 * 				equal or less MAX_DISTANCE units
 * 				Does not exclude comparing with itself if in data[t]
 * @param		p 			Point to check for
 * @param		t			Current point in time
 * @return 		True if in range else False
 */
bool Harvester::in_range(Point p, int t) {
	Point v;
	for(int n = 0; n < number_of_robots; n++) {
		v = data[index(t, n)];
		if(euclidean_distance(p, v) <= MAX_DISTANCE)
			return true;
	}
	return false;
}

/*!
 * @function 	Harvester::legal_move
 * @abstract 	Compute whether a move is legal
 * @discussion	A move is legal if the goal can be still reached in time
 * 				and there is at least one robot in range
 * 				Does not exclude comparing with itself if in data[t]
 * @param		p 			Point to check for legality
 * @param		t			Current point in time
 * @param		timeleft 	Time until mission is over
 * @return 		True if move is legal else False
 */
bool Harvester::legal_move(Point p, int t, int timeleft) {
	return taxicab_distance(p, goal) < timeleft && in_range(p, t);
}

/*!
 * @function	Harvester::random_agent
 * @abstract	Compute the state of the nth robot in t-1 stepping to time t
 * @discussion	Based on randomness
 * @param		t 			Current point in time
 * @param		n			Number of the robot
 * @param		timeleft 	Time until mission is over
 */
void Harvester::random_agent(int t, int n, int timeleft) {
	Point p = data[index(t-1,n)];

	vector<Point> neighbours;

	Point left(p.x -1, p.y);
	Point right(p.x +1, p.y);
	Point bottom(p.x, p.y - 1);
	Point top(p.x, p.y + 1);

	if( legal_move(left, t, timeleft )) neighbours.push_back(left);
	if( legal_move(right, t, timeleft )) neighbours.push_back(right);
	if( legal_move(bottom, t, timeleft )) neighbours.push_back(bottom);
	if( legal_move(top, t, timeleft )) neighbours.push_back(top);

	Point move = p;

	if(!neighbours.empty()) {
		int randomIndex = rand() % neighbours.size();
		move = neighbours[randomIndex];
		traveled++;
	}

	data[index(t,n)].x = move.x;
	data[index(t,n)].y = move.y;

	collected_cells->insert(Point(move));
}

/*!
 * @function	Harvester::heuristic_agent
 * @abstract	Compute the state of the nth robot for time t
 * @discussion	Based on a smart heuristic
 * @param		t 			Current point in time
 * @param		n			Number of the robot
 * @param		timeleft 	Time until mission is over
 */
void Harvester::heuristic_agent(int t, int n, int timeleft) {
	random_agent(t,n,timeleft);
}

/*!
 * @function	Harvester::run
 * @abstract	Update loop
 * @discussion	Loop updating the robots. Please remark that
 * 				the agent updates one robot after the other.
 * 				The agent looks at the current state of the board,
 * 				and moves one piece while keeping the constraints in mind.
 */
void Harvester::run() {
	int timeleft;
	for(int t = 1; t < steps; t++ ) {
		timeleft = steps - t;
		for(int n = 0; n < number_of_robots; n++) {
			(this->*agent)(t, n, timeleft);
		}
	}
}

int Harvester::get_traveled() {
	return traveled;
}

double Harvester::get_collected() {
	return collected_cells->size();
}

/*
 * ###
 * # Visualization
 * ###
 */

void Harvester::load(Array3D<int> array) {
	int x, y;
	for(int t = 0; t < steps; t++ ) {
		for(int n = 0; n < number_of_robots; n++) {
			x = array.get(0,n,0);
			y = array.get(0,n,1);
			data[index(t,n)].x = x;
			data[index(t,n)].y = y;
		}
	}
}

void Harvester::extract(Array3D<int> *array) {
	Point p;
	for(int t = 0; t < steps; t++ ) {
		for(int n = 0; n < number_of_robots; n++) {
			p = data[index(t,n)];
			array->set(t,n,0,p.x);
			array->set(t,n,1,p.y);
		}
	}
}

void Harvester::read_points(string filename) {
	string line;
	ifstream input;

	input.open(filename.c_str());

	input >> number_of_robots;

	int x, y;
	for(int n = 0; n < number_of_robots; n++) {
		if(input >> x >> y) {
			data[index(0,n)].x = x;
			data[index(0,n)].y = y;
		} else {
			cout << "Your file is bad, and you should feel bad!";
			return;
		}
	}
}

void Harvester::print_column(int t) {
	for (int n = 0; n < number_of_robots; n++) {
		data[index(t,n)].dump();
		cout << endl;
	}
}

void Harvester::print_finished() {
	for (int n = 0; n < number_of_robots; n++) {
		data[index(steps-1,n)].dump();
		cout << endl;
	}
}

void Harvester::print_harvest() {
	for (int n = 0; n < number_of_robots; n++) {
		for (int t = 0; t < steps; t++) {
			data[index(t,n)].dump();
		}
		cout << endl;
	}
	cout << endl;
}
