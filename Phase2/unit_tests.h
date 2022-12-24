//
// this file is the unit_test for phase 2
// mainly test all the string process functions
// and the interface of hash table
//
#include "stringProcessing.h"
#include <string>
#include <iostream>
#include <cassert>
#include  "HashTable.h"
/// <summary>
/// normal test with simple string
/// </summary>
void testStringProcessing_Normal() {
	std::string str = "$#%Alice#";
	assert("Alice" == stripNonAlphaNum(str));
	str = "#Alic0e0#";
	assert("Alic0e0" == stripNonAlphaNum(str));
	std::cout << "testStringProcessing_Normal" << " " << "PASS\n";
}
/// <summary>
/// test the string with no non-AlphaNum at begin
/// </summary>
void testStringProcessing_NoLeft() {
	std::string str = "Alice#";
	assert("Alice" == stripNonAlphaNum(str));
	str = "Alic0e0#";
	assert("Alic0e0" == stripNonAlphaNum(str));
	std::cout << "testStringProcessing_NoLeft" << " " << "PASS\n";
}

/// <summary>
///  test the string with no non-AlphaNum at end
/// </summary>
void testStringProcessing_NoRight() {
	std::string str = "$#%Alice";
	assert("Alice" == stripNonAlphaNum(str));
	str = "#Alic0e0";
	assert("Alic0e0" == stripNonAlphaNum(str));
	std::cout << "testStringProcessing_NoRight" << " " << "PASS\n";
}

/// <summary>
/// edge test:
///  test the string with no non-AlphaNum both at begin and end
/// </summary>
void testStringProcessing_AlpahNum() {
	std::string str = "Alice";
	assert("Alice" == stripNonAlphaNum(str));
	str = "Alic0e0";
	assert("Alic0e0" == stripNonAlphaNum(str));
	str = "0Alic0e0";
	assert("0Alic0e0" == stripNonAlphaNum(str));
	str = "0";
	assert("0" == stripNonAlphaNum(str));
	std::cout << "testStringProcessing_AlpahNum" << " " << "PASS\n";
}

/// <summary>
/// edge test:
///  test the string with all non-AlphaNum 
/// </summary>
void testStringProcessing_NonAlpahNum() {
	std::string str = "$$@##";
	assert("" == stripNonAlphaNum(str));
	std::cout << "testStringProcessing_NonAlpahNum" << " " << "PASS\n";
}

/// <summary>
/// edge test:
///  test an empty string
/// </summary>
void testStringProcessing_EmptyString() {
	std::string str = "";
	assert("" == stripNonAlphaNum(str));
	std::cout << "testStringProcessing_EmptyString" << " " << "PASS\n";
}
/// <summary>
/// test a words contains non alphanumeric characters in the middle. 
/// </summary>
void testStringProcessing_Middle() {
	std::string str = "comp&!$15";
	assert("comp&!$15" == stripNonAlphaNum(str));
	std::cout << "testStringProcessing_Middle" << " " << "PASS\n";
}


/// <summary>
/// test //std::string toLowercase(std::string str);
/// </summary>
void testToLowercase()
{
	std::string str = "AAAvvCC";
	assert(toLowercase(str) == "aaavvcc");
	str = "123";
	assert(toLowercase(str) == "123");
	str = "213AAc";
	assert(toLowercase(str) == "213aac");
	std::cout << "testToLowercase" << " " << "PASS\n";
}

/// <summary>
/// test //std::string toLowercase(std::string str); passing empty string
/// </summary>
void testToLowercase_Empty()
{
	std::string str;
	assert(toLowercase(str).empty());
	std::cout << "testToLowercase_Empty" << " " << "PASS\n";
}
/// <summary>
/// test stringsplit function
///	
void testStringSplit()
{
	std::string str="123 333   222";
	assert(StringSplit(str.c_str(),str.length(),' ').size()==3);
	str = "1232";
	assert(StringSplit(str.c_str(), str.length(), ' ').size() == 1);
	str = "     ";
	assert(StringSplit(str.c_str(), str.length(), ' ').empty());
	std::cout << "testStringSplit" << " " << "PASS\n";
}

/// <summary>
/// test stringsplit function with empty string 
///	
void testStringSplit_Empty()
{
	std::string str;
	assert(StringSplit(str.c_str(), str.length(), ' ').empty());
	std::cout << "testStringSplit_Empty" << " " << "PASS\n";
}


//----------Test HashTable-----------

