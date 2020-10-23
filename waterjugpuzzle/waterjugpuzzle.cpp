/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Cindy Zhang, Jessica Noel
 * Date        : 09/30/2020
 * Description : Famous water jug puzzle using breadth-first search in C++.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <ctype.h>
#include <queue>
#include <string>

using namespace std;

struct State {
	int a, b, c, gallons;
	char one, two;
	State *parent;
	State(int _a, int _b, int _c, int _gallons, char _one, char _two) :
		a{_a}, b{_b}, c{_c}, gallons{_gallons}, one{_one}, two{_two}, parent{nullptr} { }

	string to_string() {
		ostringstream oss;
		if(gallons == 0){
			oss << "Initial state. (" << a << ", " << b << ", " << c << ")";										//Initial State.
		}
		else if(gallons == 1){
			oss << "Pour 1 gallon from " << one << " to " << two << ". (" << a << ", " << b << ", " << c << ")";	//One Gallon
		}
		else{
			oss << "Pour " << gallons << " gallons from " << one << " to " << two << ". (" << a << ", " << b << ", " << c << ")";
		}
		return oss.str();
	}
};

vector<int> pour(int cap[], vector<int> cur, int one, int two){	// single pour function
	vector<int> c;												// jug one to jug two
	if(cur[two - 65] == cap[two - 65]){							// is jug two full?
		c.push_back(cur[0]);									// push back all values
		c.push_back(cur[1]);									// of current vector.
		c.push_back(cur[2]);
		return c;
	}
	int temp = cur[two - 65] + cur[one - 65];					// jug one + jug two

	if(temp <= cap[two - 65]){									// sum <= cap of two
		cur[two - 65] = temp;									// two = sum
		temp = cur[one - 65];
		cur[one - 65] = 0;										// one = 0
		c.push_back(cur[0]);									// push all values
		c.push_back(cur[1]);									// into a vector
		c.push_back(cur[2]);
		c.push_back(temp);
		return c;
	}

	temp -= cap[two - 65];										// sub cap of two from sum
	int diff = cur[one - 65] - temp;
	cur[one - 65] = temp;										// one = new sum
	cur[two - 65] = cap[two - 65];								// two = capacity of two
	c.push_back(cur[0]);
	c.push_back(cur[1]);
	c.push_back(cur[2]);
	c.push_back(diff);
	return c;
}

vector<vector<int>> mulpour(int cap[], vector<int> &current){	// multiple pour function.
	int one, two;
	vector<int> c;
	c.push_back(current[0]);
	c.push_back(current[1]);
	c.push_back(current[2]);

	//----------------------------------Jug A and B Empty-----------------------------------------

	if(current[0] == 0 && current[1] == 0){
		vector<vector<int>> ways{{67,65,cap[0],0,(cap[2]-cap[0]),cap[0]},{67,66,0,cap[1],(cap[2] - cap[1]),cap[1]}};
		return ways;
	}

	//-------------------------------------Jug A is Empty-------------------------------------------

	if(current[0] == 0){
		vector<vector<int>> ways{{67,65},{66,65},{67,66},{66,67}};
		for(int i = 0; i < 4; i++){
			c = current;
			c = current;
			one = ways[i][0];
			two = ways[i][1];
			c = pour(cap, c, one, two);
			ways[i].push_back(c[0]);
			ways[i].push_back(c[1]);
			ways[i].push_back(c[2]);
			ways[i].push_back(c[3]);
		}
		return ways;
	}

	//-------------------------------------Jug B is Empty-------------------------------------------

	if(current[1] == 0){
		vector<vector<int>> ways{{67,65},{67,66},{65,66},{65,67}};
		for(int i = 0; i < 4; i++){
			c = current;
			one = ways[i][0];
			two = ways[i][1];
			c = pour(cap, c, one, two);
			ways[i].push_back(c[0]);
			ways[i].push_back(c[1]);
			ways[i].push_back(c[2]);
			ways[i].push_back(c[3]);
		}
		return ways;
	}

	//-------------------------------------Jug C is Empty-------------------------------------------

	if(current[2] == 0){
		vector<vector<int>> ways{{66,65},{65,66},{66,67},{65,67}};
		for(int i = 0; i < 4; i++){
			c = current;
			one = ways[i][0];
			two = ways[i][1];
			c = pour(cap, c, one, two);
			ways[i].push_back(c[0]);
			ways[i].push_back(c[1]);
			ways[i].push_back(c[2]);
			ways[i].push_back(c[3]);
		}
		return ways;
	}

	//-------------------------------------Six ways-------------------------------------------

	vector<vector<int>> ways{{67,65},{66,65},{67,66},{65,66},{66,67},{65,67}};
	for(int i = 0; i < 6; i++){
		c = current;
		one = ways[i][0];
		two = ways[i][1];

		c = pour(cap, c, one, two);
		ways[i].push_back(c[0]);
		ways[i].push_back(c[1]);
		ways[i].push_back(c[2]);
		ways[i].push_back(c[3]);
	}

	return ways;
}

