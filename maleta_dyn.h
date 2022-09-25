#ifndef MALETA_DYN_INCLUDED
#define MALETA_DYN_INCLUDED
#include <stddef.h>
enum DataType {
    INT,
    STRING,
    DOUBLE
};

typedef struct DynamicArrayEntry
{
    void *memPos; // Starting position of the value
    enum DataType type; // Type of the value

} DynamicArrayEntry;

typedef struct DynamicArray {
    size_t length; // Length of mapIndexToMem[]
    size_t size; // Size of the current DynamicArray instance in bytes
    void *array; // Pointer to a continuous block of memory containing the values of the array
    size_t arraySize; // Size of the entire array memory block in bytes
    void *nextEntryMemPos; // Pointer to where the next array entry should be written to. Always unallocated
    DynamicArrayEntry mapIndexToMem[]; // Maps an index to a memory location
} DynamicArray;

DynamicArray *newDynamicArray(void);
void freeDynamicArray(DynamicArray *);

enum DataType getType(DynamicArray *, size_t);

DynamicArray *pushString(DynamicArray *, char *);
char *getString(DynamicArray *, size_t);

DynamicArray *pushInt(DynamicArray *, int);
int getInt(DynamicArray *, size_t);

DynamicArray *pushDouble(DynamicArray *, double);
double getDouble(DynamicArray *, size_t);

#endif