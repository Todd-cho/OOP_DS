#include "Manager.h"
#include "SubtitleQueueNode.h"
#include "SubtitleQueue.h"
#include "SubtitleBST.h"
#include "SubtitleBSTNode.h"
#include <iostream>
#include <string>

using namespace std;
bool Success = false;
Manager::Manager()
{
    managerRoot = nullptr; // Declare variables in the manager to use data structures created by the manager in other functions
    qNode = nullptr;
    bstNode = nullptr;
    subNode = nullptr;
    secNode = nullptr;
}
Manager::~Manager()
{

}

void Manager::Run(const char* command)
{
    // Open command & log file
    fcmd.open(command);
    flog.open("log.txt", ios::app);
    if (!fcmd)
    {
        flog << "Fail to open command file" << endl;
        exit(-1);
    }

    while (1) {
        string comtext; // Variable to store the command text
        string str[5] = { "a","a","a" ,"a" ,"a" }; // Variables to store separated characters
        getline(fcmd, comtext); // Get input from fcmd and save it in comtext
        stringstream sstr(comtext);

        int i = 0;
        while (getline(sstr, str[i], ' ')) i++; // Separate the characters by ' '

        if (str[0] == "LOAD") { // Function call by command
            if (str[1] != "a") { // If there are more functional factors
                PrintErrorCode(1000); // Call error function
                exit(-1);
            }
            Manager::LOAD(que);
        }
        else if (str[0] == "QPOP") {
            if (str[1] != "a") {// If there are more functional factors
                PrintErrorCode(1000);
                exit(-1);
            }
            Manager::QPOP(bst);
        }
        else if (str[0] == "PRINT") {
            if (str[2] != "a") { // If there are more functional factors
                PrintErrorCode(1000);
                exit(-1);
            }
            else {
                if (str[1] == "a") // If input is just "PRINT"
                    Manager::PRINT();
                else {
                    int num = stoi(str[1]); // Input "PRINT" + "number"
                    Manager::PRINT(num);
                }
            }
        }
        else if (str[0] == "SECTION") {
            int num = stoi(str[1]);
            if (str[4] != "a") { // If there are more functional factors
                PrintErrorCode(1000);
                exit(-1);
            }
            Manager::SECTION(num, str[2], str[3]);

        }
        else if (str[0] == "DELETE") {
            if (str[3] != "a") { // If there are more functional factors
                PrintErrorCode(1000);
                exit(-1);
            }
            else {
                if (str[1] == "EQUAL") {
                    Manager::DELETE1(str[2]);
                }
                if (str[1] == "UNDER") {
                    Manager::DELETE2(str[2]);
                }
            }
        }
        else if (str[0] == "EXIT") exit(-1);

        else {
            PrintErrorCode(1000);
            exit(-1);
        }
    }
    // Close command and log file
    fcmd.close();
    flog.close();


}

void Manager::PrintSuccess(string cmd) // Function to print success
{
    flog << "===== " << cmd << " =====" << endl;
    flog << "Success" << endl;
    flog << "===============\n" << endl;
}
void Manager::PrintErrorCode(int num) // Function to print error
{
    flog << "===== ERROR =====" << endl;
    flog << num << endl;
    flog << "===============\n" << endl;
}

void Manager::LOAD(SubtitleQueue& Node) {
    bool check = true; // Variable to ensure that the subtitle file has been read successfully
    qNode = new SubtitleQueueNode;
    ifstream text("subtitle.txt", ios::app);

    if (que.Front() != nullptr) {
        PrintErrorCode(100);
        exit(-1);
    }

    if (!text.is_open()) { // If the text file does not open
        PrintErrorCode(100);
        return;
    }

    std::string line; // Variable to store the line read from the subtitle file

    while (!text.eof()) {
        std::getline(text, line); // Read one line at a time and push it into the queue
        if (!Node.IsEmpty()) PrintErrorCode(100); // Error if data already exists
        Node.Push(qNode);
        if (text.eof()) { // At the end of the text file
            check = true; // Successfully read
            break;
        }
        else check = false;
    }

    while (1) {
        int count = 0;
        if (check == true) { // If successfully read and pushed
            Node.print(); // Print the queue
            count++;
        }
        if (text.eof()) {
            break; // Exit after reading all lines
        }
    }
    return;
}
int TimeToSec(string text) { // Function to convert the time in string format to seconds to be used in BST ordering
    int sec = 0;
    istringstream ss(text); // Split the string by space
    string time;
    int t[3] = { 0, };
    int i = 0;
    while (i < 3 && getline(ss, time, ':')) { // Split the string by ':' and store in array
        t[i] = stoi(time); // Convert string to integer
        i++;
    }
    sec = t[0] * 3600 + t[1] * 60 + t[2]; // Convert to seconds

    return sec;
}

