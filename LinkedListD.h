#ifndef __LINKEDLISTD_H__
#define __LINKEDLISTD_H__

#include <iostream>
using namespace std;
#include <stdexcept>
#include "Node.h"

template <typename T>
class LinkedListD
{
private:
   Node<T> *head;
   int size;
   Node<T> *getPointer(int) const;

public:
   LinkedListD();
   ~LinkedListD();

   void push_back(const T &item);          // rev
   bool remove(const T &item);             // rev
   int getSize();                          // rev
   T at(int index);                        // rev
   int contains(const T &item);            // rev
   bool replace(int index, const T &item); // TODO
};
template <typename T>
LinkedListD<T>::LinkedListD() : head(nullptr), size(0)
{
}

template <typename T>
LinkedListD<T>::~LinkedListD()
{
   Node<T> *a = head;
   while (a != nullptr)
   {
      Node<T> *temp = a->getNext();
      delete a;
      a = temp;
   }
   size = 0;
}

template <typename T>
void LinkedListD<T>::push_back(const T &item)
{
   // check for empty list
   if (!head)
   {
      head = new Node<T>(item);
   }
   Node<T> *current = getPointer(size - 1);
   Node<T> *previous = current->getPrev();
   current->setNext(new Node<T>(item, previous)); // next is nullptr
   size++;
}

template <typename T>
bool LinkedListD<T>::remove(const T &item) // REVIEW
{
   int index = contains(item);
   if (index > 0)
   {
      Node<T> *current = head;
      for (int i = 1; i < index; i++)
      {
         current = current->getNext();
      }                                   // end: current is at node before node to be removed
      Node<T> *temp = current->getNext(); // object being removed = temp
      if (temp->getNext() != nullptr)
      {                                     // next NOT EMPTY
         current->setNext(temp->getNext()); // previous obj next set to deleting objects next
         delete temp;                       // node with item deleted
         temp = current->getNext();         // next object pointer adjustment
         temp->setPrev(current);
         size--;
         return true;
      }
      else
      { // Object removed is at end of list
         current->setNext(nullptr);
         delete temp;
         size--;
         return true;
      }
   }
   return false;
}

template <typename T>
int LinkedListD<T>::getSize()
{
   return size;
}

template <typename T>
T LinkedListD<T>::at(int index)
{
   if (index < size && index > -1)
   {
      return getPointer(index)->getItem();
   }
   throw std::invalid_argument("index out of bounds");
}

template <typename T>
int LinkedListD<T>::contains(const T &item)
{
   Node<T> *current = head;
   for (int i = 0; i < size; i++)
   {
      if (size == 0 || current->getNext() == nullptr)
         return -1;
      if (current->getItem() == item)
         return i;
   }
   return -1;
}

template <typename T>
bool LinkedListD<T>::replace(int index, const T &item)
{
   if (index < size)
   {
      Node<T> *current = getPointer(index);
      current->setItem(item);
      return true;
   }
   return false;
}

template <typename T>
Node<T> *LinkedListD<T>::getPointer(int index) const
{
   Node<T> *current = head;
   for (int i = 0; i < index; i++)
   {
      current = current->getNext();
   }
   return current;
}

#endif // __LINKEDLISTD_H__