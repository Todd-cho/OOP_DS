#include "Manager.h"
#include <sstream>
#include <iostream>
#include <string>
#include "BpTree.h"
#include <vector>
#include <stack>
#include <queue>

using namespace std;

// Initialize member variables
Manager::Manager(int bpOrder) {
    avl = new AVLTree;
    bp = new BpTree(&flog, bpOrder);
    data = nullptr;
}

// Free allocated memory
Manager::~Manager() {
    Print_vector.clear();
    delete data;
    if (bp) {
        delete bp;
        bp = nullptr;
    }
    if (avl) {
        delete avl;
        avl = nullptr;
    }
}

void Manager::run(const char* command_txt) {
    fcmd.open(command_txt, ios::in);
    flog.open("log.txt", ios::app); // Open log.txt for appending
    if (!fcmd) {
        printErrorCode(100);
        return;
    }
    string line;
    while (getline(fcmd, line)) {  // Read file line by line
        if (!line.empty() && line[line.length() - 1] == '\r')
            line.erase(line.length() - 1);

        if (line.empty()) continue;

        vector<string> split; // Vector to store parsed commands
        stringstream sstr(line);  // Create stream from line
        string token;

        // Split by tab
        while (getline(sstr, token, '\t')) {
            if (!token.empty()) {  // ignore empty token
                split.push_back(token);
            }
        }
        // Skip if no command
        if (split.empty()) continue;

        // Process command
        string command = split[0];

        // LOAD command
        if (command == "LOAD") {
            if (split.size() != 1) printErrorCode(100); // Error if wrong number of arguments
            if (LOAD()) PrintSuccess("LOAD");
        }
        else if (command == "PRINT_BP") {
            if (bp->getRoot() == nullptr) printErrorCode(700); // Error if BP tree is empty
            bp->Print();
        }
        // ADD command
        else if (command == "ADD") {
            if (split.size() != 5) { // Error if wrong number of arguments
                printErrorCode(300);
            }

            if (ADD(split[1], split[2], split[3], split[4])) {
                BpTreeDataNode* Node = bp->findDataNode(split[2]);  // Search by FlightNumber
                auto iter = Node->getDataMap(); // Get map data using iterator
                auto dataiter = iter->find(split[2]);
                FlightData* fdata = dataiter->second;
                if (dataiter != iter->end()) {
                    fdata = dataiter->second;
                }
                if (Node) {
                    // Log the ADD operation
                    flog << "========== ADD ==========" << endl;
                    flog << fdata->GetFlightNumber() << " | " << fdata->GetAirlineName()
                        << " | " << fdata->GetDestination() << " | " << fdata->GetNumberofSeats()
                        << " | " << fdata->GetStatus() << endl;
                    flog << "========================" << endl << endl;
                }
                else {
                    printErrorCode(300);
                }
            }
        }
        // SEARCH_BP command
        else if (command == "SEARCH_BP") {
            if (bp->getRoot() == nullptr) {
                printErrorCode(400); // Error if BP tree is empty
            }
            if (split.size() == 2) { // Single key search
                SEARCH_BP(split[1]);
            }
            else if (split.size() == 3) { // Range search
                SEARCH_BP(split[1], split[2]);
            }
            else {
                printErrorCode(400); // Error if BP tree is empty
            }
        }
        // VLOAD command
        else if (command == "VLOAD") {
            if (!Print_vector.empty()) { // Clear if Print_vector already exists
                Print_vector.clear();
            }
            bool check = VLOAD();
            if (avl->getRoot() == nullptr) printErrorCode(200); // Error if AVL tree is empty
            if (check) PrintSuccess("VOLAD");
        }
        // SEARCH_AVL command
        else if (command == "SEARCH_AVL") {
            if (split.size() != 2) printErrorCode(500); // Error if wrong number of arguments
            if (avl == nullptr) printErrorCode(500); // Error if AVL tree doesn't exist
            if (!SEARCH_AVL(split[1])) printErrorCode(500);
        }
        // VPRINT command
        else if (command == "VPRINT") {
            if (split.size() != 2) printErrorCode(600);
            if (split[1] == "A") VPRINT();
            else if (split[1] == "B") VPRINTB();
            else printErrorCode(600);
        }
        // EXIT command
        else if (command == "EXIT") {
            PrintSuccess("EXIT");
            break;
        }
        else printErrorCode(800);
    }

    fcmd.close();
    flog.close();
}

