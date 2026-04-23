#ifndef LOCATION_H
#define LOCATION_H

// ============================================================================
// Location.h - Shared types used by EVERY module
// ----------------------------------------------------------------------------
// This file is the foundation everyone else builds on.
// DO NOT CHANGE this file without telling the whole team.
// Lock this in during Week 1.
// ============================================================================

#include <string>

// LocationID uniquely identifies a location in the Graph.
// A value of -1 means "not found" / "invalid".
using LocationID = int;
const LocationID INVALID_ID = -1;

// Category of a campus location.
// If you add a new category here, also update categoryToString() and
// stringToCategory() in Location.cpp (or wherever you implement them).
enum class Category {
    Academic,
    Residence,
    Dining,
    Parking,
    Recreation,
    Other
};

// A location on campus. Plain data struct on purpose - no methods,
// no constructors, no inheritance. Keep it simple.
struct Location {
    LocationID id;
    std::string name;
    Category category;
    std::string description;
};

// Free functions for converting Category to/from string.
// Used by FileIO when reading/writing files, and by the UI when
// displaying categories to the user.
//
// TODO (whoever implements this - probably FileIO or shared):
//   - categoryToString(Category::Dining) should return "Dining"
//   - stringToCategory("Dining") should return Category::Dining
//   - stringToCategory should be case-insensitive if possible
//   - Unknown strings should return Category::Other
std::string categoryToString(Category c);
Category stringToCategory(const std::string& s);

#endif // LOCATION_H