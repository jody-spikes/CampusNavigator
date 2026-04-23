// ============================================================================
// SortedIndex.cpp - Implementation of the sorted tree index
// OWNER: Student 3
// ============================================================================

#include "SortedIndex.h"

SortedIndex::SortedIndex() {
    // TODO: initialize root_ to nullptr.
}

SortedIndex::~SortedIndex() {
    // TODO: call destroy(root_) to free all nodes.
}

void SortedIndex::insert(const std::string& name, LocationID id) {
    // TODO: root_ = insertHelper(root_, name, id);
    (void)name; (void)id;
}

bool SortedIndex::remove(const std::string& name) {
    // TODO:
    //   bool removed = false;
    //   root_ = removeHelper(root_, name, removed);
    //   return removed;
    (void)name;
    return false;
}

std::vector<LocationID> SortedIndex::inOrder() const {
    // TODO:
    //   std::vector<LocationID> result;
    //   inOrderHelper(root_, result);
    //   return result;
    return {};
}

std::vector<LocationID> SortedIndex::findByPrefix(const std::string& prefix) const {
    // EXTENSION: optional extra credit.
    (void)prefix;
    return {};
}