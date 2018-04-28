#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define EXIT_FAILURE 1

int retfreq (int offset, int oct)
{
    int semitperoct = 12;
    int octdiff = oct - 4;
    int semitones = octdiff*semitperoct + offset;
    double mplier = round(pow(2.00,((double) semitones/12.00)) * 100000)/100000;
    int freq = (int) ((mplier*440) + 0.5);
    return freq;
}

int frequency(string note)
{
    const string notelist[] = {"C","C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
    int offset[12];
    for (int i = 0; i < 12; i++)
    {
        offset[i] = (i + 1) - 10;
    }
    int freq = 440;
    if (strlen(note) == 2)
    {
        int oct = atoi(&note[1]);
        char cmp[2] = {note[0], '\0'};
        if (strcmp(notelist[0],cmp) == 0)
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
            printf("Invalid input! :(\n");
            return 1;
            exit(EXIT_FAILURE);
        }
        return freq;
    }
    else if (strlen(note) == 3)
    {
        int oct = atoi(&note[2]);
        char cmp[3] = {note[0], note[1], '\0'};
        if (strcmp(notelist[1],cmp) == 0)
        {
            freq = retfreq(offset[1], oct);
        }
        else if (strcmp(notelist[3],cmp) == 0)
        {
            freq = retfreq(offset[3], oct);
        }
        else if (strcmp(notelist[6],cmp) == 0)
        {
            freq = retfreq(offset[6], oct);
        }
        else if (strcmp(notelist[8],cmp) == 0)
        {
            freq = retfreq(offset[8], oct);
        }
        else if (strcmp(notelist[10],cmp) == 0)
        {
            freq = retfreq(offset[10], oct);
        }
        else if (strcmp(cmp,"Db") == 0)
        {
            freq = retfreq(offset[1], oct);
        }
        else if (strcmp(cmp,"Eb") == 0)
        {
            freq = retfreq(offset[3], oct);
        }
        else if (strcmp(cmp,"Gb") == 0)
        {
            freq = retfreq(offset[6], oct);
        }
        else if (strcmp(cmp,"Ab") == 0)
        {
            freq = retfreq(offset[8], oct);
        }
        else if (strcmp(cmp,"Bb") == 0)
        {
            freq = retfreq(offset[10], oct);
        }
        else
        {
            printf("Invalid input! :(\n");
            return 1;
            exit(EXIT_FAILURE);
        }
        return freq;
    }
    else
    {
        printf("Invalid input! :(\n");
        return 1;
        exit(EXIT_FAILURE);
    }
}

int main(void)
{
    string n = get_string("Enter a string: ");
    string m = strtok(n,"@");
    printf("The frequency is: %d\n", frequency(m));
}