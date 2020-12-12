/*******************************************************************************
 * Name        : shortestpaths.cpp
 * Author      : Jessica Noel & Cindy Zhang
 * Version     : 1.0
 * Date        : December 1, 2020
 * Description : Finds the shortest path between every pair of vertices in a given edge weighted directed Graph.
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

using namespace std;

long vertices, INF = LONG_MAX;
string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int num_vertices;

typedef vector<vector<long>> matrix;

matrix dist;
matrix paths;
matrix intermediate;

void make_distance_table() {
	vector<long> temp;
	for (unsigned int i = 0; i < vertices; i++) {
		for (unsigned int j = 0; j < vertices; j++) {
			if (i == j) {
				temp.push_back(0);
			} else {
				temp.push_back(INF);
			}
		}
		dist.push_back(temp);
		temp.clear();
	}
}

void make_paths_table() {
	vector<long> temp;
	for (unsigned int i = 0; i < vertices; i++) {
		for (unsigned int j = 0; j < vertices; j++) {
			if (i == j) {
				temp.push_back(0);
			} else {
				temp.push_back(INF);
			}
		}
		paths.push_back(temp);
		temp.clear();
	}
}

void make_inter_table() {
	vector<long> temp;
	for (unsigned int i = 0; i < vertices; i++) {
		for (unsigned int j = 0; j < vertices; j++) {
			temp.push_back(INF);
		}
		intermediate.push_back(temp);
		temp.clear();
	}
}

int digitl(long n){
	int digits = 0;
	if(n == 0){
		return 1;
	}
	while (n != 0) {
		n /= 10;
		digits++;
	}
	return digits;
}

int findmaxdigits(matrix x) {
	long max = 0;
	for (unsigned i = 0; i < x.size(); i++) {
		for (unsigned j = 0; j < x[i].size(); j++) {
			if (x[i][j] != INF && x[i][j] > max) {
				max = x[i][j];
			}
		}
	}
	return digitl(max);
}

void floyd(matrix w) {
	matrix d = w;
	long next, sum;
	for (int k = 0; k < vertices; k++) {
		for (int i = 0; i < vertices; i++) {
			for (int j = 0; j < vertices; j++) {
				if(d[i][k] == INF || d[k][j] == INF){		// checks if either one is inf,
					sum = INF;								// the sum will be inf
				}
				else{
					sum = d[i][k] + d[k][j];				// otherwise we add the nums,
				}
				next = min(d[i][j], sum);					// find the smaller one
				if(next != d[i][j]){						// put value into intermediate
					intermediate[i][j] = k;
				}
				d[i][j]= next;
			}
		}
	}
	paths = d;
}

void display_table(matrix matrix, const string &label, const bool use_letters = false) {
	cout << label << endl;
	int max_cell_width = findmaxdigits(matrix);
	//cout << "max cell width " << max_cell_width;
	cout << ' ';
	for(int j = 0; j < vertices; j++) {
		cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
	}
	cout << endl;
	for(int i = 0; i < vertices; i++) {
		cout << static_cast<char>(i + 'A');
		for(int j = 0; j < vertices; j++) {
			cout << " " << setw(max_cell_width);
			if (matrix[i][j] == INF) {
				cout << "-";
			}
			else if (use_letters) {
				cout << static_cast<char>(matrix[i][j] + 'A');
			}
			else {
				cout << matrix[i][j];
			}
		}
		cout << endl;
	}
	cout << endl;
}

string pathhelper(long x, long y){
	if(x == y){
		return "";
	}
	stringstream ss;
	long n = intermediate[x][y];

	if(n == INF){
		return string(1, alpha[x]) + " -> ";
	}

	ss << pathhelper(x, n) << pathhelper(n,y);
	return ss.str();
}

string show_path(int row, int col) {
	if(paths[row][col] == INF){
		return "none";
	}
	return pathhelper(row, col) + string(1, alpha[col]);
}

void display_paths() {
	stringstream ss;
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			ss << alpha[i] << " -> " << alpha[j] << ", distance: ";
			if(paths[i][j] == INF){
				ss << "infinity";
			}
			else{
				ss << paths[i][j];
			}
			ss << ", path: " << show_path(i, j) << endl;
		}
	}
	cout << ss.str();
}

int main(int argc, const char *argv[]) {

	// ------------------------- no file input ---------------------------
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <filename>" << endl;
		return 1;
	}

	// ---------------------- cannot open file ---------------------------
	ifstream input_file(argv[1]);
	if (!input_file) {
		cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
		return 1;
	}

	// ---------------------- check more errors --------------------------
	input_file.exceptions(ifstream::badbit);

	string line, v1, v2;
	long weight;
	int row, col;
	num_vertices = 0;
	istringstream iss;
	int line_number = 1;

	try {
		while (getline(input_file, line)) {
			iss.str(line);

			//---------------------- Invalid Number of Vertices -------------
			if (line_number == 1) {
				if (!(iss >> vertices) || vertices < 1 || vertices > 26) {
					cerr << "Error: Invalid number of vertices '" << line
							<< "' on line 1." << endl;
					return 1;
				}
				line_number = 2;
				iss.clear();

				// --------------------- initialize tables ---------------------
				make_distance_table();
				make_paths_table();
				make_inter_table();
				continue;
			}
			iss >> v1;
			iss >> v2;

			// --------------------- Invalid Edge Data --------------------
			if (iss.rdbuf()->in_avail() == 0) {
				cerr << "Error: Invalid edge data '" << v1 << " " << v2
						<< "' on line " << line_number << "." << endl;
				return 1;
			}
			// --------------------- Invalid Edge Weight ------------------
			if (!(iss >> weight)) {
				size_t found = line.find_last_of(" ");
				cerr << "Error: Invalid edge weight '" << line.substr(found + 1)
						<< "' on line " << line_number << "." << endl;
				return 1;
			}
			if (weight < 1) {
				cerr << "Error: Invalid edge weight '" << weight << "' on line "
						<< line_number << "." << endl;
				return 1;
			}

			// --------------- Starting vertex is Invalid -----------------
			for (int i = 0; i < vertices; i++) {
				if (v1[0] == alpha[i]) {
					row = i;
					break;
				}
				if (v1.length() != 1 || islower(v1[0])
						|| (i == vertices - 1 && v1[0] != alpha[i])) {
					cerr << "Error: Starting vertex '" << v1 << "' on line "
							<< line_number << " is not among valid values A-"
							<< alpha[vertices - 1] << "." << endl;
					return 1;
				}
			}

			// ---------------- Ending vertex is Invalid ------------------
			for (int i = 0; i < vertices; i++) {
				if (v2.length() != 1 || islower(v1[0])
						|| (i == vertices - 1 && v2[0] != alpha[i])) {
					cerr << "Error: Ending vertex '" << v2 << "' on line "
							<< line_number << " is not among valid values A-"
							<< alpha[vertices - 1] << "." << endl;
					return 1;
				}
				if (v2[0] == alpha[i]) {
					col = i;
					break;
				}
			}
			dist[row][col] = weight;
			//cout << dist[row][col];

			iss.clear();
			line_number++;
			num_vertices++;
		}
		input_file.close();
	} catch (const ifstream::failure &f) {
		cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
		return 1;
	}

	// --------------------put values in the table -----------------
	display_table(dist, "Distance matrix:");

	floyd(dist);

	display_table(paths, "Path lengths:");
	display_table(intermediate, "Intermediate vertices:", true);

	display_paths();
	return 0;
}
