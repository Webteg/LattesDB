main: load_file.o pugixml.o
	g++ -o main load_file.o pugixml.o

load_file.o: load_file.cpp
	g++ -c -o load_file.o -Iincludes load_file.cpp

pugixml.o: includes/pugixml.cpp includes/pugixml.hpp
	gcc -g -c includes/pugixml.cpp includes/pugixml.hpp

clean: 
	rm -f *.o
