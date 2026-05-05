// ============================================================================
// FileIO.cpp - Implementation of file loading and saving
// OWNER: Tomi Babayemi
// ============================================================================

#include "FileIO.h"
#include "Graph.h"
#include "NameHashTable.h"
#include "SortedIndex.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

namespace FileIO {

static std::vector<std::string> split(const std::string& line, char delim) {
    std::vector<std::string> out;
    std::stringstream ss(line);
    std::string field;

    while (std::getline(ss, field, delim)) {
        out.push_back(field);
    }

    return out;
}

bool loadCampus(const std::string& locationsFile,
                const std::string& edgesFile,
                Graph& graph,
                NameHashTable& hashTable,
                SortedIndex& sortedIndex) {
    std::ifstream locIn(locationsFile);
    if (!locIn) {
        std::cerr << "Error: could not open locations file: " << locationsFile << "\n";
        return false;
    }

    std::string line;
    int lineNumber = 0;

    while (std::getline(locIn, line)) {
        ++lineNumber;

        if (line.empty() || line[0] == '#') {
            continue;
        }

        if (line == "id|name|category|description") {
            continue;
        }

        std::vector<std::string> fields = split(line, '|');
        if (fields.size() != 4) {
            std::cerr << "Error: malformed locations line " << lineNumber << "\n";
            return false;
        }

        const std::string& name = fields[1];
        Category category = stringToCategory(fields[2]);
        const std::string& description = fields[3];

        LocationID id = graph.addLocation(name, category, description);
        if (id == INVALID_ID) {
            std::cerr << "Error: failed to add location on line " << lineNumber << "\n";
            return false;
        }

        hashTable.insert(name, id);
        sortedIndex.insert(name, id);
    }

    std::ifstream edgeIn(edgesFile);
    if (!edgeIn) {
        std::cerr << "Error: could not open edges file: " << edgesFile << "\n";
        return false;
    }

    lineNumber = 0;

    while (std::getline(edgeIn, line)) {
        ++lineNumber;

        if (line.empty() || line[0] == '#') {
            continue;
        }

        if (line == "from_id|to_id|distance") {
            continue;
        }

        std::vector<std::string> fields = split(line, '|');
        if (fields.size() != 3) {
            std::cerr << "Error: malformed edges line " << lineNumber << "\n";
            return false;
        }

        LocationID from = std::stoi(fields[0]);
        LocationID to = std::stoi(fields[1]);
        double distance = std::stod(fields[2]);

        if (!graph.addEdge(from, to, distance)) {
            std::cerr << "Error: invalid edge on line " << lineNumber << "\n";
            return false;
        }
    }

    return true;
}

bool saveCampus(const std::string& locationsFile,
                const std::string& edgesFile,
                const Graph& graph) {
    std::ofstream locOut(locationsFile);
    if (!locOut) {
        std::cerr << "Error: could not open locations output file: " << locationsFile << "\n";
        return false;
    }

    std::vector<LocationID> ids = graph.getAllIDs();

    for (LocationID id : ids) {
        const Location* loc = graph.getLocation(id);
        if (loc == nullptr) {
            continue;
        }

        locOut << loc->id << '|'
               << loc->name << '|'
               << categoryToString(loc->category) << '|'
               << loc->description << '\n';
    }

    std::ofstream edgeOut(edgesFile);
    if (!edgeOut) {
        std::cerr << "Error: could not open edges output file: " << edgesFile << "\n";
        return false;
    }

    for (LocationID id : ids) {
        std::vector<std::pair<LocationID, double>> neighbors = graph.getNeighbors(id);
        for (const auto& neighbor : neighbors) {
            if (id < neighbor.first) {
                edgeOut << id << '|'
                        << neighbor.first << '|'
                        << neighbor.second << '\n';
            }
        }
    }

    return true;
}

} // namespace FileIO
