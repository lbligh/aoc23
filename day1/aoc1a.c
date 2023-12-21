#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int to_int(char a, char b)
{
    return (a - '0') * 10 + b - '0';
}

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
    char buffer[MAX_LENGTH];

    long unsigned int count = 0;

    while (fgets(buffer, MAX_LENGTH, fptr))
    {
        printf("%s", buffer);
        char leftmost = 'a';
        int rightmost = 'a';
        int lptr = 0;
        int rptr;
        for (rptr = 0; buffer[rptr] != '\n' && buffer[rptr] != EOF; rptr++)
            ;
        rptr--;
        // printf("%c, %c, ", buffer[lptr], buffer[rptr]);
        while (1)
        {

            if (leftmost != 'a' && rightmost != 'a')
            {
                printf("%c, %c, ", leftmost, rightmost);
                int cal = to_int(leftmost, rightmost);
                printf("%d\n", cal);
                count += cal;
                break;
            }
            if (isdigit(buffer[lptr]))
            {
                leftmost = buffer[lptr];
                lptr = -1;
            }
            if (isdigit(buffer[rptr]))
            {
                rightmost = buffer[rptr];
                rptr = -2;
            }
            if (lptr == rptr)
            {
                break;
            }
            if (lptr != -1)
                lptr++;
            if (rptr != -2)
                rptr--;
        }
    }
    printf("Count = %lu\n", count);
    // close the file
    fclose(fptr);
    return 0;
}
