#include "data_util.h"

int main()
{
    StatData test_array[] = {
        {.id = 1, .count = 2, .mode = 3, .primary = 1},
        {.id = 23, .count = 100, .mode = 2, .primary = 1},
        {.id = 354, .count = 210, .mode = 3, .primary = 0},
    };

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

        StatData *result_data;
    size_t result_records_count = 0;

    JoinDump(
        &case_1_in_a[0], ARRAY_SIZE(case_1_in_a),
        &case_1_in_b[0], ARRAY_SIZE(case_1_in_b),
        &result_data, &result_records_count);

    SortDump(&result_data, result_records_count);
    PrintTable(&result_data, 2, stdout);

    free(result_data);

    // StoreDump(test_array, ARRAY_SIZE(test_array), "./storage.bin");

    // StatData *new_data;
    // size_t records_count;
    // LoadDump(&new_data, &records_count, "./storage.bin");
}
