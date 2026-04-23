#ifndef NAME_HASH_TABLE_H
#define NAME_HASH_TABLE_H

// ============================================================================
// NameHashTable.h - Custom hash table mapping location name -> LocationID
// OWNER: Student 2
// ----------------------------------------------------------------------------
// Implementation requirements:
//   - Separate chaining for collisions (satisfies the "custom linked list"
//     requirement for the whole project - don't skip it)
//   - Rehash when load factor exceeds ~0.75
//   - DO NOT use std::unordered_map - we have to write our own
//
// This table does NOT own Location data - it stores a LocationID that
// points back into the Graph.
// ============================================================================

#include "Location.h"
#include <string>

class NameHashTable {
public:
    NameHashTable();
    ~NameHashTable();

    // Inserts a (name -> id) mapping. If the name already exists,
    // overwrite its id.
    // TODO: hash the name, walk the chain, insert or update.
    //       If load factor > threshold after insert, call rehash().
    void insert(const std::string& name, LocationID id);

    // Removes the mapping for 'name'. Returns true if something was removed.
    // TODO: hash, walk the chain, unlink the node, delete it.
    bool remove(const std::string& name);

    // Returns the LocationID for 'name', or INVALID_ID if not present.
    // TODO: hash, walk the chain, return the stored id or INVALID_ID.
    LocationID find(const std::string& name) const;

    // Removes everything.
    void clear();

    // Number of stored (name -> id) mappings.
    size_t size() const;

private:
    // TODO: Define a private Node struct for the chain:
    //   struct Node {
    //       std::string name;
    //       LocationID  id;
    //       Node*       next;
    //   };

    // TODO: Pick your bucket storage.
    //   Simplest: Node** buckets_;  (array of Node* of length capacity_)
    //   Or:       std::vector<Node*> buckets_;

    // TODO: Also track:
    //   size_t capacity_;   // number of buckets (start at something like 16)
    //   size_t size_;       // number of stored entries

    // Hash a string to a bucket index in [0, capacity_).
    // TODO: implement a simple string hash (e.g., polynomial rolling hash,
    //       or std::hash<std::string> mod capacity - your call).
    size_t hash(const std::string& key) const;

    // Doubles capacity and redistributes all entries.
    // TODO: allocate new bucket array, walk the old one, rehash each node
    //       into the new array, delete the old array.
    void rehash();
};

#endif // NAME_HASH_TABLE_H