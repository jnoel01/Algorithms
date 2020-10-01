/*******************************************************************************
 * Name    : sqrt.cpp
 * Author  : Jessica Noel
 * Version : 1.0
 * Date    : September 2, 2020
 * Description : Computes the square root of double using Newton's method.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <limits>
#include <iomanip>
#include <sstream>

using namespace std;

double sqrt(double num, double epsilon) {
	if (num < 0){
		return numeric_limits<double>::quiet_NaN();
	}

	//the sqrt of 0 and 1 are just themselves
	else if (num == 0 || num==1) {
		return num;
	}
	
	//formula to calculate difference until difference is v minimal
	double last_guess= num;
	double next_guess=(last_guess + (num/last_guess))/2;

	while(abs(last_guess-next_guess) > epsilon) {
		last_guess=next_guess;
		next_guess=(last_guess + (num/last_guess))/2;
	}
	return next_guess;
}

int main(int argc, char *argv[]) {

	double num, epsilon;
	istringstream inputstring;

	//if there aren't 2 and 3 arguments there will be an error. 
	if(argc != 2 && argc != 3) {
		cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
		return 1;
	}

	//Asserts if the first arg is a double, if not: error.
	if (argc == 2){
		inputstring.str(argv[1]);

		if (!(inputstring >> num)) {
			cerr << "Error: Value argument must be a double." << endl;
			return 1;
		}
		cout << fixed << setprecision(8)<< sqrt(num, 1e-7) << endl;
	}
	
	//when using epsilon/ asserting if it is a positive double
	if (argc == 3){
		inputstring.str(argv[1]);

		if (!(inputstring >> num)) {
			cerr << "Error: Value argument must be a double." << endl;
			return 1;
		}

		inputstring.clear();
		inputstring.str(argv[2]);

		if (!(inputstring >> epsilon)) {
			cerr << "Error: Epsilon argument must be a positive double." << endl;
			return 1;
		}
		
		//
		if (epsilon <= 0){
			cerr << "Error: Epsilon argument must be a positive double." << endl;
			return 1;
		}
		
		//sets the printed value to be 8 decimal places
		cout << fixed << setprecision(8)<< sqrt(num, epsilon) << endl;
	}
	return 0;
}





