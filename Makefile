#
# Makefile for Six Degrees
#
# Project 2 (fall 2020)
#

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++11 
INCLUDES = $(shell echo *.h)

SixDegrees: main.o SixDegrees.o CollabGraph.o Artist.o
	${CXX} -o $@ $^

SixDegrees.o: SixDegrees.cpp SixDegrees.h CollabGraph.h Artist.h
	$(CXX) $(CXXFLAGS) -c SixDegrees.cpp
	
CollabGraph.o: CollabGraph.cpp CollabGraph.h Artist.h
		$(CXX) $(CXXFLAGS) -c CollabGraph.cpp
		
Artist.o: Artist.cpp Artist.h
	$(CXX) $(CXXFLAGS) -c Artist.cpp
	
# The below rule will be used by unit_test.
unit_test: unit_test_driver.o SixDegrees.o CollabGraph.o Artist.o
	$(CXX) $(CXXFLAGS) $^

%.o: %.cpp ${INCLUDES}
	${CXX} ${CXXFLAGS} -c $<

clean:
	rm -rf SixDegrees *.o *.dSYM
