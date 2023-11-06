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
   Node<T> *partition(int (*compareFn)(T a, T b), Node<T> *head, Node<T> *tail);
   void quickSort(int (*compareFn)(T a, T b), Node<T> *head, Node<T> *tail);

public:
   LinkedListD();
   // LinkedListD(const LinkedListD other);
   // LinkedListD operator=(const LinkedListD &other);
   ~LinkedListD();

   void push_back(const T &item);
   bool remove(const T &item);
   int getSize();
   T at(int index);
   int contains(const T &item);
   bool replace(int index, const T &item);
   void sort(int (*compareFn)(T a, T b));
};
// base constructor
template <typename T>
LinkedListD<T>::LinkedListD() : head(nullptr), size(0)
{
}
// destructor
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

// pushes item to back of list
// if head isn't null, simply create a new node at head
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
// remove first instance of item
// Checks if list is empty, has just a head or if value is not at the tail
template <typename T>
bool LinkedListD<T>::remove(const T &item)
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
// private field accessor
template <typename T>
int LinkedListD<T>::getSize()
{
   return size;
}
// gets item at index (0-n)
template <typename T>
T LinkedListD<T>::at(int index)
{
   if (index < 0 || index >= size)
      throw std::invalid_argument("index out of bounds");
   return getNode(index)->getItem();
}
// returns first index of item, otherwise returns -1 if doesn't contain
// safety case within loop if it encounters a node without a next pointer
template <typename T>
int LinkedListD<T>::contains(const T &item)
{
   Node<T> *current = head;
   for (int i = 0; i < size; i++)
   {
      if (current->getNext() == nullptr)
         return -1;
      if (current->getItem() == item)
         return i;
      current = current->getNext();
   }
   return -1;
}
// replaces data at index with item :: doesn't touch pointers
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
// private method : gets a node pointer for given index
template <typename T>
Node<T> *LinkedListD<T>::getNode(int index) const
{
   Node<T> *current = head;
   for (int i = 0; i < index; i++)
   { // size - 1 == tail
      current = current->getNext();
   }
   return current;
}
// Sort helper method, divides into partitions from left:right pointers
// compareFn allows generic structure to sort on user passed compare function
template <typename T>
Node<T> *LinkedListD<T>::partition(int (*compareFn)(T a, T b), Node<T> *left, Node<T> *right)
{
   if (left == right || left == NULL || right == NULL)
      return left;
   T pivot = left->getItem();
   // previous
   Node<T> *i = left;
   Node<T> *j = right;

   while (i != j)
   {
      while (compareFn(i->getItem(), pivot) < 0)
      { // find leftmost element greater than or equal to pivot
         i = i->getNext();
      }
      while (compareFn(j->getItem(), pivot) > 0)
      { // find rightmost element less than or equal to pivot
         j = j->getPrev();
      }
      // swap i and j
      T temp = i->getItem();
      i->setItem(j->getItem());
      j->setItem(temp);
   }
   return j;
}
// PRIVATE recursive quickSort
// calls itself on [left, pivot] [pivot, right]
template <typename T>
void LinkedListD<T>::quickSort(int (*compareFn)(T a, T b), Node<T> *left, Node<T> *right)
{
   if ((right != NULL) && (left != right) && (left != right->getNext()))
   {
      Node<T> *pivot = partition(compareFn, left, right);
      quickSort(compareFn, left, pivot->getPrev());
      quickSort(compareFn, pivot->getNext(), right);
   }
}
// PUBLIC recursive helper method, user passes in needed compareFn Function
template <typename T>
void LinkedListD<T>::sort(int (*compareFn)(T a, T b))
{
   if (getSize() <= 1) // no sort on single element
      return;
   Node<T> *initialPivot = head;                          // stupid pivot point
   quickSort(compareFn, initialPivot, getNode(size - 1)); // sort from head to tail
}

#endif // __LINKEDLISTD_H__
