all : test_buddy_system unit_test

test_buddy_system : main.cpp buddy_system.o
	g++ -Wall -O2 -fprofile-arcs -ftest-coverage -o test_buddy_system main.cpp buddy_system.o

unit_test: tests.cpp buddy_system.o catch_amalgamated.o
	g++ -Wall -O2 -fprofile-arcs -ftest-coverage -o unit_test tests.cpp catch_amalgamated.o buddy_system.o

buddy_system.o: buddy_system.cpp buddy_system.hpp
	g++ -Wall -O2 -fprofile-arcs -ftest-coverage -c buddy_system.cpp

catch_amalgamated.o: catch_amalgamated.cpp catch_amalgamated.hpp
	@echo "Sorry, tarda un poco compilando las pruebas unitarias"
	g++ -Wall -O2 -fprofile-arcs -ftest-coverage -c catch_amalgamated.cpp

clean:
	rm *.o test_buddy_system unit_test *.gcov *.gcda *.gcno