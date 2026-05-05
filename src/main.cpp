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

//Ascii art logo print func
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

//Read line of string from user helper func
static std::string readLine(const std::string& prompt){
    std::cout << prompt;
    std::string line;
    std::getline(std::cin, line);
    return line;
}

//Read double (for dist...) return false on bad parse
static bool readDouble(){

}

//----
//Main
//----
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
            case 0: //quit case
                std::cout << "Goodbye!\n";
                return 0;
<<<<<<< HEAD
            case 1: { //list all places case
                auto ids = campus.listAll();
                if(ids.empty()){
                    std::cout << "No locations loaded.\n";
                    break;
                }
                std::cout << "\nAll locations (" << ids.size() << "):\n";
                for (LocationID id : ids){
                    const Location* loc = campus.getLocation(id);
                    if(loc) printLocation(*loc);
=======
            case 1: {
                std::vector<LocationID> ids = campus.listAll();

                if (ids.empty()) {
                    std::cout << "No locations found.\n";
                } else {
                    for (LocationID id : ids) {
                        const Location* loc = campus.getLocation(id);
                        printLocation(loc);
                        std::cout << "\n";
                    }
>>>>>>> c19cec35f05b47657c31c872ac41a495c46b0db6
                }
                break;
            }
            case 2:
                std::string name;
                std::cout << "Enter location name: ";
                std::getline(std::cin, name);

                LocationID id = campus.findByName(name);
                if (id == INVALID_ID) {
                    std::cout << "Location not found.\n";
                } else {
                    const Location* loc = campus.getLocation(id);
                    printLocation(loc);
                }
                break;
            case 3:
                Category category = promptCategory();
                std::vector<LocationID> ids = campus.listByCategory(category);

                if (ids.empty()) {
                    std::cout << "No locations found in that category.\n";
                } else {
                    for (LocationID id : ids) {
                        const Location* loc = campus.getLocation(id);
                        printLocation(loc);
                        std::cout << "\n";
                    }
                }
                break;
            case 4:
                std::string fromName, toName;

                std::cout << "Enter starting location name: ";
                std::getline(std::cin, fromName);

                std::cout << "Enter destination location name: ";
                std::getline(std::cin, toName);

                std::vector<LocationID> path = campus.route(fromName, toName);

                if (path.empty()) {
                    std::cout << "No route found.\n";
                } else {
                    std::cout << "Route:\n";
                    for (size_t i = 0; i < path.size(); ++i) {
                        const Location* loc = campus.getLocation(path[i]);
                        if (loc != nullptr) {
                            std::cout << loc->name;
                            if (i + 1 < path.size()) {
                                std::cout << " -> ";
                            }
                        }
                    }
                    std::cout << "\n";
                }
                break;
            case 5:
                std::string name, description;

                std::cout << "Enter location name: ";
                std::getline(std::cin, name);

                Category category = promptCategory();

                std::cout << "Enter description: ";
                std::getline(std::cin, description);

                LocationID id = campus.addLocation(name, category, description);
                if (id == INVALID_ID) {
                    std::cout << "Failed to add location.\n";
                } else {
                    std::cout << "Location added with ID " << id << ".\n";
                }
                break;
            case 6:
                std::string name;
                std::cout << "Enter location name to remove: ";
                std::getline(std::cin, name);

                if (campus.removeLocation(name)) {
                    std::cout << "Location removed successfully.\n";
                } else {
                    std::cout << "Failed to remove location.\n";
                }
                break;
            case 7:
                std::string fromName, toName;
                double distance;

                std::cout << "Enter first location name: ";
                std::getline(std::cin, fromName);

                std::cout << "Enter second location name: ";
                std::getline(std::cin, toName);

                std::cout << "Enter distance: ";
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
            case 8:
                std::string fromName, toName;

                std::cout << "Enter first location name: ";
                std::getline(std::cin, fromName);

                std::cout << "Enter second location name: ";
                std::getline(std::cin, toName);

                if (campus.removeConnection(fromName, toName)) {
                    std::cout << "Connection removed successfully.\n";
                } else {
                    std::cout << "Failed to remove connection.\n";
                }
                break;
            case 9:
                std::string oldName, newName, newDescription;

                std::cout << "Enter current location name: ";
                std::getline(std::cin, oldName);

                std::cout << "Enter new location name: ";
                std::getline(std::cin, newName);

                Category newCategory = promptCategory();

                std::cout << "Enter new description: ";
                std::getline(std::cin, newDescription);

                if (campus.updateLocation(oldName, newName, newCategory, newDescription)) {
                    std::cout << "Location updated successfully.\n";
                } else {
                    std::cout << "Failed to update location.\n";
                }
                break;
            default:
                std::cout << "Unknown choice.\n";
        }
    }
}
