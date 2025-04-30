#include "objPosSLinkedList.h"
#include <iostream>
using namespace std;

// Develop the objPos Singly Linked List WITHOUT DUMMY HEADER.  
// Use the Test cases Test.cpp to complete the Test-Driven Development

objPosSLinkedList::objPosSLinkedList()
{
    listHead = new SNode();
    persistHead = listHead;
    listSize = 0;
}

objPosSLinkedList::~objPosSLinkedList()
{
    SNode* readerHead = listHead;
    while (readerHead->next != nullptr) {
        SNode* target = readerHead;
        readerHead = readerHead->next;
        delete target;
    }
    delete readerHead;
}

int objPosSLinkedList::getSize()
{
    return listSize;
}

bool objPosSLinkedList::isEmpty()
{
   return listSize == 0;
}

void objPosSLinkedList::insertHead(const objPos &thisPos)
{
    SNode* newNode = new SNode();
    newNode->data = thisPos;
    newNode->next = listHead;
    listHead = newNode;
    if(listSize == 0){
        delete listHead->next;
        listHead->next = nullptr;
    }
    listSize++;   
}

void objPosSLinkedList::insertTail(const objPos &thisPos)
{
    if(listSize == 0) {
        insertHead(thisPos);
    }
    else{
        SNode* newNode = new SNode();
        newNode->data = thisPos;
        SNode* readerHead = listHead;
        while (readerHead->next != nullptr) {
            readerHead = readerHead->next;
        }
        readerHead->next = newNode;
        listSize++;
    }
}

void objPosSLinkedList::insert(const objPos &thisPos, int index)
{
    if (index <= 0){
        insertHead(thisPos);
    }
    else if (index >= listSize - 1){
        insertTail(thisPos);
    }
    else{
        SNode* newNode = new SNode();
        newNode->data = thisPos;
        SNode* readerHead = listHead;
        for (int i = 0; i < index - 1; i++){
            readerHead = readerHead->next;
        }
        newNode->next = readerHead->next;
        readerHead->next = newNode;
        listSize++;
    }
}

objPos objPosSLinkedList::getHead() const
{
    if (listSize != 0){
        return listHead->data;
    }
    else {
        return objPos(-99, 0, 0, 0, 0);
    }
}

objPos objPosSLinkedList::getTail() const
{
    if (listSize != 0){
        SNode* readerHead = listHead;
        while (readerHead->next != nullptr) {
            readerHead = readerHead->next;
        }
        return readerHead->data;
    }
    else {
        return objPos(-99, 0, 0, 0, 0);
    }
}

objPos objPosSLinkedList::get(int index) const
{
    if (listSize != 0){
        if (index <= 0){
            return getHead();
        }
        else if (index >= listSize - 1){
            return getTail();
        }
        SNode* readerHead = listHead;
        for (int i = 0; i < index; i++){
            readerHead = readerHead->next;
        }
        return readerHead->data;
    }
    else {
        return objPos(-99, 0, 0, 0, 0);
    }
}

objPos objPosSLinkedList::getNext()
{
    objPos data = persistHead->data;
    if(persistHead == nullptr){
        resetReadPos();
        return objPos(-99, 0, 0, 0, 0);
    }
    persistHead = persistHead->next;
    return data;
}

void objPosSLinkedList::resetReadPos()
{
    persistHead = listHead;
}

void objPosSLinkedList::set(const objPos &thisPos, int index)
{
    if(index < 0){
        index = 0;
    }
    else if(index > listSize - 1){
        index = listSize - 1;
    }
    SNode* readerHead = listHead;
    for (int i = 0; i < index; i++){
        readerHead = readerHead->next;
    }
    readerHead->data = thisPos;
}


objPos objPosSLinkedList::removeHead()
{
    if (listSize != 0) {
        SNode* readerHead = listHead;
        listHead = readerHead->next;
        objPos data = readerHead->data;
        listSize--;
        delete readerHead;
        return data;
    }
    else {
        return objPos(-99, 0, 0, 0, 0);
    }
}

objPos objPosSLinkedList::removeTail()
{
  if (listSize != 0) {
        SNode* readerHead = listHead;
        while (readerHead->next != nullptr) {
            readerHead = readerHead->next;
        }
        objPos data = readerHead->data;
        readerHead = nullptr;
        listSize--;
        delete readerHead;
        return data;
    }
    else {
        return objPos(-99, 0, 0, 0, 0);
    }
}

objPos objPosSLinkedList::remove(int index)
{
    if(index <= 0){
        return removeHead();
    }
    else if(index >= listSize - 1){
        return removeTail();
    }
    else{
        SNode* readerHead = listHead;
        for (int i = 0; i < index-1; i++){
            readerHead = readerHead->next;
        }
        SNode* readerHead2 = readerHead->next;
        readerHead->next = readerHead2->next;
        objPos data = readerHead2->data;
        listSize--;
        delete readerHead2;
        return data;
    }
}

void objPosSLinkedList::printList() const
{
    cout << "Head: " << listHead << endl;
    int counter = 0;
    for(SNode* readerHead = listHead; readerHead != nullptr; readerHead = readerHead->next){
        cout << "Element " << counter << ": (Address: " << readerHead << ")" << endl;
        cout << "Data: " << readerHead->data.getX() << ", " << readerHead->data.getY() << ", " << readerHead->data.getNum() << ", " << readerHead->data.getPF() << ", " << readerHead->data.getSym() << endl;
        cout << "Next: " << readerHead->next << endl;
        counter++;
    }
    cout << "End of List" << endl;
}


