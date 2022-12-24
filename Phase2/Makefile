CC = clang++
CFLAGS = -Wall -Wpedantic -Wshadow -Wextra -std=c++11 -O2

gerp: HashTable.o main.o Gerp.o DirNode.o FSTree.o stringProcessing.o
	$(CC) $(CXXFLAGS) -o gerp $^
HashTable.o: HashTable.cpp HashTable.h stringProcessing.h
	$(CC) $(CXXFLAGS) -c HashTable.cpp
Gerp.o: Gerp.cpp HashTable.h stringProcessing.h FSTree.h DirNode.h Gerp.h
	$(CC) $(CXXFLAGS) -c Gerp.cpp
stringProcessing.o: stringProcessing.cpp stringProcessing.h
	$(CC) $(CXXFLAGS) -c stringProcessing.cpp
main.o: main.cpp Gerp.h
	$(CC) $(CXXFLAGS) -c main.cpp 
unit_test: unit_test_driver.o stringProcessing.o HashTable.o
	$(CC) $(CXXFLAGS) $^
clean:
	rm -rf Gerp.o
	rm -rf HashTable.o
	rm -rf main.o
	rm -rf StringProcessing.o
