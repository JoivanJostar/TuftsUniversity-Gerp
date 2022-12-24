#include "DirNode.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

/*
  * default constructor creates empty dirNode;
  */
DirNode::DirNode() {
	this->parent = NULL;
}
/*
 * Constructor that sets the name of the node.
 */
DirNode::DirNode(std::string newName) {
	this->name = newName;
	this->parent = NULL;
}

/*
 * Copy Constructor
 */
DirNode::DirNode(const DirNode& other) {
	this->name = other.name;
	this->parent = other.parent;
	this->directories = other.directories;
	this->fileNames = other.fileNames;
}

/*
 * assignment overload
 */
DirNode& DirNode::operator=(const DirNode& other) {
	this->name = other.name;
	this->parent = other.parent;
	this->directories = other.directories;
	this->fileNames = other.fileNames;
	return *this;
}

/*
 * Adds a file with the name "newName" to the
 * current node
 */
void DirNode::addFile(std::string newName) {
	this->fileNames.push_back(newName);
}

/*
 * adds a sub directory (newDir) to the current node
 */
void DirNode::addSubDirectory(DirNode* newDir) {
	this->directories.push_back(newDir);
	newDir->setParent(this);
}

/*
 * returns true if there are sub directories in the
 * current node
 */
bool DirNode::hasSubDir() {
	return !this->directories.empty();
}

/*
 * returns true if there are files in the current node
 */
bool DirNode::hasFiles() {
	return !this->fileNames.empty();
}

/*
 * returns true if there are no files or sub directories
 * in the current node
 */
bool DirNode::isEmpty() {
	return this->fileNames.empty() && this->directories.empty();
}

/*
 * returns the number of sub directories
 */
int DirNode::numSubDirs() {
	return (int)this->directories.size();
}

/*
 * returns the number of files in the current node
 */
int DirNode::numFiles() {
	return (int)(this->fileNames.size());
}

/*
 * set the name of the current node
 */
void DirNode::setName(std::string newName) {
	this->name = newName;
	//this->directories.clear();
	//this->fileNames.clear();
	//this->parent = NULL;
}

/*
 * returns the name of the current directory
 */
std::string DirNode::getName() {
	return this->name;
}

/*
 * returns the nth subdirectory
 */
DirNode* DirNode::getSubDir(int n) {
	return this->directories[n];
}

/*
 * returns nth file name
 */
std::string DirNode::getFile(int n) {
	return this->fileNames[n];
}

/*
 * get parent directory node
 */
DirNode* DirNode::getParent() {
	return this->parent;
}

/*
 * set parent directory node
 */
void DirNode::setParent(DirNode* newParent) {
	this->parent = newParent;
}