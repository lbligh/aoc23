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

    long unsigned int sup_count = 0;

    while (fgets(buffer, MAX_LENGTH, fptr))
    {
        buffer[strcspn(buffer, "\n")] = 0;

        char tmp[MAX_LENGTH];
        strcpy(tmp, buffer);

        printf("%s", buffer);
        char *token;
        token = strtok(tmp, " :");
        char *start = token;
        int count = 0;
        int reached_sep = 0;
        int winning[100] = {0};
        int winning_idx = 0;
        int card[100] = {0};
        int card_idx = 0;
        while (token != NULL)
        {
            int idx = (int)(token - start);
            // printf("%s, %d, %d\n", token, atoi(token), idx);
            if (count > 1)
            {
                if (!strcmp(token, "|"))
                {
                    reached_sep = 1;
                }
                else if (!reached_sep)
                {
                    winning[winning_idx] = atoi(token);
                    winning_idx++;
                }
                else if (reached_sep)
                {
                    card[card_idx] = atoi(token);
                    card_idx++;
                }
            }
            count++;
            token = strtok(NULL, " :");
        }

        // printf("Card numbers: \n");
        int score = 0;
        for (int card_no = 0; card_no < card_idx; card_no++)
        {
            for (int winning_no = 0; winning_no < winning_idx; winning_no++)
            {
                if (card[card_no] == winning[winning_no])
                {
                    // printf("%d is winning\n", card[card_no]);
                    if (score)
                        score *= 2;
                    else
                        score = 1;
                }
            }
        }
        printf(" Score = %d\n", score);
        sup_count += score;
    }
    printf("Count = %lu\n", sup_count);
    // close the file
    fclose(fptr);
    return 0;
}