void Manager::QPOP(SubtitleBST& bst) {

    qNode = que.Front(); // Connect to the front node
    if (que.IsEmpty()) {
        Manager::PrintErrorCode(200); // If qNode is empty, print error message
        exit(-1);
    }
    while (que.Front() != nullptr) { // While frontNode is not null
        int time = TimeToSec(qNode->text); // Convert time information

        bst.Insert(time, que.Pop()); // Build BST based on time information
        qNode = que.Front(); // Move front to the next node
    }
    PrintSuccess("QPOP"); // Success
    return;
}



void Manager::PRINT() {

    managerRoot = bst.getRoot(); // Connect to the root of the bst node

    if (managerRoot != nullptr) { // If the bst is not empty, print
        flog << "===== PRINT =====" << endl;
        flog << "Subtitle_BST" << endl;
        bst.Print(managerRoot);
        flog << "===============\n" << endl;
    }
    else {
        PrintErrorCode(300); // If bst is empty, handle the error
        exit(-1);
    }
}

void Manager::PRINT(int sectionNum) { // Overloaded print function
    SectionListNode* findNode;
    SubtitleListNode* subNode; // Node to find the data for the specified section
    findNode = section.Search(sectionNum); // Find the node corresponding to the section and copy it
    if (findNode != nullptr) { // If found
        subNode = findNode->subNode;
        flog << "===== PRINT =====" << endl;
        flog << "Section " << sectionNum << endl;
        while (subNode->getNext() != nullptr) { // Loop through subtitle nodes and print
            flog << subNode->stext << endl;
            subNode = subNode->getNext();
        }
        flog << subNode->stext << endl; // Print the last node
        flog << "===============\n" << endl;
    }
    if (findNode == nullptr) {
        PrintErrorCode(300); // If not found, handle the error
        exit(-1);
    }
}

void Manager::SECTION(int SectionNum, string time1, string time2) {
    int num1 = TimeToSec(time1); // Convert time to compare numerically
    int num2 = TimeToSec(time2);
    int index = 0;
    bstNode = bst.getRoot(); // Connect to the bst
    bst.Search(bstNode, num1, num2, textArr, index); // Start search, retrieve values between start and end time, using an array and index to hold the size
    for (int i = 0; i < index; i++) { // Insert into section
        section.Insert(secNode, subNode, SectionNum, textArr[i]);
    }

    if (textArr[0] == "a") { // If no values were retrieved
        PrintErrorCode(400); // Handle error
        exit(-1);
    }
    else {
        PrintSuccess("SECTION");
        return;
    }
}

void Manager::DELETE1(string time) { // Function to delete a specific node

    managerRoot = bst.getRoot(); // Connect to bst node

    bool check = false; // Variable to check if deletion was successful
    int num = TimeToSec(time); // Convert the value to be deleted to numeric data
    managerRoot = bst.Delete1(managerRoot, num, check); // Delete and connect the return value to root to link to the parent node
    if (check == true) // If successfully deleted
        PrintSuccess("DELETE"); // Print success
    else {
        PrintErrorCode(500);
        exit(-1);
    }
}

void Manager::DELETE2(string time) { // Function to delete nodes below a certain time

    int num = TimeToSec(time); // Get the reference time
    bool check = false;
    managerRoot = bst.getRoot(); // Connect to bst
    managerRoot = bst.Delete2(managerRoot, num, check);

    if (check == true)
        PrintSuccess("DELETE");
    else {
        PrintErrorCode(500);
        exit(-1);
    }
}
