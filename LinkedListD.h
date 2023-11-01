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
   Node<T> *top;
   int size;

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
LinkedListD<T>::LinkedListD() : top(nullptr), size(0)
{
}

template <typename T>
LinkedListD<T>::~LinkedListD()
{
   Node<T> *a = top;
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
   if (!top)
   {
      top = new Node<T>(item);
   }
   Node<T> *curr = top;
   Node<T> *prev;
   while (curr && curr->getNext())
   {
      prev = curr;
      curr = curr->getNext();
   }
   curr->setNext(new Node<T>(item, prev)); // next is nullptr
   size++;
}

template <typename T>
bool LinkedListD<T>::remove(const T &item) // REVIEW
{
   int index = contains(item);
   if (index > 0)
   {
      Node<T> *current = top;
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
   if (index <= size && index > 0)
   {
      Node<T> *current = top;
      for (int i = 0; i < index; i++)
      { // index 1-n?
         current = current->getNext();
      }
      return current->getItem();
   }
   throw std::invalid_argument("index out of bounds");
}

template <typename T>
int LinkedListD<T>::contains(const T &item)
{
   int index = 0;
   if (size > 0)
   {
      Node<T> *current = top;
      for (int i = 0; i < size; i++)
      { // index 1-n?
         if (current->getNext() != nullptr)
         {
            if (current->getItem() == item)
            {
               index = i;
               break;
            }
            current = current->getNext();
         }
         else
         { // give up if next is a nullptr for some reason
            break;
         }
      }
   }
   return index;
}

template <typename T>
bool LinkedListD<T>::replace(int index, const T &item)
{
   if (index < size)
   {
      Node<T> *current = top;
      for (int i = 0; i < index; i++)
      { // index 1-n?
         current = current->getNext();
      }
      current->setItem(item);
      return true;
   }
   return false;
}

#endif // __LINKEDLISTD_H__