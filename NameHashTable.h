/*
* Author: Jack Meehan
* File: NameHashTable.h
* Due Date: 5/6/2026
* Date Created: 5/4/2026
* Date Last Modified: 5/4/2026
 */

#ifndef NAMEHASHTABLE_H_
#define NAMEHASHTABLE_H_

#include <vector>
#include <string>

using namespace std;

class NameHashTable {
public:

    struct Node {
    	string name;
    	int id;
    	Node* next;

    	//node constructor
    	Node(const string& n, int i, Node* next = nullptr);
    };

    //Hash table constructor
    explicit NameHashTable(size_t initialSize = 101, double maxLoadFactor = 0.75);

    //hash table destructor
    ~NameHashTable();

    //Insert
    bool insert(const string& name, const int& id);

    //determines if a node with a given name exists
    bool contains(const string& name) const;

    //removes the node with the given name
    bool remove(const string& name);

    //searches for a node with given name and returns its id
    int find(const string& name) const;

    //rehashes the table and deletes the old lists
    void rehash();

    //returns how many elements are in the table
    size_t size() const;

    //returns the max capacity of the table
    size_t tableSize() const;

    //calculates the current load factor of the table
    double loadFactor() const;

    //returns the total number of collisions
    size_t collisionCount() const;

    //returns the number of rehashes completed
    size_t rehashCount() const;

    //returns a string of the names of the nodes in the table
    vector<string> strings() const;

    //clears he data of each node and deletes them
    void clear();


private:
    Node** buckets_;
    size_t elementCount_;
    size_t collisionCount_;
    size_t rehashCount_;
    double maxLoadFactor_;
    size_t capacity_;

    //returns the bucket that this particular name goes in
    size_t bucketIndex(const string& string) const;

    //determines if a number is prime (for rehashing)
    static bool isPrime(size_t n);

    //finds the next prime number for rehashing
    static size_t nextPrime(size_t n);
};



#endif /* NAMEHASHTABLE_H_ */
