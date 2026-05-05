// ============================================================================
// Location.cpp - Implementations for shared free functions
// ============================================================================

#include "Location.h"

#include <cctype>

std::string categoryToString(Category c) {
    switch (c) {
        case Category::Academic:
            return "Academic";
        case Category::Residence:
            return "Residence";
        case Category::Dining:
            return "Dining";
        case Category::Parking:
            return "Parking";
        case Category::Recreation:
            return "Recreation";
        case Category::Other:
            return "Other";
        default:
            return "Other";
    }
}

Category stringToCategory(const std::string& s) {
    std::string lower;

    for (char ch : s) {
        lower += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    }

    if (lower == "academic")   return Category::Academic;
    if (lower == "residence")  return Category::Residence;
    if (lower == "dining")     return Category::Dining;
    if (lower == "parking")    return Category::Parking;
    if (lower == "recreation") return Category::Recreation;
    return Category::Other;
}
