#include <stdlib.h>
#include <stdio.h>

typedef struct StatData
{
    long id;
    int count;
    float cost;
    unsigned int primary : 1;
    unsigned int mode : 3;
} StatData;

typedef enum ErrorCodes
{
    OK = 0,
    CANT_OPEN_FILE,
    ALLOCATION_ERROR,
    FILE_ERROR,
} ErrorCodes;

// for tests only
#define CHUNK_SIZE (sizeof(StatData) * 16)

// Store data to file
int StoreDump(StatData *data_ptr, size_t record_count, const char *file_path)
{
    FILE *fd = fopen(file_path, "wb");

    if (fd == NULL)
    {
        return CANT_OPEN_FILE;
    }

    // write data to file chunk by chunk
    size_t records_left = record_count;
    while (1)
    {
        size_t records_to_write = CHUNK_SIZE / sizeof(StatData);
        if (records_left < records_to_write)
        {
            records_to_write = records_left;
        }
        fwrite(data_ptr, sizeof(StatData), records_to_write, fd);
        records_left -= records_to_write;
        if (records_left == 0)
        {
            break;
        }
    }

    fclose(fd);

    return 0;
}

// Load data from file
// WARNING: this function allocate memory buffer for storing data
int LoadDump(StatData **data_ptr, size_t *records_count, const char *file_path)
{
    FILE *fd = fopen(file_path, "rb");

    // We can read all file using fseek and rewind
    // but this method may be unefficient
    // That's why we using reading in chunks and realloc() function
    size_t records_read = 0;
    size_t current_buffer_size = 0;
    StatData *tmp_data_ptr = NULL;

    while (1)
    {
        // if current buffer size can't put new data from file
        // realloc to new size
        if (current_buffer_size < records_read * sizeof(StatData) + CHUNK_SIZE)
        {
            void *tmp = realloc(tmp_data_ptr, records_read * sizeof(StatData) + CHUNK_SIZE);
            if (tmp == NULL)
            {
                // error
                free(tmp_data_ptr);
                return ALLOCATION_ERROR;
            }
            tmp_data_ptr = tmp;
            current_buffer_size = records_read * sizeof(StatData) + CHUNK_SIZE;
        }
        size_t read_count = fread(
            tmp_data_ptr + records_read * sizeof(StatData),
            sizeof(StatData), CHUNK_SIZE / sizeof(StatData),
            fd);
        records_read += read_count;
        if (read_count == 0)
        {
            break;
        }
        if (feof(fd))
        {
            break;
        }
    }
    if (!feof(fd))
    {
        if (ferror(fd))
        {
            // somthing went wrong
            free(tmp_data_ptr);
            return FILE_ERROR;
        }
    }

    // shrink buffer to data size
    void *tmp = realloc(tmp_data_ptr, records_read * sizeof(StatData));
    if (tmp == NULL)
    {
        free(tmp_data_ptr);
        return ALLOCATION_ERROR;
    }
    tmp_data_ptr = tmp;

    *data_ptr = tmp_data_ptr;
    *records_count = records_read;

    fclose(fd);

    return 0;
}

// Find ID in array with IDs
int find_id(long id, long **ids_array, size_t array_size, size_t *id_ptr)
{
    for (size_t i = 0; i < array_size; i++)
    {
        if ((*ids_array)[i] == id)
        {
            *id_ptr = i;
            return 0;
        }
    }
    return -1;
}

