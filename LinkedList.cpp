/*
 * File:   LinkedList.cpp
 * Author: Thomas Stewart
 *
 * Last modified 15/01/2018
 * Implements the LinkedList class.
 */

#include <string>
#include <cassert>
#include <iostream>
#include <sstream>
#include "linked_list.h"
using namespace std;

//creates an empty list
LinkedList::LinkedList()
{
  Node *current = new Node();
  current->data = NULL;
  head = current;
  tail = current;
}

//creates a list with an initial value to store
LinkedList::LinkedList(int value)
{
  Node *current = new Node();
  current->data = value;
  head = current;
  tail = current;
}

//copy constructor (performs a deep copy)
LinkedList::LinkedList(const LinkedList& rhs)
{
  Node *current = new Node();
  current->data = NULL;
  head = current;
  tail = current;
  appendList(rhs);
}


//destroys (cleans up) the list
LinkedList::~LinkedList()
{
	Node *current = head;
	while(current->next != nullptr) {
		current->data = NULL;
		current = current->next;
	}
}

//adds a value to the head of the list
void LinkedList::push(int value)
{
  if(head->data == NULL && head->next == nullptr) { //head is overridden if null
	head->data = value;
    return;
  }
  Node *newHead = new Node();
  newHead->data = value;
  newHead->next = head;
  head = newHead;

}

//gets the last element from the list, without removing it
//requires: list not empty
int LinkedList::peekTail()
{
    assert(tail->data != NULL);
    return tail->data;
}

//prints the list in order from head to tail
string LinkedList::toString() const
{
    string part;
    string full = "";
    Node *current = head;
    while(true) {
      bool nextCheck = (current->next == nullptr);
      int handle = current->data;
      if(handle == NULL && nextCheck) { //checks that next is invalid as NULL can be equal to 0
        part = "";
        full.append(part);
      }
      else {
        part = to_string(handle);
        full.append(part);
      }
      if(nextCheck) {
        return full;
      }
      else {
        full.append(" ");
        current = current->next;
      }
    }
}

//removes and returns the value at the head of the list
//requires: list not empty
int LinkedList::pop()
{
    assert(head->data != NULL);
    int removedVal;
    if(head->next == nullptr) {
      removedVal = head->data;
      head->data = NULL;
    }
    else {
      removedVal = head->data;
	  head->data = NULL;
      head = head->next;
    }
    return removedVal;
}

//adds a value to the end of the list
void LinkedList::append(int value)
{
  if(head->data == NULL) { //head is overridden if null
    head->data = value;
    return;
  }
  Node *current = new Node();
  current->data = value;
  tail->next = current;
  tail = current;
}

//appends the deep copies of the nodes of rhs on to the end of this list
void LinkedList::appendList(const LinkedList& rhs)
{
  Node *current = rhs.head;
  bool isValid = current->next != nullptr;
  while(isValid)
  {
    isValid = (current->next != nullptr);
    append(current->data);
    current = current->next;
  }
  tail->next = nullptr;
}

//inserts a value immediately after the first occurrence of afterValue,
//if afterValue is not in the list then inserts at the tail
void LinkedList::insertAfter(int value, int afterValue)
{
  Node *check = head;
  bool isValid = true;
  bool isFound = false;
  int rep = 0;
  while(isValid) {
    bool nextCheck = (check->next == nullptr);
    if(nextCheck) isValid = false;
    if(check->data == afterValue) {
      isFound = true;
      break;
    }
    check = check->next;
    rep++;
  }
  if(!isFound) {
    append(value);
    return;
  }
  else {
    Node *current = new Node();
    current->data = value;
    current->next = check->next;
    check->next = current;
  }
}

//removes all occurrences of value from the list
void LinkedList::removeAllOccurences(int value)
{
  Node *check = head;
  Node *previousNode = nullptr;
  bool isNext = true; //checks if there is a next value
  while(isNext) {
    if(check->data == value) {
      if(previousNode == nullptr) //if head then pop
        pop();
      else {
        previousNode->next = check->next;
		check->data = NULL;
		check = previousNode;
      }
    }
    isNext = check->next != nullptr;
    previousNode = check;
    check = check->next;
  }
}
//reverses the list
//reverses the list
void LinkedList::reverse()
{
  if(head->next == nullptr) return; //removes a list with 0 or 1 elements
  Node *previous = nullptr;
  Node *middle = head;
  Node *next;
  tail = head;
  while (middle != nullptr)
  {
    next = middle -> next;
    middle -> next = previous;
    previous = middle;
    head = previous;
    middle = next;
    }
}

//checks if two lists are equal in state (contain the same values in the same order)
bool LinkedList::operator ==(const LinkedList& other) const
{
    Node *current = head;
    Node *currentOther = other.head;
    bool isEqual = true;
    while(isEqual && current->next != nullptr && currentOther->next != nullptr) {
      if(current->data != currentOther->data) {
		  return false;
      }
      current = current->next;
      currentOther = currentOther->next;
    }
  	return true;

}

//checks if two lists are not equal in state
bool LinkedList::operator !=(const LinkedList& other) const
{
  Node *current = head;
  Node *currentOther = other.head;
  while(current->next != nullptr && currentOther->next != nullptr) {
    if(current->data == currentOther->data) {
      return true;
    }
    current = current->next;
    currentOther = currentOther->next;
  }
  return false;
}

//pushes a new value onto the head of the list
LinkedList& LinkedList::operator +(int value)
{
	push(value);
	return *this;
}

//copy assignment operator (performs a deep copy)
LinkedList& LinkedList::operator =(const LinkedList& rhs)
{
	if (this == &rhs) {
		return *this;
	}
    bool isValid = (head->next != nullptr);
    while(isValid) {
      isValid = (head->next != nullptr);
      pop();
    }
    appendList(rhs);
    return *this;
}

//pushes values from an input stream onto the front of the list
std::istream& operator>>(std::istream &in, LinkedList &value)
{

    return in;
}

//writes the values, in order, to an output stream
std::ostream& operator<<(std::ostream &out, const LinkedList &value)
{

    return out;
}