// create a hash table but insert nothing
void testHashTableCreate()
{
	HashTable table;
	assert(table.get_size() == 0);
	assert(table.get_capacity() == table.INITIAL_CAPACITY);
	std::cout << "testHashTableCreate" << " " << "PASS\n";
}
//test the get method on empty hash table
void testEmptyHashTableGet()
{
	HashTable table;
	Entry* entry = table.getEntry("123");
	assert(entry == nullptr);
	std::cout << "testEmptyHashTableGet" << " " << "PASS\n";
}

//test the Insert method of hash table
void testHashTableInsert()
{
	HashTable table;
	table.insert("abc", Value( 3, 3));
	assert(table.get_size() == 1);
	std::cout << "testHashTableInsert" << " " << "PASS\n";
}


//test the Insert a empty key to the table
void testHashTableInsertEmpty()
{
	HashTable table;
	table.insert("", Value( 3, 3));
	assert(table.get_size() == 1);
	std::cout << "testHashTableInsertEmpty" << " " << "PASS\n";
}
//test the insert and query method of hash table
//multi value with same entry.
void testHashTableInsertAndQuery()
{
	HashTable table; //
	table.insert("abc", Value( 1, 1));
	table.insert("abc", Value(1, 2));
	table.insert("abc", Value( 1, 3));
	assert(table.get_size() == 1);
	Entry* entry = table.getEntry("abc");
	assert(entry->key == "abc");
	assert(entry->values.size() == 3);
	std::cout << "testHashTableInsertAndQuery" << " " << "PASS\n";
}
// test insert entry items to the table but with no expand
// less than load factor
void testHashTableNoExpand()
{
	HashTable table; //
	table.insert("abc", Value(1, 1));
	table.insert("abc", Value(1, 2));
	table.insert("abc", Value(1, 3));
	table.insert("Abc", Value(1, 3));
	table.insert("Grep", Value(1, 4));
	table.insert("CS15", Value(1, 5));
	assert(table.get_size() == 4);
	assert(table.get_capacity() == table.INITIAL_CAPACITY);
	table.insert("abcd", Value(1, 1));
	table.insert("DATASTRUCTURE", Value(1, 2));
	table.insert("Abc", Value(2, 3));
	table.insert("ABC", Value(2, 3));
	table.insert("#Grep#", Value(1, 4));
	assert(table.get_size() == 8);
	assert(table.get_capacity() == table.INITIAL_CAPACITY);
	table.insert("#CS15#", Value(1, 5));
	assert(table.get_size() == 9);
	assert(table.get_capacity() == table.INITIAL_CAPACITY);

	table.insert("#CS15#", Value(99, 99));
	assert(table.get_size() == 9);
	assert(table.get_capacity() == table.INITIAL_CAPACITY);

	std::cout << "testHashTableNoExpand" << " " << "PASS\n";
}

void testHashTableExpand()
{
	HashTable table; //
	table.insert("1", Value(1, 1));
	table.insert("2", Value(1, 1));
	table.insert("3", Value(1, 1));
	table.insert("4", Value(1, 1));
	table.insert("5", Value(1, 1));
	table.insert("6", Value(1, 1));
	table.insert("7", Value(1, 1));
	table.insert("8", Value(1, 1));
	table.insert("9", Value(1, 1));
	table.insert("10", Value(1, 1));
	table.insert("11", Value(1, 1));
	assert(table.get_size() == 11);
	assert(table.get_capacity() == table.INITIAL_CAPACITY);
	table.insert("12", Value(1, 1));
	assert(table.get_size() == 12);
	assert(table.get_capacity() == table.INITIAL_CAPACITY);
	table.insert("12", Value(1, 1));
	assert(table.get_size() == 12);
	assert(table.get_capacity() == table.INITIAL_CAPACITY);

	//this insert step will cause the expand of table
	table.insert("13", Value(1, 1));
	assert(table.get_size() == 13);
	assert(table.get_capacity() == 2*table.INITIAL_CAPACITY);


	///table has expanded new Capacity is 2*INITIAL_CAPACITY =32
	assert(table.getEntry("1"));
	assert(table.getEntry("2"));
	assert(table.getEntry("3"));
	assert(table.getEntry("4"));
	assert(table.getEntry("5"));
	assert(table.getEntry("6"));
	assert(table.getEntry("7"));
	assert(table.getEntry("8"));
	assert(table.getEntry("9"));
	assert(table.getEntry("10"));
	assert(table.getEntry("11"));
	assert(table.getEntry("12"));
	assert(table.getEntry("12")->values.size()==2);
	assert(table.getEntry("13"));

	std::cout << "testHashTableExpand" << " " << "PASS\n";
}

