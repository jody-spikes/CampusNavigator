#ifndef FILE_IO_H
#define FILE_IO_H

// ============================================================================
// FileIO.h - Load and save the campus dataset
// OWNER: Student 4
// ----------------------------------------------------------------------------
// Pure functions, no class state. Loads data from two pipe-delimited files
// and populates all three data structures together.
//
// File formats (pipe-delimited, no spaces around '|'):
//
//   locations.txt
//     id|name|category|description
//     0|Thompson Hall|Academic|Main CS building
//     1|Founders Dining|Dining|Central dining hall
//     2|Lot 12|Parking|North campus parking
//
//   edges.txt  (treat as UNDIRECTED - add both directions)
//     from_id|to_id|distance
//     0|1|150.5
//     1|2|200.0
//
// Why pipes instead of commas? Names can contain commas ("Jones Hall, East Wing").
// Why not spaces? Names contain spaces. Pick a delimiter that won't appear in data.
// ============================================================================

#include "Location.h"
#include <string>

// Forward declarations (keeps the header lean).
class Graph;
class NameHashTable;
class SortedIndex;

namespace FileIO {

    // Reads both files and populates the three structures together.
    // Returns false if either file cannot be opened or is malformed.
    //
    // TODO:
    //   1. Open locations file, read line by line, skip comments/blanks.
    //   2. For each valid line, parse fields, add Location to graph,
    //      and mirror (name -> id) into hash table and tree.
    //   3. Then open edges file, parse, call graph.addEdge() for each.
    //   4. Report parse errors with line numbers if something goes wrong.
    bool loadCampus(const std::string& locationsFile,
                    const std::string& edgesFile,
                    Graph& graph,
                    NameHashTable& hashTable,
                    SortedIndex& sortedIndex);

    // Writes current graph state back to the two files.
    // Returns false if either file cannot be opened for writing.
    //
    // TODO: iterate over graph.getAllIDs(), write one line per location;
    //       then iterate over edges, writing each edge ONCE (not both directions).
    bool saveCampus(const std::string& locationsFile,
                    const std::string& edgesFile,
                    const Graph& graph);

} // namespace FileIO

#endif // FILE_IO_H