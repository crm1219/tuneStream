// header files
#include "music_lib.h"

/**
 * Function: createPlaylist (provided)
 * Input argument: playlist - a double pointer to a list of songs
 * Output argument: updated head of the playlist
 * Return: true if the playlist is successfully loaded, false if errors occur
 * Dependencies: addSong, stdio.h, string.h
 */
bool createPlaylist(Song **playlist) 
{
    // open the file
    FILE *file = fopen(FILENAME, "r");
    // if the file could not be open
    if (file == NULL)
    {
        // print a message
        printf("Could not open file %s\n", FILENAME);
        // end the function with an error code
        return false;
    }

    // create variables to hold the readings
    char line[256];
    char title[100];
    char artist[100];
    int genre;

    // if it is the end of the file after the header
    if (fgets(line, sizeof(line), file) == NULL)
    {
        // close the file
        fclose(file);
        // file is empty, return false
        return false;
    }

    // while there is another line to read
    while (fgets(line, sizeof(line), file) != NULL)
    {
        // parse the line using the comma separator
        char *token = strtok(line, ",");
        // if the token is not null
        if (token != NULL)
        {
            // copy the data into the title
            strcpy(title, token);
        }
        // move to the next token
        token = strtok(NULL, ",");
        // if the token is not null
        if (token != NULL)
        {
            // copy the data into the artist
            strcpy(artist, token);
        }
        // move to the next token
        token = strtok(NULL, ",");
        // if the token is not null
        if (token != NULL)
        {
            // copy into genre as an integer
            genre = atoi(token);
        }

        // add the song to the playlist casting Genre to the correct enum
        addSong(playlist, title, artist, (Genre)genre);
    }
    // close the file
    fclose(file);
    // return success
    return true;
}

/**
 * Task 1: Play the Playlist
 * Input argument: playlist - a pointer to a list of songs
 *                 genres - an array with the names of the genres. Genres are 
 *                          listed in the array according to its enum value.
 *                          For example, "Pop" is at index genres[POP]
 * Output argument: none
 * Return: none
 * Dependencies: stdio.h, ctype.h
 */
void play(Song *playlist, char* genres[])
{
    // check if there are no songs in the playlist
    if (playlist == NULL)
    {
        // if so, print a message
        printf("Nothing to be played right now. Add songs to continue.\n");
    }
    // otherwise, print out the songs playing
    else
    {
        // create a pointer to track the current song playing and set it to the
        // first song
        Song* current = playlist;
        // create an integer variable to store the song count and set equal to
        // zero
        int count = 0;
        // loop while there are still songs in the playlist or, if the playlist
        // is continuous, until max songs have been played
        while (current != NULL && count < MAX_SONGS)
        {
            // print out the current song playing
            printf("Playing '%s' by '%s' (Genre: %s) ...\n", current->title,
            current->artist, genres[current->genre]);
            // move to next song
            current = current->next;
            // increment count
            count++;
            // check if count equals maximum songs
            if (count == MAX_SONGS)
            {
                // if so, create character variable to store user input
                char answer;
                // ask if the user is still listening
                printf("Are you still listening [Y|N]? ");
                // read their answer
                scanf(" %c", &answer);
                // convert their answer to uppercase
                answer = toupper(answer);
                // loop while the answer is invalid
                while (answer != 'Y' && answer != 'N')
                {
                    // print message requesting new input
                    printf("\nI didn't get that. Please type Y to continue \
listening or N to stop: ");
                    // read their answer
                    scanf(" %c", &answer);
                    // convert their answer to uppercase
                    answer = toupper(answer);
                }
                // check if they want to continue playing
                if (answer == 'Y')
                {
                    // if so, reset count to zero so the while loop continues
                    count = 0;
                }
            }
        }
    }
}


/**
 * Task 2: Adding a New Song to the Playlist
 * Input argument: playlist - a double pointer to a list of songs
 *                 title - a string with the title of the song
 *                 artist - a string with the artist of the song
 *                 genre - a Genre enum for the genre of the song
 * Output argument: updated head of the playlist, if needed
 * Return: true if the song is successfully added, false otherwise
 * Dependencies: stdlib.h, stdio.h, string.h
 */
