// Helper functions for music

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "helpers.h"
// Defining this to use as signal to indicate runtime failure
#define EXIT_FAILURE 1

// This is a function that calculates and return frequencies for a given ocatve and offset (compared to A)
// It gets called by the frequency function below. This function helps avoid repeated typing when we compare the given string
// with all the possible notes
int retfreq(int offset, int oct)
{
    int semitperoct = 12;
    int octdiff = oct - 4;
    int semitones = octdiff * semitperoct + offset;
    double mplier = round(pow(2.00, ((double) semitones / 12.00)) * 100000) / 100000;
    int freq = (int)((mplier * 440) + 0.5);
    return freq;
}

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // Separate numerator and denominator using strtok. Store numerator in n
    int num = atoi(&fraction[0]);
    // Store denominator in d
    int den = atoi(&fraction[strlen(fraction) - 1]);
    //Convert fraction to float and round to nearest value
    float frac = roundf(((float) num / (float) den) * 1000) / 1000;

    // Divide by 1/8 (or, 0.125) to find out the number of eighths
    int eighths = (int)(frac / 0.125);

    // Return eighths
    return eighths;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    // Create an array of strings with all the notes for comparing with the input string
    const string notelist[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
    // Create an integer array of offsets (or, number of notes it takes to get to A, "-ve" if note falls before A)
    int offset[12];
    for (int i = 0; i < 12; i++)
    {
        offset[i] = (i + 1) - 10;
    }
    // Initialize frequency, freq, which is the return value of this function
    int freq = 440;
    // Case where the input string doesn't contain # or b
    if (strlen(note) == 2)
    {
        // Store number as octave and change type to int
        int oct = atoi(&note[1]);
        // Create a string (or, char array) with the alphabet part for comparison with the input string
        // using strcmp
        char cmp[2] = {note[0], '\0'};
        // Compare with all the possible notes without # or b and calculate frequency
        if (strcmp(notelist[0], cmp) == 0)
        {
            freq = retfreq(offset[0], oct);
        }
        else if (strcmp(notelist[2], cmp) == 0)
        {
            freq = retfreq(offset[2], oct);
        }
        else if (strcmp(notelist[4], cmp) == 0)
        {
            freq = retfreq(offset[4], oct);
        }
        else if (strcmp(notelist[5], cmp) == 0)
        {
            freq = retfreq(offset[5], oct);
        }
        else if (strcmp(notelist[7], cmp) == 0)
        {
            freq = retfreq(offset[7], oct);
        }
        else if (strcmp(notelist[9], cmp) == 0)
        {
            freq = retfreq(offset[9], oct);
        }
        else if (strcmp(notelist[11], cmp) == 0)
        {
            freq = retfreq(offset[11], oct);
        }
        else
        {
            // In the rare case that the input string is 2 characters long but doesn't match any note, exit with signal 1
            printf("Invalid input! :(\n");
            return 1;
            exit(EXIT_FAILURE);
        }
        // Return the frequency
        return freq;
    }
    // Case where the input string contains # or b
    else if (strlen(note) == 3)
    {
        // Store number as octave and change type to int
        int oct = atoi(&note[2]);
        // Create a string with the alphabet part (now, 2 chars long) for comparison with the input string
        // using strcmp
        char cmp[3] = {note[0], note[1], '\0'};
        // Compare with all the possible notes without # or b and calculate frequency
        if (strcmp(notelist[1], cmp) == 0)
        {
            freq = retfreq(offset[1], oct);
        }
        else if (strcmp(notelist[3], cmp) == 0)
        {
            freq = retfreq(offset[3], oct);
        }
        else if (strcmp(notelist[6], cmp) == 0)
        {
            freq = retfreq(offset[6], oct);
        }
        else if (strcmp(notelist[8], cmp) == 0)
        {
            freq = retfreq(offset[8], oct);
        }
        else if (strcmp(notelist[10], cmp) == 0)
        {
            freq = retfreq(offset[10], oct);
        }
        else if (strcmp(cmp, "Db") == 0)
        {
            freq = retfreq(offset[1], oct);
        }
        else if (strcmp(cmp, "Eb") == 0)
        {
            freq = retfreq(offset[3], oct);
        }
        else if (strcmp(cmp, "Gb") == 0)
        {
            freq = retfreq(offset[6], oct);
        }
        else if (strcmp(cmp, "Ab") == 0)
        {
            freq = retfreq(offset[8], oct);
        }
        else if (strcmp(cmp, "Bb") == 0)
        {
            freq = retfreq(offset[10], oct);
        }
        else
        {
            // In the rare case that the input string is 3 characters long but doesn't match any note, exit with signal 1
            printf("Invalid input! :(\n");
            return 1;
            exit(EXIT_FAILURE);
        }
        return freq;
    }
    else
    {
        // In the rare case that the input string is more than 3 characters long, exit with signal 1
        printf("Invalid input! :(\n");
        return 1;
        exit(EXIT_FAILURE);
    }
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // If the user hits enter (which is, "\n") to signify rest, the get_string function returns an empty string, ""
    // (which is, "\0"), hence the comparison
    if (strcmp(s, "\0") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
