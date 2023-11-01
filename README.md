# melody_links
A Music Box Implementation with Doubly Linked Lists

NODE>LINKEDLISTD>PLAYLIST>main
music playback is optional
sort is next TODO; quick sort




class Node // Templated base structure
  //Stores item, prevPtr, nextPtr

   Node(Item);
   Node(Item, prevNodePtr);
   Node(Item, prevNodePtr, nextNodePtr);
   setItem(Item);
   setNext(nextNodePtr);
   setPrev(prevNodePtr);
   getItem();
   Node *getNext();
   Node *getPrev();

Nodes utilized by LinkedListD and Playlist :: both are doubly linked lists parent:child

class LinkedListD
  //Stores a top pointer and size

   push_back(item);   
   remove(item);        
   int getSize();                 
   item at(index);                   
   int contains(item); //returns index
   replace(index,item);

Playlist is the underlying storage of the music player

struct Track 
  stores path, title, artist, length, and an ID

  overrides ==  !=  << 

class Playlist
  addsong(Track) 
  removeSong(ID)
  currentSong()
  displayPlaylist() prints
  // TODO :: sort() QUICK SORT
  updateID() // bad implementation TODO

