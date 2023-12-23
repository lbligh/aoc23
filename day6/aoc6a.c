#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

int main(int argc, char **argv)
{
    char *input_file = "input.txt";
    FILE *fptr;
    if ((fptr = fopen(input_file, "r")) == NULL)
    {
        printf("Error! opening file");
        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    const unsigned MAX_LENGTH = 1000;
    char time[MAX_LENGTH];
    char dst[MAX_LENGTH];

    long unsigned int sup_count = 1;
    int times[4];
    int distances[4];

    fgets(time, MAX_LENGTH, fptr);
    fgets(dst, MAX_LENGTH, fptr);

    fclose(fptr);

    printf("%s", time);
    printf("%s", dst);

    char *t_token = strtok(time, " ");

    int temp = 0;
    while (t_token != NULL)
    {
        // printf("%s, %d\n", t_token, temp);
        if (temp > 0)
        {
            times[temp - 1] = atoi(t_token);
        }
        temp++;
        t_token = strtok(NULL, " ");
    }

    char *d_token = strtok(dst, " ");
    temp = 0;
    while (d_token != NULL)
    {
        // printf("%s, %d\n", d_token, temp);
        if (temp > 0)
        {
            distances[temp - 1] = atoi(d_token);
        }
        temp++;
        d_token = strtok(NULL, " ");
    }
    temp--;

    for (int game = 0; game < temp; game++)
    {
        int time = times[game];
        int record = distances[game];
        int counter = 0;
        int dist = 0;
        printf("Time: %d, Record: %d\n", time, record);
        for (int held = 0; held <= time; held++)
        {
            dist = held * (time - held);
            if (dist > record)
            {
                printf("\tHeld %d, reached %d\n", held, dist);
                counter++;
            }
        }
        sup_count *= counter;
    }

    printf("Multiplier: %lu\n", sup_count);
    /*
        game is t long
        hold for x
        then for t-x millis go at x mpms
        distance = speed * time = x * t-x
        */

    return 0;
}

// char tmp[MAX_LENGTH];
// strcpy(tmp, buffer);

// char *token;
// token = strtok(tmp, " :");
// char *start = token;

// while (token != NULL)
// {
//     int idx = (int)(token - start);
//     printf("%s\n", token);

//     token = strtok(NULL, " :");
// }