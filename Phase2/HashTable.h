/*
* the interface definition of HashTable
*/
#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <string>
#include <iostream>
#include <list>
#include <vector>
typedef struct Value {
	Value( int _fileID, int _lineNumber) {
		fileID = _fileID;
		lineNumber = _lineNumber;
	}
	int fileID; // the fileID can help us to find the file's path
	int lineNumber;
	bool operator == (const Value & another) const{
		return fileID==another.fileID && lineNumber==another.lineNumber;
	}
	bool operator < (const Value & another)const{
		    return  fileID==another.fileID ? lineNumber< another.lineNumber : fileID< another.fileID ;
	}
}Value;
typedef struct Entry {
	std::string key; //
	size_t hash; //used for speed re-hash
	std::list<Value> values;
	Entry* next;
}Entry;
class HashTable
{
public:
	// the load factor 
	const float LOAD_FACTOR = 0.75f;  //if size/capacity >= LOAD_FACTOR then expand the table and reHash
	const int INITIAL_CAPACITY = 16;
	HashTable();
	~HashTable();
	//get the table entry pointer by the key.
	Entry * getEntry(std::string key);
	// insert a value to the corresponding entry's value list
	// if the entry of this key has not been created, then
	// create it and push the value into its value list
	void insert(std::string key, Value value);

//get all the entrys whose key's lowercase  is the same as the parameter. used for query insensitive
	std::vector<Entry *>  getAllLowercaseEntry(std::string lowercase);


		// these 2 getter is used for unit_test
	size_t get_capacity() const
	{
		return capacity;
	}

	size_t get_size() const
	{
		return size;
	}

private:
	//my hash function , it will use the lowercase format of
	//given string to compute the hash value, so all the words
	//in case insensitive will has the same index. This will help
	//the gerp to query insensitively.
	size_t myHash(std::string original_string);

	//the re-Hash algorithm for expanding the table capacity
	//when its size reaches the load factor
	void reHash();
	Entry** table;
	size_t capacity = INITIAL_CAPACITY;
	size_t size = 0;
};

#endif