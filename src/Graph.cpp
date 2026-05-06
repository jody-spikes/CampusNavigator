/*
* Author: Ian Dudley
* Assignment Title:  Graph
* Assignment Description: makes a cpp file for the graph
* Due Date: 5/6/2026
* Date Created: 4/30/2026
* Date Last Modified: 5/4/2026
 */

#include "Graph.h"

Graph::Graph() {
    // leave empty
}

Graph::~Graph() {
    // leave empty
}

//sanity check
bool Graph::isValid(LocationID id) const{
    return id >= 0 &&
    id < static_cast<LocationID>(active_.size()) &&
    active_[id];
}

LocationID Graph::addLocation(const std::string& name,
                              Category category,
                              const std::string& description) {
    LocationID id = static_cast<LocationID>(locations_.size());
    Location loc{id, name, category, description};
    locations_.push_back(loc);
    active_.push_back(true);
    adjacency_.emplace_back();
    return id;
}

bool Graph::removeLocation(LocationID id) {
    if (!isValid(id)) return false;

    for (const Edge& e : adjacency_[id]) {
        auto& neighborEdges = adjacency_[e.to];
        neighborEdges.erase(
            std::remove_if(neighborEdges.begin(), neighborEdges.end(),
                           [id](const Edge& x) { return x.to == id; }),
            neighborEdges.end()
        );
    }
    adjacency_[id].clear();
    active_[id] = false;
    return true;
}

bool Graph::updateLocation(LocationID id,
                           const std::string& name,
                           Category category,
                           const std::string& description) {
    if (!isValid(id)) return false;
    locations_[id].name = name;
    locations_[id].category = category;
    locations_[id].description = description;
    return true;
}

const Location* Graph::getLocation(LocationID id) const {
    if (!isValid(id)) return nullptr;
    return &locations_[id];
}

std::vector<LocationID> Graph::getAllIDs() const {
    std::vector<LocationID> ids;
    for(LocationID id = 0; id < static_cast<LocationID>(active_.size()); id++){
        if(active_[id]) ids.push_back(id);
    }
    return ids;
}

//---------------
//Edge Operations
//---------------

bool Graph::addEdge(LocationID from, LocationID to, double distance) {
    if (!isValid(from) || !isValid(to)) return false;
    if (from == to) return false;   // remove if we wanna self loop
    adjacency_[from].push_back({ to, distance });
    adjacency_[to].push_back({ from, distance });
    return true;
}

bool Graph::removeEdge(LocationID from, LocationID to) {
    if (!isValid(from) || !isValid(to)) return false;

    auto eraseEdge = [](std::vector<Edge>& edges, LocationID target) {
        auto before = edges.size();
        edges.erase(
            std::remove_if(edges.begin(), edges.end(),
                           [target](const Edge& e) { return e.to == target; }),
            edges.end()
        );
        return edges.size() != before;
    };

    bool a = eraseEdge(adjacency_[from], to);
    bool b = eraseEdge(adjacency_[to], from);
    return a && b;
}

std::vector<std::pair<LocationID, double>> Graph::getNeighbors(LocationID id) const {
    std::vector<std::pair<LocationID, double>> result;
    if (!isValid(id)) return result;
    for (const Edge& e : adjacency_[id]) {
        result.emplace_back(e.to, e.distance);
    }
    return result;
}

std::vector<LocationID> Graph::bfsPath(LocationID from, LocationID to) const {
    if (!isValid(from) || !isValid(to)) return {};
    if (from == to) return { from };

    const LocationID n = static_cast<LocationID>(locations_.size());
    std::vector<LocationID> parent(n, INVALID_ID);
    std::vector<bool> visited(n, false);

    std::vector<LocationID> frontier;
    frontier.push_back(from);
    visited[from] = true;   // updated from Ian's code

    bool found = false;
    while (!frontier.empty()) {
        LocationID current = frontier.front();
        frontier.erase(frontier.begin());

        if (current == to) { found = true; break; }

        for (const Edge& e : adjacency_[current]) {
            if (!visited[e.to] && active_[e.to]) {
                visited[e.to] = true;
                parent[e.to] = current;
                frontier.push_back(e.to);
            }
        }
    }

    if (!found) return {};

    // Walk parent pointers from to back to from, then reverse.
    std::vector<LocationID> path;
    for (LocationID cur = to; cur != INVALID_ID; cur = parent[cur]) {
        path.push_back(cur);
        if (cur == from) break;
    }
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<double> Graph::dijkstraPath(LocationID start) const {
   // EXTENSION: extra credit. Stub for baseline.
	const LocationID n = static_cast<LocationID>(locations_.size());
	bool visited[n] = {};
	std::vector<int> distances(n, std::numeric_limits<int>::max());




    return distances;
}
