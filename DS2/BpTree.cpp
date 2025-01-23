#include "BpTree.h"

bool BpTree::Insert(FlightData* newData) {
    string key = newData->GetFlightNumber(); // Set the key

    // If tree is empty
    if (root == nullptr) {
        root = new BpTreeDataNode();
        ((BpTreeDataNode*)root)->insertDataMap(key, newData); // Insert into map
        return true;
    }

    // Find the data node for insertion
    BpTreeNode* dataNode = searchDataNode(key);

    // Insert data
    ((BpTreeDataNode*)dataNode)->insertDataMap(key, newData);

    // Check if node is full
    if (excessDataNode(dataNode)) {
        splitDataNode(dataNode);
    }

    return true;
}

bool BpTree::excessDataNode(BpTreeNode* pDataNode) {
    // Check if node exceeds maximum size
    if (pDataNode->getDataMap()->size() > order - 1) return true; // order is equal to the number of elements 
    else return false;
}

bool BpTree::excessIndexNode(BpTreeNode* pIndexNode) {
    // Check if index node exceeds maximum size
    if (pIndexNode->getIndexMap()->size() > order - 1) return true; // order is equal to the number of elements 
    else return false;
}

void BpTree::splitDataNode(BpTreeNode* pDataNode) {
    // Split data (leaf) node
    BpTreeDataNode* newDataNode = new BpTreeDataNode();
    map<string, FlightData*>* dataMap = pDataNode->getDataMap(); // Store data

    // Find middle key
    int mid = (order) / 2;
    auto iter = dataMap->begin();
    advance(iter, mid);
    string midKey = iter->first;

    // Move data to new node
    while (iter != dataMap->end()) {
        newDataNode->insertDataMap(iter->first, iter->second);
        iter++;
    }

    // Delete latter half from original node
    iter = dataMap->begin();
    advance(iter, mid);
    while (iter != dataMap->end()) {
        dataMap->erase(iter++);
    }

    // Update linked list connections
    newDataNode->setNext(((BpTreeDataNode*)pDataNode)->getNext()); // Set new node's next to original node's next
    newDataNode->setPrev(pDataNode); // Set new node's prev
    if (((BpTreeDataNode*)pDataNode)->getNext()) // If original node has next, set its prev to new node
        ((BpTreeDataNode*)((BpTreeDataNode*)pDataNode)->getNext())->setPrev(newDataNode);
    ((BpTreeDataNode*)pDataNode)->setNext(newDataNode); // Set original node's next to new node

    // Handle parent node
    if (pDataNode == root) { // If split node is root
        BpTreeIndexNode* newRoot = new BpTreeIndexNode();
        newRoot->insertIndexMap(midKey, newDataNode);
        newRoot->setMostLeftChild(pDataNode); // Set leftmost child to original node
        root = newRoot; // Change root
        pDataNode->setParent(root); // Set parent nodes
        newDataNode->setParent(root);
    }
    else {
        BpTreeIndexNode* parent = (BpTreeIndexNode*)pDataNode->getParent();
        parent->insertIndexMap(midKey, newDataNode);
        newDataNode->setParent(parent); // Set new node's parent to existing parent node

        if (excessIndexNode(parent)) {
            splitIndexNode(parent);
        }
    }
}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {
    // Split index node
    BpTreeIndexNode* newIndexNode = new BpTreeIndexNode();
    map<string, BpTreeNode*>* indexMap = pIndexNode->getIndexMap();

    // Find middle key
    int mid = (order) / 2;
    auto iter = indexMap->begin();
    advance(iter, mid); // Move to middle
    string midKey = iter->first;
    BpTreeNode* midChild = iter->second;

    // Move indices to new node
    iter++;
    while (iter != indexMap->end()) {
        newIndexNode->insertIndexMap(iter->first, iter->second);
        iter->second->setParent(newIndexNode); // Set new node as parent
        iter++;
    }

    // Delete latter half from original node
    iter = indexMap->begin();
    advance(iter, mid);
    while (iter != indexMap->end()) {
        indexMap->erase(iter++);
    }

    // Handle parent node
    if (pIndexNode == root) { // If split node is root
        BpTreeIndexNode* newRoot = new BpTreeIndexNode();
        newRoot->insertIndexMap(midKey, newIndexNode);
        newRoot->setMostLeftChild(pIndexNode); // Set new node's leftmost child to original node
        root = newRoot;
        pIndexNode->setParent(root); // Set split nodes' parent to new root
        newIndexNode->setParent(root);
    }
    else {
        BpTreeIndexNode* parent = (BpTreeIndexNode*)pIndexNode->getParent(); // Get current parent node
        parent->insertIndexMap(midKey, newIndexNode);
        newIndexNode->setParent(parent); // Set new index node's parent

        if (excessIndexNode(parent)) {
            splitIndexNode(parent); // Check if parent is overflowed
        }
    }
}

