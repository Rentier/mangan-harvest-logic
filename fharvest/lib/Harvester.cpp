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

#include <stdlib.h> // abs

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

Harvester::Harvester(int t, int n, Point g) {
	number_of_robots = n;
	steps = t;
	goal = g;	
	data = new Point[steps * number_of_robots];
}

Harvester::~Harvester() {
	delete[] data;
}

/*
 * ###
 * # Private
 * ###
 */

int Harvester::index(int t, int n) {
	return t * number_of_robots + n;
}

int Harvester::taxicab_distance(Point u, Point v) {
	return abs(u.x - v.x) + abs(u.y - v.y);
}

bool Harvester::in_range(Point p, int t) {
	for(int n = 0; n < number_of_robots; n++) {
		if( taxicab_distance(p, data[index(t, n)]) <= MAX_DISTANCE - 2)
			return true;
	}
	return false;
}

bool Harvester::legal_move(Point p, int t, int timeleft) {
	return taxicab_distance(p, goal) < timeleft && in_range(p, t);
}

void Harvester::random_agent(int t, int n, int timeleft) {
	Point p = data[index(t-1,n)];

	vector<Point> neighbours;

	Point left(p.x -1, p.y);
	Point right(p.x +1, p.y);
	Point bottom(p.x, p.y - 1);
	Point top(p.x, p.y + 1);

	if( legal_move(left, t-1, timeleft )) neighbours.push_back(left);
	if( legal_move(right, t-1, timeleft )) neighbours.push_back(right);
	if( legal_move(bottom, t-1, timeleft )) neighbours.push_back(bottom);
	if( legal_move(top, t-1, timeleft )) neighbours.push_back(top);

	if(!neighbours.empty()) {
		int randomIndex = rand() % neighbours.size();
		Point j = neighbours[randomIndex];
		data[index(t,n)].x = j.x;
		data[index(t,n)].y = j.y;
	} else {
		data[index(t,n)].x = p.x;
		data[index(t,n)].y = p.y;
	}
}

void Harvester::run() {
	int timeleft;
	for(int t = 1; t < steps; t++ ) {
		timeleft = steps - t;
		for(int n = 0; n < number_of_robots; n++) {
			random_agent(t, n, timeleft);
		}
	}
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
			x = array.get(t,n,0);
			y = array.get(t,n,1);
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





