#ifndef __DATA_UTIL_H__
#define __DATA_UTIL_H__

#include <stdlib.h>
#include <stdio.h>

#define BINARY_NUMBER_OUTPUT(num,fd) do{int t=num;size_t i=3;do{i--;fputc((((t&(1<<i))>>i)&0x01)+'0',fd);}while(i!=0);}while(0)

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

#define CHUNK_SIZE (sizeof(StatData) * 16)

// ------

/**
 * Store data to file
 *
 * @param data_ptr pointer to array
 * @param record_count count of records in array
 * @param file_path path to file
**/
int StoreDump(StatData *data_ptr, size_t record_count, const char *file_path);

/**
 * Load data from file
 *
 * @warning this function allocate memory buffer for storing data
 *
 * @param data_ptr pointer for storing pointer with loaded data
 * @param records_count pointer for storing records count
 * @param file_path path to file
**/
int LoadDump(StatData **data_ptr, size_t *records_count, const char *file_path);

/**
 * Merge data from two arrays
 *
 * @warning allocates new memory
 *
 * @param a_ptr pointer to first rray
 * @param a_records_count counts of records in first array
 * @param b_ptr pointer to second array
 * @param b_records_count pointer to second array
 * @param result_ptr pointer for storing pointer to result array
 * @param result_records_count pointer for storing count of records in result array
**/
int JoinDump(
    const StatData *a_ptr, const size_t a_records_count,
    const StatData *b_ptr, const size_t b_records_count,
    StatData **result_ptr, size_t *result_records_count);

/**
 * Sort data in array by 'cost' field
 *
 * @param data_ptr poiniter that stores pointer to array
 * @param data_records_count count of records
**/
int SortDump(StatData **data_ptr, size_t data_records_count);

/**
 * Prety print table with data to buffer
 *
 * @param data_ptr poiniter that stores pointer to array
 * @param elements_to_print count of records for printing
 * @param fd file descriptor of buffer
**/
void PrintTable(StatData **data_ptr, const size_t elements_to_print, FILE *fd);


#endif
