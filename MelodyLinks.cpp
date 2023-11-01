#include "Playlist.cpp"
#include <string>
#include <iostream>
using namespace std;

#include <stdlib.h> // CLS
// #include <filesystem> // File path
#include <windows.h> // Audio playback,
#pragma comment(lib, "Winmm.lib")

Playlist master;
Playlist all;

static const string exePath = "DIRECT_PATH"; // input file path to mp3s
//(std::filesystem::current_path()).string() + ("\\tracks");

Track Catalogue(Playlist &deck, bool io)
{
    int choice = 0;
    int n = deck.getSize();
    system("cls");
    do
    {
        cout << "~( The Current Melodylinks Catalogue)~"
             << "\n\n";
        for (int i = 1; i < n + 1; i++)
        {
            cout << deck.at(i) << "\n";
        }
        cout << "[Input your Choice (1-" << n << ") ";
        if (io)
        { // true is adding | false is removing
            cout << "to ADD] :";
        }else
        {
            cout << "to REMOVE] :";
        }
        cin >> choice;
        if (choice < 1 || choice > 6)
        {
        }
        return deck.at(choice);
    } while (choice < 1 || choice > 6);
}

// in place of a proper input system, method handles audio file input
void localIn(Playlist &deck)
{

    deck.addSong(Track((exePath + "amsterjam.mp3"), "Amsterjam", "FKJ", 363));
    deck.addSong(Track((exePath + "anagram.mp3"), "Anagram", "Young The Giant", 294));
    deck.addSong(Track((exePath + "apartment.mp3"), "Apartment", "Young The Giant", 236));
    deck.addSong(Track((exePath + "the other.mp3"), "The Other", "Lauv", 189));
    deck.addSong(Track((exePath + "too much.mp3"), "Too Much", "Drake", 260));
    deck.addSong(Track((exePath + "woods.mp3"), "Woods", "Bon Iver", 285));
}

int main()
{
    localIn(all);
    int choice;
    Track next = Track((exePath + "amsterjam.mp3"), "Amsterjam", "FKJ", 363);
    do
    {
        // play next now

        cout << "Welcome to MelodyLinks!"
             << "\n";

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
        cout << "8. Exit"
             << "\n\n";
        cout << "[Input your Choice (1-8)] : ";
        cin >> choice;
        system("cls");
        switch (choice)
        {
        case 1:
            master.addSong(Catalogue(all, true));
            break;
        case 2:
            master.removeSong(Catalogue(master, false).ID);
            break;
        case 3:
            // master.playNext();
            // cout << "Now Playing: " << master.currentSong().title << "\n\n";
            break;
        case 4:
            // master.playPrevious();
            break;
        case 5:
            // master.currentSong();
            break;
        case 6:
            cout << "\n";
            master.displayPlaylist();
            break;
        case 7:
            // Search for a song; use contains() index; 0 being no?
            break;
        case 8:
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again."
                 << "\n";
        }
    } while (choice != 8);

    return 0;
}

// cout << "1. AmsterJam - FKJ (363s)" << "\n";
// cout << "2. Anagram - Young The Giant (294s)" << "\n";
// cout << "3. Apartment - Young The Giant (236s)" << "\n";
// cout << "4. The Other - Lauv (189s)" << "\n";
// cout << "5. Too Much - Drake (260s)" << "\n";
// cout << "6. Woods - Bon Iver (285s)" << "\n";