//
//  FileIO.cpp
//  gp_project
//
//  Created by Tomi Babayemi on 5/1/26.
//

#include "FileIO.h"
#include "Graph.h"
#include "NameHashTable.h"
#include "SortedIndex.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;

namespace FileIO {

static vector<string> split(const string& line, char delim) {
    vector<string> out;
    string field;
    stringstream ss(line);

    while (getline(ss, field, delim)) {
        out.push_back(field);
    }

    return out;
}

bool loadCampus(const string& locationsFile,
                const string& edgesFile,
                Graph& graph,
                NameHashTable& hashTable,
                SortedIndex& sortedIndex) {
    ifstream locIn(locationsFile);
    if (!locIn) {
        cout << "Error: could not open locations file: " << locationsFile << endl;
        return false;
    }

    string line;
    int lineNumber = 0;

    while (getline(locIn, line)) {
        ++lineNumber;

        if (line.empty() || line[0] == '#') {
            continue;
        }

        vector<string> fields = split(line, '|');
        if (fields.size() != 4) {
            cerr << "Warning: malformed location line " << lineNumber << " in " << locationsFile << " (expected 4 fields)." << endl;
            continue;
        }

        const string& idStr       = fields[0];
        const string& name        = fields[1];
        const string& categoryStr = fields[2];
        const string& description = fields[3];

        (void)idStr; // graph will assign its own ID

        Category cat = stringToCategory(categoryStr);
        LocationID id = graph.addLocation(name, cat, description);

        if (id == INVALID_ID) {
            cerr << "Warning: graph.addLocation failed on line "
                 << lineNumber << " (name='" << name << "')." << endl;
            continue;
        }

        hashTable.insert(name, id);
        sortedIndex.insert(name, id);
    }

    locIn.close();

    ifstream edgeIn(edgesFile);
    if (!edgeIn) {
        cerr << "Error: could not open edges file: "
             << edgesFile << endl;
        return false;
    }

    lineNumber = 0;
    while (getline(edgeIn, line)) {
        ++lineNumber;

        if (line.empty() || line[0] == '#') {
            continue;
        }

        vector<string> fields = split(line, '|');
        if (fields.size() != 3) {
            cerr << "Warning: malformed edge line " << lineNumber << " in " << edgesFile << " (expected 3 fields)." << endl;
            continue;
        }

        try {
            LocationID from = static_cast<LocationID>(stoi(fields[0]));
            LocationID to   = static_cast<LocationID>(stoi(fields[1]));
            double distance = stod(fields[2]);

            if (!graph.addEdge(from, to, distance)) {
                cerr << "Warning: graph.addEdge failed on line " << lineNumber << " in " << edgesFile << " (from=" << from << ", to=" << to << ")." << endl;
            }
        } 
        catch (const exception& e) {
            cerr << "Warning: error parsing edge line " << lineNumber << " in " << edgesFile << ": " << e.what() << endl;
            continue;
        }
    }

    edgeIn.close();
    return true;
}

bool saveCampus(const string& locationsFile,
                const string& edgesFile,
                const Graph& graph) {
    ofstream locOut(locationsFile);
    if (!locOut) {
        cout << "Error: could not open locations file for writing: " << locationsFile << endl;
        return false;
    }

    vector<LocationID> ids = graph.getAllIDs();
    for (LocationID id : ids) {
        const Location* loc = graph.getLocation(id);
        if (loc == nullptr) {
            continue;
        }

        locOut << loc->id << '|' << loc->name << '|' << categoryToString(loc->category) << '|' << loc->description << '\n';
    }

    locOut.close();

    ofstream edgeOut(edgesFile);
    if (!edgeOut) {
        cout << "Error: could not open edges file for writing: " << edgesFile << endl;
        return false;
    }

    for (LocationID from : ids) {
        const Location* loc = graph.getLocation(from);
        if (loc == nullptr) {
            continue;
        }

        auto neighbors = graph.getNeighbors(from);
        for (const auto& nb : neighbors) {
            LocationID to   = nb.first;
            double distance = nb.second;

            if (from < to) {
                edgeOut << from << '|'
                        << to << '|'
                        << distance << '\n';
            }
        }
    }

    edgeOut.close();
    return true;
}

}
