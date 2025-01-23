#include "SubtitleBST.h"
#include <iostream>
#include <fstream>
using namespace std;

SubtitleBST::SubtitleBST() : root(nullptr)
{
}
SubtitleBST::~SubtitleBST()
{
    bool check = true;
    Delete2(root, 4320, check); // Delete nodes with value less than 4320
}

SubtitleBSTNode* SubtitleBST::getRoot()
{
    return root;
}

SubtitleBSTNode* SubtitleBST::Insert(int data, string addtext) {
    SubtitleBSTNode* addNode = new SubtitleBSTNode;
    if (root == nullptr) { // If it is the first node
        addNode->value = data; // Insert data
        addNode->text = addtext;
        root = addNode; // Root is the newly created node
        return addNode;
    }
    SubtitleBSTNode* curNode = root; // If not the first node, traverse starting from the root
    while (1) {
        while (curNode->value > data) { // If the data is smaller than the current node value, move left
            if (curNode->getLeft() == nullptr) { // If it's the leftmost node
                curNode->setLeft(addNode);  // Insert
                addNode->text = addtext;
                addNode->value = data;
                return addNode;
            }
            else // If there is a left child
                curNode = curNode->getLeft(); // Move to the left child
        }
        while (curNode->value < data) { // If the data is larger than the current node value, move right
            if (curNode->getRight() == nullptr) { // If it's the rightmost node
                curNode->setRight(addNode); // Insert
                addNode->text = addtext;
                addNode->value = data;
                return addNode;
            } // If there is a right child
            else
                curNode = curNode->getRight(); // Move to the right child
        }
    }
}

void SubtitleBST::Print(SubtitleBSTNode* Node) {
    ofstream log("log.txt", ios::app);
    if (Node != nullptr) {
        Print(Node->getLeft()); // Recursively move to the leftmost node
        log << Node->text << endl; // Print and return to the parent node
        Print(Node->getRight()); // Recursively move to the rightmost node, print, then return to the parent node
    }
}

void SubtitleBST::Search(SubtitleBSTNode* Node, int target1, int target2, string textString[], int& index) {
    if (Node != nullptr) {
        Search(Node->getLeft(), target1, target2, textString, index); // Recursively move to the leftmost node
        if (Node->value >= target1 && target2 >= Node->value) { // If the node is within the range
            textString[index] = Node->text; // Store the text in the array
            index++; // Move to the next array element and return to the parent node
        }
        Search(Node->getRight(), target1, target2, textString, index); // Move to the right, execute if condition, and return to parent node
    }
    return;
}

SubtitleBSTNode* SubtitleBST::Delete1(SubtitleBSTNode* delNode, int target, bool& check) {
    SubtitleBSTNode* temp; // Temporary node to store the node to be deleted
    if (delNode != nullptr) {
        if (target < delNode->value)
            delNode->setLeft(Delete1(delNode->getLeft(), target, check)); // Rebuild the BST by linking the result to the parent node
        else if (target > delNode->value)
            delNode->setRight(Delete1(delNode->getRight(), target, check));

        else if (target == delNode->value) { // If the values match
            if (delNode->getLeft() == nullptr && delNode->getRight() == nullptr) { // If there are no child nodes
                delete delNode; // Delete the node
                return nullptr;
            }
            else if (delNode->getRight() == nullptr) { // If only the left child exists
                temp = delNode->getLeft(); // Copy the left child's data to the temp node
                delete delNode; // Delete the node
                return temp; // Link the left child to the parent node
            }
            else if (delNode->getLeft() == nullptr) { // If only the right child exists
                temp = delNode->getRight(); // Copy the right child's data to the temp node
                delete delNode; // Delete the node
                return temp;
            }
            else { // If both children exist
                temp = getMax(delNode->getLeft()); // Find the maximum value in the left subtree
                if (temp != nullptr) {
                    delNode->value = temp->value; // Replace the value of the node to be deleted
                    delNode->text = temp->text;
                    delNode->setLeft(Delete1(delNode->getLeft(), temp->value, check)); // Delete the duplicate node in the left subtree
                }
            }
        }
        check = true;
    }
    return delNode;
}

SubtitleBSTNode* SubtitleBST::getMax(SubtitleBSTNode* maxNode) { // Find the maximum value in the left subtree
    if (maxNode != nullptr) {
        if (maxNode->getRight() != nullptr)
            return getMax(maxNode->getRight()); // Move to the rightmost node to find the maximum value
    }
    return maxNode;
}

SubtitleBSTNode* SubtitleBST::Delete2(SubtitleBSTNode* delNode, int target, bool& check) {

    if (delNode != nullptr) {
        delNode->setLeft(Delete2(delNode->getLeft(), target, check)); // Traverse to the leftmost node
        delNode->setRight(Delete2(delNode->getRight(), target, check)); // Traverse to the rightmost node (post-order traversal)
        if (delNode->value < target) {
            delNode = Delete1(delNode, delNode->value, check); // Delete the node if it's less than the target and recursively perform this for all nodes
        }
    }
    else return nullptr;
    check = true;
    return delNode;
}
