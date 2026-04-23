#ifndef GRAPH_H
#define GRAPH_H

// ============================================================================
// Graph.h - Campus graph and route engine
// OWNER: Student 1
// ----------------------------------------------------------------------------
// The Graph is the single source of truth for Location data.
// Other modules (HashTable, SortedIndex) store only LocationIDs that
// point back into this Graph.
//
// Implementation suggestion:
//   - Store locations in a vector<Location>, where the index IS the ID.
//   - Store edges as an adjacency list: vector<vector<Edge>>.
//   - When a location is "removed", mark it inactive rather than shifting
//     indices (shifting would invalidate every other module's IDs).
// ============================================================================

#include "Location.h"
#include <vector>
#include <utility>

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
    // TODO: assign a fresh ID, push a Location onto storage, return the ID.
    LocationID addLocation(const std::string& name,
                           Category category,
                           const std::string& description);

    // Removes the location with the given ID. Returns true on success.
    // TODO: also remove all edges touching this location.
    // HINT: consider marking inactive instead of erasing, so other IDs stay valid.
    bool removeLocation(LocationID id);

    // Updates an existing location's fields. Returns true on success.
    // TODO: look up the ID and overwrite the fields.
    bool updateLocation(LocationID id,
                        const std::string& name,
                        Category category,
                        const std::string& description);

    // Returns a pointer to the Location with the given ID, or nullptr if not found.
    // The returned pointer is read-only and valid until the next graph mutation.
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
    //
    // TODO: implement breadth-first search using a queue.
    // Remember to track visited nodes and record parent pointers
    // so you can reconstruct the path.
    std::vector<LocationID> bfsPath(LocationID from, LocationID to) const;

    // EXTENSION (extra credit): Dijkstra's shortest weighted path.
    // Leave unimplemented or stub-returning empty for the baseline.
    std::vector<LocationID> dijkstraPath(LocationID from, LocationID to) const;

private:
    // TODO: pick internal storage. Suggestion:
    //   std::vector<Location> locations_;
    //   std::vector<bool> active_;                  // mark removed slots
    //   std::vector<std::vector<Edge>> adjacency_;  // adjacency_[id] = edges from id
};

#endif // GRAPH_H