// Merge data from two arrays
int JoinDump(
    const StatData *a_ptr, const size_t a_records_count, 
    const StatData *b_ptr, const size_t b_records_count,
    StatData **result_ptr, size_t *result_records_count)
{
    // we need to store list with ID's in result array
    // default records count will be 16 and will be resized in process
    // at the end we shrink array to count of records
    size_t list_capacity = 16;
    size_t list_size = 0;
    StatData *result_array = malloc(sizeof(StatData) * list_capacity);
    long *ids_array = malloc(sizeof(long) * list_capacity);

    for (int k = 0; k < 2; k++)
    {
        const StatData *current_ptr;
        size_t current_records_count;
        if (k == 0)
        {
            current_ptr = a_ptr;
            current_records_count = a_records_count;
        }
        else
        {
            current_ptr = b_ptr;
            current_records_count = b_records_count;
        }

        for (size_t i = 0; i < current_records_count; i++)
        {
            size_t id_pos = 0;
            if (find_id(current_ptr[i].id, &ids_array, list_size, &id_pos) == 0)
            {
                // ID found in array
                // merge data with record in result array
                result_array[id_pos].cost += current_ptr[i].cost;
                result_array[id_pos].count += current_ptr[i].count;
                result_array[id_pos].primary &= current_ptr[i].primary;
                result_array[id_pos].mode = result_array[id_pos].primary > current_ptr[i].mode ? result_array[id_pos].primary : current_ptr[i].mode;
            }
            else
            {
                // can't find, write to list new element
                result_array[list_size] = current_ptr[i];
                ids_array[list_size] = current_ptr[i].id;
                list_size++;
                if (list_size == list_capacity)
                {
                    list_capacity += 16;
                    void *tmp_1 = realloc(result_array, list_capacity);
                    void *tmp_2 = realloc(ids_array, list_capacity);
                    if (tmp_1 == NULL || tmp_2 == NULL)
                    {
                        // can't allocate memory
                        free(result_array);
                        free(ids_array);
                        return -1;
                    }
                    result_array = tmp_1;
                    ids_array = tmp_2;
                }
            }
        }
    }

    *result_ptr = result_array;
    *result_records_count = list_size;

    free(ids_array);

    return 0;
}

int cmp(const void *a_ptr, const void *b_ptr)
{
    if (((StatData *)a_ptr)->cost < ((StatData *)b_ptr)->cost)
    {
        return -1;
    }
    else if (((StatData *)a_ptr)->cost  > ((StatData *)b_ptr)->cost)
    {
        return 1;
    }
    // if (((StatData *)a_ptr)->cost  == ((StatData *)b_ptr)->cost)
    else
    {
        return 0;
    }
}
// Sort data in array by 'cost' field
int SortDump(StatData **data_ptr, const size_t data_records_count)
{
    qsort(*data_ptr, data_records_count, sizeof(StatData), cmp);

    return 0;
}

#define BINARY_NUMBER_OUTPUT(num,fd) do{int t=num;size_t i=3;do{i--;fputc((((t&(1<<i))>>i)&0x01)+'0',fd);}while(i!=0);}while(0)

void PrintTable(StatData **data_ptr, const size_t data_records_count, const size_t elements_to_print, FILE *fd)
{
    fputs("+------------+-------------+------------+---------+--------+\n", fd);
    fputs("|     id     |    count    |    cost    | primary |  mode  |\n", fd);
    fputs("+------------+-------------+------------+---------+--------+\n", fd);
    for (size_t i = 0; i < elements_to_print; i++)
    {
        fprintf(fd, "| 0x%08lX | %11d |  %4.3e |    ", (*data_ptr)[i].id, (*data_ptr)[i].count, (*data_ptr)[i].cost);
        if ((*data_ptr)[i].primary == 0)
        {
            fputc('n', fd);
        }
        else
        {
            fputc('y', fd);
        }
        fprintf(fd, "    |  0b");
        BINARY_NUMBER_OUTPUT((*data_ptr)[i].mode, fd);
        fprintf(fd, " |");

        fputc('\n', fd);
    }
    fputs("+------------+-------------+------------+---------+--------+\n", fd);
    // put table to buffer
}

#define ARRAY_SIZE(x) ((sizeof(x)) / (sizeof((x)[0])))

// g++ ./main.cpp -o build/calc -std=c++17 -O0 -ggdb3
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
    PrintTable(&result_data, result_records_count, 2, stdout);

    // StoreDump(test_array, ARRAY_SIZE(test_array), "./storage.bin");

    // StatData *new_data;
    // size_t records_count;
    // LoadDump(&new_data, &records_count, "./storage.bin");

    return 0;
}
