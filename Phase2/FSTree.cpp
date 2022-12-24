#include "FSTree.h"
#include "DirNode.h"
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>   // /usr/include/dirent.h
#include<string.h>
#include<iostream>
using namespace std;

/*
 * creates an empty FSTree
 */
FSTree::FSTree() {
	this->root = nullptr;
}
int getAbsoluteFiles(string directory, DirNode * node) 
{
    DIR* dir = opendir(directory.c_str()); //打开目录   DIR-->类似目录句柄的东西 
    if ( dir == NULL )
    {
        cout<<directory<<" is not a directory or not exist!"<<endl;
        return -1;
    }

    struct dirent* d_ent = NULL;       //dirent-->会存储文件的各种属性
    char fullpath[128] = {0};
    char dot[3] = ".";                //linux每个下面都有一个 .  和 ..  要把这两个都去掉
    char dotdot[6] = "..";

    while ( (d_ent = readdir(dir)) != NULL )    //一行一行的读目录下的东西,这个东西的属性放到dirent的变量中
    {
        if ( (strcmp(d_ent->d_name, dot) != 0)
              && (strcmp(d_ent->d_name, dotdot) != 0) )   //忽略 . 和 ..
        {
            if ( d_ent->d_type == DT_DIR ) //d_type可以看到当前的东西的类型,DT_DIR代表当前都到的是目录,在usr/include/dirent.h中定义的
            {
				string dirname=string(d_ent->d_name);
				DirNode * subDirNode=new DirNode(dirname);
				node->addSubDirectory(subDirNode);
                string newDirectory = directory + string("/") + string(d_ent->d_name); //d_name中存储了子目录的名字
                if ( -1 == getAbsoluteFiles(newDirectory, subDirNode) )  //递归子目录
                {
                    return -1;
                }
            }
            else   //如果不是目录
            {
                string filename =string(d_ent->d_name);
                node->addFile(filename);
            }
        }
    }

    closedir(dir);
    return 0;
}

/*
 * creates a file system representation of the folder passed.
 * The folder will be "root", and its contents will form the
 * rest of the tree
 */
FSTree::FSTree(std::string rootName) {
	this->root = new DirNode(rootName);
	getAbsoluteFiles(rootName,root);
/*
	this->root->addFile("File0.txt");
	this->root->addFile("File1.txt");
	this->root->addSubDirectory(new DirNode("Dir1"));
	this->root->addSubDirectory(new DirNode("Dir2"));
	this->root->getSubDir(0)->addFile("File3.txt");
	this->root->getSubDir(0)->addSubDirectory(new DirNode("Dir3"));
	this->root->getSubDir(0)->getSubDir(0)->addFile("File4.txt");
*/
}

/*
 * FSTree Copy constructor
 */
FSTree::FSTree(const FSTree& other) {
	return;
}

/*
 * Deletes all alocated memory using a post order delete
 * algorithm
 */
FSTree::~FSTree() {
	burnTree();
}

/*
 * Assignment overload for FSTree.
 */
FSTree& FSTree::operator=(const FSTree& other) {
	return *this;
}

/*
 * returns the root of the tree in order to traverse it.
 * The destructor will still delete all the allocated data.
 * The user should not manually delete the data.
 */
DirNode* FSTree::getRoot() const {
	return this->root;
}

/*
 * returns true if tree is empty
 */
bool FSTree::isEmpty() {
	return this->root->hasFiles() == false && this->root->hasSubDir() == false;
}
void freeTree(DirNode* node) {
	if (node->isEmpty()) { delete node;return; }

	if (node->hasSubDir()) {
		for (int i = 0; i < node->numSubDirs(); i++) {
			DirNode* sub_dir = node->getSubDir(i);
			freeTree(sub_dir);
		}
	}
	delete node;
}
/*
 * destroys the tree and deletes all the allocated data.
 */
void FSTree::burnTree() {
	freeTree(this->root);
}