bool addSong(
    Song **playlist, const char *title, const char *artist, Genre genre)
{
    // check if song genre is invalid
    if (genre < 0 || genre >= GENRE_COUNT)
    {
        // print error message
        printf("Invalid genre. Song not added.\n");
        // return false
        return false;
    }
    // otherwise, dynamically allocate new song
    Song* newSong = (Song*)malloc(sizeof(Song));
    // copy the given title into the song's title
    strcpy(newSong->title, title);
    // copy the given artist into the song's artist name
    strcpy(newSong->artist, artist);
    // set the song's genre to the given genre
    newSong->genre = genre;
    // check if there are no songs in the playlist so far
    if (*playlist == NULL)
    {
        // if so, place the new song in the playlist
        *playlist = newSong;
        // set its pointer to the next song equal to null
        newSong->next = NULL;
    }
    // otherwise, loop to the end of the playlist
    else
    {
        // create pointer to keep track of current song
        Song* currentSong = *playlist;
        // loop until the last song is reached
        while (currentSong->next != NULL)
        {
            // move ahead by one song
            currentSong = currentSong->next;
        }
        // place the new song at the end of the playlist
        currentSong->next = newSong;
        // set its pointer to the next song equal to null
        newSong->next = NULL;
    }
    // return success
    return true;
}


/**
 * Task 3: Removing a Song from the Playlist
 * Input argument: playlist - a double pointer to a list of songs
 *                 title - a string with the title of the song
 * Output argument: updated head of the playlist, if needed
 * Return: true if the song is successfully removed, false otherwise
 * Dependencies: stdlib.h, stdio.h, string.h
 */
bool removeSong(Song **playlist, const char *title)
{
    // check if playlist is empty
    if (*playlist == NULL)
    {
        // if so, return false
        return false;
    }
    // create variable to store current song
    Song* current = *playlist;
    // check if song is at the beginning of the playlist
    if (strcmp(title, current->title) == 0)
    {
        // if so, shift the playlist so it points to the second song
        *playlist = current->next;
        // free the first song
        free(current);
        // return true
        return true;
    }
    // loop while the title has not been found in the next song and the next
    // song is not null
    while (current->next != NULL && strcmp(title, (current->next)->title) != 0)
    {
        // move ahead by one song
        current = current->next;
    }
    // check if next song is null, indicating the title has not been found
    if (current->next == NULL)
    {
        // if so, print error message
        printf("Song '%s' is not in the list.\n", title);
        // return false
        return false;
    }
    // otherwise, delete the song
    else
    {
        // create a pointer that tracks the song to be deleted
        Song* delete = current->next;
        // have the current song point to the song following the song to be
        // deleted (or to null, if the deleted song is the last song)
        current->next = delete->next;
        // free the song
        free(delete);
        // return success
        return true;
    }
}


/**
 * Task 4: Shuffle Play
 * Input argument: playlist - a pointer to a list of songs
 *                 genres - an array with the names of the genres. Genres are 
 *                          listed in the array according to its enum value.
 *                          For example, "Pop" is at index genres[POP]
 * Output argument: none
 * Return: none
 * Dependencies: stdlib.h, stdio.h
 */
void playShuffle(Song *playlist, char* genres[])
{
    // create variable to store current song
    Song* current = playlist;
    // create variable to store length of playlist
    int length = 0;
    // loop through playlist
    while (current != NULL)
    {
        // increment length
        length++;
        // move ahead to next song
        current = current->next;
    }
    // set current pointer back to the beginning of the playlist
    current = playlist;
    // allocate memory for a shuffled list of song pointers
    Song** shuffledList = (Song**)malloc(length*sizeof(Song*));
    // loop through shuffled list
    for (int i = 0; i < length; i++)
    {
        // set each value in it equal to null
        shuffledList[i] = NULL;
    }
    // create variable to store index in the shuffled list
    int index;
    // loop through playlist
    while (current != NULL)
    {
        // calculate random index
        index = rand() % length;
        // if there is already a song at that index, loop until an unused
        // index is reached
        while (shuffledList[index] != NULL)
        {
            // calculate new random index
            index = rand() % length;
        }
        // place the current song at that index
        shuffledList[index] = current;
        // move ahead to the next song
        current = current->next;
    }
    // loop through shuffled playlist
    for (int i = 0; i < length; i++)
    {
        // print each song in the playlist
        printf("Playing '%s' by '%s' (Genre: %s) ...\n", 
        shuffledList[i]->title, shuffledList[i]->artist, 
        genres[shuffledList[i]->genre]);
    }
    // free the memory used to create the shuffled list
    free(shuffledList);
}


