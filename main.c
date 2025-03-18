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
    const char *result_path = argv[3];

    if (access(a_path, R_OK) != 0)
    {
        fputs("The first file does not exist or cannot be accessed\n", stderr);
        return -1;
    }
    if (access(b_path, R_OK) != 0)
    {
        fputs("The second file does not exist or cannot be accessed\n", stderr);
        return -1;
    }

    if (access(result_path, R_OK) == 0)
    {
        fputs("The file for the results already exists\n", stderr);
        return -1;
    }

    StatData *a_data;
    StatData *b_data;
    StatData *result_data;
    size_t a_records_count;
    size_t b_records_count;
    size_t result_records_count = 0;

    LoadDump(&a_data, &a_records_count, a_path);
    LoadDump(&b_data, &b_records_count, b_path);

    JoinDump(a_data, a_records_count, b_data, b_records_count, &result_data, &result_records_count);

    free(a_data);
    free(b_data);

    SortDump(&result_data, result_records_count);

    StoreDump(result_data, result_records_count, result_path);

    size_t t = result_records_count;
    if (t > 10)
    {
        t = 10;
    }
    PrintTable(&result_data, t, stdout);

    free(result_data);

    return 0;
}
