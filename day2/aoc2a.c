#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char **split(char *input, char *separator, int *len)
{
    char **result = 0;
    char tmp[strlen(input)];
    strcpy(tmp, input);
    size_t count = 0;
    char *token = strtok(tmp, separator);
    while (token)
    {
        token = strtok(NULL, separator);
        count++;
    }

    result = malloc(sizeof(char *) * count);
    *len = count;

    count = 0;
    token = strtok(input, separator);
    result[count] = token;
    while (token)
    {
        count++;
        token = strtok(NULL, separator);
        result[count] = token;
    }
    return result;
}

int main(int argc, char **argv)
{
    const int max_red = 12;
    const int max_green = 13;
    const int max_blue = 14;

    char *input_file = "inputa.txt";
    FILE *fptr;
    if ((fptr = fopen(input_file, "r")) == NULL)
    {
        printf("Error! opening file");
        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];

    long unsigned int count = 0;
    int test = 1;
    int sum_of_ids = 0;

    while (fgets(buffer, MAX_LENGTH, fptr))
    {
        printf("%d\n", test);
        test++;
        int game_id;
        printf("%s", buffer);
        char game_id_buff[MAX_LENGTH];
        strcpy(game_id_buff, buffer);

        // get game id
        int count = 0;
        char **splitted = split(game_id_buff, " ", &count);
        char game_id_temp[5];
        strncpy(game_id_temp, splitted[1], strlen(game_id_buff) - 2);
        game_id = atoi(game_id_temp);
        printf("Game ID = %d\n", game_id);

        for (int i = 2; i < count; i++)
        {
            printf("%s\n", splitted[i]);
        }

        free(splitted);
    }

    fclose(fptr);
    return 0;
}
