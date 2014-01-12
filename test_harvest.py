import numpy as np

import fharvest.logic as fhl


ROBO_COUNT = 2
MISSION_TIME = 8
STEPS = MISSION_TIME + 1

GOAL_X = 2
GOAL_Y = 2

data = np.zeros([STEPS, ROBO_COUNT, 2], dtype=int)

data[0][0] = 1, 2
data[0][1] = 3, 4
data[1][0] = 5, 6
data[1][1] = 7, 8

traveled, collected = fhl.harvest(data, "random", GOAL_X, GOAL_Y, STEPS, ROBO_COUNT)
print data
print "Traveled: ", traveled
print "Collected: ", collected
  