bool saw(vector<State*> seen, State &s){
	for(size_t i = 0; i < seen.size(); ++i){											// loop through seen
		if((s.a == seen[i]->a) && (s.b == seen[i]->b) && (s.c ==seen[i]->c)){			// if current is seen
			return true;
		}
	}
	return false;
}

void display(State* result){
	vector<State*> r;

	while(result->parent != NULL){				// reverse sort
		r.push_back(result);					// into an array
		result = result->parent;
	}											// push because parent is null
	r.push_back(result);						// last parent

	for(size_t i = r.size() - 1; i > 0; i--){	// Iterate through
		cout << r[i]->to_string() << endl;		// print state
	}
	cout << r[0]->to_string() << endl;
}

int bfs(State* start, State goal, int cap[]){
	vector<State*> seen;
	queue<State*> q;
	q.push(start);
	State* current;

	while(!q.empty()){
		current = q.front();
		q.pop();

		if((current->a == goal.a) && (current->b == goal.b) && (current->c == goal.c)){	 // if current state
			display(current);															 // print sequence
			delete current;																 // delete current
			while(!q.empty()){															 // delete q
				delete q.front();
				q.pop();
			}
			for(size_t i = 1; i < seen.size(); i++){									 // delete seen vector
				delete seen[i];
			}
																						 // 0 says
			return 0; 																	 // bfs found solution
		}
		if(saw(seen, *current)){														 // if current is seen
			delete current;																 // delete current state
			continue;																	 // restart while loop
		}
		seen.push_back(current);														 // seen this current state
		vector<int> s{(*current).a, current->b, current->c};							 // put current jug to vect
		vector<vector<int>> ss = mulpour(cap, s);										 // pour into diff states.

		for(size_t i = 0; i < ss.size(); i++){											 					// go through vector
			State* s = new State(ss[i][2], ss[i][3], ss[i][4], ss[i][5], (char)ss[i][0], (char)ss[i][1]);	// make new state, with circum.
			s->parent = current;																			// make their parent current
			q.push(s);																						// push state onto q
		}
	}

	//-------------------------------------No solution-------------------------------------------

	while(!q.empty()){							// delete q
		delete q.front();
		q.pop();
	}
	for(size_t i = 1; i < seen.size(); i++){	// delete seen vector
		delete seen[i];
	}
	return 1;
}

int main(int argc, char * const argv[]) {
	if(argc != 7){
		cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
		return 1;
	}

	istringstream temp;
	int caps[3];
	int goals[3];
	char jug;

	//----------------------------------checks caps-----------------------------------------

	for(int i = 0; i < 3; i++){
		jug = i + 65;
		temp.str(argv[i+1]);
		if(!(temp >> caps[i]) || (caps[i] <= 0)) {
			cerr << "Error: Invalid capacity '" << argv[i+1] << "' for jug " << jug << "."  << endl;
			return 1;
		}
		temp.clear();
	}

	//----------------------------------checks goals-----------------------------------------

	for(int i = 0; i < 3; i++){
		jug = i + 65;
		temp.str(argv[i+4]);
		if(!(temp >> goals[i]) || (goals[i] < 0)){
			cerr << "Error: Invalid goal '" << argv[i+4] << "' for jug " << jug << "."  << endl;
			return 1;
		}
		temp.clear();
	}

	//----------------------------------goal > caps?-----------------------------------------

	for(int i = 0; i < 3; i++){
		jug = i + 65;
		if(goals[i] > caps[i]){
			cerr << "Error: Goal cannot exceed capacity of jug " << jug << "." << endl;
			return 1;
		}
	}

	//----------------------------------does it add up?-----------------------------------------

	int sum = goals[0] + goals[1] + goals[2];
	if(sum != caps[2]){
		cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
		return 1;
	}

	//----------------------------------Goal == Start-----------------------------------------

	State s(0,0,caps[2],0,0,0);
	State g(goals[0], goals[1], goals[2], 0,0,0);

	if(goals[2] == caps[2]){
		cout << s.to_string();
		return 0;
	}

	//--------------------------------------BFS-------------------------------------------------

	if(bfs(&s, g, caps) != 0){
		cout << "No solution." << endl;
	}

	return 0;
}
