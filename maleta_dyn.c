#include <stdlib.h>
#include <string.h>
#include "maleta_dyn.h"

DynamicArray *newDynamicArray(void) {
    DynamicArray *myArray= malloc(sizeof *myArray);
    myArray->size= sizeof *myArray;
    myArray->length= 0;
    // Initial byte
    myArray->array= malloc(1);
    myArray->arraySize= 1;
    // There are no values in the array, so the next value should be written to the starting position
    myArray->nextEntryMemPos= myArray->array;
    return myArray;
}

void freeDynamicArray(DynamicArray *dArray) {
    free(dArray->array);
    free(dArray);
    return;
}

enum DataType getType(DynamicArray *dArray, size_t index) {
    return dArray->mapIndexToMem[index].type;
}

DynamicArray *pushString(DynamicArray *dArray, char *value) {
    //      --Allocate and write to the array of DynamicArrayEntry 

    // Allocate memory for a new DynamicArrayEntry
    dArray= realloc(dArray, dArray->size + sizeof(DynamicArrayEntry));
    dArray->size+= sizeof(DynamicArrayEntry);
    // Populate the new DynamicArrayEntry
    dArray->mapIndexToMem[dArray->length].memPos= dArray->nextEntryMemPos; // At this point nextEntryMemPos is unallocated
    dArray->mapIndexToMem[dArray->length].type= STRING;

    //      --Allocate and write to the array of values--

    // Get size of string
    size_t strLength= strlen(value)+1;

    // If this is the first entry, account for the previously allocated inital byte
    if (dArray->length == 0) {
        dArray->array= realloc(dArray->array, sizeof(char)*strLength - 1);
        dArray->arraySize= sizeof(char)*strLength;
    } else {
        dArray->array= realloc(dArray->array, dArray->arraySize + sizeof(char)*strLength);
        dArray->arraySize+= sizeof(char)*strLength;
    }
    dArray->nextEntryMemPos+= sizeof(char)*strLength;
    // Write the string to memory
    strcpy(dArray->mapIndexToMem[dArray->length].memPos, value);
    
    // Update DynamicArray length
    dArray->length++;
    return dArray;
}

char *getString(DynamicArray *dArray, size_t index) {
    return dArray->mapIndexToMem[index].memPos;
}

DynamicArray *pushInt(DynamicArray *dArray, int value) {
    //      --Allocate and write to the array of DynamicArrayEntry 

    // Allocate memory for a new DynamicArrayEntry
    dArray= realloc(dArray, dArray->size + sizeof(DynamicArrayEntry));
    dArray->size+= sizeof(DynamicArrayEntry);
    // Populate the new DynamicArrayEntry
    dArray->mapIndexToMem[dArray->length].memPos= dArray->nextEntryMemPos; // At this point nextEntryMemPos is unallocated
    dArray->mapIndexToMem[dArray->length].type= INT;
    //      --Allocate and write to the array of values--

    // If this is the first entry, account for the previously allocated inital byte
    if (dArray->length == 0) {
        dArray->array= realloc(dArray->array, sizeof(int) - 1);
        dArray->arraySize= sizeof(int);
    } else {
        dArray->array= realloc(dArray->array, dArray->arraySize + sizeof(int));
        dArray->arraySize+= sizeof(int);
    }
    dArray->nextEntryMemPos+= sizeof(int);

    // Write the int to memory
    (*(int *)(dArray->mapIndexToMem[dArray->length].memPos))= value;

    // Update DynamicArray length
    dArray->length++;
    return dArray;
}

int getInt(DynamicArray *dArray, size_t index) {
    return *((int *)(dArray->mapIndexToMem[index].memPos));
}

DynamicArray *pushDouble(DynamicArray *dArray, double value) {
    //      --Allocate and write to the array of DynamicArrayEntry 

    // Allocate memory for a new DynamicArrayEntry
    dArray= realloc(dArray, dArray->size + sizeof(DynamicArrayEntry));
    dArray->size+= sizeof(DynamicArrayEntry);
    // Populate the new DynamicArrayEntry
    dArray->mapIndexToMem[dArray->length].memPos= dArray->nextEntryMemPos; // At this point nextEntryMemPos is unallocated
    dArray->mapIndexToMem[dArray->length].type= DOUBLE;
    //      --Allocate and write to the array of values--

    // If this is the first entry, account for the previously allocated inital byte
    if (dArray->length == 0) {
        dArray->array= realloc(dArray->array, sizeof(double) - 1);
        dArray->arraySize= sizeof(double);
    } else {
        dArray->array= realloc(dArray->array, dArray->arraySize + sizeof(double));
        dArray->arraySize+= sizeof(double);
    }
    dArray->nextEntryMemPos+= sizeof(double);

    // Write the int to memory
    (*(double *)(dArray->mapIndexToMem[dArray->length].memPos))= value;

    // Update DynamicArray length
    dArray->length++;
    return dArray;
}

double getDouble(DynamicArray *dArray, size_t index) {
    return *((double *)(dArray->mapIndexToMem[index].memPos));
}