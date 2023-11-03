#include <string>
#include <iostream>
#include <stdlib.h> // CLS
//  #include <filesystem> // File path
#include <Windows.h> // Audio playback,
// #include <Mmsystem.h>
// #include <mciapi.h>
#pragma comment(lib, "Winmm.lib")

#include "Playlist.cpp"

Playlist master("master");
Playlist all("all"); // contains all possible tracks.

static const std::string exePath = "DIRECT_PATH"; // input file path to mp3s
//(std::filesystem::current_path()).string() + ("\\tracks");
bool active = false;

Track catalogue(Playlist &deck, bool io)
{
   int choice = 0;
   int n = deck.getSize();

   do
   {
      std::cout << "~( The Current Melodylinks Catalogue)~"
                << "\n\n";
      deck.displayPlaylist();
      std::cout << "[Input your Choice (1-" << n << ") ";
      if (io)
      { // true is adding | false is removing
         std::cout << "to ADD] : ";
      }
      else
      {
         std::cout << "to REMOVE] : ";
      }
      cin >> choice;
      std::cout << "\n\n\n";
   } while (choice < 1 || choice > n);
   return deck.getSong(choice);
}

// Handle 0 currentSong|1 playNext|2 playPrev
void controller(int _case)
{
   if (master.currentSong(1) > -1)
   { // playlist !empty
      if (_case == 1)
      { // play next
         master.playNext();
      }
      else if (_case == 2)
      { // play previous
         if (master.currentSong(1) > 0)
         {
            master.playPrevious();
         }
         else
         {
            std::cout << "Nope! This is the only song in the playlist\n\n";
            return;
         }
      }
      else if (_case != 0)
      {
         std::cout << "Something went wrong...\n";
         return;
      }
      // Now Playing for Next|Previous|Current
      std::cout << "Now Playing: " << master.currentSong().title << "\n\n";
   }
   else
   {
      std::cout << "Add a song! \n\n";
   }
}

void playback()
{
   int choice;
   do
   {
      choice = 0;
      std::cout << "Playback Menu:"
                << "\n";
      std::cout << "1 : [PLAY/PAUSE]"
                << "\n";
      std::cout << "2 : [NEXT]"
                << "\n";
      std::cout << "3 : [PREVIOUS]"
                << "\n";
      std::cout << "4 : [Current song]"
                << "\n";
      std::cout << "5 : [[Main Menu]]"
                << "\n";
      std::cout << "[Input your Choice (1-5)] : ";
      std::cin >> choice;
      std::cout << "\n\n";
      switch (choice)
      {
      case 1:
         if (master.currentSong(1) > -1) // ensure a song is loaded
         {
            if (!active)
            {
               // play
               active = true;
            }
            else
            {
               // pause
               active = false;
            }
         }
         break;
      case 2:
         controller(1); // next
         break;
      case 3:
         controller(2); // prev
         break;
      case 4:
         controller(0); // current
         break;
      case 5:
         cout << "Returning to Main Menu..."
              << "\n\n\n";
         break;
      default:
         std::cout << "Invalid choice. Please try again."
                   << "\n";
      }

   } while (choice != 5);
}

// in place of a proper inputs system, method handles audio file input
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

   std::cout << "Welcome to MelodyLinks!"
             << "\n\n";
   localIn(all);
   int choice;
   int index;
   std::string _title;
   Track next = Track((exePath + "amsterjam.mp3"), "Amsterjam", "FKJ", 363);
   do
   {
      choice = 10;
      std::cout << "Menu:"
                << "\n";
      std::cout << "1 : [Add song]"
                << "\n";
      std::cout << "2 : [Remove song]"
                << "\n";
      std::cout << "3 : [Playback Menu]"
                << "\n";
      std::cout << "4 : [Current song]"
                << "\n";
      std::cout << "5 : [Current Playlist details]"
                << "\n";
      std::cout << "6 : [Search current Playlist]"
                << "\n";
      std::cout << "7 : [Sort current Playlist]"
                << "\n";
      std::cout << "8 : [Shuffle Playlist]"
                << "\n";
      std::cout << "9 : [[EXIT]]"
                << "\n\n";
      std::cout << "[Input your Choice (1-9)] : ";
      std::cin >> choice;
      std::cout << "\n\n\n";

      switch (choice)
      {
      case 1:
         master.addSong(catalogue(all, true));
         break;
      case 2:
         master.removeSong(catalogue(master, false));
         break;
      case 3:
         playback(); // Enter playback menu
         break;
      case 4:
         controller(0);
         break;
      case 5:
         std::cout << "\n"
                   << "Currently loaded playlist : \n";
         master.displayPlaylist();
         break;
      case 6:
         index = -1;
         _title = " ";
         std::cout << "\" 0 \" to return to the menu. \n";
         std::cout << "To search, enter the title desired: ";
         cin.ignore();
         while (_title != "0")
         {
            std::getline(std::cin, _title);
            index = master.searchSong(_title);
            if (index > -1)
               std::cout << "\n"
                         << _title << " is Track #" << index << " in the current playlist \n\n";
            break;
         }
         break;
      case 7:
         // master.sort();
         // std::cout << "Sorted the active playlist by title!" << "\n\n";
         break;
      case 8:
         // master.shuffle();
         // std::cout << "Shuffled the active playlist by title!" << "\n\n";
         break;
      case 9:
         std::cout << "Goodbye!" << endl;
         break;
      default:
         std::cout << "Invalid choice. Please try again."
                   << "\n";
      }
   } while (choice != 0);

   return 0;
}