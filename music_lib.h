#ifndef MUSIC_LIB_H
#define MUSIC_LIB_H

// header files
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// global definitions
#define FILENAME "playlist.csv"
#define MAX_SONGS 150
#define STR_LEN 50

typedef enum 
{
    POP,
    ROCK,
    JAZZ,
    CLASSICAL,
    OTHER,
    GENRE_COUNT
}
Genre;

typedef struct Song 
{
    char title[50];
    char artist[50];
    Genre genre;
    struct Song *next;
}
Song;

// function prototypes

/**
 * Function: createPlaylist (provided)
 * Input argument: playlist - a double pointer to a list of songs
 * Output argument: updated head of the playlist
 * Return: true if the playlist is successfully loaded, false if errors occur
 * Dependencies: addSong, stdio.h, string.h
 */
bool createPlaylist(Song **playlist);

/**
 * Function: play
 * Input argument: playlist - a pointer to a list of songs
 *                 genres - an array with the names of the genres. Genres are 
 *                          listed in the array according to its enum value.
 *                          For example, "Pop" is at index genres[POP]
 * Output argument: none
 * Return: none
 * Dependencies: stdio.h, ctype.h
 */
void play(Song *playlist, char* genres[]);

/**
 * Function: addSong
 * Input argument: playlist - a double pointer to a list of songs
 *                 title - a string with the title of the song
 *                 artist - a string with the artist of the song
 *                 genre - a Genre enum for the genre of the song
 * Output argument: updated head of the playlist, if needed
 * Return: true if the song is successfully added, false otherwise
 * Dependencies: stdlib.h, stdio.h, string.h
 */
bool addSong(
    Song **playlist, const char *title, const char *artist, Genre genre);

/**
 * Function: removeSong
 * Input argument: playlist - a double pointer to a list of songs
 *                 title - a string with the title of the song
 * Output argument: updated head of the playlist, if needed
 * Return: true if the song is successfully removed, false otherwise
 * Dependencies: stdlib.h, stdio.h, string.h
 */
bool removeSong(Song **playlist, const char *title);

/**
 * Function: playShuffle
 * Input argument: playlist - a pointer to a list of songs
 *                 genres - an array with the names of the genres. Genres are 
 *                          listed in the array according to its enum value.
 *                          For example, "Pop" is at index genres[POP]
 * Output argument: none
 * Return: none
 * Dependencies: stdlib.h, stdio.h
 */
void playShuffle(Song *playlist, char* genres[]);

/**
 * Function: playByArtist
 * Input argument: playlist - a pointer to a list of songs
 *                 artist - a string representing the artist name
 *                 genres - an array with the names of the genres. Genres are 
 *                          listed in the array according to its enum value.
 *                          For example, "Pop" is at index genres[POP]
 * Output argument: none
 * Return: none
 * Dependencies: string.h, stdio.h
 */
void playByArtist(Song *playlist, const char *artist, char* genres[]);

/**
 * Function: sortByGenre
 * Input argument: playlist - a double pointer to a list of songs
 * Output argument: playlist sorted by genre
 * Return: void
 * Dependencies: stdio.h - printf
 */
void sortByGenre(Song **playlist); 

/**
 * Function: detectCycle
 * Input argument: playlist - a pointer to a list of songs
 * Output argument: none
 * Return: true if the last song points to the head of the playlist,
 *         false otherwise
 * Dependencies: none
 */
bool detectCycle(Song *playlist);  

/**
 * Function: makePlaylistCircular
 * Input argument: playlist - a double pointer to a list of songs
 * Output argument: playlist is configured to be circular
 * Return: void
 * Dependencies: detectCycle
 */
void makePlaylistCircular(Song **playlist);

/**
 * Function: makePlaylistLinear
 * Input argument: playlist - a double pointer to a list of songs
 * Output argument: playlist is configured to be linear (last points to null)
 * Return: void
 * Dependencies: detectCycle
 */
void makePlaylistLinear(Song **playlist);

/**
 * Function: reversePlaylist
 * Input argument: playlist - a double pointer to a list of songs
 * Output argument: playlist is reversed
 * Return: void
 * Dependencies: detectCycle
 */
void reversePlaylist(Song **playlist);

#endif // MUSIC_LIB_H