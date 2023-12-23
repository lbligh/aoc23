#include <stdio.h>

int main(int argc, char **argv)
{
    int list1[5] = {1, 2, 3, 4, 5};
    // int list2[5] = {2, 3, 4, 5, 6};
    int(*ptr)[5];
    ptr = &list1;

    for (int i = 0; i < 5; i++)
    {
        printf("%d\n", (*ptr)[i]);
    }
}
