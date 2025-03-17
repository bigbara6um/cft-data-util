#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "data_util.h"

#define ARRAY_SIZE(x) ((sizeof(x)) / (sizeof((x)[0])))

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        fputs("Invalid number of arguments\n", stderr);
        return -1;
    }

    const char *a_path = argv[1];
    const char *b_path = argv[2];

    if (access(a_path, R_OK) != 0)
    {
        fputs("The first file does not exist or cannot be accessed.\n", stderr);
        return -1;
    }
    if (access(b_path, R_OK) != 0)
    {
        fputs("The second file does not exist or cannot be accessed.\n", stderr);
        return -1;
    }

    const char *result_path = argv[3];

    return 0;
}
