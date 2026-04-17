#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 100000

int countNodes(const char *input)
{
    int count = 0;

    while (*input && *input != '[')
        input++;
    if (*input == '[')
        input++;

    while (*input && *input != ']')
    {
        while (*input && (*input == ' ' || *input == ','))
            input++;
        if (*input == ']')
            break;

        if (strncmp(input, "null", 4) == 0)
        {
            input += 4;
        }
        else
        {
            int sign = 1;
            if (*input == '-')
            {
                sign = -1;
                input++;
            }
            while (*input >= '0' && *input <= '9')
            {
                input++;
            }

            count++;
        }
    }

    return count;
}

int main()
{
    char input[100000];

    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        printf("0");
        return 0;
    }

    input[strcspn(input, "\n")] = '\0';

    printf("%d\n", countNodes(input));

    return 0;
}
