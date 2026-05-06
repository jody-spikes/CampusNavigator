#ifndef SORTED_INDEX_H
#define SORTED_INDEX_H

// ----------------------------------------------------------------------------
// SortedIndex.h - Tree-based sorted index of locations by name
// OWNER: Hailey Pieper
// ----------------------------------------------------------------------------
// A binary search tree keyed by location name, storing LocationIDs.
// Used for the "display all locations in alphabetical order" feature.
// ----------------------------------------------------------------------------

#include "Location.h"
#include <string>
#include <vector>

using namespace std;

class SortedIndex {
public:
    SortedIndex();
    ~SortedIndex();

    // Inserts (name -> id). If name already exists, overwrite its id.
    void insert(const string& name, LocationID id);

    // Removes the node with the given name. Returns true on success.
    bool remove(const string& name);

    // Returns all LocationIDs in alphabetical order by name.
    vector<LocationID> inOrder() const;

    // Returns all LocationIDs whose names start with the given prefix.
    vector<LocationID> findByPrefix(const string& prefix) const;

private:
    struct Node {
        string name;
        LocationID id;
        Node* left;
        Node* right;

        Node(const string& n, LocationID i)
            : name(n), id(i), left(nullptr), right(nullptr) {}
    };

    Node* root_;

    Node* insertHelper(Node* node, const string& name, LocationID id);
    Node* removeHelper(Node* node, const string& name, bool& removed);
    void inOrderHelper(Node* node, vector<LocationID>& out) const;
    void prefixHelper(Node* node, const string& prefix,
                      vector<LocationID>& out) const;
    void destroy(Node* node);
};

#endif // SORTED_INDEX_H
