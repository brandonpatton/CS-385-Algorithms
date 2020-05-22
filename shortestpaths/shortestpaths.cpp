/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : bpatton rkim4
 * Date        : December 4, 2018
 * Description : Finds all pairs shortest paths using Floyd's algorithm
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 * 						Brandon Patton  Ronald Kim
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>
#include <limits>
#include <cmath>
#include <iomanip>
#include <stack>
#include <iomanip>
#include <limits>


using namespace std;
long num_vertices = 0;
const long INF = numeric_limits<long>::max();
long** matrix;
vector<string> params;
char maxLetter = 'A' + num_vertices - 1;

int len(int num) {
     int digits = 1;
    while(num >= 10){
       	digits ++;
    	num /= 10;
    }
    return digits;
}


void display_table(long** const matrix, const string &label, const bool use_letters = false) {
	cout << label << endl;
	long max_val = 0;
	for (int i = 0; i < num_vertices; i++) {
		for (int j = 0; j < num_vertices; j++) {
			long cell = matrix[i][j];
			if (cell < INF && cell > max_val) {
				max_val = matrix[i][j];
			}
		}
	}
	int max_cell_width = len(max(static_cast<long>(num_vertices), max_val));
	cout << ' ';
	for (int j = 0; j < num_vertices; j++) {
		cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
	}
	cout << endl;
	for (int i = 0; i < num_vertices; i++) {
		cout << static_cast<char>(i + 'A');
		for (int j = 0; j < num_vertices; j++) {
			cout << " " << setw(max_cell_width);
			if (matrix[i][j] == INF) {
				cout << "-";
			} else if (use_letters) {
				cout << static_cast<char>(matrix[i][j] + 'A');
			} else {
				cout << matrix[i][j];
			}
		}
		cout << endl;
	}
	cout << endl;
}

 void floyd(long* adj_mat[]) {
 	long** d = adj_mat;
 	long** d1 = new long*[num_vertices];
 	for(int k = 1; k <= num_vertices; k++) {
 		for(int i = 1; i <= num_vertices; i++) {
 			for(int j = 1; j <= num_vertices; j++) {
 				if(d[i][j] > d1[i][k] + d[k][j]) {
 					d[i][j] = d1[i][k] + d[k][j];
 				} else {
 					d[i][j] = d1[i][j];
 				}
 			}
 		}
 	}
 }

void add(char v1, char v2, int edgeWeight){
	matrix[v1-'A'][v2-'A'] = edgeWeight;
}


int main(int argc, const char * argv[]) {
	// Make sure the right number of command line arguments exist.
	    if (argc != 2) {
	        cerr << "Usage: " << argv[0] << " <filename>" << endl;
	        return 1;
	    }
	    // Create an ifstream object.
	    ifstream input_file(argv[1]);
	    // If it does not exist, print an error message.
	    if (!input_file) {
	        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
	        return 1;
	    }
	    // Add read errors to the list of exceptions the ifstream will handle.
	    input_file.exceptions(ifstream::badbit);
	    string line;
	    try {
	        unsigned int line_number = 1;
	        getline(input_file, line);
	        try {
				if(!(stoi(line))) {
					cerr << "Error: Invalid number of vertices '" << line << "' on line " << line_number << ".";
					return 1;
				}
			} catch (invalid_argument) {
				cerr << "Error: Invalid number of vertices '" << line << "' on line " << line_number << ".";
				return 1;
			}
			if(stoi(line) < 1 || stoi(line) > 26) {
				cerr << "Error: Invalid number of vertices '" << line << "' on line " << line_number << ".";
				return 1;
			}
			long ending = 64 + stol(line);
	        // Use getline to read in a line.
	        // See http://www.cplusplus.com/reference/string/string/getline/
			while (getline(input_file, line)) {
				if(line.length() < 5) {
					cerr << "Error: Invalid edge data '" << line << "' on line " << line_number + 1 << ".";
					return 1;
				}
				if(isspace(line[0]) || (long)line[0] > ending || (long)line[0] < 65) {
					int temp = 0;
					for(unsigned int i = 0; i < line.length(); i++) {
						if(isspace(line[i])) {
							temp = i;
							break;
						}
					}
					cerr << "Error: Starting vertex '" << line.substr(0,temp) << "' on line " << line_number + 1 << " is not among valid values A-" << char(ending) << ".";
					return 1;
				}
				if(isspace(line[2]) || (long)line[2] > ending || (long)line[2] < 65) {
					int temp = 0;
					for(unsigned int i = 2; i < line.length(); i++) {
						if(isspace(line[i])) {
							temp = i;
							break;
						}
					}
					cerr << "Error: Ending vertex '" << line.substr(2,temp-2) << "' on line " << line_number + 1 << " is not among valid values A-" << char(ending) << ".";
					return 1;
				}
				try {
					if(stol(line.substr(4, line.length() - 1)) < 1){
						cerr << "Error: Invalid edge weight '" << line.substr(4) << "' on line " << line_number + 1 << ".";
						return 1;
					}
				} catch (invalid_argument &) {
					cerr << "Error: Invalid edge weight '" << line.substr(4) << "' on line " << line_number + 1 << ".";
					return 1;
				}

				//cout << line_number << ":\t" << line << endl;
				++line_number;
			}

	        // Don't forget to close the file.
	        input_file.close();
	    } catch (const ifstream::failure &f) {
	        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
	        return 1;
	    }
	    getline(input_file, line);
	    //long** amount_nodes = line[0];
	    //cout << display_table(Floyd(amount_nodes), "Distance matrix:", false) << endl;
	    //cout << display_table(, "Path lengths:", false) << endl;
	    return 0;
}