BpTreeNode* BpTree::searchDataNode(string key) {
    BpTreeNode* current = root;

    // Search until leaf node
    while (current && typeid(*current) != typeid(BpTreeDataNode)) { // Continue until null or data node is found
        BpTreeIndexNode* indexNode = (BpTreeIndexNode*)current;
        map<string, BpTreeNode*>* indexMap = indexNode->getIndexMap();

        BpTreeNode* next = indexNode->getMostLeftChild();
        for (auto iter = indexMap->begin(); iter != indexMap->end(); iter++) { // Continue moving down
            if (key < iter->first) break; // If current key is larger than search key, break and move to previous node
            next = iter->second; // Otherwise continue to next node
        }
        current = next;
    }

    return current;
}

BpTreeDataNode* BpTree::findDataNode(string key) {
    BpTreeNode* current = root;

    while (current && typeid(*current) != typeid(BpTreeDataNode)) { //Repeat until reach to DataNode
        BpTreeIndexNode* indexNode = static_cast<BpTreeIndexNode*>(current); 
        BpTreeNode* next = indexNode->getMostLeftChild(); //Move to the leftmost child

        for (const auto& iter : *(indexNode->getIndexMap())) { //If the value is greater than the key, break
            if (key < iter.first) break;
            next = iter.second; //Or move on
        }
        current = next;
    }

    if (!current) return nullptr; //When It can't find it

    BpTreeDataNode* dataNode = static_cast<BpTreeDataNode*>(current); 
    auto dataMap = dataNode->getDataMap(); //copy data

    return (dataMap->find(key) != dataMap->end()) ? dataNode : nullptr; //Return dataNode as it is if found
}

FlightData* BpTree::findFlightData(string key) { 
    BpTreeDataNode* dataNode = findDataNode(key); //receive value through findDataNode
    if (!dataNode) return nullptr; //When It can't find it

    auto iter = dataNode->getDataMap()->find(key); //Find and insert a value that matches the key in the iter
    return (iter != dataNode->getDataMap()->end()) ? iter->second : nullptr; //If you find it, return it as it is

}

bool BpTree::SearchRange(string start, string end) {
    // Range search function
    if (!root) return false;

    BpTreeNode* startNode = searchDataNode(start); // Search for target value
    if (!startNode) return false;

    bool found = false;
    BpTreeDataNode* current = (BpTreeDataNode*)startNode;
    *fout << "==========SEARCH_BP==========" << endl;
    while (current) {
        for (auto iter = current->getDataMap()->begin(); iter != current->getDataMap()->end(); iter++) {
            if (iter->first[0] >= start[0] && iter->first[0] <= end[0]) { // If within search range, print
                *fout << iter->second->GetFlightNumber() << " | "
                    << iter->second->GetAirlineName() << " | "
                    << iter->second->GetDestination() << " | "
                    << iter->second->GetNumberofSeats() << " | "
                    << iter->second->GetStatus() << endl;
                found = true;
            }
            if (iter->first[0] > end[0]) {
                *fout << "========================" << endl << endl;
                return found;
            }
        }
        current = (BpTreeDataNode*)current->getNext();
    }
    return found;
}

void BpTree::Print() {
    if (!root) return;

    BpTreeNode* current = root; // Traversal node
    while (typeid(*current) != typeid(BpTreeDataNode)) {
        current = ((BpTreeIndexNode*)current)->getMostLeftChild();
    }

    BpTreeDataNode* dataNode = (BpTreeDataNode*)current;
    *fout << "==========PRINT_BP==========" << endl;
    while (dataNode) {
        for (auto iter = dataNode->getDataMap()->begin(); iter != dataNode->getDataMap()->end(); iter++) {
            *fout << iter->second->GetFlightNumber() << " | " <<
                iter->second->GetAirlineName() << " | " <<
                iter->second->GetDestination() << " | " <<
                iter->second->GetNumberofSeats() << " | " <<
                iter->second->GetStatus() << endl;
        }
        dataNode = (BpTreeDataNode*)dataNode->getNext(); // Move node and print all nodes
    }
    *fout << "========================" << endl << endl;
}