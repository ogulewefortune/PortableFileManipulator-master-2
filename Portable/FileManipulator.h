#pragma once
#include "vector"
#include "string"


constexpr auto COMMAND = 0 ;

using namespace std;
class FileManipulator {


public:
	static int createFile(vector<string> listArgs);
	static int deleteFile(vector<string> listArgs);
	static int renameFile(vector<string> listArgs);
	static int copyFile(vector<string> listArgs);
	static int moveFile(vector<string> listArgs);
	static int appendTextEndFile(vector<string> listArgs,string name);
	static int InsertTextByPosition(vector<string> listArgs, string command);
	static void removeAllTextFile(vector<string> listArgs);
	static void help(vector<string> listArgs);
	


};
