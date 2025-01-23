#include "SectionList.h"
#include "SectionListNode.h"
#include "SubtitleListNode.h"

SectionList::SectionList() : head(nullptr)
{
}
SectionList::~SectionList() // Delete all linked lists
{
    SectionListNode* delNode;
    SubtitleListNode* delSub = head->subNode; // Initialize to the subtitle node pointed to by the head
    while (head != nullptr) {
        while (delSub != nullptr) { // Traverse and delete subtitle nodes first
            SubtitleListNode* temp = delSub;
            delSub = delSub->getNext();
            delete temp;
        }
        delNode = head; // Delete section node
        head = head->getNext();
        delete delNode;
    }
}

SectionListNode* SectionList::getHead()
{
    return head;
}

void SectionList::Insert(SectionListNode* newNode, SubtitleListNode* subtitleNode, int sNum, string stext) {
    if (head == nullptr) { // If there's nothing
        newNode = new SectionListNode; // Create a new node
        newNode->sectionNum = sNum; // Insert data

        subtitleNode = new SubtitleListNode;
        newNode->subNode = subtitleNode;
        subtitleNode->stext = stext;

        head = newNode; // Head node is the newly created node
        return;
    }
    SectionListNode* sectionCur; // Node to traverse the section nodes
    SubtitleListNode* subCur; // Node to traverse the subtitle nodes
    sectionCur = head;
    while (sectionCur->getNext() != nullptr) { // Move to the end of the section nodes
        sectionCur = sectionCur->getNext();
    }
    if (sectionCur->sectionNum == sNum) { // If section number matches
        subCur = sectionCur->subNode;
        while (subCur->getNext() != nullptr) { // Move to the end of the subtitle nodes
            subCur = subCur->getNext();
        }
        subtitleNode = new SubtitleListNode;
        subtitleNode->stext = stext;
        subCur->setNext(subtitleNode); // Link the new subtitle node
    }
    else { // If section number doesn't match
        newNode = new SectionListNode;
        newNode->sectionNum = sNum;
        sectionCur->setNext(newNode); // Link the new section node

        subtitleNode = new SubtitleListNode;
        subtitleNode->stext = stext;
        newNode->subNode = subtitleNode; // Link the new subtitle node
    }
}

SectionListNode* SectionList::Search(int searchNum) {
    SectionListNode* cur = head;
    bool check = false; // Variable to check if the section was found
    if (cur->sectionNum == searchNum) return cur; // If section number matches, return the node
    while (cur->getNext() != nullptr) { // Traverse to the end of the section nodes
        if (cur->sectionNum == searchNum) {
            check = true;
            break;
        }
        cur = cur->getNext();
    }
    if (cur->sectionNum == searchNum) {
        check = true;
    }
    if (check) return cur;
    else return nullptr; // Return null if not found
}
