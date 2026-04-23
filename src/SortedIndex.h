#ifndef SORTED_INDEX_H
#define SORTED_INDEX_H

// ============================================================================
// SortedIndex.h - Tree-based sorted index of locations by name
// OWNER: Student 3
// ----------------------------------------------------------------------------
// A binary search tree keyed by location name, storing LocationIDs.
// Used for the "display all locations in alphabetical order" feature.
//
// Baseline: plain BST is fine. If you have time, upgrade to AVL for
// guaranteed O(log n) operations (this is worth points in the report).
//
// This index does NOT own Location data - it stores a LocationID that
// points back into the Graph.
// ============================================================================

#include "Location.h"
#include <string>
#include <vector>

class SortedIndex {
public:
    SortedIndex();
    ~SortedIndex();

    // Inserts (name -> id). If name already exists, overwrite its id.
    // TODO: standard BST insert. If doing AVL, rebalance on the way up.
    void insert(const std::string& name, LocationID id);

    // Removes the node with the given name. Returns true on success.
    // TODO: BST delete. Three cases: leaf, one child, two children
    //       (replace with in-order successor for the two-child case).
    bool remove(const std::string& name);

    // Returns all LocationIDs in alphabetical order by name.
    // TODO: in-order traversal (recursive is fine), push IDs into the vector.
    std::vector<LocationID> inOrder() const;

    // EXTENSION: returns all LocationIDs whose names start with the given prefix.
    // TODO: walk the tree, collecting anything in the matching subtree range.
    std::vector<LocationID> findByPrefix(const std::string& prefix) const;

private:
    // TODO: Define a private Node struct:
    //   struct Node {
    //       std::string name;
    //       LocationID  id;
    //       Node*       left;
    //       Node*       right;
    //       int         height;   // only needed for AVL
    //   };

    // TODO: Node* root_ = nullptr;

    // Recursive helpers. Using helpers keeps the public API clean and
    // makes it easy to pass/return subtree roots.
    // TODO: implement these.
    //   Node* insertHelper(Node* node, const std::string& name, LocationID id);
    //   Node* removeHelper(Node* node, const std::string& name, bool& removed);
    //   void  inOrderHelper(Node* node, std::vector<LocationID>& out) const;
    //   void  destroy(Node* node);  // post-order delete, called by destructor
};

#endif // SORTED_INDEX_H