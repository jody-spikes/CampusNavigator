#ifndef CAMPUS_H
#define CAMPUS_H

// ============================================================================
// Campus.h - The integration hub
// OWNER: Student 5 (Jody)
// ----------------------------------------------------------------------------
// This is the front-door class for the whole system.
// main.cpp talks to Campus. Campus talks to Graph, NameHashTable, SortedIndex.
//
// GOLDEN RULE:
//   Any mutation (add / remove / update) MUST write to all three structures
//   so they stay consistent. If you add to the graph but forget the hash
//   table, lookups break. If you remove from the graph but forget the tree,
//   the sorted listing shows ghosts. This class is where consistency lives.
// ============================================================================

#include "Location.h"
#include "Graph.h"
#include "NameHashTable.h"
#include "SortedIndex.h"

#include <string>
#include <vector>
#include <algorithm>

class Campus {
public:
    Campus();

    // File I/O
    bool load(const std::string& locFile, const std::string& edgeFile);
    bool save(const std::string& locFile, const std::string& edgeFile) const;

    // Mutations - these MUST keep graph, hash, and tree in sync.
    LocationID addLocation(const std::string& name,
                           Category category,
                           const std::string& description);
    bool removeLocation(const std::string& name);
    bool updateLocation(const std::string& name,
                        const std::string& newName,
                        Category newCategory,
                        const std::string& newDescription);

    bool addConnection(const std::string& fromName,
                       const std::string& toName,
                       double distance);
    bool removeConnection(const std::string& fromName,
                          const std::string& toName);

    // Queries
    LocationID findByName(const std::string& name) const;   // uses hash
    std::vector<LocationID> listAll() const;                // uses tree
    std::vector<LocationID> listByCategory(Category c) const;
    std::vector<LocationID> route(const std::string& fromName,
                                  const std::string& toName) const;

    // Accessor used by main.cpp to print details for an ID.
    const Location* getLocation(LocationID id) const;

private:
    Graph          graph_;
    NameHashTable  nameIndex_;
    SortedIndex    sortedIndex_;
};

#endif // CAMPUS_H
