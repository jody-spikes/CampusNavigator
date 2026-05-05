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

LocationID Campus::addLocation(const std::string& name,
                               Category category,
                               const std::string& description) {
    LocationID id = graph_.addLocation(name, category, description);
    if (id == INVALID_ID) return INVALID_ID;

    nameIndex_.insert(name, id);
    sortedIndex_.insert(name, id);

    return id;
}

bool Campus::removeLocation(const std::string& name) {
    LocationID id = nameIndex_.find(name);
    if (id == INVALID_ID) return false;

    if (!nameIndex_.remove(name)) return false;
    if (!sortedIndex_.remove(name)) return false;

    return graph_.removeLocation(id);
}

bool Campus::updateLocation(const std::string& name,
                            const std::string& newName,
                            Category newCategory,
                            const std::string& newDescription) {
    LocationID id = nameIndex_.find(name);
    if (id == INVALID_ID) return false;

    if (name != newName) {
        nameIndex_.remove(name);
        sortedIndex_.remove(name);
    }

    if (!graph_.updateLocation(id, newName, newCategory, newDescription)) {
        return false;
    }

    if (name != newName) {
        nameIndex_.insert(newName, id);
        sortedIndex_.insert(newName, id);
    }

    return true;
}

bool Campus::addConnection(const std::string& fromName,
                           const std::string& toName,
                           double distance) {
    LocationID from = nameIndex_.find(fromName);
    LocationID to   = nameIndex_.find(toName);

    if (from == INVALID_ID || to == INVALID_ID) return false;

    return graph_.addEdge(from, to, distance);
}

bool Campus::removeConnection(const std::string& fromName,
                              const std::string& toName) {
    LocationID from = nameIndex_.find(fromName);
    LocationID to   = nameIndex_.find(toName);

    if (from == INVALID_ID || to == INVALID_ID) return false;

    return graph_.removeEdge(from, to);
}

LocationID Campus::findByName(const std::string& name) const {
    return nameIndex_.find(name);
}

std::vector<LocationID> Campus::listAll() const {
    return sortedIndex_.inOrder();
}

std::vector<LocationID> Campus::listByCategory(Category c) const {
    std::vector<LocationID> result;
    std::vector<LocationID> all = sortedIndex_.inOrder();

    for (LocationID id : all) {
        const Location* loc = graph_.getLocation(id);
        if (loc != nullptr && loc->category == c) {
            result.push_back(id);
        }
    }

    return result;
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
