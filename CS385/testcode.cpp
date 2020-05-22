/*
 * testcode.cpp
 *
 *  Created on: Aug 31, 2018
 *      Author: bpatton
 */
#include <iostream>
#include <sstream>

using namespace std;

int max(int m, int n){
	return m > n ? m : n;
}

int main(int argc, char *argv[]) {
	int m, n;
	istringstream iss;
	if (argc != 3){
		cerr << "Usage: " << argv[0] << " <integer m> <integer n>" << endl;
		return 1;
	}
	iss.str(argv[1]);
	if ( !(iss >> m) ){
		cerr << "m is not an integer." << endl;
		return 1;
	}
	iss.clear();
	iss.str(argv[2]);
	if( !(iss >> n) ){
		cerr << "Error: n is not an integer." << endl;
		return 1;
	}
	cout << "max(" << m << "," << n << ") = " << max(m, n) << endl;
	return 0;
}


