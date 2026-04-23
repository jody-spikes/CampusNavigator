// ============================================================================
// FileIO.cpp - Implementation of file loading and saving
// OWNER: Student 4
// ============================================================================

#include "FileIO.h"
#include "Graph.h"
#include "NameHashTable.h"
#include "SortedIndex.h"

#include <fstream>
#include <sstream>
#include <vector>

namespace FileIO {

// Helper: split a string by delimiter.
// TODO: this is the main parsing workhorse. Example:
//   split("0|Thompson Hall|Academic|Main CS building", '|')
//   -> ["0", "Thompson Hall", "Academic", "Main CS building"]
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
    // TODO:
    //   std::ifstream locIn(locationsFile);
    //   if (!locIn) return false;
    //   std::string line;
    //   while (std::getline(locIn, line)) {
    //       if (line.empty() || line[0] == '#') continue;  // skip blanks/comments
    //       auto fields = split(line, '|');
    //       if (fields.size() != 4) continue;  // or report error
    //       // parse id (unused - graph assigns its own), name, category, desc
    //       LocationID id = graph.addLocation(name, stringToCategory(cat), desc);
    //       hashTable.insert(name, id);
    //       sortedIndex.insert(name, id);
    //   }
    //
    //   Then same pattern for edges, calling graph.addEdge(from, to, dist).
    (void)locationsFile; (void)edgesFile;
    (void)graph; (void)hashTable; (void)sortedIndex;
    return false;
}

bool saveCampus(const std::string& locationsFile,
                const std::string& edgesFile,
                const Graph& graph) {
    // TODO:
    //   std::ofstream locOut(locationsFile);
    //   if (!locOut) return false;
    //   for each id in graph.getAllIDs():
    //       write "id|name|category|description\n"
    //
    //   Edges: be careful not to write each undirected edge twice.
    //   Easy trick: only write edge (a, b) when a < b.
    (void)locationsFile; (void)edgesFile; (void)graph;
    return false;
}

} // namespace FileIO