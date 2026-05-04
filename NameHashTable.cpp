/*
* Author: Jack Meehan
* File: NameHashTable.cpp
* Due Date: 5/6/2026
* Date Created: 5/4/2026
* Date Last Modified: 5/4/2026
 */


#include "NameHashTable.h"
#include <vector>
#include <functional>
#include <stdexcept>
#include <cstddef>
#include <cmath>
#include <string>

using namespace std;



    //node constructor
    NameHashTable::Node::Node(const string& n, int i, Node* next):
    	name(n), id(i), next(next){}


    //Hash table constructor
    NameHashTable::NameHashTable(size_t initialSize, //DONE
                       double maxLoadFactor):
							   elementCount_(0), collisionCount_(0),
							   rehashCount_(0),
							   maxLoadFactor_(maxLoadFactor){
    	//initializes capacity and buckets_ in function
    	//cap is set to next prime value
    	capacity_ = nextPrime(initialSize);
    	buckets_ = new Node*[capacity_]();
    }

    //hash table destructor
    //clear() deletes the nodes and then the list is deleted
    NameHashTable::~NameHashTable(){ //DONE
    	clear();
    	delete[] buckets_;
    }

    //Inserts a new node with name and id unless it already exists
    //has collision checks too
    bool NameHashTable::insert(const string& name, const int& id) { //DONE
    	size_t index = bucketIndex(name);

    	//check through chain for existing name/id combo
    	for (Node* current = buckets_[index]; current != nullptr;
    			current = current->next) {
    		if(current->name == name) {
    			current->id = id;
    			return false;
    		}
    	}

    	//collision check and increment
    	if(buckets_[index] != nullptr) {
    		collisionCount_++;
    	}

    	//makes and prepends new node (increments element count)
    	buckets_[index] = new Node(name, id, buckets_[index]);
    	elementCount_++;

    	//checks load factor and rehashes if > 75%
    	if (loadFactor() > maxLoadFactor_) rehash();
    	return true;
    }

    //determines if a node with a given name exists
    bool NameHashTable::contains(const string& name) const { //DONE
    	return find(name) != -1;
    }

    //removes the node with the given name
    //reattaches the list afterwards
    bool NameHashTable::remove(const string& name) { //DONE

    	size_t index = bucketIndex(name);
		Node* previous = nullptr;

    	for (Node* current = buckets_[index]; current != nullptr;
    			current = current->next) {
    		if(current->name == name) {

    			if(previous == nullptr){
    				buckets_[index] = current->next;
    			}
    			else {
        			previous->next = current->next;
    			}
    			delete current;
    			elementCount_--;
    			return true;
    		}

    		previous = current;
    	}



    	return false;
    }

    //searches for a node with given name and returns its id
    int NameHashTable::find(const string& name) const{ //DONE
    	size_t index = bucketIndex(name);

    	for (Node* current = buckets_[index]; current != nullptr;
    			current = current->next) {
    		if(current->name == name) {
    			return current->id;
    		}
    	}
    	return -1;
    }

    //rehashes the table and deletes the old lists
    void NameHashTable::rehash() { //DONE
    	Node** oldbuckets = buckets_;
    	size_t oldCapacity = capacity_;

    	capacity_ = nextPrime(oldCapacity * 2 + 1);
    	buckets_ = new Node*[capacity_]();
    	elementCount_ = 0;
    	rehashCount_++;


    	for (size_t i = 0; i < oldCapacity; i++) {

    		Node* current = oldbuckets[i];
    		while (current != nullptr) {
    			Node* next = current->next;

    			insert(current->name, current->id);
    			delete current;

    			current = next;
    		}
    	}

    	delete[] oldbuckets;


    }

    //returns how many elements are in the table
    size_t NameHashTable::size() const { //DONE
    	return elementCount_;
    }

    //returns the max capacity of the table
    size_t NameHashTable::tableSize() const { //DONE
    	return capacity_;
    }

    //calculates the current load factor of the table
    double NameHashTable::loadFactor() const { //DONE
    	return static_cast<double>(elementCount_) / capacity_;
    }

    //returns the total number of collisions
    size_t NameHashTable::collisionCount() const { //DONE
    	return collisionCount_;
    }

    //returns the number of rehashes completed
    size_t NameHashTable::rehashCount() const { //DONE
    	return rehashCount_;
    }

    //returns a string of the names of the nodes in the table
    vector<string> NameHashTable::strings() const { //DONE

    	vector<string> result;
    	for (size_t i = 0; i < capacity_; i++) {
    		Node* current = buckets_[i];
    		while (current != nullptr){

    			result.push_back(current->name);
    			current = current->next;
    		}
    	}
    	return result;
    }

    //clears he data of each node and deletes them
    void NameHashTable::clear() { //DONE
    	//walks down the list and clears all nodes and leaves null head
    	for (size_t i = 0; i < capacity_; i++){
    		Node* current = buckets_[i];
    		while (current != nullptr) {
    			Node* next = current->next;
    			delete current;
    			current = next;
    		}


    		buckets_[i] = nullptr;
    	}
    }




    //returns the bucket that this particular name goes in
    size_t NameHashTable::bucketIndex(const string& name) const { //DONE
    	return std::hash<string>()(name) % capacity_;
    }

    //determines if a number is prime (for rehashing)
    bool NameHashTable::isPrime(size_t n) { //DONE
    	if (n < 2){
    		return false;
    	}
    	else if(n == 2) {
    		return true;
    	}
    	else if (n % 2 == 0){
    		return false;
    	}
    	for (size_t i = 3; i * i <= n; i += 2){
    		if (n % i == 0){
    		    return false;
    		}
    	}
    	return true;
    }

    //finds the next prime number for rehashing
    size_t NameHashTable::nextPrime(size_t n) { //DONE
    	while (isPrime(n) == false){
    		n++;
    	}
    	return n;
    }





