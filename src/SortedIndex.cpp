// ============================================================================
// SortedIndex.cpp - Implementation of the sorted tree index
// OWNER: Hailey Pieper
// ============================================================================

#include "SortedIndex.h"

SortedIndex::SortedIndex() : root_(nullptr) {}

SortedIndex::~SortedIndex() {
    destroy(root_);
}

void SortedIndex::insert(const string& name, LocationID id) {
    root_ = insertHelper(root_, name, id);
}

bool SortedIndex::remove(const string& name) {
    bool removed = false;
    root_ = removeHelper(root_, name, removed);
    return removed;
}

vector<LocationID> SortedIndex::inOrder() const {
    vector<LocationID> result;
    inOrderHelper(root_, result);
    return result;
}

SortedIndex::Node* SortedIndex::insertHelper(Node* node,
                                             const string& name,
                                             LocationID id) {
    if (node == nullptr) {
        return new Node(name, id);
    }

    if (name < node->name) {
        node->left = insertHelper(node->left, name, id);
    } else if (name > node->name) {
        node->right = insertHelper(node->right, name, id);
    } else {
        node->id = id;
    }

    return node;
}

SortedIndex::Node* SortedIndex::removeHelper(Node* node,
                                             const string& name,
                                             bool& removed) {
    if (node == nullptr) {
        return nullptr;
    }

    if (name < node->name) {
        node->left = removeHelper(node->left, name, removed);
        return node;
    }

    if (name > node->name) {
        node->right = removeHelper(node->right, name, removed);
        return node;
    }

    removed = true;

    if (node->left == nullptr && node->right == nullptr) {
        delete node;
        return nullptr;
    }

    if (node->left == nullptr) {
        Node* temp = node->right;
        delete node;
        return temp;
    }

    if (node->right == nullptr) {
        Node* temp = node->left;
        delete node;
        return temp;
    }

    Node* successor = node->right;
    while (successor->left != nullptr) {
        successor = successor->left;
    }

    node->name = successor->name;
    node->id = successor->id;

    bool dummyRemoved = false;
    node->right = removeHelper(node->right, successor->name, dummyRemoved);
    return node;
}

void SortedIndex::inOrderHelper(Node* node, vector<LocationID>& out) const {
    if (node == nullptr) {
        return;
    }

    inOrderHelper(node->left, out);
    out.push_back(node->id);
    inOrderHelper(node->right, out);
}

void SortedIndex::destroy(Node* node) {
    if (node == nullptr) {
        return;
    }

    destroy(node->left);
    destroy(node->right);
    delete node;
}
