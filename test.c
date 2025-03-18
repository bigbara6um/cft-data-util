#include <time.h>
#include <string.h>

#include "data_util.h"

#define ARRAY_SIZE(x) ((sizeof(x)) / (sizeof((x)[0])))

int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv)
{
    /* Содержимое для исходных файлов */
    const StatData case_1_in_a[] = {
        {.id = 90889, .count = 13, .cost = 3.567, .primary = 0, .mode = 3},
        {.id = 90089, .count = 1, .cost = 88.90, .primary = 1, .mode = 0},
    };
    const StatData case_1_in_b[] = {
        {.id = 90089, .count = 13, .cost = 0.011, .primary = 0, .mode = 2},
        {.id = 90189, .count = 1000, .cost = 1.00003, .primary = 1, .mode = 2},
    };
    /* Ожидаемый результат обработки */
    const StatData case_1_out[] = {
        {.id = 90189, .count = 1000, .cost = 1.00003, .primary = 1, .mode = 2},
        {.id = 90889, .count = 13, .cost = 3.567, .primary = 0, .mode = 3},
        {.id = 90089, .count = 14, .cost = 88.911, .primary = 0, .mode = 2},
    };

    StoreDump((StatData *)&case_1_in_a[0], ARRAY_SIZE(case_1_in_a), "./test_1.bin");
    StoreDump((StatData *)&case_1_in_b[0], ARRAY_SIZE(case_1_in_b), "./test_2.bin");

    struct timespec start_ts;
    struct timespec end_ts;
    struct timespec diff_ts;

    clock_gettime(CLOCK_MONOTONIC, &start_ts);

    int result = system("./data-util ./test_1.bin ./test_2.bin ./test_3.bin");

    if (result == 0)
    {
        // data-util completed successfully
    }
    else
    {
        fputs("Test failed\n", stderr);
        return -1;
    }

    StatData *result_data;
    size_t result_records_count;
    LoadDump(&result_data, &result_records_count, "./test_3.bin");

    if (result_records_count != ARRAY_SIZE(case_1_out))
    {
        fputs("Test failed\n", stderr);
        return -1;
    }
    else
    {
        int r = memcmp(result_data, &case_1_out[0], ARRAY_SIZE(case_1_out) * sizeof(StatData));
        if (r == 0)
        {
            fputs("Test passed\n", stdout);
        }
        else
        {
            fputs("Test failed\n", stderr);
            return -1;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end_ts);

    diff_ts.tv_sec = end_ts.tv_sec - start_ts.tv_sec;
    diff_ts.tv_nsec = end_ts.tv_nsec - start_ts.tv_nsec;
    if (diff_ts.tv_nsec < 0)
    {
        diff_ts.tv_sec -= 1;
        diff_ts.tv_nsec = -diff_ts.tv_nsec;
    }
    printf("Time elapsed: %lds %ldns\n", diff_ts.tv_sec, diff_ts.tv_nsec);

    return 0;

    // StatData *new_data;
    // size_t records_count;
    // LoadDump(&new_data, &records_count, "./storage.bin");
}