bool Manager::LOAD() {
    if (bp->getRoot() != nullptr) { //Error if BP tree already exists
        printErrorCode(100);
        return false;
    }
    ifstream input_txt("input_data.txt");
    if (!input_txt) { //Fail to open file
        printErrorCode(100);
        return false;
    }

    string comtext;
    while (getline(input_txt, comtext)) {
        vector<string> fields(5);
        stringstream sstr(comtext);
        int i = 0;
        while (i < 5 && getline(sstr, fields[i], ' ')) i++;

        if (i != 5) {  // If the number of data items is incorrect
            printErrorCode(100);
            continue;
        }

        int seats;
        try {
            seats = stoi(fields[3]);
        }
        catch (invalid_argument& e) {  // If the number of seats is not valid
            printErrorCode(100);
            continue;
        }

        FlightData* data = new FlightData;
        data->SetAirlineName(fields[0]);
        data->SetFlightNumber(fields[1]);
        data->SetDestination(fields[2]);
        data->SetNumberofSeats(seats);
        data->SetStatus(fields[4]);

        if (!bp->Insert(data)) { //If the BP tree fails to insert
            delete data;
            printErrorCode(100);
        }
    }

    input_txt.close();
    return true;
}

bool Manager::VLOAD() {
    avl->GetVector(Print_vector); // Load data into Print_vector

    if (Print_vector.size() == 0) return false; // Check if data loading was successful
    return true;
}

bool Manager::ADD(string Airline, string FlightNumber, string Destination, string Status) {
    FlightData* dataNode = bp->findFlightData(FlightNumber); // Search by flight number
    string currentStatus = dataNode->GetStatus(); //Variables for character removal
    currentStatus.erase(remove(currentStatus.begin(), currentStatus.end(), '\n'), currentStatus.end()); //\n Removal
    currentStatus.erase(remove(currentStatus.begin(), currentStatus.end(), '\r'), currentStatus.end()); //\r Removal

    if (!dataNode) { // Add new flight if number doesn't exist
        data = new FlightData;
        data->SetAirlineName(Airline);
        data->SetFlightNumber(FlightNumber);
        data->SetDestination(Destination);
        data->SetStatus(Status);

        // Set number of seats based on airline
        if (Airline == "KoreanAir" || Airline == "ASIANA")
            data->SetNumberofSeats(7);
        else if (Airline == "JEJU") {
            if (Destination != "CJU") {
                printErrorCode(300); //if destination is not CJU, error
            }
            else data->SetNumberofSeats(5);
        }
        else if (Airline == "JeanAir")
            data->SetNumberofSeats(5);
        else
            data->SetNumberofSeats(6);
        bp->Insert(data);
    }
    else { // Modify existing flight
        if (dataNode->GetNumberofSeats() == 0) { // Add to AVL tree if seats are 0
            avl->Insert(dataNode);
            printErrorCode(300);
            return false;
        }
        // Handle BOARDING status
        if (Status == "Boarding") {
            if (currentStatus == "Boarding" || currentStatus == "Cancelled") {
                dataNode->SetSeatsDec(); // Decrease seats if current status is BOARDING or CANCELLED
            }
            else if (currentStatus == "Cancelled") {
                dataNode->SetStatus("Boarding"); // Update status if CANCELLED
            }
            else {
                printErrorCode(300);
                return false;
            }
        }
        // Handle DELAYED status
        else if (Status == "Delayed") {
            if (dataNode->GetStatus() == "Delayed") {
                dataNode->SetSeatsDec(); // Decrease seats
            }
            else {
                printErrorCode(300);
                return false;
            }
        }
        // Handle CANCELLED status
        else if (Status == "Cancelled") {
            if (dataNode->GetStatus() == "Boarding") {
                dataNode->SetStatus("Cancelled"); // Only update status
            }
            else {
                printErrorCode(300);
                return false;
            }
        }
        else { // Error for invalid status
            printErrorCode(300);
            return false;
        }
        if (dataNode->GetNumberofSeats() == 0) { // Add to AVL tree if seats become 0
            avl->Insert(dataNode);
        }
    }
    return true;
}

