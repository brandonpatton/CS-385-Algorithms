/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : bpatton
 * Version     : 1.0
 * Date        : 11/3/18
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 * 							Brandon Patton
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
	long inversion_count = 0;
	for (int i = 0; i < length - 1; i++){
		for(int j = i + 1; j < length; j++){
			if (array[i] > array[j]){
				inversion_count++;
			}
		}
	}
	return inversion_count;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    // Hint: Use mergesort!
	int *scratch = new int[length];
	long count_inversions = mergesort(array, scratch, 0, length - 1);
	delete[] scratch;
	return count_inversions;

}

static long mergesort(int array[], int scratch[], int low, int high) {
    long inversion_count = 0;
	if (low < high){
		int mid = low + (high - low) / 2;
		inversion_count += mergesort(array, scratch, low, mid);
		inversion_count += mergesort(array, scratch, mid + 1, high);
		int L = low;
		int H = mid + 1;
		for (int k = low; k <= high; k++){
			if (L <= mid && (H > high || array[L] <= array[H])){
				scratch[k] = array[L];
				L += 1;
			} else {
				inversion_count += mid + 1 - L;
				scratch[k] = array[H];
				H += 1;
			}
		}
		for (int k = low; k <= high; k++){
			array[k] = scratch[k];
		}
	}
	return inversion_count;
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument

	if (argc > 2){
		cerr << "Usage: ./inversioncounter [slow]";
		return 1;
	}
	bool slow = 0;
	if ((argv[1] != NULL) && (strcmp(argv[1], "slow") == 0)){
		slow = 1;
	}
	else if (argv[1] != NULL) {
		cerr << "Error: Unrecognized option '" << argv[1] << "'.";
		return 1;
	}
    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    // TODO: produce output
    if (values.size() > 0){
    	if (slow){
    		cout << "Number of inversions: " << count_inversions_slow(&values[0], values.size()) << endl;
    	} else {
    		cout << "Number of inversions: " << count_inversions_fast(&values[0], values.size()) << endl;
    	}
    } else {
    	cerr << "Error: Sequence of integers not received." << endl;
    	return 1;
    }
    return 0;
}
