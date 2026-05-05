// ============================================================================
// main.cpp - Entry point and menu loop
// OWNER: Jody Spikes
// ============================================================================

#include "Campus.h"
#include "Location.h"

#include <iostream>
#include <string>
#include <limits>

// Prints the menu options from the project spec.
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

//Print Location helper function for casees 1,2,3,4 - ensures similar output
static void printLocation(const Location& loc){
    std::cout << " [" << loc.id << "] " << loc.name << "\n"
              << "      Category: " << categoryToString(loc.category) << "\n"
              << "      " << loc.description << "\n";
}


int main() {
    printLogo();

    Campus campus;

    // Try to load the default dataset. Non-fatal if missing - user can still
    // add locations manually through the menu.
    if (!campus.load("data/locations.txt", "data/edges.txt")) {
        std::cout << "(No dataset loaded - starting empty.)\n";
    }

    // TODO: flesh out each menu branch.
    // The skeleton below handles input parsing and gives you a place to wire
    // each option up to the corresponding Campus method.
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
                if(ids.empty()){
                    std::cout << "No locations loaded.\n";
                    break;
                }
                std::cout << "All locations (" << ids.size() << "):\n";
                for (LocationID id : ids){
                    const Location* loc = campus.getLocation(id);
                    if(loc) printLocation(*loc);
                }
                break;
            }
            case 2:
                // TODO: prompt for name, call campus.findByName(), print result.
                std::cout << "[TODO] Search by name\n";
                break;
            case 3:
                // TODO: prompt for category, call campus.listByCategory().
                std::cout << "[TODO] Display by category\n";
                break;
            case 4:
                // TODO: prompt for two names, call campus.route(), print path.
                std::cout << "[TODO] Find route\n";
                break;
            case 5:
                // TODO: prompt for name, category, description; call addLocation.
                std::cout << "[TODO] Add location\n";
                break;
            case 6:
                // TODO: prompt for name, call removeLocation.
                std::cout << "[TODO] Remove location\n";
                break;
            case 7:
                // TODO: prompt for two names + distance, call addConnection.
                std::cout << "[TODO] Add connection\n";
                break;
            case 8:
                // TODO: prompt for two names, call removeConnection.
                std::cout << "[TODO] Remove connection\n";
                break;
            case 9:
                // TODO: prompt for old name + new fields, call updateLocation.
                std::cout << "[TODO] Update location\n";
                break;
            default:
                std::cout << "Unknown choice.\n";
        }
    }
}