/*
* Author: Ian Dudley
* Assignment Title:  Graph
* Assignment Description: makes a cpp file for the graph
* Due Date: 5/6/2026
* Date Created: 4/30/2026
* Date Last Modified: 5/4/2026
 */
#include "CampusGraph.h"

bool Graph::AddLocation(const string& name,
		const string& category, const string& description){
	Locations.push_back(Location(name, category, description));

	return false;
};
// finds the index of a location
// returns -1 if it doesn't find it
int Graph::FindLocation(const Location& loc){
	int index = 0, size = Locations.size();
	while (Locations[index] != loc && index < size){
		index++;
	}
	if (index == size)
		index = -1;
	return index;
}
//sets the location to something like dead. doesnt delete the spot
bool Graph::RemoveLocation(Location& loc){
	int index = FindLocation(loc);
	Locations[index] = Location();
	return Locations[index].name == "glumped";
};
//edits the location given (index, name, category, description)
//I don't really get why one would use this
bool Graph::UpdateLocation(const int& index, const string& name,
		const string& category, const string& description){

	return false;
};
//gives all of the positions in the location vector that are taken
vector<int> Graph::GetAllIDs(){
	vector<int> indexes;
	cout << "man i love shlump" << endl;

	return indexes;
};


// adds an edge to the edge vector on both the adjacency
// list of i1 and the list of i2
void Graph::AddEdge(const int& i1, const int& i2, const double& weight){
	adjacencyList[i1].push_back(pair<int, double>(i2, weight));
	adjacencyList[i2].push_back(pair<int, double>(i1, weight));
};
//removes the edge pointing from i1 to i2 and i2 to i1
bool Graph::RemoveEdge(const int& i1, const int& i2){
	int erasdex1 = 0, erasdex2 = 0;
	bool glump = false;
	while (adjacencyList[i1][erasdex1].first != i2){
		erasdex1++;
	}
	while (adjacencyList[i2][erasdex2].first != i1){
		erasdex2++;
	}
	if (erasdex1 < adjacencyList[i1].size() &&
		erasdex2 < adjacencyList[i2].size()){
		adjacencyList[i1].erase(adjacencyList[i1].begin() + erasdex1);
		adjacencyList[i2].erase(adjacencyList[i2].begin() + erasdex2);
		glump = true;
	}
	return glump;
}
//returns the adjacency list of whatever index is given
vector<pair<int, double>>& Graph::GetNeighbors(const int& index){
	return adjacencyList[index];
};

// uses BFS to find cheapest path from i1 to i2
vector<string> Graph::BFS_Path(const int& i1, const int& i2){
	queue<Location> q;
	vector<bool> visited(Locations.size(), false);
	vector<int> parent(Locations.size());
	vector<string> path;
	q.push(Locations[i1]);

	while(!q.empty()){
		Location vector = q.front();
		q.pop();
		int vecIndex = FindLocation(vector);
		for(pair<int, double> edge: GetNeighbors(vecIndex)){
			if (!visited[edge.first]){
				visited[edge.first] = true;
				parent[edge.first] = vecIndex;
				q.push(Locations[edge.first]);
			}
		}
	}
	if (visited[i2]){
		int current = i2;
		while (current != i1){
			path.push_back(Locations[current].name);
			current = parent[current];
		}
		path.push_back(Locations[i1].name);
		std::reverse(path.begin(), path.end());
	}

	return path;
};



