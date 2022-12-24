/*
* the implementation of HashTable
*/

#include "HashTable.h"
#include <functional>
#include  <string.h>
#include "stringProcessing.h"
using namespace std;

//constructor
HashTable::HashTable()
{
	this->table = new Entry*[INITIAL_CAPACITY];
	this->capacity = INITIAL_CAPACITY;
	memset(this->table, 0, sizeof(Entry*) * capacity);
	this->size = 0;
}

HashTable::~HashTable()
{
	for (size_t i = 0; i < capacity; ++i)
	{
		Entry* e = table[i];
		while (e)
		{
			Entry* next = e->next;
			delete e;
			e = next;
		}
	}
	delete[] this->table;
}
// get the hash value use the lowercase of parameter string
size_t HashTable::myHash(std::string original_string)
{
	return std::hash<string>{}(toLowercase(original_string));
}
//expand and rehash algorithm
void HashTable::reHash()
{
	size_t oldCapacity = this->capacity;
	size_t newCapacity = oldCapacity *2 ;
	Entry** newTable = new Entry * [newCapacity];
	memset(newTable, 0, sizeof(Entry*) * newCapacity);
	for (size_t i = 0; i < oldCapacity; ++i)
	{
		Entry* e = table[i];
		while(e)
		{
			Entry* next = e->next;
			e->next = nullptr;
			size_t newIndex = e->hash % newCapacity;
			if (newTable[newIndex] == nullptr)
				newTable[newIndex] = e;
			else
			{
				e->next = newTable[newIndex];
				newTable[newIndex] = e;
			}
			e = next;
		}
	}
	delete[] table;
	this->table = newTable;
	this->capacity = newCapacity;
}
//return the entry pointer whose key equals the parameter key
Entry* HashTable::getEntry(std::string key)
{
	Entry *entry = this->table[myHash(key)%capacity];
	while(entry)
	{
		if (entry->key == key)
			break;
		entry = entry->next;
	}
	return entry;
}
//return all the entry pointers whose lowercase key equals the parameter
vector<Entry *>   HashTable::getAllLowercaseEntry(std::string lowercase){
	vector<Entry *> result;
	Entry *entry = this->table[myHash(lowercase)%capacity];
		while(entry)
	{
		if ( toLowercase(entry->key) == lowercase){
			result.emplace_back(entry);
		}
		entry = entry->next;
	}
	return result;
}
//insert a value to table , if the entry dose not exist, create it 
void HashTable::insert(std::string key, Value value)
{
	Entry* entry = getEntry(key);
	if(nullptr==entry)
	{
		//create new entry
		if ( ((double)size)/capacity >= LOAD_FACTOR)
			reHash();
		size_t hashval = myHash(key);
		Entry* e = new Entry{ key, hashval, list<Value>{}, nullptr };
		e->values.push_back(value);
		size_t index = e->hash % capacity;
		if (table[index] == nullptr)
			table[index] = e;
		else
		{
			e->next = table[index];
			table[index] = e;
		}
		this->size++;
	}else
	{
		entry->values.emplace_back(value);
	}
}
