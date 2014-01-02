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
	mission_time = t;
	number_of_robots = n;
	goal = g;
	steps = mission_time + 1;
	data = new Point[number_of_robots * steps];
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
	return t*number_of_robots + n;
}

int Harvester::taxicab_distance(Point u, Point v) {
	return abs(u.x - v.x) + abs(u.y - v.y);
}

void Harvester::random_agent(int t, int n, int timeleft) {
	Point p = data[index(t-1,n)];

	vector<Point> neighbours;

	Point left(p.x -1, p.y);
	Point right(p.x +1, p.y);
	Point bottom(p.x, p.y - 1);
	Point top(p.x, p.y + 1);

	if( taxicab_distance(left, goal) < timeleft ) neighbours.push_back(left);
	if( taxicab_distance(right, goal) < timeleft ) neighbours.push_back(right);
	if( taxicab_distance(bottom, goal) < timeleft ) neighbours.push_back(bottom);
	if( taxicab_distance(top, goal) < timeleft ) neighbours.push_back(top);

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
			//cout << x << " " << y << endl;
		} else {
			cout << "Your file is bad, and you should feel bad!";
			return;
		}
	}
}

void Harvester::print_finished() {
	for (int n = 0; n < number_of_robots; n++) {
		data[index(steps-1,n)].print();
		cout << endl;
	}
}

void Harvester::print_harvest() {
	for (int n = 0; n < number_of_robots; n++) {
		for (int t = 0; t < steps; t++) {
			data[index(t,n)].print();
		}
		cout << endl;
	}
	cout << endl;

}





