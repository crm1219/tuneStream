#include "music_lib.h"

int main() 
{
    // seed a random number generator
    srand(time(NULL));
    // variable to store user menu choice
    int choice = 0; 
    // arrays to store song title and artist name
    char title[50], artist[50];
    // variable to store genre choice
    int genre;
    // array of genre names
    char* genres[] = {"Pop", "Rock", "Jazz", "Classical", "Other"};
    // create an initial playlist
        // declare a variable to hold the playlist
    Song *playlist = NULL;
        // create an initial playlist
    if(!createPlaylist(&playlist))
    {
        // print a message if something went wrong
        printf("Something went wrong. Please give it another try.\n");
        // exit with an error code
        return 1;
    }
        // print an initial message
    printf("\nTuneStream Music Player\n\n");
    printf("Initial playlist created with 20 songs!\n"); 

    // Infinite loop to keep the program running
    while (choice != 10)
    {
        // print the menu options for the user
        printf("\n1. Play\n");
        printf("2. Shuffle play\n");
        printf("3. Play by Artist\n");
        printf("4. Add a song to the playlist\n");
        printf("5. Remove a song by name\n");
        printf("6. Sort by Genre\n");
        printf("7. Set to Continuous Play Mode\n");
        printf("8. Set to Single Execution Play Mode\n");
        printf("9. Reverse Playlist\n");
        printf("10. Exit\n");

        // prompt user for choice
        printf("Choose an option: "); 

        // read the user's choice
        scanf("%d", &choice); 

        // switch case to handle different menu options
        switch (choice) 
        {
            // case for playing the songs
            case 1:
                // play the songs
                play(playlist, genres);
                // end of case
                break;

            // case for shuffling play 
            case 2: 
                // play songs in the shuffle mode
                playShuffle(playlist, genres);
                // exit the case
                break;

            // case for searching by artist    
            case 3:
                // prompt for artist name 
                printf("Enter artist name to search: "); 
                // read the artist name from user
                scanf(" %[^\n]%*c", artist); 
                // play by artist
                playByArtist(playlist, artist, genres);
                // exit the case
                break;

            // case for adding a song
            case 4: 
                // prompt for song title
                printf("Enter song title: "); 
                // read the song title from user
                scanf(" %[^\n]%*c", title);
                // prompt for artist name
                printf("Enter artist: "); 
                // read the artist name from user
                scanf(" %[^\n]%*c", artist);
                // prompt for genre
                printf("Enter genre (0: POP, 1: ROCK, 2: JAZZ, 3: CLASSICAL, " 
                        "4: OTHER): ");
                // read the genre from user
                scanf("%d", &genre); 

                // try to add a new song
                if(addSong(&playlist, title, artist, (Genre)genre))
                {
                    // print a confirmation message if successfully
                    puts("Song added successfully!\n");
                }
                // exit the case
                break;

            // case for removing a song
            case 5: 
                // prompt for song title to remove
                printf("Enter song title to remove: ");
                // read the song title from user
                scanf(" %[^\n]%*c", title);
                // try to remove the song
                if(removeSong(&playlist, title))
                {
                    puts("Song removed successfully\n");
                }
                // exit the case
                break;

            // case for sorting by genre    
            case 6:
                // sort the list by genre
                sortByGenre(&playlist);
                // exit the case
                break;

            // case for making the playlist circular    
            case 7: 
                // make the playlist circular
                makePlaylistCircular(&playlist);
                // exit case
                break;

            // case for making the playlist singly linked
            case 8:
                // set the playlist for single execution
                makePlaylistLinear(&playlist);
                // exit the case
                break;

            // Case for reversing the playlist    
            case 9: 
                // Call function to reverse the playlist
                reversePlaylist(&playlist); 

                // Confirmation message
                printf("Playlist reversed.\n"); 
                break; // Exit the case

            // Case for exiting the program    
            case 10: 
                // Message indicating exit
                printf("Exiting...\n"); 

                return 0; // Exit the program

            // Default case for invalid option    
            default: 
                printf("Invalid option, please try again.\n"); 
        }
    }

    // Return statement for main function (not reached due to infinite loop)
    return 0; 
}
