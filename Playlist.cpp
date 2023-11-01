#include "LinkedListD.h"
#include <string>
#include <iostream>
using namespace std;

#include <windows.h>
#pragma comment(lib, "Winmm.lib")

struct Track
{
   std::string path;
   std::string title;
   std::string artist;
   int length;
   int ID; // initialized when added to a playlist

   Track(std::string _path, std::string _title, std::string _artist, int _length) : path(_path), title(_title), artist(_artist), length(_length)
   {
   }

   bool Track::operator==(Track other)
   {
      return ((path == other.path) && (title == other.title) && (artist == other.artist));
   }

   bool Track::operator!=(Track other)
   {
      return ((path != other.path) && (title != other.title) && (artist != other.artist));
   }

   friend ostream &operator<<(ostream &os, const Track &track)
   {
      return cout << track.ID << ". " << track.title << " - " << track.artist << " (" << track.length << "s)"
                  << "\n";
   }
};

class Playlist : public LinkedListD<Track>
{
private:
   Node<Track> *top;
   int size;

public:
   Playlist::Playlist() : top(nullptr), size(0)
   { // default constructor
   }
   // Playlist(Playlist& other);
   // Playlist operator=(Playlist& other);
   //~Playlist();

   void Playlist::addSong(Track &song)
   {
      size++;
      song.ID = size;
      push_back(song);
   }
   void removeSong(int ID)
   {
      remove(at(ID));
      size--;
      updateID();
   } // parameter ID or name?
   // void playNext();
   // void playPrevious();
   Track Playlist::currentSong()
   {
      return top->getItem();
   } // need to override << operator in Track
   void displayPlaylist()
   {
      cout << "Currently loaded playlist : \n";
      for (int i = 1; i <= size; i++)
      { // index 1-n?
         cout << at(i) << "\n";
      }
   }
   // void sort();
   void updateID()
   {
      Node<Track> *current = top;
      for (int i = 1; i <= size; i++)
      {
         cout << "updoot" << i << endl;
         Track now = current->getItem();
         now.ID = i;
         current = current->getNext();
      }
   }
};
