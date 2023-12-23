#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>

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

    long long unsigned int i_time = 0;
    long long unsigned int i_distance = 0;

    fgets(time, MAX_LENGTH, fptr);
    fgets(dst, MAX_LENGTH, fptr);

    time[strcspn(time, "\n")] = 0;
    dst[strcspn(dst, "\n")] = 0;

    fclose(fptr);

    printf("%s\n", time);
    printf("%s\n", dst);

    char *t_token = strtok(time, " ");

    int temp = 0;
    while (t_token != NULL)
    {
        // printf("%s, %d\n", t_token, temp);
        if (temp > 0)
        {
            // times[temp - 1] = atoi(t_token);
            i_time = i_time * pow(10, strlen(t_token)) + atoi(t_token);
            // printf("%lu\n", i_time);
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
            // distances[temp - 1] = atoi(d_token);
            i_distance = i_distance * pow(10, strlen(d_token)) + atoi(d_token);
            // printf("%lu\n", i_distance);
        }
        temp++;
        d_token = strtok(NULL, " ");
    }
    temp--;

    long long unsigned counter = 0;
    long long unsigned int dist = 0;
    printf("Time: %llu, Record: %llu\n", i_time, i_distance);
    for (long long unsigned int held = 0; held <= i_time; held++)
    {
        dist = held * (i_time - held);
        if (dist > i_distance)
        {
            // printf("\tHeld %lu, reached %lu\n", held, dist);
            counter++;
        }
    }

    printf("Count: %llu\n", counter);
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