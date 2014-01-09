/*
 * main.cpp
 *
 *  Created on: Jan 3, 2014
 *      Author: Jan-Christoph Klie
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>
#include <cassert>
#include "Point.h"

#include "Harvester.h"
#include "Agent.h"
#include "Array3D.h"

using namespace std;

int main() {
	int mission_time;
	int number_of_robots;
	Point goal;
	string path;
	bool print = true;

	int choice = 10;

	if(choice == 2) {
		mission_time = 8;
		number_of_robots = 2;
		goal.x = 2;
		goal.y = 2;
		path = "robots_002.txt";
	}else if (choice == 4) {
		mission_time = 400;
		number_of_robots = 4;
		goal.x = 300;
		goal.y = 300;
		path = "robots_004.txt";
	} else if (choice == 10) {
		mission_time = 282;
		number_of_robots = 10;
		goal.x = 1569;
		goal.y = 4011;
		path = "robots_010.txt";
	} else if (choice == 20) {

	} else if (choice == 100) {
		mission_time = 2 * 1141;
		number_of_robots = 100;
		goal.x = 5821;
		goal.y = 6711;
		path = "robots_100.txt";
		print = false;
	}

	int steps = mission_time + 1;

	Harvester h(HEURISTIC, steps, number_of_robots, goal);
	h.read_points("fixtures/" + path);
	h.run();

	int *buffer = new int[steps * number_of_robots * 2];
	Array3D<int> arr(steps, number_of_robots, 2, buffer);

	h.extract(&arr);

	cout << "Final positions: " << endl;
	h.print_harvest();
	cout << "Goal: ";
	goal.dump();
	cout << endl;
	cout << "Steps:  " << steps << endl;
	cout << "Collected: " << h.get_collected() << endl;
	cout << "Traveled: " << h.get_traveled() << endl;

	cout << "Max traveled: " << number_of_robots * steps << endl;
	cout << "Max collected: " << "Magic formula" << endl;
	cout << "Percentage: " << "Insert here" << endl;

	return 0;
}

