#include "LinkedListD.h"
#include <string>
#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

// Structure to hold song info to be contained in list
struct Track
{
   std::string path;
   std::string title;
   std::string artist;
   int length;

   Track(std::string _path, std::string _title, std::string _artist, int _length) : path(_path), title(_title), artist(_artist), length(_length)
   {
   }

   static int Track::compareTitle(Track a, Track b) // compare only title
   {
      return a.title.compare(b.title); // string comparison
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
      return std::cout << track.title << " - " << track.artist << " (" << track.length << "s)"
                       << "\n";
   }
};

class Playlist
{
private:
   std::string title;
   int nowPlaying; // index of storage
   LinkedListD<Track> storage;

public:
   Playlist::Playlist(std::string _title) : title(_title), nowPlaying(-1)
   { // default constructor
   }
   Playlist::Playlist(Playlist &other)
   { // copy constructor
      other.title = title;
      other.nowPlaying = nowPlaying;
      for (int i = 0; i < storage.getSize(); i++)
      {
         other.storage.push_back(storage.at(i));
      }
   }
   // adds Track to end of list, increments nowPlaying if first Track added.
   void Playlist::Playlist::addSong(Track &song)
   {
      storage.push_back(song);
      if (nowPlaying == -1) // track removed before current
      {
         nowPlaying++;
      }
   }
   // removes first instance of Track
   // utilizes contains() to find the index
   void Playlist::removeSong(Track &song)
   {
      int index = storage.contains(song);
      storage.remove(song);
      // if (index == nowPlaying)
      //  stop playback UNUSED
      if (index <= nowPlaying) // track removed before/is current
      {
         std::cout << nowPlaying << " " << storage.getSize() << endl;
         manageQueue(false);
         std::cout << nowPlaying << endl;
      }
   }
   // returns Track at user index - 1;
   Track Playlist::getSong(int index)
   {
      return storage.at(index - 1);
   }
   // CASE SENSITIVE SEARCH - returns index + 1
   // Note: Given implementation of displayPlaylist, this search is not needed.
   int Playlist::searchSong(std::string _title)
   {
      for (int i = 0; i < storage.getSize(); i++)
      {
         Track song = storage.at(i);
         if (song.title.compare(_title) == 0)
         {
            return (i + 1);
         }
      }
      return -1;
   }
   // Helper method for playNext/Prev while minding end points
   // io = true for adding a song
   // io = false for removing a song
   void Playlist::manageQueue(bool io)
   {
      int n = (storage.getSize() - 1);
      if (io)
      { // added song
         if (nowPlaying == n)
         {
            nowPlaying = 0;
         }
         else
         {
            nowPlaying++;
         }
      }
      else
      { // removed song
         if (nowPlaying == 0 && (storage.getSize() != 0))
         {
            nowPlaying = n;
         }
         else
         {
            nowPlaying--;
         }
      }
   }
   void Playlist::playNext()
   {
      manageQueue(true);
   }
   void Playlist::playPrevious()
   {
      manageQueue(false);
   }
   // returns the track at the index of nowplaying
   Track Playlist::currentSong()
   {
      return storage.at(nowPlaying);
   }
   // override as accessor; parameter unused but signals to return nowplaying
   int Playlist::currentSong(int foo)
   {
      return nowPlaying;
   }
   // Formats each track, displaying it's index + 1
   // utilizes Track::<< operator
   void Playlist::displayPlaylist() // prints out each Track
   {
      int length = 0;
      if (storage.getSize() == 0)
      {
         std::cout << "Playlist is empty! \n";
         return;
      }
      for (int i = 0; i < storage.getSize(); i++)
      { // i. Title - artist (duration s) \n
         std::cout << i + 1 << ". " << storage.at(i) << "\n";
         length += storage.at(i).length;
      }
      std::cout << "Length: " << length << " seconds"
                << "\n\n";
   }

   // for each track, generates a random index to swap with
   void Playlist::shuffle()
   {
      for (int i = 0; i < storage.getSize(); i++)
      {
         srand(static_cast<signed>(time(0)));
         int random = rand() % (storage.getSize() - 1) + 1;
         Track temp = storage.at(i);
         storage.replace(i, storage.at(random));
         storage.replace(random, temp);
      }
   }

   // compareTitle(Track a, Track b)
   // Passes the Track comparison method into ListD quick sort
   void Playlist::sort()
   {
      storage.sort(Track::compareTitle);
   }
   int Playlist::getSize()
   {
      return storage.getSize();
   }
};
