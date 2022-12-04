#include "FileManipulator.h"
#include <stdio.h>
#include "utilities.h"
#include <iostream>
#include <fstream> 
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <string>
#include <stdexcept>
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable : 4996)
#include <stdio.h>
using namespace std;

 int FileManipulator::createFile(vector<string> listArgs)
{

	 //Erase first argument because its the command and args are only needed.
	 listArgs.erase(listArgs.begin() );

	 if (listArgs.size() == 0) {
		 std::cout << "Missing an args" << std::endl;
		 return 0;
	 }


	 for (auto fileName : listArgs) {

		 //Append the extension .pofm to end of filename
		 std::string newFileName = fileName + ".pofm";

		 //create an object stream
		 ifstream f(newFileName);

		 //Check if this file name already exist in the current directory
		 if (f.good()) {

			 std::cout <<newFileName<< " already exists. Please use another name." <<endl;		// Print error message.
			 f.close();

		 }else{

			 //If doesn't exist create the file

			 std::ofstream outfile(newFileName);
			 cout << "Successfully created " << newFileName << endl;			// Print success message

			 outfile.close();


		 }
	 }
	
	
	 return 0;
}

 /* List Args takes into account all the oldFileNames which
  *	need to be deleted.
  */

int FileManipulator::renameFile(vector<string> listArgs) {
	cout << "rename a file....." << endl;

	// Deleting the [command] from the code
	listArgs.erase(listArgs.begin());
	


	if (listArgs.size() == 0) {
		std::cout << "Missing an args" << std::endl;
		return 0;
	}




	// listArgs takes into account the names of all the files that need to be renamed.
	// 
	
	char* oldFileNameCharArray;
	char* newFileNameCharArray;


	
	for (auto fileName : listArgs) {
		
		// variable for newFileName

		string oldFileName = fileName + ".pofm";
		string newFileName;
		
		// Checking if the file exists
		ifstream f(oldFileName);

		// If file exists
		if (f.good()) {
			// Need to close the file in order to rename the file.
			f.close();

			// Accept the file Name to renamed.
			cout << "Enter the new File Name for " <<oldFileName << endl;
			cin >> newFileName;		// Only if the file exists do we request for renaming a file.

			// Appending the extension to newFileName
			newFileName = newFileName + ".pofm";

			// Converting string to char pointer
			oldFileNameCharArray = &oldFileName[0];
			newFileNameCharArray = &newFileName[0];
			
			// Rename function is used.
			// It returns 0 if successful.
			// Returns 1 if the unsuccessful.
			if (rename(oldFileNameCharArray, newFileNameCharArray) != 0)
				cout << "Error in renaming files. Please close the file before renaming it."<< endl;
			else
				cout << "Renaming Successful\n";


		}
		else
		{	
			// File does not exist to rename.
			cout << "File does not exist\n";
		}

	

	}


	return 0;
}

 int FileManipulator::deleteFile(vector<string> listArgs) {

	 char choice;
	 // Erasing the command from the input string
	 listArgs.erase(listArgs.begin());

	 if (listArgs.size() == 0) {
		 std::cout << "Missing an args" << std::endl;
		 return 0;
	 }
	
	 // for loop to delete files files
	 for (auto fileName : listArgs) {
	
		 // each file requested to be deleted is input into string deleteFileName
		 std::string deleteFileName = fileName + ".pofm";
		
		 ifstream f(deleteFileName);

		 // Checking the file exists.
		 if (f.good()) {
			
			 // Closing the file is necessary in order to delete the file.
			 f.close();
			 // Recheck if the user wants to delete the file
			 std::cout << "Are you sure you want to delete " << deleteFileName << " (y/n)" << std::endl;
			 std::cin >> choice;
			
			 // If yes, the file is deleted.
			 if (choice == 'y') {
				 if (!std::remove(deleteFileName.c_str()))
					 std::cout << "Successfully deleted " << deleteFileName << "\n";		// Printing success message.
				 else
					 std::cout << "Unable to Delete " << deleteFileName << "Please close the file and try deleting again.\n";			// Printing error message.
			 }
			 // If no, the file is not deleted.
			 else if (choice == 'n')
				 std::cout << deleteFileName << " not deleted\n";
			 
			 // Any other option, the program exits.
			 else
				 std::cout << "Exiting program\n";

		 }
		 else {
			 f.close();
			 // If unable to locate the file
			 cout<<"File to be deleted cannot be located\n";
		 }



		 
	 }
	 return 0;
 }


