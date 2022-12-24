/*
* the interface definition of Gerp
*/


#ifndef __GERP_H__
#define __GERP_H__
#include "HashTable.h"
#include "FSTree.h"
#include "DirNode.h"
#include <vector>
#include <list>
#include  <fstream>

typedef struct {
	std::string path;
	std::vector<std::string> lines;
}File;

class Gerp
{
public:
	//default constructor
	Gerp();
	//generate the vector filePaths  by the FSTree
	//this will be called by run()
	void generateFileVec(FSTree& tree);
	//build index of each file's content using filePaths vector
	//this will be called by void generateFileVec(FSTree& tree);
	void buildIndex(std::string path);
	//query a word true: found it ; false: not found
	//this will be called by run()
	bool query(std::string word, bool isCaseInsensitive);
	//save the query result to the output file
	//this will be called by query
	void dump(std::list<Value> & values, std::ostream& out);
	// firstly build the index. 
	// then use a loop for getting command from input, and execute the command
	//this will be called by main.cpp: main()
	void run(FSTree& tree, std::string outputFileName);

private:
	//a helper for generate file vector and build the file content index
	void TraverseFileTree(DirNode* node, std::string prefix);
	HashTable hashTable;
	std::ofstream outfile; // the file where the query information output to;
	std::vector<File> files; // each file's information the path and content of each line
	//the subscript of this vector is the ID of the file, this will be used in hashtable
};

#endif