/**
 * Task 5: Play Songs by Artist
 * Input argument: playlist - a pointer to a list of songs
 *                 artist - a string representing the artist name
 *                 genres - an array with the names of the genres. Genres are 
 *                          listed in the array according to its enum value.
 *                          For example, "Pop" is at index genres[POP]
 * Output argument: none
 * Return: none
 * Dependencies: string.h, stdio.h
 */
void playByArtist(Song *playlist, const char *artist, char* genres[])
{
    // create variable to store current song
    Song* current = playlist;
    // create variable to indicate if the artist's name has been found
    bool artistFound = false;
    // loop through playlist
    while (current != NULL) 
    {
        // check if the current song is by the given artist
        if (strcmp(current->artist, artist) == 0)
        {
            // if so, print out that song
            printf("Playing '%s' by '%s' (Genre: %s) ...\n", current->title,
            artist, genres[current->genre]);
            // set artist found variable to true
            artistFound = true;
        }
        // move ahead to next song
        current = current->next;
    }
    // check if the artist is not in the playlist
    if (!artistFound)
    {
        // if so, print a message to the users
        printf("Nothing to be played by %s right now. Add songs to \
continue.\n", artist);
    }
}


/**
 * Task 6: Sorting the Playlist by Genre
 * Input argument: playlist - a double pointer to a list of songs
 * Output argument: playlist sorted by genre
 * Return: void
 * Dependencies: stdio.h - printf
 */
void sortByGenre(Song **playlist)
{
    // check if no songs are in the playlist
    if (*playlist == NULL)
    {
        // if so, print message to user
        printf("It is quiet here. Add songs to continue.\n");
    }
    // otherwise, sort the playlist
    else
    {
        // create variable to store number of swaps
        int swaps = 1;
        // create pointer to current song
        Song* current = *playlist;
        // create pointer to first song being swapped
        Song* swap1 = NULL;
        // create pointer to second song being swapped
        Song* swap2 = NULL;
        // loop until no swaps are needed
        while (swaps > 0)
        {
            // set swaps equal to zero
            swaps = 0;
            // loop until the second-to-last song is reached
            while ((current->next)->next != NULL)
            {
                // check if the first and second songs need to be swapped
                if (current == *playlist && current->genre > 
                (current->next)->genre)
                {
                    // if so, set swap1 to the first song
                    swap1 = current;
                    // set swap2 to the second song
                    swap2 = current->next;
                    // have the first song point to the song after the second
                    swap1->next = swap2->next;
                    // have the second song point to the first
                    swap2->next = swap1;
                    // increment number of swaps
                    swaps ++;
                    // move current pointer to second song
                    current = swap1;
                    // have playlist pointer point to the new first song
                    *playlist = swap2;
                }
                // otherwise, the current pointer is in the middle of the 
                // playlist
                else 
                {
                    // set swap1 to the first song after current
                    swap1 = current->next;
                    // set swap2 to the second song after current
                    swap2 = (current->next)->next;
                    // check if swap1's genre exceeds swap2's
                    if (swap1->genre > swap2->genre)
                    {
                        // if so, have current point to the second song
                        current->next = swap2;
                        // have the first song point to the song after the 
                        // second song
                        swap1->next = swap2->next;
                        // have the second song point to the first
                        swap2->next = swap1;
                        // have the current pointer move to the second song
                        current = swap2;
                        // increment number of swaps
                        swaps++;
                    }
                    // if not, no swaps need to be performed
                    else
                    {
                        // have current point to the next song in the playlist
                        current = current->next;
                    }
                }
            }
            // reset current to point to the beginning of the playlist
            current = *playlist;
        }
        // print message to user
        printf("Playlist will play by genre from here on!\n");
    }
}