bool Manager::SEARCH_BP(string name) { // Single search function
    if (!bp->getRoot()) {
        printErrorCode(400);
        return false;
    }
    FlightData* dataNode = bp->findFlightData(name);

    if (!dataNode) {
        printErrorCode(400); // Error if flight not found
        return false;
    }
    else {
         // Log search results
        flog << "========SEARCH_BP========" << endl;
        flog << dataNode->GetFlightNumber() << " | "
            << dataNode->GetAirlineName() << " | "
            << dataNode->GetDestination() << " | "
            << dataNode->GetNumberofSeats() << " | "
            << dataNode->GetStatus() << endl;
        flog << "=========================" << endl << endl;
    }
    return true;
}

bool Manager::SEARCH_BP(string start, string end) { // Range search function
    if (!bp->SearchRange(start, end)) {
        printErrorCode(400); // Error if no flights in range
        return false;
    }
    return true;
}

bool Manager::SEARCH_AVL(string name) {
    FlightData* AVLData = avl->Search(name);
    if (!AVLData)
        return false; // Error if name not found in AVL
    // Log search results
    flog << "========== SEARCH_AVL ==========" << endl
        << AVLData->GetFlightNumber() << " | " << AVLData->GetAirlineName() << " | "
        << AVLData->GetDestination() << " | " << AVLData->GetNumberofSeats() << " | "
        << AVLData->GetStatus() << endl
        << "========================" << endl << endl;

    return true;
}

bool Compare(FlightData* flight1, FlightData* flight2) { // Condition A sorting
    if (flight1->GetAirlineName() != flight2->GetAirlineName())
        return flight1->GetAirlineName() < flight2->GetAirlineName();
    else if (flight1->GetDestination() != flight2->GetDestination())
        return flight1->GetDestination() < flight2->GetDestination();
    else return flight1->GetStatus() > flight2->GetStatus();
}

bool Compare_B(FlightData* flight1, FlightData* flight2) { // Condition B sorting
    if (flight1->GetDestination() != flight2->GetDestination())
        return flight1->GetDestination() < flight2->GetDestination();
    else if (flight1->GetStatus() != flight2->GetStatus())
        return flight1->GetStatus() < flight2->GetStatus();
    else return flight1->GetAirlineName() > flight2->GetAirlineName();
}

bool Manager::VPRINT() {
    if (avl->getRoot() == nullptr) {
        printErrorCode(600); // Error if AVL tree is empty
        return false;
    }
    // VPRINT A
    sort(Print_vector.begin(), Print_vector.end(), Compare); // Sort by condition A
    flog << "========== VPRINT A ==========" << endl;
    for (FlightData* flight : Print_vector) {
        flog << flight->GetAirlineName() << " |"
            << flight->GetFlightNumber() << " |"
            << flight->GetDestination() << " |"
            << flight->GetStatus() << endl;
    }
    flog << "========================" << endl << endl;
}
bool Manager::VPRINTB() {
    // VPRINT B
    if (avl->getRoot() == nullptr) {
        printErrorCode(600); // Error if AVL tree is empty
        return false;
    }
    sort(Print_vector.begin(), Print_vector.end(), Compare_B); // Sort by condition B
    flog << "========== VPRINT B ==========" << endl;
    for (FlightData* flight : Print_vector) {
        flog << flight->GetAirlineName() << " |"
            << flight->GetFlightNumber() << " |"
            << flight->GetDestination() << " |"
            << flight->GetStatus() << endl;
    }
    flog << "========================" << endl << endl;
    return true;
}

void Manager::printErrorCode(int n) {
    ofstream fout;
    fout.open("log.txt", ofstream::app);
    fout << "========== ERROR ==========" << endl;
    fout << n << endl;
    fout << "===========================" << endl << endl;
    fout.close();
}

void Manager::PrintSuccess(string cmd) {
    ofstream fout;
    fout.open("log.txt", ofstream::app);
    fout << "========== " << cmd << " ==========" << endl;
    fout << "Success" << endl;
    fout << "=========================" << endl << endl;
    fout.close();
}
