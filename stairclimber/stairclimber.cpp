/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Jessica Noel
 * Date        : September 29, 2020
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
	//initializes a vector of type int
	vector<vector<int>> ways;
	unsigned int j;

	//When n has reached 0 and has no more stairs to go through
	if (num_stairs <= 0) {
		ways.push_back(vector<int>());
	}
	else {
		//Iterates through the main/bigger
		for (int i=1; i < 4; ++i) {
			if (num_stairs >= i) {
				vector<vector<int>>result;
				result = get_ways(num_stairs-i);
				//Iterates through the vectors inside the main vector
				//Return the actual integers that make up the whole vector
				for (j=0; j < result.size(); ++j) {
					auto iterator = result[j].begin();
					result[j].insert(iterator, i);
					ways.push_back(result[j]);
				}
			}
		}
	}
	return ways;
}

void display_ways(const vector< vector<int> > &ways) {
	//Displays the different ways to climb num_stairs in the proper format
	int waysize = ways.size();
	int start = 0;

	while(waysize > 0) {
		start++;
		waysize = waysize/10;
	}

	for (size_t i=0; i < ways.size(); ++i) {
		//Formats the beginning of each line properly (1. [...)
		 cout << setw(start) << i+1 << ". " << "[";
		for(size_t j=0; j < ways[i].size(); ++j) {
			//When you've reached the last number in each line
			//you do not need a comma and space so just end
			if (j == (ways[i].size() - 1)) {
				cout << ways[i][j];
			}
			else {
				//Formatting for numbers in the middle of the output ex [..., 2, 3...]
				cout << ways[i][j] << ", ";
			}
		}
		cout << "]" << endl;

	}
}

int main(int argc, char * const argv[]) {
	istringstream inputstring;
	int input;

	//When there are not 2 arguments print usage message
	if (argc != 2) {
		cout << "Usage: ./stairclimber <number of stairs>" << endl;
		return 1;
	}

	inputstring.str(argv[1]);

	//If the number of stairs are not an integer, print error
	if (!(inputstring >> input)) {
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}

	//If the number of stairs is not a positive integer print error
	if (input < 0) {
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}

	//For when the input is one (changes the plurality of each word in the output)
	if (input == 1) {
		cout << (get_ways(input)).size() << " way to climb " << input << " stair." << endl;
	}

	//Calls the methods to show the ways to climb N number of stairs
	else {
		cout << (get_ways(input)).size() << " ways to climb " << input << " stairs." << endl;
	}

	//Displays all ways to climb N stairs
	display_ways(get_ways(input));
	return 0;
}



