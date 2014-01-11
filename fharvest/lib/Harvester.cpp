/*
 * Harvester.cpp
 *
 *  Created on: Jan 2, 2014
 *      Author: jan-christoph
 */

#include "Harvester.h"

/*     n=0 n=1 n=2
 * t=0
 * t=1
 * t=2
 * t=3
 */
Harvester::Harvester(Array3D<int> * arr, Agent a, Point g) {
	steps = arr->x();
	number_of_robots = arr->y();
	goal = g;	

	traveled = 0;
	collected_cells = new set<Point>();
	collected_edges_upper_left = new set<Point>();
	collected_edges_upper_right = new set<Point>();
	collected_edges_lower_left = new set<Point>();
	collected_edges_lower_right = new set<Point>();
	robots = new Point[number_of_robots];
	data = arr;

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
	delete[] robots;
	delete collected_cells;
	delete collected_edges_upper_left;
	delete collected_edges_upper_right;
	delete collected_edges_lower_left;
	delete collected_edges_lower_right;
}

/*
 * ###
 * # Private
 * ###
 */

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
 * @return 		True if in range else False
 */
bool Harvester::in_range(Point p) {
	Point v;
	for(int n = 0; n < number_of_robots; n++) {
		v = robots[n];
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
bool Harvester::legal_move(Point p, int timeleft) {
	return taxicab_distance(p, goal) < timeleft && in_range(p);
}

bool Harvester::is_harvested(Point p) {
	return collected_cells->count(p);
}

/*!
 * @function	Harvester::random_agent
 * @abstract	Compute the state of the nth robot in t-1 stepping to time t
 * @discussion	Based on randomness
 * @param		t 			Current point in time
 * @param		n			Number of the robot
 * @param		timeleft 	Time until mission is over
 */
void Harvester::random_agent(int n, int timeleft) {
	Point p = robots[n];

	vector<Point> neighbours;

	Point left(p.x -1, p.y);
	Point right(p.x +1, p.y);
	Point bottom(p.x, p.y - 1);
	Point top(p.x, p.y + 1);

	if( legal_move(left, timeleft )) neighbours.push_back(left);
	if( legal_move(right, timeleft )) neighbours.push_back(right);
	if( legal_move(bottom, timeleft )) neighbours.push_back(bottom);
	if( legal_move(top, timeleft )) neighbours.push_back(top);

	Point move = p;

	if(!neighbours.empty()) {
		int randomIndex = rand() % neighbours.size();
		move = neighbours[randomIndex];
		traveled++;
	}

	update_collected(p, move);

	robots[n].x = move.x;
	robots[n].y = move.y;
}

void Harvester::update_collected(Point start, Point end) {
	collected_cells->insert(end);
	Direction dir = get_movement_direction(start, end);

	switch(dir) {
		cout << dir;
		case LEFT:
			collected_edges_lower_left->insert(start);
			collected_edges_upper_left->insert(start);
			collected_edges_lower_right->insert(end);
			collected_edges_upper_right->insert(end);
			break;
		case RIGHT:
			collected_edges_lower_right->insert(start);
			collected_edges_upper_right->insert(start);
			collected_edges_lower_left->insert(end);
			collected_edges_upper_left->insert(end);
			break;
		case UP:
			collected_edges_upper_left->insert(start);
			collected_edges_upper_right->insert(start);
			collected_edges_lower_left->insert(end);
			collected_edges_lower_right->insert(end);
			break;
		case DOWN:
			collected_edges_lower_left->insert(start);
			collected_edges_lower_right->insert(start);
			collected_edges_upper_left->insert(end);
			collected_edges_upper_right->insert(end);
			break;
		case NONE:
		default:
			break;
	}
}

/*!
 * @function	Harvester::heuristic_agent
 * @abstract	Compute the state of the nth robot for time t
 * @discussion	Based on a smart heuristic
 * @param		t 			Current point in time
 * @param		n			Number of the robot
 * @param		timeleft 	Time until mission is over
 */
void Harvester::heuristic_agent(int n, int timeleft) {
	Point p = robots[n];

	vector<Point> neighbours;

	Point left(p.x -1, p.y);
	Point right(p.x +1, p.y);
	Point bottom(p.x, p.y - 1);
	Point top(p.x, p.y + 1);

	if( legal_move(left, timeleft )) neighbours.push_back(left);
	if( legal_move(right, timeleft )) neighbours.push_back(right);
	if( legal_move(bottom, timeleft )) neighbours.push_back(bottom);
	if( legal_move(top, timeleft )) neighbours.push_back(top);

	Point move = p;

	if(!neighbours.empty()) {
		vector<Point> new_neighbours;


		//choose unharvested move
		for(unsigned int i = 0; i < neighbours.size(); i++) {
			if(!is_harvested(Point(neighbours[i]))) {
				new_neighbours.push_back(neighbours[i]);
			}
		}
		if(!new_neighbours.empty()) {
			neighbours = new_neighbours;
		}


		//choose max density direction
		new_neighbours.clear();
		Point topleft;
		Point lookout;
		Point robot;
		signed int score;
		signed int maxscore = std::numeric_limits<int>::min();;
		for(unsigned int nb = 0; nb < neighbours.size(); nb++) {
			score = 0;
			topleft.x = p.x + 2 * (Point(neighbours[nb]).x - p.x) - 2;
			topleft.y = p.y + 2 * (Point(neighbours[nb]).y - p.y) - 2;

			for(unsigned int i = 0; i < 5; i++) {
				for(unsigned int j = 0; j < 5; j++) {
					lookout.x = topleft.x + j;
					lookout.y = topleft.y + i;

					if(!is_harvested(lookout)) {
						score++;
					}
				}
			}

			//potentially expensive computation (hashset for robots? how in c++?)
			for(unsigned int i = 0; i < number_of_robots; i++) {
				if(i == n) {
					continue;
				}

				robot = robots[i];
				if(topleft.x <= robot.x && topleft.y <= robot.y
						&& topleft.x + 5 > robot.x && topleft.y + 5 > robot.y) {
					//penalty if there is another robot in that direction
					score -= 5;
				}
			}

			if(score > maxscore) {
				new_neighbours.clear();
				new_neighbours.push_back(neighbours[nb]);
				maxscore = score;
			} else if(score == maxscore) {
				new_neighbours.push_back(neighbours[nb]);
			}
		}

		/*
		if(!new_neighbours.empty()) {
			neighbours = new_neighbours;
		}
		*/
	}

	if(!neighbours.empty()) {
		int randomIndex = rand() % neighbours.size();
		move = neighbours[randomIndex];
		traveled++;
	}

	update_collected(p, move);

	robots[n].x = move.x;
	robots[n].y = move.y;
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
			(this->*agent)(n, timeleft);
			Point p = robots[n];
			data->set(t,n,0, p.x);
			data->set(t,n,1, p.y);

		}
	}
}

