/*******************************************************************************
 * Name    : powergrid.cpp
 * Author  : Jessica Noel
 * Version : 1.0
 * Date    : January 9, 2016
 * Description : Computes the minimum set of roads on which to install power lines.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string.h>
#include <limits>
#include <stdio.h>
#include <ctype.h>
#include <cstddef>
#include <iomanip>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

using namespace std;

int num_vertices;

typedef vector<vector<int>> matrix;

void prims(int num_vertices, string** streets, int** dist){
	int edges = 0;
	long total = 0;

	vector<bool> included(num_vertices +1);

	for (int i = 0; i < num_vertices + 1; ++i){
		included[i] = false;
	}

	included[1] = true;

	vector<string> output;

	while(edges < num_vertices -1){
		int start = 1;
		int end = 1;
		int minweight = INT_MAX;

		for(int i = 1; i < num_vertices +1; ++i){
			if (included[i]){
				for (int j = 1; j < num_vertices +1; ++j) {
					if (!included[j] && dist[i][j] && (minweight > dist[i][j])){
							minweight = dist[i][j];
							start = i;
							end = j;
					}
				}
			}
		}
		if (start != end) {
			total += minweight;
			ostringstream oss;
			oss << streets[start][end] << " [" << minweight << "]";
			output.push_back(oss.str());
			oss.clear();
			included[end] = true;
		}
		edges++;
	}
	cout << "Total wire length (meters): " << total << endl;
	sort(output.begin(), output.end());

	for (size_t i = 0; i < output.size(); ++i){
		cout << output[i] << endl;
	}
}

template <typename Out>
void split(const std::string &s, char delim, Out result) {
	istringstream iss(s);
	string item;
	while (getline(iss, item, delim)) {
		*result++ = item;
	}
}

int main(int argc, const char *argv[]) {
	vector<string> input;
	int vv1, vv2, wweight;
	string line, v1, v2, weight, street;
	istringstream iss;
	int line_number = 1;

	// ------------------------- no file input ---------------------------
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <input file>" << endl;
		return 1;
	}

	// ---------------------- cannot open file ---------------------------
	ifstream input_file(argv[1]);
	if (!input_file) {
		cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
		input_file.close();
		return 1;
	}

	// ---------------------- check more errors --------------------------
	input_file.exceptions(ifstream::badbit);

	getline(input_file, line);
	iss.str(line);

	//---------------------- Invalid Number of Vertices ------------------

	if ((!(iss >> num_vertices)) || num_vertices < 1 || num_vertices > 1000) {
		cerr << "Error: Invalid number of vertices '" << line
				<< "' on line 1." << endl;
		return 1;
	}
	line_number = 2;
	iss.clear();

	string** streets = new string*[num_vertices +1];
	int** dist = new int*[num_vertices +1];

	for (int i = 0; i < num_vertices +1; ++i){
		streets[i] = new string[num_vertices +1];
		dist[i] = new int[num_vertices + 1];
	}

	for (int i = 0; i < num_vertices +1; i++) {
		for (int j = 0; j < num_vertices +1; j++) {
			streets[i][j] == i + " , " + j;
			if (i == j) {
				dist[i][j] = 0;

			} else {
				dist[i][j] = INT_MAX;
			}
		}
	}


	while (getline(input_file, line)){
		int commacounter = 0;
		for (size_t i = 0; i < line.size(); ++i) {
			if (line.at(i) == ','){
				commacounter++;
			}
		}
		// --------------------- Invalid Edge Data --------------------
		if (commacounter != 3){
			cerr << "Error: Invalid edge data '" << line
					<< "' on line " << line_number << "." << endl;
			for (int i = 0; i < num_vertices +1; ++i){
				delete[] streets[i];
				delete[] dist[i];
			}
			delete[] streets;
			delete[] dist;
			input_file.close();
			return 1;
		}

		string str = line;
		stringstream ss(str);


		split(str, ',', back_inserter(input));

		v1 = input[0];
		v2 = input[1];
		weight = input[2];
		street = input[3];

		input.erase(input.begin(), input.end());

		stringstream sss(v1);

		// --------------- Starting vertex is Invalid -----------------
		if (!(sss >> vv1) || !(1 <= stoi(v1) && stoi(v1) <= num_vertices)) {
				cerr << "Error: Starting vertex '" << v1 << "' on line "
						<< line_number << " is not among valid values 1-"
						<< num_vertices << "." << endl;
				for (int i = 0; i < num_vertices +1; ++i){
					delete[] streets[i];
					delete[] dist[i];
				}
				delete[] streets;
				delete[] dist;
				input_file.close();
				return 1;
		}
		sss.clear();
		sss.str(v2);

		// ---------------- Ending vertex is Invalid ------------------
		if (!(sss >> vv2) || !(1 <= stoi(v2) && stoi(v2) <= num_vertices)) {
			cerr << "Error: Ending vertex '" << v2 << "' on line "
					<< line_number << " is not among valid values 1-"
					<< num_vertices << "." << endl;
			for (int i = 0; i < num_vertices +1; ++i){
				delete[] streets[i];
				delete[] dist[i];
			}
			delete[] streets;
			delete[] dist;
			input_file.close();
			return 1;
		}

		sss.clear();
		sss.str(weight);
		// --------------------- Invalid Edge Weight ------------------
		if (!(sss >> wweight) || wweight < 1) {
			cerr << "Error: Invalid edge weight '" << weight << "' on line "
					<< line_number << "." << endl;
		for (int i = 0; i < num_vertices +1; ++i){
			delete[] streets[i];
			delete[] dist[i];
		}
		delete[] streets;
		delete[] dist;
		input_file.close();
		return 1;
		}
		streets[vv1][vv2] = street;
		streets[vv2][vv1] = street;
		dist[vv1][vv2] = wweight;
		dist[vv2][vv1] = wweight;
		line_number++;
	}

	//--------------------------No Solution-------------------------------
	if ((line_number - 1 < num_vertices) || num_vertices == 1){
		cerr << "No solution." << endl;
		for (int i = 0; i < num_vertices +1; ++i){
			delete[] streets[i];
			delete[] dist[i];
		}
		delete[] streets;
		delete[] dist;
		input_file.close();
		return 1;
	}

	prims(num_vertices, streets, dist);
	iss.clear();
	input_file.close();
	for (int i = 0; i < num_vertices +1; ++i){
		delete[] streets[i];
		delete[] dist[i];
	}
	delete[] streets;
	delete[] dist;
	return 1;
}
