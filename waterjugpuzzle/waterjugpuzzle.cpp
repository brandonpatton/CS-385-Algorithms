/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : bpatton rkim4
 * Date        : October 21, 2018
 * Description : Solves water jug puzzle using breadth-first search
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 * 						Brandon Patton  Ronald Kim
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <queue>

using namespace std;

struct State {
    int a, b, c;
    vector<string> path;

    State(int _a, int _b, int _c) : a(_a), b(_b), c(_c) { }

    // String representation of state in tuple form.
       string to_string() {
           ostringstream oss;
           oss << "(" << a << ", " << b << ", " << c << ")";
           return oss.str();
       }

    State(int _a, int _b, int _c, vector<string> _path) : a(_a), b(_b), c(_c), path(_path) { }

    	/*
    	 * add_path
    	 * 		adds any new path to the path vector
    	 */
    	void add_path(string new_path) {
    		path.push_back(new_path);
    	}

    	void print_path() {
    		for (unsigned int i = 0; i < path.size(); i++) {
    			cout << path[i] << endl;
    		}
    	}
};

/*
 * prepare_output
 * 		Prepares each pouring action for output.
 * 		Takes in where pouring from, where pouring to, the max (capacity) of where it is pour to, and a ready parameter
 * 		Covers the cases where output is singular (when pouring 1 gallon) and when plural (when pouring >1 gallons)
 */
string prepare_output(int from, int to, int max_to, bool ready) {
	ostringstream output;
	if (ready) {
		if (from == 1) {
			output << "Pour " << from << " gallon ";
		} else {
			output << "Pour " << from << " gallons ";
		}
	} else {
		if ((max_to - to) == 1) {
			output << "Pour " << (max_to - to) << " gallon ";
		} else {
			output << "Pour " << (max_to - to) << " gallons ";
		}
	}
	return output.str();
}

/*
 * can_pour
 * 		Checks if it is possible to pour into a jug from another
 * 		To be used later in the body of the pour function
 */
bool can_pour(int from, int to, int max_to) {
	if (from == 0 || to == max_to) {
		return false;
	} else {
		return true;

	}
}

/*
 * pour
 * 		Handles each pour as described by the path given by the assignment.
 * 		Uses an overarching pour state function and applies it to each path (or case) using a switch
 * 		After each pour takes place, adds the desired pour in string form to the path vector to make output easier
 * 		At each pour a comparison is made to make sure a jug has not reached its capacity yet. This is to prevent putting more water in a jug than can be held.
 * 		Each case breaks out after that specific pour is made.
 */
State pour(State s, int do_pour, State max) {
	State n = s;
	ostringstream path;
	switch (do_pour) {
	case 1:
		//pour jug c into jug a
		if (can_pour(s.c, s.a, max.a)) {
			if ((max.a - s.a) >= s.c) {
				n.a = s.a + s.c;
				n.c = 0;
				path << prepare_output(s.c, s.a, max.a, true) << "from C to A. "
						<< n.to_string();
			} else {
				n.a = max.a;
				n.c = s.c - (max.a - s.a);
				path << prepare_output(s.c, s.a, max.a, false) << "from C to A. "
						<< n.to_string();
			}
		} else {
			n.a = -1, n.b = -1, n.c = -1;
		}
		break;
	case 2:
		//pour jug b into jug a
		if (can_pour(s.b, s.a, max.a)) {
			if ((max.a - s.a) >= s.b) {
				n.a = s.a + s.b;
				n.b = 0;
				path << prepare_output(s.b, s.a, max.a, true) << "from B to A. "
						<< n.to_string();
			} else {
				n.a = max.a;
				n.b = s.b - (max.a - s.a);
				path << prepare_output(s.b, s.a, max.a, false) << "from B to A. "
						<< n.to_string();
			}
		} else {
			n.a = -1, n.b = -1, n.c = -1;
		}
		break;
	case 3:
		//pour jug c into jug b
		if (can_pour(s.c, s.b, max.b)) {
			if ((max.b - s.b) >= s.c) {
				n.b = s.b + s.c;
				n.c = 0;
				path << prepare_output(s.c, s.b, max.b, true) << "from C to B. "
						<< n.to_string();
			} else {
				n.b = max.b;
				n.c = s.c - (max.b - s.b);
				path << prepare_output(s.c, s.b, max.b, false) << "from C to B. "
						<< n.to_string();
			}
		} else {
			n.a = -1, n.b = -1, n.c = -1;
		}
		break;
	case 4:
		//pour jug a into jug b
		if (can_pour(s.a, s.b, max.b)) {
			if ((max.b - s.b) >= s.a) {
				n.b = s.b + s.a;
				n.a = 0;
				path << prepare_output(s.a, s.b, max.b, true) << "from A to B. "
						<< n.to_string();
			} else {
				n.b = max.b;
				n.a = s.a - (max.b - s.b);
				path << prepare_output(s.a, s.b, max.b, false) << "from A to B. "
						<< n.to_string();
			}
		} else {
			n.a = -1, n.b = -1, n.c = -1;
		}
		break;

	case 5:
		//pour jug b into jug c
		if (can_pour(s.b, s.c, max.c)) {
			if ((max.c - s.c) >= s.b) {
				n.c = s.c + s.b;
				n.b = 0;
				path << prepare_output(s.b, s.c, max.c, 1) << "from B to C. "
						<< n.to_string();
			} else {
				n.c = max.c;
				n.b = s.b - (max.c - s.c);
				path << prepare_output(s.b, s.c, max.c, 2) << "from B to C. "
						<< n.to_string();
			}
		} else {
			n.a = -1, n.b = -1, n.c = -1;
		}
		break;

	case 6:
		//pour jug a into jug c
		if (can_pour(s.a, s.c, max.c)) {
			if ((max.c - s.c) >= s.a) {
				n.c = s.c + s.a;
				n.a = 0;
				path << prepare_output(s.a, s.c, max.c, 1) << "from A to C. "
						<< n.to_string();
			} else {
				n.c = max.c;
				n.a = s.a - (max.c - s.c);
				path << prepare_output(s.a, s.c, max.c, 2) << "from A to C. "
						<< n.to_string();
			}
		} else {
			n.a = -1, n.b = -1, n.c = -1;
		}
		break;
	}
	n.add_path(path.str());
	return n;
}

