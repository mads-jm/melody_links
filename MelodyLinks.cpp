#include "Playlist.cpp"
#include <string>
#include <iostream>
using namespace std;

#include <stdlib.h> // CLS
// #include <filesystem> // File path
#include <windows.h> // Audio playback,
#pragma comment(lib, "Winmm.lib")

Playlist master("master");
Playlist all("all"); // contains all possible tracks.

static const string exePath = "DIRECT_PATH"; // input file path to mp3s
//(std::filesystem::current_path()).string() + ("\\tracks");

Track Catalogue(Playlist &deck, bool io)
{
   int choice = 0;
   int n = deck.getSize();

   do
   {
      cout << "~( The Current Melodylinks Catalogue)~"
           << "\n\n";
      deck.displayPlaylist();
      cout << "[Input your Choice (1-" << n << ") ";
      if (io)
      { // true is adding | false is removing
         cout << "to ADD] : ";
      }
      else
      {
         cout << "to REMOVE] : ";
      }
      cin >> choice;
      cout << "\n\n";
   } while (choice < 1 || choice > n);
   return deck.getSong(choice);
}

// in place of a proper input system, method handles audio file input
void localIn(Playlist &deck)
{
   // proper implementation would allow manual input of paths and details
   deck.addSong(Track((exePath + "amsterjam.mp3"), "Amsterjam", "FKJ", 363));
   deck.addSong(Track((exePath + "anagram.mp3"), "Anagram", "Young The Giant", 294));
   deck.addSong(Track((exePath + "apartment.mp3"), "Apartment", "Young The Giant", 236));
   deck.addSong(Track((exePath + "the other.mp3"), "The Other", "Lauv", 189));
   deck.addSong(Track((exePath + "too much.mp3"), "Too Much", "Drake", 260));
   deck.addSong(Track((exePath + "woods.mp3"), "Woods", "Bon Iver", 285));
}

int main()
{

   cout << "Welcome to MelodyLinks!"
        << "\n\n";
   localIn(all);
   int choice;
   int index;
   string _title;
   Track next = Track((exePath + "amsterjam.mp3"), "Amsterjam", "FKJ", 363);
   do
   {
      // play next now
      choice = 0;
      cout << "Menu:"
           << "\n";
      cout << "1. Add song to the playlist"
           << "\n";
      cout << "2. Remove song from the playlist"
           << "\n";
      cout << "3. Play the next song"
           << "\n";
      cout << "4. Play the previous song"
           << "\n";
      cout << "5. Display current song info"
           << "\n";
      cout << "6. Display the entire playlist with durations"
           << "\n";
      cout << "7. Search for a song"
           << "\n";
      cout << "8. Sort playlist by title"
           << "\n\n";
      cout << "9. Exit"
           << "\n\n";
      cout << "[Input your Choice (1-8)] : ";
      cin >> choice;
      cout << "\n\n";

      switch (choice)
      {
      case 1:
         master.addSong(Catalogue(all, true));
         break;
      case 2:
         master.removeSong(Catalogue(master, false));
         break;
      case 3:
         if (master.currentSong(1) > -1)
         {
            master.playNext();
            cout << "Now Playing: " << master.currentSong().title << "\n\n";
         } // duplicate code :^)
         else
            cout << "Add a song! \n\n";
         break;
      case 4:
         master.playPrevious();
         cout << "Now Playing: " << master.currentSong().title << "\n\n";
         break;
      case 5:
         if (master.currentSong(1) > -1)
            cout << "Now Playing: " << master.currentSong().title << "\n\n";
         else
            cout << "Add a song! \n\n";
         break;
      case 6:
         cout << "\n"
              << "Currently loaded playlist : \n";
         master.displayPlaylist();
         break;
      case 7:
         index = -1;
         _title = "";
         cout << "\" x \" to return to the menu. \n";
         cout << "To search, enter the title desired: ";
         while (_title != "x")
         {
            cout << "\n"
                 << index << _title << endl;
            getline(cin, _title);
            index = master.searchSong(_title);
            if (index > -1)
               break;
         }
         break;
      case 8:
         // master.sort();
         // cout << "Sorted the active playlist by title!" << "\n\n";
         break;
      case 9:
         cout << "Goodbye!" << endl;
         break;
      default:
         cout << "Invalid choice. Please try again."
              << "\n";
      }
   } while (choice != 9);

   return 0;
}

// cout << "1. AmsterJam - FKJ (363s)" << "\n";
// cout << "2. Anagram - Young The Giant (294s)" << "\n";
// cout << "3. Apartment - Young The Giant (236s)" << "\n";
// cout << "4. The Other - Lauv (189s)" << "\n";
// cout << "5. Too Much - Drake (260s)" << "\n";
// cout << "6. Woods - Bon Iver (285s)" << "\n";