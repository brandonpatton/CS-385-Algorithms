/*
* waterjugpuzzle.cpp
* Bryan Valarezo and Christopher Lyons
* 10/19/2016
*
*/

#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <iomanip>
#include <cstdlib>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
	int a, b, c;
	vector<string> path;

	//create a new state with each jug's amount
	State(int _a, int _b, int _c) :
			a(_a), b(_b), c(_c) {
	}

	//create a new state with each jug's amount and
	State(int _a, int _b, int _c, vector<string> _path) :
			a(_a), b(_b), c(_c), path(_path) {
	}

	void add_path(string x) {
		path.push_back(x);
	}

	void print_path() {
		for (unsigned int i = 0; i < path.size(); i++) {
			cout << path[i] << endl;
		}

	}
	// String representation of state in tuple form.
	string to_string() {
		ostringstream oss;
		oss << "(" << a << ", " << b << ", " << c << ")";
		return oss.str();
	}
};
//Helper function that checks if its possible to pour jug uno into jug dos
//max_dos is the capacity of jug dos
bool pour_possible(int uno, int dos, int max_dos) {
	if (uno == 0 or dos == max_dos) {
		return false;
	} else {
		return true;

	}
}

string string_me(int uno, int dos, int max_dos, bool a_or_b) {
	ostringstream stringy;
	if (a_or_b) {
		if (uno == 1) {
			stringy << "Pour " << uno << " gallon ";
		} else {
			stringy << "Pour " << uno << " gallons ";
		}
	} else {
		if ((max_dos - dos) == 1) {
			stringy << "Pour " << (max_dos - dos) << " gallon ";
		} else {
			stringy << "Pour " << (max_dos - dos) << " gallons ";
		}
	}
	return stringy.str();
}
//Helper function desinged to create a new state if possible
//s is the state to be modified
//to_pour is a command to choose which jug to pour
//returns state of (-1,-1,-1) if not possible
State pour(State s, int to_pour, State max) {
	State n = s;
	ostringstream path;
	string taco;
	switch (to_pour) {
	case 1:
		//c to a
		if (pour_possible(s.c, s.a, max.a)) { //see if pour is possible
			if ((max.a - s.a) >= s.c) { //if whats available in cup a is >= whats in in cup c
				n.a = s.a + s.c;
				n.c = 0;
				path << string_me(s.c, s.a, max.a, true) << "from C to A. "
						<< n.to_string();
			} else {
				n.a = max.a;
				n.c = s.c - (max.a - s.a);
				path << string_me(s.c, s.a, max.a, false) << "from C to A. "
						<< n.to_string();
			}
		} else {
			n.a = -1, n.b = -1, n.c = -1;
		}
		break;
	case 2:
		//b to a
		if (pour_possible(s.b, s.a, max.a)) {
			if ((max.a - s.a) >= s.b) {
				n.a = s.a + s.b;
				n.b = 0;
				path << string_me(s.b, s.a, max.a, true) << "from B to A. "
						<< n.to_string();
			} else {
				n.a = max.a;
				n.b = s.b - (max.a - s.a);
				path << string_me(s.b, s.a, max.a, false) << "from B to A. "
						<< n.to_string();
			}
		} else {
			n.a = -1, n.b = -1, n.c = -1;
		}
		break;
	case 3:
		//c to b
		if (pour_possible(s.c, s.b, max.b)) {
			if ((max.b - s.b) >= s.c) {
				n.b = s.b + s.c;
				n.c = 0;
				path << string_me(s.c, s.b, max.b, true) << "from C to B. "
						<< n.to_string();
			} else {
				n.b = max.b;
				n.c = s.c - (max.b - s.b);
				path << string_me(s.c, s.b, max.b, false) << "from C to B. "
						<< n.to_string();
			}
		} else {
			n.a = -1, n.b = -1, n.c = -1;
		}
		break;
	case 4:
		//a to b
		if (pour_possible(s.a, s.b, max.b)) {
			if ((max.b - s.b) >= s.a) {
				n.b = s.b + s.a;
				n.a = 0;
				path << string_me(s.a, s.b, max.b, true) << "from A to B. "
						<< n.to_string();
			} else {
				n.b = max.b;
				n.a = s.a - (max.b - s.b);
				path << string_me(s.a, s.b, max.b, false) << "from A to B. "
						<< n.to_string();
			}
		} else {
			n.a = -1, n.b = -1, n.c = -1;
		}
		break;

	case 5:
		//b to c
		if (pour_possible(s.b, s.c, max.c)) {
			if ((max.c - s.c) >= s.b) {
				n.c = s.c + s.b;
				n.b = 0;
				path << string_me(s.b, s.c, max.c, 1) << "from B to C. "
						<< n.to_string();
			} else {
				n.c = max.c;
				n.b = s.b - (max.c - s.c);
				path << string_me(s.b, s.c, max.c, 2) << "from B to C. "
						<< n.to_string();
			}
		} else {
			n.a = -1, n.b = -1, n.c = -1;
		}
		break;

	case 6:
		//a to c
		if (pour_possible(s.a, s.c, max.c)) {
			if ((max.c - s.c) >= s.a) {
				n.c = s.c + s.a;
				n.a = 0;
				path << string_me(s.a, s.c, max.c, 1) << "from A to C. "
						<< n.to_string();
			} else {
				n.c = max.c;
				n.a = s.a - (max.c - s.c);
				path << string_me(s.a, s.c, max.c, 2) << "from A to C. "
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

//Helper that simply checks if two states are the same --should delete
bool same_state(State uno, State dos) {
	if (uno.a == dos.a and uno.b == dos.b and uno.c == dos.c) {
		return true;
	} else
		return false;
}

//Helper to check if state s is in vector v
bool not_in_vector(State s, vector<State> v) {
	for (unsigned int i = 0; i < v.size(); i++) {
		if (same_state(v[i], s)) {
			return false;
		}
	}
	return true;
}

//Breadth first search to find and print each pour nessiary to reach the final state
//start is the initial state
//end is the final state
//max is not a state but instead the capacity of each jug
void bfs_pathfinder(State start, State end, State max) {
	//all states that have been visited that are a dead end.
	vector<State> visited_states;
	//queue to perform bfs on tree resulting from each possible pour
	queue<State> state_queue;
	state_queue.push(start);    // pushing first state on the queue
	visited_states.push_back(start);  //adding first state to visited_states
	if (same_state(start, end)) { //found the desired end
		start.print_path();
		return;
	}
	while (!state_queue.empty()) {
		State current = state_queue.front();
		for (int i = 1; i <= 6; i++) { //Checks all 6 possible new states

			if (same_state(current, end)) {
				current.print_path();
				return;
			}
			State current = pour(state_queue.front(), i, max);
			if (current.a != -1 and current.b != -1 and current.c != -1
					and not_in_vector(current, visited_states)) {
				//if the current state is different then the previous state (see pour) and the state is not in visited_states
				state_queue.push(current); //add this new state to the queue
				visited_states.push_back(current); //add it to the visited_states as well
			}
		}
		state_queue.pop();
	}
	cout << "No solution." << endl;
}

//the dumbest function I've ever made
const string dummy(const int n) {
	if (n == 1) {
		return "A";
	} else if (n == 2) {
		return "B";
	} else if (n == 3) {
		return "C";
	}
	return "X";
}

int main(int argc, char * const argv[]) {
	int n, m;

	istringstream iss;

	if (argc != 7) {
		cerr << "Usage: " << argv[0]
				<< " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>"
				<< endl;
		return 1;
	}

	//negative numbers jugs
	for (int i = 1; i <= 3; i++) {
		if (atoi(argv[i]) < 0) {
			cerr << "Error: Invalid capacity '" << argv[i] << "' for jug "
					<< dummy(i) << "." << endl;
			return 1;
		}
	}

	//negative numbers goals
	for (int i = 4; i <= 6; i++) {
		if (atoi(argv[i]) < 0) {
			cerr << "Error: Invalid goal '" << argv[i] << "' for jug "
					<< dummy(i - 3) << "." << endl;
			return 1;
		}
	}

	//jug is 0
	for (int i = 1; i <= 3; i++) {
		if (atoi(argv[i]) == 0) {
			cerr << "Error: Invalid capacity '" << argv[i] << "' for jug "
					<< dummy(i) << "." << endl;
			return 1;
		}
	}

	for (int i = 1; i <= 3; i++) {
		iss.str(argv[i]);
		if (!(iss >> n)) {
			cerr << "Error: Invalid capacity '" << argv[i] << "' for jug "
					<< dummy(i) << "." << endl;
			return 1;
		}
		iss.clear();
	}

	for (int i = 4; i <= 6; i++) {
		iss.str(argv[i]);
		if (!(iss >> m)) {
			cerr << "Error: Invalid goal '" << argv[i] << "' for jug "
					<< dummy(i - 3) << "." << endl;
			return 1;
		}
		iss.clear();
	}

	for (int i = 1; i <= 3; i++) {
		if (atoi(argv[i]) < atoi(argv[i + 3])) {
			cerr << "Error: Goal cannot exceed capacity of jug " << dummy(i)
					<< "." << endl;
			return 1;
		}

	}

	if ((atoi(argv[3]) != (atoi(argv[4]) + atoi(argv[5]) + atoi(argv[6])))) {
		cerr
				<< "Error: Total gallons in goal state must be equal to the capacity of jug C."
				<< endl;
		return 1;

	}

	State capacity((atoi(argv[1])), (atoi(argv[2])), (atoi(argv[3])));
	State start(0, 0, (atoi(argv[3])));
	ostringstream s;
	s << "Initial state. (0, 0, " << argv[3] << ")";
	start.add_path(s.str());
	State end((atoi(argv[4])), (atoi(argv[5])), (atoi(argv[6])));
	bfs_pathfinder(start, end, capacity);
	return 0;

}
