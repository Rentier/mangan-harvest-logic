/*
 * Mission.h
 *
 *  Created on: Jan 8, 2014
 *      Author: jan-christoph
 */

#ifndef MISSION_H_
#define MISSION_H_

#include "Harvester.h"
#include "Agent.h"

class Mission {

private:
	Harvester *h;

public:
	Mission();
	virtual ~Mission();

	void start(Agent, int * , int , int , int, int);
	int traveled();
	double collected();
};

#endif /* MISSION_H_ */
