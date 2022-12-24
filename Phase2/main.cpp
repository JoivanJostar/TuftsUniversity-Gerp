/*
* main driver
*/
#include "FSTree.h"
#include  "Gerp.h"
using namespace std;

int main(int argc, char* argv[])
{

    if (argc != 3) {
        cerr << "Usage: ./gerp inputDirectory outputFile" << endl;
        exit(EXIT_FAILURE);
    }
    else {
        string rootPath = argv[1];
        string outfileName = argv[2];
		while(!rootPath.empty()&&rootPath.back()=='/')
			rootPath.pop_back();
        FSTree fstree= FSTree(rootPath);
        Gerp gerp;
        gerp.run(fstree, outfileName);
    }
    return 0;
}
