#include "AVLTree.h"
#include <algorithm>  // for std::max
#include <stack>

// Helper function to get the height of a node
int height(AVLNode* node) {
    if (!node) return 0;
    return std::max(height(node->getLeft()), height(node->getRight())) + 1; // Recursively returns height difference between left and right children
}

// Helper function to update the balance factor of a node
void updateBalanceFactor(AVLNode* node) {
    if (node) {
        node->setBF(height(node->getLeft()) - height(node->getRight())); // BF = height of left child - height of right child
    }
}

// Right rotation
AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->getLeft();
    AVLNode* T2 = x->getRight();

    x->setRight(y);
    y->setLeft(T2); // In LL case, promote child to parent node when BF is broken

    updateBalanceFactor(y); // Update BF
    updateBalanceFactor(x);

    return x;
}

// Left rotation
AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->getRight();
    AVLNode* T2 = y->getLeft();

    y->setLeft(x);
    x->setRight(T2); // In RR case, promote child to parent node when BF is broken

    updateBalanceFactor(x); // Update BF
    updateBalanceFactor(y);

    return y;
}

// Insert a new node with given flight data
AVLNode* insertNode(AVLNode* node, FlightData* pFlightData) {
    if (node == nullptr) {
        AVLNode* newNode = new AVLNode();
        newNode->setFlightData(pFlightData);
        return newNode;
    }

    if (pFlightData->GetFlightNumber() < node->getFlightData()->GetFlightNumber()) { // If inserted data is smaller
        node->setLeft(insertNode(node->getLeft(), pFlightData)); // Go to left child
    }
    else if (pFlightData->GetFlightNumber() > node->getFlightData()->GetFlightNumber()) {
        node->setRight(insertNode(node->getRight(), pFlightData)); // Otherwise go to right child
    }
    else {
        return node;  // Duplicate keys are not allowed
    }

    updateBalanceFactor(node); // Check BF after insertion

    int balance = node->getBF();

    // Left Left Case
    if (balance > 1 && pFlightData->GetFlightNumber() < node->getLeft()->getFlightData()->GetFlightNumber()) {
        return rotateRight(node);
    }

    // Right Right Case
    if (balance < -1 && pFlightData->GetFlightNumber() > node->getRight()->getFlightData()->GetFlightNumber()) {
        return rotateLeft(node);
    }

    // Left Right Case
    if (balance > 1 && pFlightData->GetFlightNumber() > node->getLeft()->getFlightData()->GetFlightNumber()) {
        node->setLeft(rotateLeft(node->getLeft())); // LL rotation
        return rotateRight(node); // RR rotation
    }

    // Right Left Case
    if (balance < -1 && pFlightData->GetFlightNumber() < node->getRight()->getFlightData()->GetFlightNumber()) {
        node->setRight(rotateRight(node->getRight())); // RR rotation
        return rotateLeft(node); // LL rotation
    }

    return node;
}

bool AVLTree::Insert(FlightData* pFlightData) {
    root = insertNode(root, pFlightData); // Function to call insertNode to stabilize BF before adding to AVL
    return true;
}

FlightData* AVLTree::Search(string name) {
    AVLNode* current = root; // Traversal node
    while (current) {
        if (name == current->getFlightData()->GetFlightNumber()) { // If matches search data
            return current->getFlightData(); // Return current node
        }
        else if (name < current->getFlightData()->GetFlightNumber()) { // If search value is smaller
            current = current->getLeft(); // Go to left child
        }
        else {
            current = current->getRight(); // Otherwise go to right child
        }
    }
    return nullptr; // Return null if not found
}

void AVLTree::inorderTraversal(AVLNode* root, vector<FlightData*>& v) { // Traversal function
    stack<AVLNode*> stack; // Use stack to construct vector
    AVLNode* current = root;

    while (current != nullptr || !stack.empty()) {
        // Push all left children onto stack
        while (current != nullptr) {
            stack.push(current);
            current = current->getLeft(); // Move left
        }

        // Pop node from stack and add to vector
        current = stack.top();
        stack.pop();
        v.push_back(current->getFlightData());

        // Move to right child
        current = current->getRight();
    }
}

void AVLTree::GetVector(vector<FlightData*>& v) {
    inorderTraversal(root, v);
}