int FileManipulator::copyFile(vector<string> listArgs)
{
	listArgs.erase(listArgs.begin());

	if (listArgs.size() == 0) {
		std::cout << "Missing two args" << std::endl;
		return 0;
	} else if (listArgs.size() == 1) {
		 std::cout << "Missing one arg" << std::endl;
		 return 0;
	  }

	string to = listArgs.back();
	string from = listArgs.front();
	ifstream fi;
	ofstream fo;
	char c;
	
	//access sourcefile
	fi.open(from, fstream::in | fstream::binary);

	if (fi.is_open())
	{
		//copy to target location
		fo.open(to, fstream::out);

		while (fi.read(&c, 1)) {
			fo.write(&c, 1);
		}

		//close both files
		fo.close();
		fi.close();
		std::cout << "Successfully copied file..."<<endl;
	}
	else {
		std::cout << "Source File error.."<<endl;
	}

	return 0;
}

int FileManipulator::moveFile(vector<string> listArgs)
{
	//not using streams
	listArgs.erase(listArgs.begin());

	if (listArgs.size() == 0) {
		std::cout << "Missing an args" << std::endl;
		return 0;
	}
	else if (listArgs.size() == 1) {
		std::cout << "Missing one more arg" << std::endl;
		return 0;
	}


	string to = listArgs.back();
	string from = listArgs.front();
	const char* f = from.c_str();
	const char* t = to.c_str();

	std::cout << to << std::endl;
	std::cout << from << std::endl;

	//instead use rename function to move directory
	int process = rename(f, t);
	if (process == 0)
		std::cout << "File successfully moved"<<endl;
	else 
		std::cout << "Error moving file"<<endl;

	return process;
}

int FileManipulator::appendTextEndFile(vector<string> listArgs, string command) {

	
	 std::string newFileName;
	 std::string text;
	 std::string stringVersion;
	 std::size_t posFirstSingleQuotation = 0;
	 std::size_t posSecondSingleQuotation = 0;
	 char ch;

	//Erase the first arg because its just the command
	listArgs.erase(listArgs.begin());

	if (listArgs.size() == 0) {
		std::cout << "Missing two args" << std::endl;
		return 0;
	}
	else if (listArgs.size() == 1) {
		std::cout << "Missing one arg" << std::endl;
		return 0;
	}


	 command.erase(command.begin(), command.begin() + 6);

	       stringVersion = command;
	     
	     //Find the first single quotation mark
		 posFirstSingleQuotation = stringVersion.find("'");

		 // if you found the first single quotation mark
		if (posFirstSingleQuotation != std::string::npos) {


		

			//Erase the first single quotation mark
			stringVersion.erase(stringVersion.begin() + posFirstSingleQuotation);

			//find the second quotation mark
			posSecondSingleQuotation = stringVersion.find("'");

			//Erase the second quotation mark
			stringVersion.erase(stringVersion.begin() + posSecondSingleQuotation);
			
		}
		  //Retrieve the text between the first quotation mark and second quotation mark and store in variable text;
		 text = stringVersion.substr(posFirstSingleQuotation, posSecondSingleQuotation);


		// Erase the text the user trying to append
		// The leftover in stringVersion is the file name
		stringVersion.erase(posFirstSingleQuotation, posSecondSingleQuotation);
		
		
		

		// Attach file extension
		 newFileName = stringVersion + ".pofm";

		 //If there is any extra space in the name remove it.
		 newFileName.erase(std::remove(newFileName.begin(), newFileName.end(), ' '), newFileName.end());
		 



		 ifstream file(newFileName);

		 if (file.good() == false) {

			 std::cout << "Something wrong with the file or it doesn't exist" << std::endl;
			 

			 file.close();

			 return 0;

		 } else {


			 //create an output stream and open the stream in append mode
			 ofstream file(newFileName, ios::app);

			 //if file does exist than append text than close the output stream

			 file << text;

			 file.close();

		 }
		
	

		 return 0;
}