int Harvester::get_traveled() {
	return traveled;
}

double Harvester::get_collected() {
	double collected = 0.0;
	collected += collected_edges_lower_left->size() * EDGE_AREA;
	collected += collected_edges_upper_left->size() * EDGE_AREA;
	collected += collected_edges_lower_right->size() * EDGE_AREA;
	collected += collected_edges_upper_right->size() * EDGE_AREA;
	collected += collected_cells->size() * CIRCLE_AREA;
	return collected;
}

/*
 * ###
 * # Visualization
 * ###
 */

void Harvester::load(Array3D<int> array) {
	int x, y;
	for (int n = 0; n < number_of_robots; n++) {
		x = array.get(0, n, 0);
		y = array.get(0, n, 1);
		robots[n] = Point(x,y);
	}
}

void Harvester::read_points(string filename) {
	string line;
	ifstream input;

	input.open(filename.c_str());

	input >> number_of_robots;

	int x, y;
	for(int n = 0; n < number_of_robots; n++) {
		if (input >> x >> y) {
			robots[n].x = x;
			robots[n].y = y;
			data->set(0,n,0, x);
			data->set(0,n,1, y);
		} else {
			cout << "Your file is bad, and you should feel bad!";
			return;
		}
	}
}

void Harvester::print_robot(int t, int n) {
	int x,y;
	x = data->get(t,n,0);
	y = data->get(t,n,1);
	printf("(%d, %d) ", x,y);
}

void Harvester::print_finished() {
	for (int n = 0; n < number_of_robots; n++) {
		print_robot(0,n);
		cout << endl;
	}
}

void Harvester::print_harvest() {
	for (int n = 0; n < number_of_robots; n++) {
		for (int t = 0; t < steps; t++) {
			print_robot(t,n);
		}
		cout << endl;
	}
	cout << endl;
}
