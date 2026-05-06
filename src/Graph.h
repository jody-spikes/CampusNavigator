#ifndef GRAPH_H
#define GRAPH_H

/*
* Author: Ian Dudley
* Assignment Title:  Graph
* Assignment Description: makes a cpp file for the graph
* Due Date: 5/6/2026
* Date Created: 4/30/2026
* Date Last Modified: 5/4/2026
 */

#include "Location.h"
#include <vector>
#include <utility>
#include <algorithm>

struct Edge {
    LocationID to;
    double distance;
};

class Graph {
public:
    Graph();
    ~Graph();

    // ------------------------------------------------------------------------
    // Location operations
    // ------------------------------------------------------------------------

    // Adds a new location. Returns the new LocationID.
    LocationID addLocation(const std::string& name,
                           Category category,
                           const std::string& description);

    // Removes the location with the given ID. Returns true on success.
    bool removeLocation(LocationID id);

    // Updates an existing location's fields. Returns true on success.
    bool updateLocation(LocationID id,
                        const std::string& name,
                        Category category,
                        const std::string& description);

    // Returns a pointer to the Location with the given ID, or nullptr if not found.
    const Location* getLocation(LocationID id) const;

    // Returns all valid LocationIDs in the graph (any order).
    std::vector<LocationID> getAllIDs() const;


    // ------------------------------------------------------------------------
    // Edge operations (treat edges as undirected: add both directions)
    // ------------------------------------------------------------------------

    // Adds an undirected edge between two locations with the given distance.
    // Returns true on success, false if either ID is invalid.
    bool addEdge(LocationID from, LocationID to, double distance);

    // Removes the edge between two locations. Returns true on success.
    bool removeEdge(LocationID from, LocationID to);

    // Returns all neighbors of the given location as (neighbor_id, distance) pairs.
    std::vector<std::pair<LocationID, double>> getNeighbors(LocationID id) const;

    // ------------------------------------------------------------------------
    // Pathfinding
    // ------------------------------------------------------------------------

    // Returns a path from 'from' to 'to' as a list of LocationIDs
    // (starting with 'from', ending with 'to'). Empty vector if no path exists.
    
    // Breadth First Search Function
    std::vector<LocationID> bfsPath(LocationID from, LocationID to) const;

    // EXTENSION (extra credit): Dijkstra's shortest weighted path.
    std::vector<int> dijkstraPath(LocationID start) const;

private:
    std::vector<Location> locations_;
    std::vector<bool> active_; // marks removed slots
    std::vector<std::vector<Edge>> adjacency_;  // adjacency_[id] = edges from id

    bool isValid(LocationID id) const;
};

#endif // GRAPH_H
