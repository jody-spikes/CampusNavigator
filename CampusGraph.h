/*
* Author: Ian Dudley
* Assignment Title:  Graph
* Assignment Description: makes a graph object
* Due Date: 5/6/2026
* Date Created: 4/30/2026
* Date Last Modified: 5/4/2026
 */

#ifndef CAMPUSGRAPH_H_
#define CAMPUSGRAPH_H_

#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

class Graph{
private:
	struct Location{
		string name, category, description;

		// Location constructor for an empty/dead location
		Location():name("glumped"), category(), description(){};

		// Location constructor. takes in name, category, and description
		Location(const string& n, const string& cat, const string& desc)
			:name(n), category(cat), description(desc){};

		// comparison operator to see if two locations are the same
		bool operator==(const Location& loc){
			return name == loc.name;
		};
		bool operator!=(const Location& loc){
			return name != loc.name;
		};
	};

	vector<Location> Locations;
	// for the edges, using an adjacancyList that stores the name
	// of the connecting edge, and its weight as a double
	vector<vector<pair<int, double>>> adjacencyList;


public:
	//puts a location into the location vector
	bool AddLocation(const string& name,
			const string& category, const string& description);
	// finds the index of a location
	// returns -1 if it doesn't find it
	int FindLocation(const Location& loc);
	//sets the location to something like dead. doesnt delete the spot
	bool RemoveLocation(Location& loc);
	//edits the location given (index, name, category, description)
	bool UpdateLocation(const int& index, const string& name,
			const string& category, const string& description);
	//gives all of the positions in the location vector that are taken
	vector<int> GetAllIDs();

	// adds an edge to the edge vector on both the adjacency
	// list of i1 and the list of i2
	void AddEdge(const int& i1, const int& i2, const double& weight);
	//removes the edge pointing from i1 to i2 and i2 to i1
	bool RemoveEdge(const int& i1, const int& i2);
	//returns the adjacency list of whatever index is given
	vector<pair<int, double>>& GetNeighbors(const int& index);

	// uses BFS to find a path from index1(i1) to index2(i2)
	// returns the path as a vector of strings
	vector<string> BFS_Path(const int& i1, const int& i2);
};

#endif /* CAMPUSGRAPH_H_ */
