/*******************************************************************************
 * Name        : unique.cpp
 * Author      : bpatton
 * Date        : September 25 2018
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 * 						Brandon Patton
 ******************************************************************************/
#include <iostream>
#include <cctype>



using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
	for (unsigned int i = 0; i < s.length(); i++){
		if(isupper(s[i]) || !isalpha(s[i])){
			return false;
		}
	}
	return true;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.
	unsigned int buffer = 0;
	unsigned int temp = 1;

	for (unsigned int i = 0; i < s.length(); i++){
		temp <<= s[i]-'a';
		if(buffer & temp){
			return false;
		}
		buffer = buffer | temp;
		temp = 1;
	}
	return true;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
	if(argc != 2){
		cout << "Usage: ./unique <string>" << endl;
		return 1;
	}
	if(!is_all_lowercase(argv[1])){
		cout << "Error: String must contain only lowercase letters." << endl;
		return 1;
	}
	if(all_unique_letters(argv[1])){
		cout << "All letters are unique." << endl;
	}
	else {
		cout << "Duplicate letters found." << endl;
	}
	return 0;
}