/*
 * check_jugs
 * 		Takes in where it is to pour from, and where it is to pour to.
 * 		Checks if the state pouring from is the same as the state pouring to.
 * 		Used later in breadth first search when checking if the goal has been reached.
 */
bool check_jugs(State from, State to) {
	if (from.a == to.a && from.b == to.b && from.c == to.c) {
		return true;
	} else {
		return false;
	}
}

/*
 * not_in_path
 * 		Takes in the current state of the jugs as determined in the breadth first search and the vector of steps already visited.
 * 		Determines, based on the information above, if the current step is already present in the vector of steps already visited.
 */
bool not_in_path(State s, vector<State> v) {
	for (unsigned int i = 0; i < v.size(); i++) {
		if (check_jugs(v[i], s)) {
			return false;
		}
	}
	return true;
}

/*
 * breadth_first_search
 * 		Takes in the initial state of the jugs before any pours have been done, the desired goal to work towards by pouring the jugs
 * 		and the capacities of each jug.
 * 		Uses breadth first search strategy to find a way to the solution.
 * 		Fills up a queue with all the moves performed and adds each step to a vector to be outputted later in the correct order.
 * 		Checks if a step has been visited already, and if it hasn't, adds it to the queue and the vector visited.
 * 		Once the queue is empty, and if all moves (in the pour function above) are performed, and the goal is not reached, there is no solution and such a result
 * 		is thusly printed.
 * 		The syntax of the each step's output is handled by the pour functions, adding each unique step to a vector after it is performed.
 */
void breadth_first_search(State initial, State goal, State capacity) {
	vector<State> visited;
	queue<State> queue;
	queue.push(initial);
	visited.push_back(initial);
	if (check_jugs(initial, goal)) {
		initial.print_path();
		return;
	}
	while (!queue.empty()) {
		State current = queue.front();
		for (int i = 1; i <= 6; i++) {

			if (check_jugs(current, goal)) {
				current.print_path();
				return;
			}
			State current = pour(queue.front(), i, capacity);
			if (current.a != -1 && current.b != -1 && current.c != -1 && not_in_path(current, visited)) {
				queue.push(current);
				visited.push_back(current);
			}
		}
		queue.pop();
	}
	cout << "No solution." << endl;
}


int main(int argc, const char*argv[]){

	if (argc != 7){
			cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
			return 1;
	}
	string jugs [4] = {"$", "A", "B", "C"};      //Created to avoid having to make many different cases for each jug, iterator in loop is used to reference each jug as needed.
												 //$ is a placeholder as the loop starts at index 1.
	int goal_total = atoi(argv[4]) + atoi(argv[5]) + atoi(argv[6]);
	for (int i = 1; i <= 6; i++){
		istringstream iss(argv[i]);
		int temp;
		if (i <= 3){
			if (!(iss >> temp) || (temp <= 0)){
				cerr << "Error: Invalid capacity '" << argv[i] << "' for jug " << jugs[i] << "." << endl;
				return 1;
		    }
		} else {
			int jug_index = i - 3;
			if (!(iss >> temp) || (temp < 0)){
			cerr << "Error: Invalid goal '" << argv[i] << "' for jug " << jugs[jug_index] << "." << endl;
			return 1;
			}
		}
		}
	for (int i = 1; i <= 3; i++){
		if (atoi(argv[i + 3]) > atoi(argv[i])){
			 cerr << "Error: Goal cannot exceed capacity of jug " << jugs[i] << "." << endl;
			return 1;
		}
	}
	if (atoi(argv[3]) != goal_total){
		cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
		return 1;
	}

	State capacities((atoi(argv[1])), (atoi(argv[2])), (atoi(argv[3])));
	State initial(0, 0, (atoi(argv[3])));
	ostringstream input;
	input << "Initial state. (0, 0, " << argv[3] << ")";
	initial.add_path(input.str());
	State end((atoi(argv[4])), (atoi(argv[5])), (atoi(argv[6])));
	breadth_first_search(initial, end, capacities);
	return 0;
}




