# Author: Suki Sahota
#
# This is the Makefile that can be used to create the "PlayerDriver" executable
# To create "PlayerDriver" executable, do:
#	make PlayerDriver
#
# To clean project, do:
#	make clean
#
CXXFLAGS = -ggdb -Wall -std=c++14

PlayerDriver: PlayerDriver.o Player.o
	g++ $(CXXFLAGS) -o PlayerDriver PlayerDriver.o Player.o

PlayerDriver.o: PlayerDriver.cpp Player.h
	g++ $(CXXFLAGS) -c PlayerDriver.cpp

Player.o: Player.cpp Player.h
	g++ $(CXXFLAGS) -c Player.cpp

clean:
	rm -f *.o PlayerDriver

