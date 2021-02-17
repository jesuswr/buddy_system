all : test_buddy_system

test_buddy_system : main.cpp buddy_system.o
	g++ -Wall -O2 -o test_buddy_system main.cpp buddy_system.o

buddy_system.o: buddy_system.cpp buddy_system.hpp
	g++ -Wall -O2 -c buddy_system.cpp

clean:
	rm *.o test_buddy_system