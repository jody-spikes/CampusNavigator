// ============================================================================
// Graph.cpp - Implementation of the campus graph
// OWNER: Student 1
// ============================================================================

#include "Graph.h"

Graph::Graph() {
    // TODO: initialize internal storage if needed.
}

Graph::~Graph() {
    // TODO: clean up dynamic memory if you allocate any.
    // If you only use std::vector, nothing needed here.
}

LocationID Graph::addLocation(const std::string& name,
                              Category category,
                              const std::string& description) {
    // TODO: push a new Location onto storage, return its index as the ID.
    (void)name; (void)category; (void)description;  // silence unused warnings
    return INVALID_ID;
}

bool Graph::removeLocation(LocationID id) {
    // TODO: mark location inactive, remove all edges touching it.
    (void)id;
    return false;
}

bool Graph::updateLocation(LocationID id,
                           const std::string& name,
                           Category category,
                           const std::string& description) {
    // TODO: overwrite the fields of the Location with this ID.
    (void)id; (void)name; (void)category; (void)description;
    return false;
}

const Location* Graph::getLocation(LocationID id) const {
    // TODO: bounds-check id, return pointer if active, else nullptr.
    (void)id;
    return nullptr;
}

std::vector<LocationID> Graph::getAllIDs() const {
    // TODO: return a list of every active LocationID.
    return {};
}

bool Graph::addEdge(LocationID from, LocationID to, double distance) {
    // TODO: validate IDs, append to both adjacency lists (undirected).
    (void)from; (void)to; (void)distance;
    return false;
}

bool Graph::removeEdge(LocationID from, LocationID to) {
    // TODO: remove the edge from both adjacency lists.
    (void)from; (void)to;
    return false;
}

std::vector<std::pair<LocationID, double>> Graph::getNeighbors(LocationID id) const {
    // TODO: return adjacency_[id] converted to pairs.
    (void)id;
    return {};
}

std::vector<LocationID> Graph::bfsPath(LocationID from, LocationID to) const {
    // TODO: breadth-first search.
    //   1. queue<LocationID> frontier; push 'from'.
    //   2. vector<LocationID> parent(size(), INVALID_ID); parent[from] = from.
    //   3. while frontier not empty: pop current, for each neighbor not yet
    //      visited, set parent[neighbor] = current, push neighbor.
    //   4. if 'to' was reached, walk parent pointers back to reconstruct path.
    (void)from; (void)to;
    return {};
}

std::vector<LocationID> Graph::dijkstraPath(LocationID from, LocationID to) const {
    // EXTENSION: extra credit. Leave empty for baseline.
    (void)from; (void)to;
    return {};
}