/**
 * Task 7: Detecting a Cycle in the Playlist
 * Input argument: playlist - a pointer to a list of songs
 * Output argument: none
 * Return: true if the last song points to the head of the playlist,
 *         false otherwise
 * Dependencies: none
 */
bool detectCycle(Song *playlist)
{
    // create pointer to current song
    Song* currentSong = playlist;
    // loop through playlist
    while (currentSong != NULL)
    {
        // move ahead by one song
        currentSong = currentSong->next;
        // check if the current variable points to the same song as the
        // head of the playlist
        if (currentSong == playlist)
        {
            // if so, the playlist is on a loop, so return true
            return true;
        }
    }
    // return false if the end of the playlist has been reached
    return false;
}


/**
 * Task 8: Play Non-Stop
 * Input argument: playlist - a double pointer to a list of songs
 * Output argument: playlist is configured to be circular
 * Return: void
 * Dependencies: detectCycle, stdio.h
 */
void makePlaylistCircular(Song **playlist)
{
    // check if no songs are in the playlist
    if (*playlist == NULL)
    {
        // if so, print a message to the user
        printf("It is quiet here. Add songs to continue.\n");
    }
    // check if music is already playing continuously
    else if (detectCycle(*playlist))
    {
        // if so, print a message to the user
        printf("Music is already playing continuously!\n");
    }
    // otherwise, change the playlist to be continuous
    else
    {
        // create a pointer to the current song
        Song* current = *playlist;
        // loop until the last song is reached
        while (current->next != NULL)
        {
            // move ahead by one song
            current = current->next;
        }
        // have the last song point to the head of the playlist
        current->next = *playlist;
        // print message to user
        printf("Music will play continuously from here on!\n");
    }
}

/**
 * Task 9: Play Up to the End
 * Input argument: playlist - a double pointer to a list of songs
 * Output argument: playlist is configured to be linear (last points to null)
 * Return: void
 * Dependencies: detectCycle
 */
void makePlaylistLinear(Song **playlist)
{
    // check if no songs are in the playlist
    if (*playlist == NULL)
    {
        // if so, print a message to the user
        printf("It is quiet here. Add songs to continue.\n");
    }
    // check if music is already playing to the last song
    else if (!detectCycle(*playlist))
    {
        // if so, print a message to the user
        printf("Music is already playing up to the last song!\n");
    }
    // otherwise, change the playlist to be linear
    else
    {
        // create a pointer to the current song
        Song* current = *playlist;
        // loop until the last song is reached before the playlist repeats
        while (current->next != *playlist)
        {
            // move ahead by one song
            current = current->next;
        }
        // have the last song point to null
        current->next = NULL;
        // print message to user
        printf("Music will stop playing when the playlist is over!\n");
    }
}


/**
 * Task 10: Reversing the Playlist
 * Input argument: playlist - a double pointer to a list of songs
 * Output argument: playlist is reversed
 * Return: void
 * Dependencies: detectCycle
 */
void reversePlaylist(Song **playlist)
{
    // create a pointer to the current song
    Song* current = *playlist;
    // check if the playlist is continuous
    if (detectCycle(*playlist))
    {
        // loop until the last song is reached before the playlist repeats
        while (current->next != *playlist)
        {
            // move ahead by one song
            current = current->next;
        }
        // have the last song point to null
        current->next = NULL;
    }
    // reset current to the head of the playlist
    current = *playlist;
    // create pointer to previous song
    Song* previous = NULL;
    // create pointer to next song
    Song* next = current->next;
    // loop until the last song in the playlist is reached
    while (current->next != NULL)
    {
        // check if the loop is only at the first song
        if (previous == NULL)
        {
            // have the first song in the playlist point to null
            current->next = NULL;
            // have previous point to the first song
            previous = current;
            // move current pointer to the next song
            current = next;
            // move next pointer to the song after current
            next = current->next;
        }
        // otherwise, the loop is in the middle of the playlist
        else
        {
            // have the current song point to the song before it
            current->next = previous;
            // have previous point to the current song
            previous = current;
            // have current point to the next song
            current = next;
            // move the next pointer to the next song
            next = current->next;
        }
    }
    // have the last song point to the previous song
    current->next = previous;
    // have the playlist point to the last song, so it's now at the head of
    // the playlist
    *playlist = current;
}

