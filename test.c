#include "data_util.h"

#define ARRAY_SIZE(x) ((sizeof(x)) / (sizeof((x)[0])))

int main()
{
    StatData test_array_1[] = {

        {.id = 0, .count = 1381, .cost = 870.752590, .mode = 2, .primary = 0},
        {.id = 1, .count = 4376, .cost = 714.571390, .mode = 1, .primary = 1},
        {.id = 2, .count = 7766, .cost = 618.937060, .mode = 4, .primary = 0},
        {.id = 3, .count = 3744, .cost = 500.870560, .mode = 0, .primary = 1},
        {.id = 4, .count = 1881, .cost = 739.767540, .mode = 1, .primary = 0},
        {.id = 5, .count = 8201, .cost = 968.939850, .mode = 1, .primary = 0},
        {.id = 6, .count = 9381, .cost = 822.825560, .mode = 5, .primary = 1},
        {.id = 7, .count = 7807, .cost = 501.628830, .mode = 1, .primary = 0},
        {.id = 8, .count = 8600, .cost = 350.797640, .mode = 5, .primary = 1},
        {.id = 9, .count = 3638, .cost = 461.379120, .mode = 4, .primary = 1},
        {.id = 10, .count = 5277, .cost = 642.761720, .mode = 3, .primary = 1},
        {.id = 11, .count = 8606, .cost = 186.353330, .mode = 4, .primary = 0},
        {.id = 12, .count = 7286, .cost = 617.401850, .mode = 4, .primary = 0},
        {.id = 13, .count = 3312, .cost = 498.206490, .mode = 0, .primary = 0},
        {.id = 14, .count = 7760, .cost = 103.677850, .mode = 4, .primary = 1},
        {.id = 15, .count = 4107, .cost = 404.465880, .mode = 3, .primary = 0},
        {.id = 16, .count = 421, .cost = 452.128830, .mode = 2, .primary = 0},
        {.id = 17, .count = 2477, .cost = 881.470850, .mode = 1, .primary = 1},
        {.id = 18, .count = 1762, .cost = 660.509120, .mode = 5, .primary = 1},
        {.id = 19, .count = 7663, .cost = 904.923060, .mode = 5, .primary = 0},
        {.id = 20, .count = 5553, .cost = 569.529130, .mode = 3, .primary = 0},
        {.id = 21, .count = 5090, .cost = 574.614920, .mode = 5, .primary = 1},
        {.id = 22, .count = 2196, .cost = 41.410290, .mode = 5, .primary = 0},
        {.id = 23, .count = 4617, .cost = 871.876700, .mode = 1, .primary = 1},
        {.id = 24, .count = 2123, .cost = 664.977650, .mode = 1, .primary = 0},
        {.id = 25, .count = 9760, .cost = 709.327750, .mode = 0, .primary = 0},
        {.id = 26, .count = 9884, .cost = 688.797750, .mode = 3, .primary = 1},
        {.id = 27, .count = 2358, .cost = 831.581420, .mode = 3, .primary = 0},
        {.id = 28, .count = 4828, .cost = 702.539210, .mode = 1, .primary = 1},
        {.id = 29, .count = 9393, .cost = 218.105280, .mode = 5, .primary = 1},
        {.id = 30, .count = 287, .cost = 16.231060, .mode = 2, .primary = 1},
        {.id = 31, .count = 1814, .cost = 985.397490, .mode = 5, .primary = 0},
        {.id = 32, .count = 3171, .cost = 529.468390, .mode = 0, .primary = 1},
        {.id = 33, .count = 1222, .cost = 912.229660, .mode = 3, .primary = 1},
        {.id = 34, .count = 4700, .cost = 335.774870, .mode = 0, .primary = 1},
        {.id = 35, .count = 8263, .cost = 850.497040, .mode = 5, .primary = 0},
        {.id = 36, .count = 8751, .cost = 329.405140, .mode = 2, .primary = 1},
        {.id = 37, .count = 8446, .cost = 671.547190, .mode = 5, .primary = 0},
        {.id = 38, .count = 3620, .cost = 387.456810, .mode = 0, .primary = 0},
        {.id = 39, .count = 9678, .cost = 4.086800, .mode = 4, .primary = 0},
    };
    StatData test_array_2[] = {
        {.id = 40, .count = 57, .cost = 106.711150, .mode = 3, .primary = 1},
        {.id = 41, .count = 175, .cost = 372.757510, .mode = 1, .primary = 1},
        {.id = 42, .count = 8302, .cost = 747.930770, .mode = 0, .primary = 1},
        {.id = 43, .count = 708, .cost = 674.428480, .mode = 2, .primary = 0},
        {.id = 44, .count = 1595, .cost = 764.361460, .mode = 0, .primary = 1},
        {.id = 45, .count = 6384, .cost = 881.829170, .mode = 1, .primary = 1},
        {.id = 46, .count = 2557, .cost = 796.918870, .mode = 0, .primary = 0},
        {.id = 47, .count = 6320, .cost = 55.440750, .mode = 0, .primary = 1},
        {.id = 48, .count = 7608, .cost = 599.828540, .mode = 2, .primary = 0},
        {.id = 49, .count = 7423, .cost = 332.787580, .mode = 2, .primary = 1},
        {.id = 50, .count = 5401, .cost = 24.992320, .mode = 2, .primary = 1},
        {.id = 51, .count = 4923, .cost = 285.206680, .mode = 0, .primary = 1},
        {.id = 52, .count = 8208, .cost = 246.456880, .mode = 3, .primary = 1},
        {.id = 53, .count = 6731, .cost = 794.920410, .mode = 4, .primary = 1},
        {.id = 54, .count = 6624, .cost = 563.697240, .mode = 3, .primary = 0},
        {.id = 55, .count = 734, .cost = 598.034430, .mode = 3, .primary = 0},
        {.id = 56, .count = 9034, .cost = 684.708650, .mode = 4, .primary = 0},
        {.id = 57, .count = 8783, .cost = 269.053960, .mode = 4, .primary = 1},
        {.id = 58, .count = 4993, .cost = 882.471040, .mode = 3, .primary = 1},
        {.id = 59, .count = 4489, .cost = 231.912520, .mode = 3, .primary = 1},
        {.id = 60, .count = 927, .cost = 870.732090, .mode = 1, .primary = 1},
        {.id = 61, .count = 967, .cost = 856.147770, .mode = 5, .primary = 0},
        {.id = 62, .count = 5379, .cost = 464.292620, .mode = 3, .primary = 0},
        {.id = 63, .count = 2649, .cost = 596.001560, .mode = 3, .primary = 1},
        {.id = 64, .count = 3956, .cost = 121.870830, .mode = 4, .primary = 0},
        {.id = 65, .count = 9316, .cost = 454.097590, .mode = 3, .primary = 1},
        {.id = 66, .count = 413, .cost = 333.884050, .mode = 4, .primary = 0},
        {.id = 67, .count = 4234, .cost = 161.267180, .mode = 5, .primary = 1},
        {.id = 68, .count = 687, .cost = 827.682030, .mode = 5, .primary = 0},
        {.id = 69, .count = 2745, .cost = 650.848130, .mode = 3, .primary = 0},
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

#if 0
    StatData *result_data;
    size_t result_records_count = 0;

    JoinDump(
        &case_1_in_a[0], ARRAY_SIZE(case_1_in_a),
        &case_1_in_b[0], ARRAY_SIZE(case_1_in_b),
        &result_data, &result_records_count);

    SortDump(&result_data, result_records_count);
    PrintTable(&result_data, 2, stdout);

    free(result_data);
#endif
    StoreDump(test_array_1, ARRAY_SIZE(test_array_1), "./storage_1.bin");
    StoreDump(test_array_2, ARRAY_SIZE(test_array_2), "./storage_2.bin");

    return 0;

    // StatData *new_data;
    // size_t records_count;
    // LoadDump(&new_data, &records_count, "./storage.bin");
}
