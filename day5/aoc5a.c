#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

enum Stage
{
    SEED_DEFS,
    SEED_TO_SOIL,
    SOIL_TO_FERTILIZER,
    FERTILIZER_TO_WATER,
    WATER_TO_LIGHT,
    LIGHT_TO_TEMP,
    TEMP_TO_HUMIDITY,
    HUMIDITY_TO_LOCATION
};

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
    enum Stage state = 0;
    const unsigned MAX_LENGTH = 1000;
    char buffer[MAX_LENGTH];

    long unsigned int sup_count = 0;
    int line_no = 0;

    unsigned long long seeds[100] = {0};
    int num_desired_seeds = 0;

    unsigned long long soils[100] = {0};
    unsigned long long ferts[100] = {0};
    unsigned long long waters[100] = {0};
    unsigned long long lights[100] = {0};
    unsigned long long temps[100] = {0};
    unsigned long long hums[100] = {0};
    unsigned long long locs[100] = {0};

    while (fgets(buffer, MAX_LENGTH, fptr))
    {
        printf("%s", buffer);
        // buffer[strcspn(buffer, "\n")] = 0;
        if (line_no == 0)
        {
            char *token = strtok(buffer, " :");

            while (token != NULL)
            {
                // printf("%s\n", token);
                if (num_desired_seeds > 0)
                    seeds[num_desired_seeds - 1] = strtoull(token, NULL, 10);
                num_desired_seeds++;
                token = strtok(NULL, " :");
            }
            num_desired_seeds--;
        }
        else
        {
            if (buffer[0] == '\n')
            {
                ;
            }
            else if (isalpha(buffer[0]))
            {
                state++;
            }
            else
            {
                unsigned long long dest;
                unsigned long long src;
                unsigned long long len;

                char *token = strtok(buffer, " ");
                dest = strtoull(token, NULL, 10);
                token = strtok(NULL, " :");
                src = strtoull(token, NULL, 10);
                token = strtok(NULL, " :");
                len = strtoull(token, NULL, 10);

                unsigned long long(*last)[100];
                unsigned long long(*current)[100];

                for (int i = 0; i < num_desired_seeds; i++)
                {
                    switch (state)
                    {
                    case SEED_TO_SOIL:
                        last = &seeds;
                        current = &soils;
                        break;
                    case SOIL_TO_FERTILIZER:
                        last = &soils;
                        current = &ferts;
                        break;
                    case FERTILIZER_TO_WATER:
                        last = &ferts;
                        current = &waters;
                        break;
                    case WATER_TO_LIGHT:
                        last = &waters;
                        current = &lights;
                        break;
                    case LIGHT_TO_TEMP:
                        last = &lights;
                        current = &temps;
                        break;
                    case TEMP_TO_HUMIDITY:
                        last = &temps;
                        current = &hums;
                        break;
                    case HUMIDITY_TO_LOCATION:
                        last = &hums;
                        current = &locs;
                        break;
                    default:
                        break;
                    }

                    if ((*last)[i] >= src && (*last)[i] < (src + len))
                    {
                        (*current)[i] = dest + (*last)[i] - src;
                    }
                    else
                    {
                        if ((*current)[i] == 0)
                            (*current)[i] = (*last)[i];
                    }
                }
                // for (int seed = 0; seed < num_desired_seeds; seed++)
                // {
                //     printf("%llu, ", seeds[seed]);
                //     printf("%llu, ", soils[seed]);
                //     printf("%llu, ", ferts[seed]);
                //     printf("%llu, ", waters[seed]);
                //     printf("%llu, ", lights[seed]);
                //     printf("%llu, ", temps[seed]);
                //     printf("%llu, ", hums[seed]);
                //     printf("%llu, ", locs[seed]);
                //     printf("\n");
                // }
            }
        }

        line_no++;
    }
    unsigned long long min = ULLONG_MAX;
    unsigned long long min_seed;
    for (int seed = 0; seed < num_desired_seeds; seed++)
    {
        // printf("%llu, ", seeds[seed]);
        // printf("%llu, ", soils[seed]);
        // printf("%llu, ", ferts[seed]);
        // printf("%llu, ", waters[seed]);
        // printf("%llu, ", lights[seed]);
        // printf("%llu, ", temps[seed]);
        // printf("%llu, ", hums[seed]);
        // printf("%llu, ", locs[seed]);
        // printf("\n");
        if (locs[seed] < min)
        {
            min = locs[seed];
            min_seed = seeds[seed];
        }
    }

    printf("Closest Loc is %llu for seed %llu\n", min, min_seed);
    // close the file
    fclose(fptr);
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