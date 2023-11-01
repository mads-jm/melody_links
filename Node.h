#ifndef NODE_
#define NODE_

// Node for Doubly Linked List
// two pointers

template <typename T>
class Node
{
private:
   T item; // A data item
   Node<T> *prev;
   Node<T> *next; // Pointer to next node
public:
   Node();
   Node(const T &anItem);
   Node(const T &anItem, Node<T> *prevNodePtr);
   Node(const T &anItem, Node<T> *prevNodePtr, Node<T> *nextNodePtr);
   void setItem(const T &anItem);
   void setNext(Node<T> *nextNodePtr);
   void setPrev(Node<T> *prevNodePtr);
   T getItem() const;
   Node<T> *getNext() const;
   Node<T> *getPrev() const;
}; // end Node

template <typename T>
Node<T>::Node() : item(NULL), next(nullptr), prev(nullptr)
{
} // end default constructor
template <typename T>
Node<T>::Node(const T &anItem) : item(anItem), next(nullptr), prev(nullptr)
{
} // end constructor
template <typename T>
Node<T>::Node(const T &anItem, Node<T> *prevNodePtr)
    : item(anItem), prev(prevNodePtr), next(nullptr)
{
}
template <typename T>
Node<T>::Node(const T &anItem, Node<T> *prevNodePtr, Node<T> *nextNodePtr)
    : item(anItem), prev(prevNodePtr), next(nextNodePtr)
{
} // end constructor
template <typename T>
void Node<T>::setItem(const T &anItem)
{
   item = anItem;
} // end setItem
template <typename T>
void Node<T>::setNext(Node<T> *nextNodePtr)
{
   next = nextNodePtr;
} // end setNext
template <typename T>
void Node<T>::setPrev(Node<T> *prevNodePtr)
{
   prev = prevNodePtr;
} // end setPrev

template <typename T>
T Node<T>::getItem() const
{
   return item;
} // end getItem
template <typename T>
Node<T> *Node<T>::getNext() const
{
   return next;
}
template <typename T>
Node<T> *Node<T>::getPrev() const
{
   return prev;
}

#endif