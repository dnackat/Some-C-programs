// Helper functions for music

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "helpers.h"

// This is a function that calculates and return frequencies for a given ocatve and offset (compared to A)
// It gets called by the frequency function below.
double retfreq(int offset, int oct)
{
    int semitperoct = 12;
    int octdiff = oct - 4;
    int semitones = octdiff * semitperoct + offset;
    double mplier = round(pow(2.0, ((double) semitones / 12.0)) * 100000) / 100000;
    double freq = mplier * 440.0;
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
    // Get and store the octave from note
    int oct = 4;
    if (strlen(note) == 2)
    {
        oct = atoi(&note[1]);
    }
    else if (strlen(note) == 3)
    {
        oct = atoi(&note[2]);
    }

    // Use switch statement to calculate frequencies based on offsets (relative to A)
    double freq = 440.0;

    switch (note[0])
    {
        case 'A':
            freq = retfreq(0, oct);
            break;
        case 'B':
            freq = retfreq(2, oct);
            break;
        case 'C':
            freq = retfreq(-9, oct);
            break;
        case 'D':
            freq = retfreq(-7, oct);
            break;
        case 'E':
            freq = retfreq(-5, oct);
            break;
        case 'F':
            freq = retfreq(-4, oct);
            break;
        case 'G':
            freq = retfreq(-2, oct);
            break;
    }

    // If there's a sharp or a flat, modify frequency accordingly
    if (strlen(note) == 3)
    {
        switch (note[1])
        {
            case '#':
                freq = freq * pow(2.0, (1.0 / 12.0));
                break;
            case 'b':
                freq = freq / pow(2.0, (1.0 / 12.0));
                break;
        }
    }

    // Round the frequency to the nearest integer before returning
    return (int)(freq + 0.5);
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
