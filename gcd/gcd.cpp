/***********************************************************************************
 * Name			: helloworld.cpp
 * Author		: bpatton
 * Date			: Aug 31, 2018
 * Description 	: GCD program that calculates GCD both iteratively and recursively.
 * Pledge		: I pledge my honor that I have abided by the Stevens Honor System.
 * 					Brandon Patton
 **********************************************************************************/
#include <iostream>
#include <sstream>

using namespace std;


/**
 * gcd_iterative
 * 		Calculates gcd iteratively using a for loop.
 */
int gcd_iterative(int m, int n){
	m = abs(m);
	n = abs(n);
	int gcd = 0;
	int lesser = 0;
	if (m == 0){
		return n;
	}
	if (n == 0){
		return m;
	}
	if (m > n){
		lesser = n;
	} else {
		lesser = m;
	}
	for (int i = 1; i < lesser + 1; i += 1){
		if ((m % i == 0) && (n % i == 0)){
			gcd = i;
		}
	}
	return gcd;
}

/**
 * gcd_recursive
 * 		Calculates gcd recursively.
 */
int gcd_recursive(int m, int n){
	m = abs(m);
	n = abs(n);
	if (n == 0){
		return m;
	} else {
		return gcd_recursive(n, m % n);
	}
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
		cerr << "Error: The first argument is not a valid integer." << endl;
		return 1;
	}
	iss.clear();
	iss.str(argv[2]);
	if( !(iss >> n) ){
		cerr << "Error: The second argument is not a valid integer." << endl;
		return 1;
	}
	cout << "Iterative: gcd(" << m << ", " << n << ") = " << gcd_iterative(m, n) << endl;
	cout << "Recursive: gcd(" << m << ", " << n << ") = " << gcd_recursive(m, n) << endl;
	return 0;
}



