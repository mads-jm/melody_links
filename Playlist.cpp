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
      return cout << track.title << " - " << track.artist << " (" << track.length << "s)"
                  << "\n";
   }
};

class Playlist
{
private:
   string title;
   int nowPlaying; // index of storage
   LinkedListD<Track> storage;

public:
   Playlist::Playlist(string _title) : title(_title), nowPlaying(-1)
   { // default constructor
   }
   Playlist::Playlist(Playlist &other)
   {
      other.title = title;
      other.nowPlaying = nowPlaying;
      for (int i = 0; i < storage.getSize(); i++)
      {
         other.storage.push_back(storage.at(i));
      }
   }
   // Playlist operator=(Playlist& other);

   void Playlist::Playlist::addSong(Track &song)
   {
      storage.push_back(song);
   }

   void Playlist::removeSong(int index)
   {
      storage.remove(storage.at(index - 1));
   }
   void Playlist::playNext()
   {
      nowPlaying++;
      // trigger stop / start of playback calling currentSong()
   }
   void Playlist::playPrevious()
   {
      nowPlaying--;
      // trigger stop / start of playback calling currentSong()
   }
   Track Playlist::currentSong()
   {
      return storage.at(nowPlaying);
   }
   void Playlist::isplayPlaylist() // prints out each Track
   {
      cout << "Currently loaded playlist : \n";
      for (int i = 0; i < storage.getSize(); i++)
      { // i. Title - artist (duration s) \n
         cout << i + 1 << ". " << storage.at(i) << "\n";
      }
   }
   void Playlist::sort()
   { // by title via quick sort
   }
};
