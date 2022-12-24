/*
* the implementation of Gerp
*/

#include "Gerp.h"
#include "stringProcessing.h"
#include <fstream>
#include  <set>

using namespace std;

// constructor
Gerp::Gerp()
{
	this->files.clear();
}

// a helper for build content index, it will recursively traverse the tree
//and build the index of that file
void Gerp::TraverseFileTree(DirNode* node, string prefix)
{
	if (node->hasFiles())
	{
		for (int i = 0; i < node->numFiles(); ++i)
		{
			string path = prefix + "/" + node->getFile(i);
			buildIndex(path);
		}
	}
	if (node->hasSubDir())
	{
		for (int i = 0; i < node->numSubDirs(); ++i)
		{
			TraverseFileTree(node->getSubDir(i), prefix + "/" + node->getSubDir(i)->getName());
		}
	}
}

//generate the vector files  by the FSTree
void Gerp::generateFileVec(FSTree& tree)
{
	TraverseFileTree(tree.getRoot(), tree.getRoot()->getName());
}

//build index of each file's content using files vector
void Gerp::buildIndex(string path){
	File file;
	int presentFileID = static_cast<int>(this->files.size());
	file.path = path;
	this->files.push_back(file);
	ifstream infile(path);
	if (!infile.is_open())
	{
		cerr << "Can not open the file " + file.path << endl;
		this->files.pop_back();
		return;
	}
	string line;
	int presentLineNumber = 0; //line number start with 0 but when output it need add 1
	while (getline(infile, line))
	{
		this->files.back().lines.push_back(line);
		vector<string> words = StringSplit(line.c_str(), line.length(), ' ');
		//process  the string
		for (string & word : words){
			word = stripNonAlphaNum(word);
		}
		//remove repeat string
		set<string> rmv_dup(words.begin(), words.end());
		words.clear();
		words.assign(rmv_dup.begin(), rmv_dup.end());
		for (string& word : words)
		{
			string lowercase = toLowercase(word);
			Entry* entry = hashTable.getEntry(word);
			if (entry == nullptr)
			{
				hashTable.insert(word, Value(presentFileID,presentLineNumber));
			}
			else
			{
				list<Value> &values = entry->values;
				if (values.empty()) {
					values.emplace_back(Value(presentFileID, presentLineNumber));
				}
				else {
					entry->values.emplace_back(Value(presentFileID, presentLineNumber));//this line is error in version1.0
				}
			}
			entry = nullptr;
		}
		presentLineNumber++;
	}
	infile.close();
}
//query a word true: found it ; false: not found
bool Gerp::query(std::string word, bool isCaseInsensitive)
{
	string lowercase = toLowercase(word);

	if(isCaseInsensitive)
	{ //insensitive then query all entry that have the same
	// lowercase key and output them
		vector<Entry *> entrys; 
		list<Value> values;
		entrys = hashTable.getAllLowercaseEntry(lowercase);
		for( Entry * entry : entrys){
			values.insert(values.end(),entry->values.begin(),entry->values.end());
		}
		if(values.empty())
			return false;
		dump(values,this->outfile);

	}else
	{
		Entry* entry  = hashTable.getEntry(word);
		if (entry == nullptr)
			return false;
		if (entry->values.empty())
			return false;
		dump(entry->values, this->outfile);
	}

	return true;
}
//output the word information to the out file
void Gerp::dump(std::list<Value> &values, ostream &out)
{
	//remove the repeated lines before output
	set<Value> valueset(values.begin(),values.end()); 
	for (Value value : valueset)
	{
		//small_test/test.txt:5: we are the champions
		int fileID = value.fileID;
		int lineNumber = value.lineNumber;
		//cout << files[fileID].path << ":" << lineNumber+1 << ": " << files[fileID].lines[lineNumber] << endl; 
		out << files[fileID].path << ":" << lineNumber+1 << ": " << files[fileID].lines[lineNumber] << endl;  

	}
}

// firstly build the index.
// then use a loop for getting command from input, and execute the command
void Gerp::run(FSTree& tree, std::string outputFileName)
{

	this->outfile.open(outputFileName, ios::out | ios::trunc);
	generateFileVec(tree); // this function has already build the index of file content
	cout << "Query? ";
	string input;
	while (cin >> input)
	{
		if (input == "@q" || input == "@quit")
		{
			break;
		}
		if (input == "@f")
		{
			cin >> input;
			this->outfile.close();
			this->outfile.open(input, ios::out | ios::trunc);
		}
		else if (input == "@i" || input == "@insensitive")
		{
			cin >> input;
			std::string word = stripNonAlphaNum(input);
			if (query(word, true) == false)
			{
				cout << "query Not Found." << endl;
			}
		}
		else
		{
			std::string word = stripNonAlphaNum(input);
			if (query(word, false) == false)
			{
				cout << "query Not Found. Try with @insensitive or @i." << endl;
			}
		}
		cout << "Query? ";
	}
	if (cin.eof() || input == "@q" || input == "@quit")
	{
		cout << "Goodbye! Thank you and have a nice day." << endl;
	}
	if(outfile.is_open())
		outfile.close();
}
