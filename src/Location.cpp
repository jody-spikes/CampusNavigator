// ============================================================================
// Location.cpp - Implementations for shared free functions
// ============================================================================

#include "Location.h"

std::string categoryToString(Category c) {
    // TODO: return a human-readable string for each Category value.
    // Example: Category::Academic -> "Academic"
    switch (c) {
        case Category::Academic:   return "Academic";
        case Category::Residence:  return "Residence";
        case Category::Dining:     return "Dining";
        case Category::Parking:    return "Parking";
        case Category::Recreation: return "Recreation";
        case Category::Other:      return "Other";
    }
    return "Other";
}

Category stringToCategory(const std::string& s) {
    // TODO: convert a string back to a Category.
    // Consider making this case-insensitive so "dining", "Dining",
    // and "DINING" all work.
    if (s == "Academic")   return Category::Academic;
    if (s == "Residence")  return Category::Residence;
    if (s == "Dining")     return Category::Dining;
    if (s == "Parking")    return Category::Parking;
    if (s == "Recreation") return Category::Recreation;
    return Category::Other;
}