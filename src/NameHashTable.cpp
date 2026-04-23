// ============================================================================
// NameHashTable.cpp - Implementation of custom hash table
// OWNER: Student 2
// ============================================================================

#include "NameHashTable.h"

NameHashTable::NameHashTable() {
    // TODO: allocate initial bucket array, initialize capacity_ and size_.
}

NameHashTable::~NameHashTable() {
    // TODO: walk every bucket, delete every Node in every chain,
    //       then free the bucket array.
}

void NameHashTable::insert(const std::string& name, LocationID id) {
    // TODO: see header TODO.
    (void)name; (void)id;
}

bool NameHashTable::remove(const std::string& name) {
    // TODO: see header TODO.
    (void)name;
    return false;
}

LocationID NameHashTable::find(const std::string& name) const {
    // TODO: see header TODO.
    (void)name;
    return INVALID_ID;
}

void NameHashTable::clear() {
    // TODO: delete all nodes, zero out buckets, reset size_ to 0.
}

size_t NameHashTable::size() const {
    // TODO: return size_
    return 0;
}

size_t NameHashTable::hash(const std::string& key) const {
    // TODO: see header TODO.
    (void)key;
    return 0;
}

void NameHashTable::rehash() {
    // TODO: see header TODO.
}