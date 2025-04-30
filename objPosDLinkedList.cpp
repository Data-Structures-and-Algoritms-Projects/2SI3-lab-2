#include "objPosDLinkedList.h"
#include <iostream>
using namespace std;

// Develop the objPos Doubly Linked List WITH DUMMY HEADER here.  
// Use the Test cases Test.cpp to complete the Test-Driven Development

objPosDLinkedList::objPosDLinkedList()
{
    listHead = new DNode();
    listHead->prev = nullptr;
    listTail = new DNode();
    listTail->next = nullptr;
    listHead->next = listTail;
    listTail->prev = listHead;
    persistHead = listHead;
    listSize = 0;

}

objPosDLinkedList::~objPosDLinkedList()
{
    DNode* readerHead = listHead;
    while (readerHead->next != nullptr) {
        DNode* target = readerHead;
        readerHead = readerHead->next;
        delete target;
    }
    delete readerHead;

}

int objPosDLinkedList::getSize()
{
    return listSize;
}

bool objPosDLinkedList::isEmpty()
{
    return listSize == 0;
}

void objPosDLinkedList::insertHead(const objPos &thisPos)
{
    DNode* newNode = new DNode();
    newNode->data = thisPos;
    newNode->next = listHead->next;
    newNode->prev = listHead;
    listHead->next->prev = newNode;
    listHead->next = newNode;
    listSize++;
}

void objPosDLinkedList::insertTail(const objPos &thisPos)
{
    DNode* newNode = new DNode();
    newNode->data = thisPos;
    newNode->prev = listTail->prev;
    newNode->next = listTail;
    listTail->prev->next = newNode;
    listTail->prev = newNode;
    listSize++;
}

void objPosDLinkedList::insert(const objPos &thisPos, int index)
{
    if (index <= 0){
        insertHead(thisPos);
    }
    else if (index >= listSize - 1){
        insertTail(thisPos);
    }
    else{
        DNode* newNode = new DNode();
        newNode->data = thisPos;
        DNode* readerHead = listHead;
        for (int i = 0; i < index; i++){
            readerHead = readerHead->next;
        }
        newNode->next = readerHead->next;
        newNode->prev = readerHead;
        readerHead->next->prev = newNode;
        readerHead->next = newNode;
        listSize++;
    }
}

objPos objPosDLinkedList::getHead() const
{
    if (listSize != 0){
        return listHead->next->data;
    }
    else {
        return objPos(-99, 0, 0, 0, 0);
    }
}

objPos objPosDLinkedList::getTail() const
{
    if (listSize != 0){
        return listTail->prev->data;
    }
    else {
        return objPos(-99, 0, 0, 0, 0);
    }
}

objPos objPosDLinkedList::get(int index) const
{
    if (listSize != 0){
        if (index <= 0){
            return getHead();
        }
        else if (index >= listSize - 1){
            return getTail();
        }
        else {
            DNode* readerHead = listHead;
            for (int i = 0; i < index; i++){
                readerHead = readerHead->next;
            }
            return readerHead->next->data;
        }
    }
    else {
        return objPos(-99, 0, 0, 0, 0);
    }
}

objPos objPosDLinkedList::getNext()
{
    persistHead = persistHead->next;
    if(persistHead == listTail){
        resetReadPos();
        return objPos(-99, 0, 0, 0, 0);
    }
    return persistHead->data;
}

void objPosDLinkedList::resetReadPos()
{
    persistHead = listHead;
}

void objPosDLinkedList::set(const objPos &thisPos, int index)
{
    if(index < 0){
        index = 0;
    }
    else if(index > listSize - 1){
        index = listSize - 1;
    }
    DNode* readerHead = listHead;
    for (int i = 0; i < index; i++){
        readerHead = readerHead->next;
    }
    readerHead->next->data = thisPos;
}


objPos objPosDLinkedList::removeHead()
{
    if (listSize != 0) {
        DNode* readerHead = listHead->next;
        listHead->next = readerHead->next;
        readerHead->next->prev = listHead;
        objPos data = readerHead->data;
        listSize--;
        delete readerHead;
        return data;
    }
    else{
        return objPos(-99, 0, 0, 0, 0);
    }
}

objPos objPosDLinkedList::removeTail()
{
    if (listSize != 0) {
        DNode* readerHead = listTail->prev;
        listTail->prev = readerHead->prev;
        readerHead->prev->next = listTail;
        objPos data = readerHead->data;
        listSize--;
        delete readerHead;
        return data;
    }
    else{
        return objPos(-99, 0, 0, 0, 0);
    }
}

objPos objPosDLinkedList::remove(int index)
{
    if(index <= 0){
        return removeHead();
    }
    else if(index >= listSize - 1){
        return removeTail();
    }
    else{
        DNode* readerHead = listHead;
        for (int i = 0; i < index; i++){
            readerHead = readerHead->next;
        }
        DNode* readerHead2 = readerHead->next;
        readerHead->next = readerHead2->next;
        readerHead2->next->prev = readerHead;
        objPos data = readerHead2->data;
        listSize--;
        delete readerHead2;
        return data;
    }

}


void objPosDLinkedList::printList() const
{
    cout << "Head: " << listHead << endl;
    int counter = 0;
    for(DNode* readerHead = listHead; readerHead != nullptr; readerHead = readerHead->next){
        cout << "Element " << counter << ": (Address: " << readerHead << ")" << endl;
        cout << "Data: " << readerHead->data.getX() << ", " << readerHead->data.getY() << ", " << readerHead->data.getNum() << ", " << readerHead->data.getPF() << ", " << readerHead->data.getSym() << endl;
        cout << "Next: " << readerHead->next << endl;
        cout << "Prev: " << readerHead->prev << endl;
        counter++;
    }
    cout << "Tail: " << listTail << endl;
}