int  FileManipulator::InsertTextByPosition(vector<string> listArgs, string command) {
	// insert filename position_number text;


	std::string fileName;
	int SpecifiedPostion = 1;
	int countChars = 0;
	std::string tempData;
	std::string line;
	std::string data;
	std::size_t posFirstSingleQuotation = 0;
	std::size_t posSecondSingleQuotation = 0;
	std::string perviousData; // to store text the pervious text until specified position
	std::string lastData; // to store text after the specified position

	listArgs.erase(listArgs.begin());


	if (listArgs.size() == 0) {
		std::cout << "Missing three args" << std::endl;
		return 0;
	}

	if (listArgs.size() == 2) {
		std::cout << "Missing one args" << std::endl;
		return 0;
	}
	
	try {

		SpecifiedPostion += std::stoi(listArgs.at(1));

	}catch (const std::out_of_range& error) {
		std::cout << "Missing an position arg" << std::endl;
		return 0;


	}



	fileName = listArgs.at(0);
	// data = listArgs.at(2);

	posFirstSingleQuotation = command.find("'");

	// if you found the first single quotation mark
	if (posFirstSingleQuotation != std::string::npos) {

		//Erase the first single quotation mark
		command.erase(command.begin() + posFirstSingleQuotation);

		//find the second quotation mark
		posSecondSingleQuotation = command.find("'");

		//Erase the second quotation mark
		command.erase(command.begin() + posSecondSingleQuotation);

	}
	//Retrieve the text between the first quotation mark and second quotation mark and store in variable text;
	data = command.substr(posFirstSingleQuotation, posSecondSingleQuotation);

	 //check for all args if they are valid or not
	std::string newFileName = fileName + ".pofm";


	//create an object stream
	ifstream file(newFileName, fstream::in);

	//Check if this file exist
	if (file.good() == false) {

		std::cout << "This file doesn't exist" << std::endl;

	}

	char ch;
	//Check if the position is valid or not
	if (SpecifiedPostion < 0) {
		std::cout << "Pos shouldn't be negative !" << std::endl;
	}
	int count = 0;


	

	// file character by character
	while (file.get(ch)) {


		//As you read he file character by character, increment the position to track current position
		count++;

		//If specified position is greater than count than store data in perviousData;
		//Otherwise store it in EndData
		if (SpecifiedPostion > count) {

			perviousData += ch;

		}
		else {

			lastData += ch;
		}

	}

	file.close();

	ofstream file1(newFileName, fstream::in);


		   // combine pervious data, new data from the user, and last data after specified positioned into a new string
		   std::string newdata = perviousData + data + lastData;

		   //write the new string into the file
		   file1 << newdata;

		   file1.close();

		   return 0;
	   }




void FileManipulator::help(vector<string> listArgs) {

	

	listArgs.erase(listArgs.begin());

	
	if (listArgs.empty()) {
		std::cout << "must include an additional arg" << std::endl;
		cout << "Useful commands for this program are " << endl;
		cout << " 1. create \n 2. delete \n 3. rename \n 4. append \n 5. move \n 6. insert\n";
	}

	else if (listArgs.at(0) == "delete") {

		std::cout << "\n";
		std::cout << "delete filename" << std::endl;
		std::cout << "delete filename1 filename2...filename(N)" << std::endl;
		std::cout << "delete file1" << std::endl;
		std::cout << "\n";

	} 
	else if (listArgs.at(0) == "insert") {

		std::cout << "\n";
		std::cout << "insert position 'text' " << std::endl;
		std::cout << "insert 5 'Hello world' " << std::endl;
		std::cout << "\n";
	}
	else if (listArgs.at(0) == "create") {

		std::cout << "\n";
		std::cout << "create filename" << std::endl;
		std::cout << "create filename1 filename2...filename(N)" << std::endl;
		std::cout << "create file2 " << std::endl;
		std::cout << "\n";

	}
	else if (listArgs.at(0) == "append") {

		std::cout << "\n";
		std::cout << "append filename 'text'" << std::endl;
		std::cout << "append file2 'my name is john' " << std::endl;
		std::cout << "\n";

	}else if (listArgs.at(0) == "rename") {

		std::cout << "\n";
		std::cout << "rename file1 file2 file3 .... file(N)" << std::endl << "Here you are required to enter the names of files you want to rename. The new file name will be accepted later in the program.\n";
		std::cout << "rename file1 " << std::endl << "Here you are required to enter the names of files you want to rename. The new file name will be accepted later in the program.\n"; 
		std::cout << "\n";

	}
	else if (listArgs.at(0) == "move") {

		std::cout << "\n";
		std::cout << "move path1 path2" << std::endl;
		std::cout << "move c:drive/documents/file1 c:drive/folder1/file3 " << std::endl;
		std::cout << "\n";

	}
	else if (listArgs.at(0) == "removedata") {

		std::cout << "\n";
		std::cout << "move filename " << std::endl;
		std::cout << "move filename1 filename2....filename(N) " << std::endl;
		std::cout << "move c:drive/documents/file1 c:drive/folder1/file3 " << std::endl;
		std::cout << "\n";

	}












	   
}

void FileManipulator::removeAllTextFile(vector<string> listArgs) {

	

	//Erase the command
	listArgs.erase(listArgs.begin());
	

	for (auto fileName : listArgs) {


		//check for all args if they are valid or not
		std::string newFileName = fileName + ".pofm";


		//create an object input stream
		ifstream file(newFileName);
		

		//Check if this file exist
		if (file.good() == false) {

			std::cout << "This file doesn't exist !" << std::endl;

		}

		//close the object input file stream
		file.close();

		ofstream ofile(newFileName);
		
		// we open the file for writing and use the trunc option to discard all the data in the file
		ofile.open(newFileName, std::ofstream::out | std::ofstream::trunc);
		//close the file output stream
		ofile.close();



	}

}

