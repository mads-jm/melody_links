#include "LinkedListD.h"
#include <string>
#include <iostream>

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
      if (nowPlaying == -1) // track removed before current
      {
         nowPlaying++;
      }
   }

   void Playlist::removeSong(Track &song)
   {
      int index = storage.contains(song);
      storage.remove(song);
      if (index == nowPlaying)
      {
         // stop playback
      }
      if (index <= nowPlaying) // track removed before/is current
      {
         std::cout << nowPlaying << " " << storage.getSize() << endl;
         manageQueue(false);
         std::cout << nowPlaying << endl;
      }
   }
   Track Playlist::getSong(int index)
   {
      return storage.at(index - 1);
   }
   int Playlist::searchSong(std::string _title) // TODO
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
   void Playlist::playNext()
   {
      manageQueue(true);
      // trigger stop / start of playback calling currentSong()
   }
   void Playlist::playPrevious()
   {
      manageQueue(false);
      // trigger stop / start of playback calling currentSong()
   }
   Track Playlist::currentSong()
   {
      return storage.at(nowPlaying);
   }
   int Playlist::currentSong(int foo) // override as accessor; parameter unused
   {
      return nowPlaying;
   }
   void Playlist::displayPlaylist() // prints out each Track
   {
      for (int i = 0; i < storage.getSize(); i++)
      { // i. Title - artist (duration s) \n
         std::cout << i + 1 << ". " << storage.at(i) << "\n";
      }
      if (storage.getSize() == 0)
         std::cout << "Playlist is empty! \n";
   }
   void Playlist::sort()
   { // by title via quick sort
   }

   int Playlist::getSize()
   {
      return storage.getSize();
   }

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
};
