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
   Node<T> *getNode(int) const;

public:
   LinkedListD();
   ~LinkedListD();
   bool operator==(LinkedListD);

   void push_back(const T &item);
   bool remove(const T &item);
   int getSize();
   T at(int index);
   int contains(const T &item);
   bool replace(int index, const T &item);
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
}

template <typename T>
void LinkedListD<T>::push_back(const T &item)
{
   // check for empty list
   if (!head) // special case needed?
   {
      head = new Node<T>(item);
      size++;
      return;
   }
   Node<T> *tail = getNode(size - 1);
   tail->setNext(new Node<T>(item, tail));
   size++;
}

template <typename T>
bool LinkedListD<T>::remove(const T &item) // REVIEW
{
   int index = contains(item);
   if (index != -1)
   {
      Node<T> *current = getNode(index); // node to delete
      if (index == 0)                    // head
      {
         if (size == 1) // only head
         {
            current = head;
         }
         else
         {
            head = current->getNext();
            head->setPrev(nullptr);
         }
      }
      else // any node but head
      {
         current->getPrev()->setNext(current->getNext()); // move previous:next
      }
      if (index != size - 1) // NOT tail
      {
         current->getNext()->setPrev(current->getPrev()); // move next:previous
      }
      delete current;
      size--;
      return true;
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
   if (index < 0 || index >= size)
      throw std::invalid_argument("index out of bounds");
   return getNode(index)->getItem();
}

template <typename T>
int LinkedListD<T>::contains(const T &item)
{
   Node<T> *current = head;
   for (int i = 0; i < size; i++)
   {
      if (current->getNext() == nullptr)
         return 0;
      if (current->getItem() == item)
         return i;
      current = current->getNext();
   }
   return -1;
}

template <typename T>
bool LinkedListD<T>::replace(int index, const T &item)
{
   if (index < size)
   {
      Node<T> *current = getNode(index);
      current->setItem(item);
      return true;
   }
   return false;
}

template <typename T>
Node<T> *LinkedListD<T>::getNode(int index) const
{
   Node<T> *current = head;
   for (int i = 0; i < index; i++)
   {
      current = current->getNext();
   }
   return current;
}

#endif // __LINKEDLISTD_H__