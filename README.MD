美国塔夫茨大学数据结构课Project，基于哈希表实现的硬盘文本单词出现情况统计，功能类似Linux的工具Grep,能在常量时间得到某个单词在某个路径下所有文件里面出现的地方。



# FILES

stringProcessing.h : the head file which has a interface of function 
std::string stripNonAlphaNum(std::string input);

stringProcessing.cpp: the implementation of 
std::string stripNonAlphaNum(std::string input);

FSTreeTraversal.cpp: a cpp file that has a main() function, you can complie 
this file and then run it. It will build a FSTree of given directory and print 
all the file path name in it and its sub-directories.

unit_tests.h: unit test for function 
std::string stripNonAlphaNum(std::string input);

FSTree.h: the head file of FSTree
DirNode.h: the head file of DirNode.

#COMPLIE & RUN
Compile: make

Run the treeTraversal to print all the files' path in a given directory 
./treeTraversal Directory

# TEST

I test the std::string stripNonAlphaNum(std::string input); in these test case:

1. pass a normal string  "$#%Alice#" to it, the expected result is "Alice"
2. pass a string with non-alphanum only  at the end. like "Alice#"
3. pass a string with non-alphanum only  at the beginning like "#Alice"
4. pass a string with no non-alphanum .like "Comp15"
5. pass a string with all non-alphanum .like "###@@@@".
    the expected result is empty string "".
6. pass an empty string "", the expected result is also an empty string "".
7. pass a words contains non alphanumeric characters in the middle. 
    the word is "comp&!$15", expected is "comp&!$15";