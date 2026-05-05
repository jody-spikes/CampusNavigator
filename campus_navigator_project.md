# CSI 3334 Spring 2026 Group Project

## Project Title
**Campus Navigator: A Data-Structure-Driven Route and Resource Finder**

---

## Project Overview
Students will design and implement a console-based campus navigation and resource management system in C++. The program will model a simplified university campus as a graph and allow users to search locations, manage points of interest, and compute routes between buildings.

The project emphasizes the practical application of core data structures rather than user-interface design. The final product should demonstrate sound software engineering, appropriate abstraction, and meaningful use of multiple data structures.

---

## Educational Purpose
This project allows students to apply the major ideas from CSI 3334 in a single coherent system. In particular, it reinforces:

- class design and modular programming  
- linked structures and dynamic memory  
- hash tables for efficient lookup  
- trees or ordered structures for sorted access  
- graphs for campus connectivity  
- queues or priority queues for traversal and pathfinding  
- algorithm analysis and testing  

---

## Core Functional Requirements

### 1. Campus Map Representation
Represent the campus as a graph in which:
- each vertex is a campus location  
- each edge is a walkable path between locations  
- edges store a distance or travel cost  

Each location should include:
- building name  
- category (academic, residence, dining, parking, recreation, etc.)  
- short description  

### 2. Location Lookup
The program must allow users to search for locations by name efficiently using a custom hash table implemented by the students.

### 3. Sorted Listing of Locations
The program must allow all locations to be displayed in sorted order by name using either:
- a binary search tree / AVL tree, or  
- another instructor-approved ordered structure  

### 4. Route Computation
The system must compute a route between two campus locations. At minimum:
- breadth-first search for minimum-hop paths  

Optional:
- Dijkstra’s algorithm for shortest weighted distance  

### 5. Category-Based Queries
Users must be able to list all locations belonging to a category.

### 6. Add / Remove / Update Locations
Support:
- adding a new location  
- removing a location  
- updating location information  
- adding or removing connections  

### 7. File Input / Output
The system must read an initial campus dataset from files and optionally save updates.

Minimum:
- one file for locations  
- one file for edges  

---

## Required Data Structures
- Graph for campus structure  
- Custom hash table for name lookup  
- Custom linked list or dynamic structure  
- Queue for BFS  
- Tree-based structure for sorted listing  

Allowed:
- string  
- fstream  
- sstream  
- vector (limited use)  

Not allowed as replacements:
- unordered_map  
- map  
- queue (if implementing your own)  

---

## Suggested Scope Constraints
- console-based interface only  
- 20–40 locations  
- no GUI  
- no real map rendering  
- no database  
- no networking  
- no authentication  

---

## Team Structure (5 Students)
- **Student 1:** Graph and Route Engine  
- **Student 2:** Hash Table and Lookup  
- **Student 3:** Tree-Based Sorted Index  
- **Student 4:** File Management and Data Integration  
- **Student 5:** Interface, Testing, and Integration  

---

## Five-Week Schedule

### Week 1: Design and Planning
- project proposal  
- class diagram  
- file format specification  
- team roles  

### Week 2: Core Data Structures
- graph implementation  
- hash table implementation  
- tree implementation  

### Week 3: Functional Integration
- file input working  
- graph populated  
- lookup integrated  
- route search working  

### Week 4: Features and Testing
- add/remove/update  
- category filtering  
- error handling  

### Week 5: Finalization
- final program  
- report  
- presentation  

---

## Required Deliverables

### 1. Source Code
Well-organized modular C++ code.

### 2. Design Report
Include:
- project overview  
- data structure explanations  
- complexity analysis  
- challenges  
- team contributions  

### 3. Test Plan
- input data  
- normal cases  
- edge cases  
- error cases  

### 4. Demo
Show:
- location lookup  
- sorted display  
- route computation  
- modification operations  

### 5. Peer Evaluation
Confidential team assessment.

---

## Grading

| Category | Weight |
|--------|--------|
| Data Structures | 30% |
| Functionality | 25% |
| Code Quality | 15% |
| Testing | 10% |
| Report | 10% |
| Demo | 5% |
| Peer Evaluation | 5% |

---

## Recommended Menu Options
- Display all locations  
- Search by name  
- Display by category  
- Find route  
- Add/remove/update location  
- Add/remove connection  
- Quit  

---

## Extension Options (Optional)
- Dijkstra’s algorithm  
- Autocomplete search  
- Nearest resource queries  
- Accessibility-aware routing  
- Graph statistics  
