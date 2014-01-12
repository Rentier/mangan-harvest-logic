import cython

import numpy as np
cimport numpy as np
from libcpp.string cimport string

cdef extern from "stdint.h":
	ctypedef int int32_t 

cdef extern from "Mission.h":
	cdef cppclass Mission:
		Mission() except +
		
		void start(string, int32_t * , int , int , int, int) except +
		int traveled()
		double collected()

def harvest(np.ndarray[np.int32_t, ndim=3, mode="c"] data not None, 
			agent, 
	        int goal_x, 
	        int goal_y, 
	        int steps, 
	        int number_of_robots): 

	cdef string s = agent

	m, n, o = data.shape[0], data.shape[1], data.shape[2]

	assert m == steps
	assert n == number_of_robots
	assert o == 2

	data = np.ascontiguousarray(data)

	cdef Mission *mission = new Mission()
	mission.start(s, &data[0,0,0], goal_x, goal_y, steps, number_of_robots)
	return mission.traveled(), mission.collected()

	

	
	

