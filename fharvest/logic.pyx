cdef extern from "Point.h":
	cdef cppclass Point:
		Point() except +
		Point(int, int) except +
		int x
		int y
		void dump()	

def test():
	cdef Point *p = new Point(5, 3)
	p.dump()
