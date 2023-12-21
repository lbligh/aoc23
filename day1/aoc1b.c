#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char *nums[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
int num_lens[] = {3, 3, 5, 4, 4, 3, 5, 5, 4};

char left_check(char *buffer, int left)
{
    for (int num = 0; num < 9; num++)
    {
        // printf("checking for %s...\n", nums[num]);
        int new = 0;
        while (nums[num][new] != '\0')
        {
            // printf("\t buffer[left+new] = %c, nums[num][new] = %c\n", buffer[left + new], nums[num][new]);
            if (nums[num][new] != buffer[left + new])
            {
                break;
            }
            new ++;
        }
        if (new == num_lens[num])
        {
            return (char)(num + 1 + '0');
        }
    }
    return 'a';
}

char right_check(char *buffer, int right)
{
    for (int num = 0; num < 9; num++)
    {
        // printf("checking for %s...\n", nums[num]);
        int new = 0;
        while (nums[num][new] != '\0')
        {
            // printf("\t buffer[right - num_lens[num] + 1 + new] = %c, nums[num][new] = %c\n", buffer[right - num_lens[num] + 1 + new], nums[num][new]);
            if (nums[num][new] != buffer[right - num_lens[num] + 1 + new])
            {
                break;
            }
            new ++;
        }
        if (new == num_lens[num])
        {
            return (char)(num + 1 + '0');
        }
    }
    return 'a';
}

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
        printf("Error! opening file\n");
        // Program exits if the file pointer returns NULL.
        exit(0);
    }

    const unsigned MAX_LENGTH = 1000;
    char buffer[MAX_LENGTH];

    long unsigned int count = 0;
    int line_count = 0;

    while (fgets(buffer, MAX_LENGTH, fptr))
    {
        printf("LINE %d: ", ++line_count);
        printf("%s", buffer);
        char leftmost = 'a';
        char rightmost = 'a';
        int lptr = 0;
        int rptr;
        for (rptr = 0; buffer[rptr] != '\n' && buffer[rptr] != EOF; rptr++)
            ;
        rptr--;

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
            if (lptr != -1)
            {
                if (isdigit(buffer[lptr]))
                {
                    leftmost = buffer[lptr];
                    lptr = -1;
                }
                else
                {
                    char l_string = left_check(buffer, lptr);
                    if (isdigit(l_string))
                    {
                        leftmost = l_string;
                        lptr = -1;
                    }
                }
            }
            if (rptr != -2)
            {
                if (isdigit(buffer[rptr]))
                {
                    rightmost = buffer[rptr];
                    rptr = -2;
                }
                else
                {
                    char r_string = right_check(buffer, rptr);
                    if (isdigit(r_string))
                    {
                        rightmost = r_string;
                        rptr = -2;
                    }
                }
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
