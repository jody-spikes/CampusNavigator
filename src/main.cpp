// ============================================================================
// main.cpp - Entry point and menu loop
// OWNER: Jody Spikes
// ============================================================================

#include "Campus.h"
#include "Location.h"

#include <iostream>
#include <string>
#include <vector>
#include <limits>

// ----------------------------------------------------------------------------
// Helpers
// ----------------------------------------------------------------------------

static void printMenu() {
    std::cout << "\n=== Select an option ===\n"
              << " 1. Display all locations\n"
              << " 2. Search for a location by name\n"
              << " 3. Display locations by category\n"
              << " 4. Find route between two locations\n"
              << " 5. Add a location\n"
              << " 6. Remove a location\n"
              << " 7. Add a connection\n"
              << " 8. Remove a connection\n"
              << " 9. Update a location\n"
              << " 0. Quit\n"
              << "Choice: ";
}

static void printLogo(){
    std::cout << R"(
   _____                                  _   _             _             _
  / ____|                                | \ | |           (_)           | |
 | |     __ _ _ __ ___  _ __  _   _ ___  |  \| | __ ___   ___  __ _  __ _| |_ ___  _ __
 | |    / _` | '_ ` _ \| '_ \| | | / __| | . ` |/ _` \ \ / / |/ _` |/ _` | __/ _ \| '__|
 | |___| (_| | | | | | | |_) | |_| \__ \ | |\  | (_| |\ V /| | (_| | (_| | || (_) | |
  \_____\__,_|_| |_| |_| .__/ \__,_|___/ |_| \_|\__,_| \_/ |_|\__, |\__,_|\__\___/|_|
                       | |                                     __/ |
                       |_|                                    |___/

    )";
}

static void printLocation(const Location& loc){
    std::cout << " [" << loc.id << "] " << loc.name << "\n"
              << "      Category: " << categoryToString(loc.category) << "\n"
              << "      " << loc.description << "\n";
}

static std::string readLine(const std::string& prompt){
    std::cout << prompt;
    std::string line;
    std::getline(std::cin, line);
    return line;
}

static Category promptCategory() {
    std::string input = readLine(
        "Enter category (Academic, Residence, Dining, Parking, Recreation, Other): ");
    return stringToCategory(input);
}

// ----------------------------------------------------------------------------
// Main
// ----------------------------------------------------------------------------
int main() {
    printLogo();

    Campus campus;

    if (!campus.load("data/locations.txt", "data/edges.txt")) {
        std::cout << "(No dataset loaded - starting empty.)\n";
    }

    while (true) {
        printMenu();
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 0:
                std::cout << "Goodbye!\n";
                return 0;

            case 1: {
                auto ids = campus.listAll();
                if (ids.empty()) {
                    std::cout << "No locations loaded.\n";
                    break;
                }
                std::cout << "\nAll locations (" << ids.size() << "):\n";
                for (LocationID id : ids){
                    const Location* loc = campus.getLocation(id);
                    if (loc) printLocation(*loc);
                }
                break;
            }

            case 2: {
                std::string name = readLine("Enter location name: ");
                LocationID id = campus.findByName(name);
                if (id == INVALID_ID) {
                    std::cout << "Location not found.\n";
                } else {
                    const Location* loc = campus.getLocation(id);
                    if (loc) printLocation(*loc);
                }
                break;
            }

            case 3: {
                Category category = promptCategory();
                std::vector<LocationID> ids = campus.listByCategory(category);
                if (ids.empty()) {
                    std::cout << "No locations found in that category.\n";
                } else {
                    for (LocationID id : ids) {
                        const Location* loc = campus.getLocation(id);
                        if (loc) printLocation(*loc);
                    }
                }
                break;
            }

            case 4: {
                std::string fromName = readLine("Enter starting location name: ");
                std::string toName   = readLine("Enter destination location name: ");
                std::vector<LocationID> path = campus.route(fromName, toName);
                if (path.empty()) {
                    std::cout << "No route found.\n";
                } else {
                    std::cout << "Route:\n";
                    for (size_t i = 0; i < path.size(); ++i) {
                        const Location* loc = campus.getLocation(path[i]);
                        if (!loc) continue;
                        std::cout << loc->name;
                        if (i + 1 < path.size()) std::cout << " -> ";
                    }
                    std::cout << "\n";
                }
                break;
            }

            case 5: {
                std::string name        = readLine("Enter location name: ");
                Category    category    = promptCategory();
                std::string description = readLine("Enter description: ");
                LocationID id = campus.addLocation(name, category, description);
                if (id == INVALID_ID) {
                    std::cout << "Failed to add location.\n";
                } else {
                    std::cout << "Location added with ID " << id << ".\n";
                }
                break;
            }

            case 6: {
                std::string name = readLine("Enter location name to remove: ");
                if (campus.removeLocation(name)) {
                    std::cout << "Location removed successfully.\n";
                } else {
                    std::cout << "Failed to remove location.\n";
                }
                break;
            }

            case 7: {
                std::string fromName = readLine("Enter first location name: ");
                std::string toName   = readLine("Enter second location name: ");
                std::cout << "Enter distance: ";
                double distance;
                if (!(std::cin >> distance)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid distance.\n";
                    break;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (campus.addConnection(fromName, toName, distance)) {
                    std::cout << "Connection added successfully.\n";
                } else {
                    std::cout << "Failed to add connection.\n";
                }
                break;
            }

            case 8: {
                std::string fromName = readLine("Enter first location name: ");
                std::string toName   = readLine("Enter second location name: ");
                if (campus.removeConnection(fromName, toName)) {
                    std::cout << "Connection removed successfully.\n";
                } else {
                    std::cout << "Failed to remove connection.\n";
                }
                break;
            }

            case 9: {
                std::string oldName        = readLine("Enter current location name: ");
                std::string newName        = readLine("Enter new location name: ");
                Category    newCategory    = promptCategory();
                std::string newDescription = readLine("Enter new description: ");
                if (campus.updateLocation(oldName, newName, newCategory, newDescription)) {
                    std::cout << "Location updated successfully.\n";
                } else {
                    std::cout << "Failed to update location.\n";
                }
                break;
            }

            default:
                std::cout << "Unknown choice.\n";
        }
    }
}