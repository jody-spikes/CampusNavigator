// ============================================================================
// Campus.cpp - Integration hub implementation
// OWNER: Student 5 (Jody)
// ============================================================================

#include "Campus.h"
#include "FileIO.h"

Campus::Campus() {
    // Default-constructed members handle themselves.
}

bool Campus::load(const std::string& locFile, const std::string& edgeFile) {
    return FileIO::loadCampus(locFile, edgeFile, graph_, nameIndex_, sortedIndex_);
}

bool Campus::save(const std::string& locFile, const std::string& edgeFile) const {
    return FileIO::saveCampus(locFile, edgeFile, graph_);
}

// ----------------------------------------------------------------------------
// EXAMPLE PATTERN for mutations (read this - every mutation looks like this):
// ----------------------------------------------------------------------------
LocationID Campus::addLocation(const std::string& name,
                               Category category,
                               const std::string& description) {
    // 1. Write to graph first (graph assigns the ID).
    LocationID id = graph_.addLocation(name, category, description);
    if (id == INVALID_ID) return INVALID_ID;

    // 2. Mirror into hash table.
    nameIndex_.insert(name, id);

    // 3. Mirror into sorted tree.
    sortedIndex_.insert(name, id);

    return id;
}

bool Campus::removeLocation(const std::string& name) {
    // TODO: mirror the pattern above, but in the OPPOSITE order:
    //   1. find id via nameIndex_.find(name); bail if INVALID_ID.
    //   2. remove from nameIndex_ and sortedIndex_ (by name).
    //   3. remove from graph_ (by id).
    //   Reason for order: you need the name-to-id lookup BEFORE you nuke the name.
    (void)name;
    return false;
}

bool Campus::updateLocation(const std::string& name,
                            const std::string& newName,
                            Category newCategory,
                            const std::string& newDescription) {
    // TODO: tricky case - if the name changes, you must remove the old
    //       name from hash and tree, then insert the new one.
    //       If the name doesn't change, just update the graph's copy.
    (void)name; (void)newName; (void)newCategory; (void)newDescription;
    return false;
}

bool Campus::addConnection(const std::string& fromName,
                           const std::string& toName,
                           double distance) {
    // TODO: look up both IDs via hash, call graph_.addEdge(from, to, distance).
    (void)fromName; (void)toName; (void)distance;
    return false;
}

bool Campus::removeConnection(const std::string& fromName,
                              const std::string& toName) {
    // TODO: look up both IDs via hash, call graph_.removeEdge(from, to).
    (void)fromName; (void)toName;
    return false;
}

LocationID Campus::findByName(const std::string& name) const {
    return nameIndex_.find(name);
}

std::vector<LocationID> Campus::listAll() const {
    return sortedIndex_.inOrder();
}

std::vector<LocationID> Campus::listByCategory(Category c) const {
    // TODO: iterate sortedIndex_.inOrder() (so results stay alphabetical),
    //       look up each Location via graph_.getLocation(id), keep those
    //       whose category matches c.
    (void)c;
    return {};
}

std::vector<LocationID> Campus::route(const std::string& fromName,
                                      const std::string& toName) const {
    LocationID from = nameIndex_.find(fromName);
    LocationID to   = nameIndex_.find(toName);
    if (from == INVALID_ID || to == INVALID_ID) return {};
    return graph_.bfsPath(from, to);
}

const Location* Campus::getLocation(LocationID id) const {
    return graph_.getLocation(id);
}