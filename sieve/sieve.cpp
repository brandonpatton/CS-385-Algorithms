/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : bpatton
 * Date        : September 17, 2018
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 * 					Brandon Patton
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>


using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit) : is_prime_{new bool[limit + 1]}, limit_{limit} {
        sieve();
    }

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    inline int num_primes() const {
        return num_primes_;
    }

    /*
     * void display_primes() const
     * 		Displays the primes in the format specified in the requirements document.
     */
    void display_primes() const {
    	int current_row = 0;
    	const int max_prime_width = num_digits(max_prime_),
    			  primes_per_row = 80 / (max_prime_width +1);
    	if (num_primes_ < primes_per_row){
    		for(int i = 2; i <= limit_; ++i){
    			if(is_prime_[i] == true){
    				if(current_row != 0){
    					cout << " ";
    				}
    				cout << i;
    				++current_row;
    			}
    		}
    	}
    	else{
    		for(int i = 2; i <= limit_; ++i){
    			if(current_row == primes_per_row){
    				cout << endl;
    				current_row = 0;
    			}
    			if (is_prime_[i] == true){
    				if (current_row != 0){
    					cout << " ";
    				}
    				cout << setw(max_prime_width) << i;
    				++current_row;
    			}
    		}
    	}
    }

private:
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    /*
     * int count_num_primes() const
     * 		Counts the number of primes found
     */
    int count_num_primes() const {
    	int prime = 0;
    	for (int i = 2; i <= limit_; ++i){
    		if(is_prime_[i] == true){
    			++prime;
    		}
    	}
    	return prime;
    }

    /*
     * int num_digits(int num) const
     * 		Determines how many digits are in an integer
     */
    int num_digits(int num) const {
    		int len = 1;
    		while (num >= 10){
    			++len;
    			num = num / 10;
    		}
    		return len;
    }

    /*
     * void sieve()
     * 		Determines if an element of a list is a prime number, attributing the value true to elements that are prime,
     * 		and false those not prime
     */
    void sieve() {
    	for (int n = 2; n <= limit_; ++n){  //Sets all the elements in is_prime_ to true
    		is_prime_[n] = true;
    	}
        for (int i = 2; i <= sqrt(limit_); ++i){
        	if (is_prime_[i] == true){
        		for (int j = i*i; j <= limit_; j+=i){
        			is_prime_[j] = false;
        		}
        	}
        }
        num_primes_ = count_num_primes();
        			max_prime_ = 0;
        			int k = limit_;
        			while (max_prime_ == 0){
        				if (is_prime_[k] == true){
        					max_prime_ = k;
        				}
        				else {
        					--k;
        				}
        			}
    }
};

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }
    PrimesSieve s1(limit);
		cout << endl;
		cout << "Number of primes found: " << s1.num_primes() << endl;
		cout << "Primes up to " << limit << ":" << endl;
		s1.display_primes();
		return 0;
}
