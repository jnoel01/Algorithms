/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Jessica Noel
 * Date        : September 21, 2020
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
	/*Iterates through the alphabet and checks to see if each letter is lowercase
	if it is, it will return false, else it will return true */
	int instring = s.length();
	for (int i=0; i < instring; ++i) {
		if (!islower(s[i])){
			return false;
		}
	}
	return true;
}

bool all_unique_letters(const string &s) {
	//initialize values
	unsigned int base = 0;
	unsigned int set = 0;
	unsigned int instring = s.length();
	
	//iterates through the string and assigns the setter to "000..1"  (a)
	for (unsigned int i=0; i < instring; ++i) {
		set = 1 << (s[i]-s[0]);
		
		//if the base and setter are equal to 1 then it is not unique so return false
		//must be != 0 because the base and the setter can be equal to other numbers
		if((base & set) != 0) {
			return false;
		}
		
		//replaces the base with new value to continue with comparison/iteration through string
		base = base | set;
	}
	return true;
}

//prints outputs
int main(int argc, char * const argv[]) {
    //must have two arguments: unique <string>
	if (argc != 2) {
			cout << "Usage: ./unique <string>" << endl;
			return 1;
	}
	//calls the function which checks if the string has only lowercase
	//if the string is not only lowercase (func != true) return an error
	if (is_all_lowercase(argv[1]) != true) {
			cout << "Error: String must contain only lowercase letters." << endl;
			return 1;
	}
	/*calls the unique letter function and if true will
	 return that the string is unique, if not it will 
	 output that it is not unique (duplicate letters..)*/
	if (all_unique_letters(argv[1])) {
		cout << "All letters are unique." << endl;
	}
	else {
		cout << "Duplicate letters found." << endl;
	}
	return 0;
}
