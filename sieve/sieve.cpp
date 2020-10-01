/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Jessica Noel
 * Date        : September 14th, 2020
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {

public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
    const int max_prime_width = num_digits(max_prime_), primes_per_row = 80 / (max_prime_width + 1);

    int numprime = 0;

    //If number of primes is less than primes that can fit in a row just print 1 line
    //Fixes spacing for single lined outputs
    if (num_primes_ <= primes_per_row) {
    	for (int i=2; i <= limit_; ++i) {
    		if(is_prime_[i] && i != max_prime_) {
    			cout << i << " ";
    		}
    		else {
    			//if its the last number in the row do not add a space after i
    			if(is_prime_[i]) {
    				cout << i;
    			}
    		}
    	}
    }
    else {
    	//Spacing for "regular first" prime numbers
		for (int i=2; i <= limit_; ++i) {
			if(is_prime_[i] && numprime == 0) {
				cout << setw(max_prime_width) << i;
				++numprime;
			}
			else {
				//Spacing for all other (not the first in the row) numbers
				if (is_prime_[i]) {
					cout << setw(max_prime_width + 1) << i;
					++numprime;

					/*Once a row is finished (numprime==primes_per_row) move on to next row
					and start loop over/reset numprimes (there a 0 num in the new row
					*/
					if (numprime == primes_per_row) {
						cout << endl;
						numprime = 0;
					}
				}
			}
		}
    }
}

int PrimesSieve::count_num_primes() const {
	int totalprimes = 0;

	//counts the number of primes found by seeing which numbers are true in the array
	for(int i = 2; i <= limit_; ++i) {
		if(is_prime_[i]) {
			totalprimes++;
		}
	}
    return totalprimes;
}

void PrimesSieve::sieve() {
	//Initially set each element in the array to true
	//You can start at 2 because 0 & 1 are not prime
	for (int i=2; i <= limit_; ++i) {
		is_prime_[i] = true;
	}

	for (int i = 2; i <= sqrt(limit_); ++i) {
		if (is_prime_[i]) {
			for (int j=pow(i,2); j<=limit_; j=j+i) {
				is_prime_[j] =false;
			}
		}
	}

	for (int i = limit_; i >= 0; --i) {
		if (is_prime_[i] == true) {
			max_prime_ = i;
			break;
		}
	}

	num_primes_ = count_num_primes();
}

int PrimesSieve::num_digits(int num) {
    //Determines how many digits are present in an integer (divide by 10 and count the number of times you divide by 10 unitl 0)
	int i =0 ;
	while (num > 0) {
		num = num / 10;
		++i;
	}
    return i;
}

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
    if (!(iss >> limit)) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    PrimesSieve totalprimes(limit);

    //Produces the desired output
    cout << endl;
    cout << "Number of primes found: " << totalprimes.num_primes() << endl;
    cout << "Primes up to " << limit << ":" << endl;
    totalprimes.display_primes();

    return 0;
}
