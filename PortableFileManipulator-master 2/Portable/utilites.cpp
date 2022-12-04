#include "utilities.h"
#include <sstream>
#include <sstream>
#include <iterator>
#include <iostream>


std::vector<string>  Utility::convertStringToVectorString(std::string command){

	    std::vector<std::string> listArgs;

		std::stringstream ss(command);
		std::istream_iterator<std::string> begin(ss);
		std::istream_iterator<std::string> end;
		std::vector<std::string> vstrings(begin, end);
		std::copy(vstrings.begin(), vstrings.end(), std::back_inserter(listArgs));
	

	

	

	return listArgs;
}
