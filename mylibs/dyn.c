#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "dyn.h"

#define GROW 2
#define SHRINK 1

typedef struct DynamicArrayEntry {
    void *value;
    enum DataType type;
} DynamicArrayEntry;

struct DynamicArray {
    size_t length;
    size_t size;
    size_t allocatedSize;
    DynamicArrayEntry *array;
};

// Function Declarations
static DynamicArray *makeDynamicArray(void);
static void freeDynamicArray(DynamicArray *dArray);

static void pushString(DynamicArray *dArray, char *str);
static void pushInt(DynamicArray *dArray, int value);
static void pushDouble(DynamicArray *dArray, double value);
static void pushChar(DynamicArray *dArray, char value);
static void pushBool(DynamicArray *dArray, bool value);
static void pushSize_t(DynamicArray *dArray, size_t value);

static void popLast(DynamicArray *dArray);

static void insertString(DynamicArray *dArray, size_t index, char *str);
static void insertInt(DynamicArray *dArray, size_t index, int value);
static void insertDouble(DynamicArray *dArray, size_t index, double value);
static void insertChar(DynamicArray *dArray, size_t index, char value);
static void insertBool(DynamicArray *dArray, size_t index, bool value);
static void insertSize_t(DynamicArray *dArray, size_t index, size_t value);

static void deleteEntry(DynamicArray *dArray, size_t index);

static void writeString(DynamicArray *dArray, size_t index, char *str);
static void writeInt(DynamicArray *dArray, size_t index, int value);
static void writeDouble(DynamicArray *dArray, size_t index, double value);
static void writeChar(DynamicArray *dArray, size_t index, char value);
static void writeBool(DynamicArray *dArray, size_t index, bool value);
static void writeSize_t(DynamicArray *dArray, size_t index, size_t value);



static const enum DataType getType(DynamicArray *dArray, size_t index);
static void *getPtrToValue(DynamicArray *dArray, size_t index);

static char *getString(DynamicArray *dArray, size_t index);
static int getInt(DynamicArray *dArray, size_t index);
static double getDouble(DynamicArray *dArray, size_t index);
static char getChar(DynamicArray *dArray, size_t index);
static bool getBool(DynamicArray *dArray, size_t index);
static size_t getSize_t(DynamicArray *dArray, size_t index);

static bool forEach(DynamicArray *dArray, dyn_ForEachCallback callback, void *cbParams);
static void logTypes(DynamicArray *dArray);
//

// Initialize global Dyn struct
const struct Dyn Dyn= {
    .makeDynamicArray= &makeDynamicArray,
    .freeDynamicArray= &freeDynamicArray,
    .pushString= &pushString,
    .pushInt= &pushInt,
    .pushDouble= &pushDouble,
    .pushChar= &pushChar,
    .pushBool= &pushBool,
    .pushSize_t= &pushSize_t,
    .popLast= &popLast,
    .insertString= &insertString,
    .insertInt= &insertInt,
    .insertDouble= &insertDouble,
    .insertChar= &insertChar,
    .insertBool= &insertBool,
    .insertSize_t= &insertSize_t,
    .deleteEntry= &deleteEntry,
    .writeString= &writeString,
    .writeInt= &writeInt,
    .writeDouble= &writeDouble,
    .writeChar= &writeChar,
    .writeBool= &writeBool,
    .writeSize_t= &writeSize_t,
    .getType= &getType,
    .getPtrToValue= &getPtrToValue,
    .getString= &getString,
    .getInt= &getInt,
    .getDouble= &getDouble,
    .getChar= &getChar,
    .getBool= &getBool,
    .getSize_t= &getSize_t,
    .forEach= &forEach,
    .logTypes= &logTypes
};
//


// Function Definitions
static DynamicArray *makeDynamicArray(void) {
    DynamicArray *dArray= malloc(sizeof *dArray);
    dArray->length= 0;
    dArray->size= 0;
    dArray->allocatedSize= 0;
    dArray->array= NULL;
    return dArray;
}

static void initialize(DynamicArray *dArray) {
    dArray->allocatedSize+= 5 * sizeof(DynamicArrayEntry);
    dArray->array= malloc(5 * sizeof(DynamicArrayEntry));
    return;
}

static void resize(DynamicArray *dArray, int option) {
    switch (option) {
        default: // Assume GROW
        case GROW: {
            dArray->array= realloc(dArray->array, dArray->allocatedSize + 5 * sizeof(DynamicArrayEntry));
            dArray->allocatedSize+= 5 * sizeof(DynamicArrayEntry);
            return;
        }
        case SHRINK: {
            dArray->array= realloc(dArray->array, dArray->allocatedSize - 5 * sizeof(DynamicArrayEntry));
            dArray->allocatedSize-= 5 * sizeof(DynamicArrayEntry);
            return;
        }
    }
    return;
}

static void repeatResize(DynamicArray *dArray, size_t times) {
    dArray->array= realloc(dArray->array, dArray->allocatedSize + times * 5 * sizeof(DynamicArrayEntry));
    dArray->allocatedSize+= times * 5 * sizeof(DynamicArrayEntry);
    return;
}

static void freeDynamicArray(DynamicArray *dArray) {
    for (size_t i= 0; i < dArray->length; i++) {
        free(dArray->array[i].value);
    }
    free(dArray->array);
    free(dArray);
    return;
}

static void pushString(DynamicArray *dArray, char *str) {
    if (dArray->allocatedSize == 0) {
        initialize(dArray);
    }
    if (dArray->allocatedSize < dArray->size + sizeof(DynamicArrayEntry)) {
        resize(dArray, GROW);
    }
    dArray->size+= sizeof(DynamicArrayEntry);
    dArray->array[dArray->length].type= STRING;
    dArray->array[dArray->length].value= malloc(sizeof(char) * (strlen(str)+1));
    strcpy(dArray->array[dArray->length].value, str);
    dArray->length++;
    return;
}
static void pushInt(DynamicArray *dArray, int value) {
    if (dArray->allocatedSize == 0) {
        initialize(dArray);
    }
    if (dArray->allocatedSize < dArray->size + sizeof(DynamicArrayEntry)) {
        resize(dArray, GROW);
    }
    dArray->size+= sizeof(DynamicArrayEntry);
    dArray->array[dArray->length].type= INT;
    dArray->array[dArray->length].value= malloc(sizeof(int));
    *((int *)(dArray->array[dArray->length].value))= value;
    dArray->length++;
    return;
}
static void pushDouble(DynamicArray *dArray, double value) {
    if (dArray->allocatedSize == 0) {
        initialize(dArray);
    }
    if (dArray->allocatedSize < dArray->size + sizeof(DynamicArrayEntry)) {
        resize(dArray, GROW);
    }
    dArray->size+= sizeof(DynamicArrayEntry);
    dArray->array[dArray->length].type= DOUBLE;
    dArray->array[dArray->length].value= malloc(sizeof(double));
    *((double *)(dArray->array[dArray->length].value))= value;
    dArray->length++;
    return;
}
static void pushChar(DynamicArray *dArray, char value) {
    if (dArray->allocatedSize == 0) {
        initialize(dArray);
    }
    if (dArray->allocatedSize < dArray->size + sizeof(DynamicArrayEntry)) {
        resize(dArray, GROW);
    }
    dArray->size+= sizeof(DynamicArrayEntry);
    dArray->array[dArray->length].type= CHAR;
    dArray->array[dArray->length].value= malloc(sizeof(char));
    *((char *)(dArray->array[dArray->length].value))= value;
    dArray->length++;
    return;
}
static void pushBool(DynamicArray *dArray, bool value) {
    if (dArray->allocatedSize == 0) {
        initialize(dArray);
    }
    if (dArray->allocatedSize < dArray->size + sizeof(DynamicArrayEntry)) {
        resize(dArray, GROW);
    }
    dArray->size+= sizeof(DynamicArrayEntry);
    dArray->array[dArray->length].type= BOOL;
    dArray->array[dArray->length].value= malloc(sizeof(bool));
    *((bool *)(dArray->array[dArray->length].value))= value;
    dArray->length++;
    return;
}
static void pushSize_t(DynamicArray *dArray, size_t value) {
    if (dArray->allocatedSize == 0) {
        initialize(dArray);
    }
    if (dArray->allocatedSize < dArray->size + sizeof(DynamicArrayEntry)) {
        resize(dArray, GROW);
    }
    dArray->size+= sizeof(DynamicArrayEntry);
    dArray->array[dArray->length].type= SIZE_T;
    dArray->array[dArray->length].value= malloc(sizeof(size_t));
    *((size_t *)(dArray->array[dArray->length].value))= value;
    dArray->length++;
    return;
}

static void popLast(DynamicArray *dArray) {
    if (dArray->length == 0) {
        return;
    }
    free(dArray->array[dArray->length - 1].value);
    dArray->size-= sizeof(DynamicArrayEntry);
    dArray->length--;
    if (dArray->allocatedSize - dArray->size >= 5*sizeof(DynamicArrayEntry)) {
        resize(dArray, SHRINK);
    }
    return;
}

static void insertString(DynamicArray *dArray, size_t index, char *str) {
    // If inserting a value on the last position, call push method.
    if (index == dArray->length) {
        return pushString(dArray, str);
    }

    // If inserting a value on a existent position, move everything to the left.
    if (index < dArray->length) {
        if (dArray->allocatedSize < dArray->size + sizeof(DynamicArrayEntry)) {
            resize(dArray, GROW);
        }
        dArray->size+= sizeof(DynamicArrayEntry);

        for (size_t i= dArray->length; i > index; i--) {
            dArray->array[i].type= dArray->array[i-1].type; 
            dArray->array[i].value= dArray->array[i-1].value; 
        }
        dArray->length++;
    }

    // If inserting a value thats many slots ahead of last, fill the in between values with EMPTY.
    if (index > dArray->length) {
        size_t newElements= (index+1) - dArray->length;
        if (newElements * sizeof(DynamicArrayEntry) + dArray->size > dArray->allocatedSize) {
            size_t resizeNTimes= (size_t) ceil(newElements/5);
            repeatResize(dArray, resizeNTimes);
        }
        dArray->size+= newElements * sizeof(DynamicArrayEntry);
        for (size_t i= index-1; i >= dArray->length; i--) {
            dArray->array[i].value= NULL;
            dArray->array[i].type= EMPTY;
        }
        dArray->length+= newElements;
    }

    dArray->array[index].value= malloc(sizeof(char) * (strlen(str) + 1)); 
    dArray->array[index].type= STRING;

    strcpy(dArray->array[index].value, str);
    return;
}
static void insertInt(DynamicArray *dArray, size_t index, int value) {
    // If inserting a value on the last position, call push method.
    if (index == dArray->length) {
        return pushInt(dArray, value);
    }

    // If inserting a value on a existent position, move everything to the left.
    if (index < dArray->length) {
        if (dArray->allocatedSize < dArray->size + sizeof(DynamicArrayEntry)) {
            resize(dArray, GROW);
        }
        dArray->size+= sizeof(DynamicArrayEntry);

        for (size_t i= dArray->length; i > index; i--) {
            dArray->array[i].type= dArray->array[i-1].type; 
            dArray->array[i].value= dArray->array[i-1].value; 
        }
        dArray->length++;
    }

    // If inserting a value thats many slots ahead of last, fill the in between values with EMPTY.
    if (index > dArray->length) {
        size_t newElements= (index+1) - dArray->length;
        if (newElements * sizeof(DynamicArrayEntry) + dArray->size > dArray->allocatedSize) {
            size_t resizeNTimes= (size_t) ceil(newElements/5); // Round up to nearest integer
            repeatResize(dArray, resizeNTimes);
        }
        dArray->size+= newElements * sizeof(DynamicArrayEntry);
        for (size_t i= index-1; i >= dArray->length; i--) {
            dArray->array[i].value= NULL;
            dArray->array[i].type= EMPTY;
        }
        dArray->length+= newElements;
    }

    dArray->array[index].value= malloc(sizeof(int));
    dArray->array[index].type= INT;

    *((int *)(dArray->array[index].value))= value;

    return;
}
static void insertDouble(DynamicArray *dArray, size_t index, double value) {
    // If inserting a value on the last position, call push method.
    if (index == dArray->length) {
        return pushDouble(dArray, value);
    }

    // If inserting a value on a existent position, move everything to the left.
    if (index < dArray->length) {
        if (dArray->allocatedSize < dArray->size + sizeof(DynamicArrayEntry)) {
            resize(dArray, GROW);
        }
        dArray->size+= sizeof(DynamicArrayEntry);

        for (size_t i= dArray->length; i > index; i--) {
            dArray->array[i].type= dArray->array[i-1].type; 
            dArray->array[i].value= dArray->array[i-1].value; 
        }
        dArray->length++;
    }

    // If inserting a value thats many slots ahead of last, fill the in between values with EMPTY.
    if (index > dArray->length) {
        size_t newElements= (index+1) - dArray->length;
        if (newElements * sizeof(DynamicArrayEntry) + dArray->size > dArray->allocatedSize) {
            size_t resizeNTimes= (size_t) ceil(newElements/5);
            repeatResize(dArray, resizeNTimes);
        }
        dArray->size+= newElements * sizeof(DynamicArrayEntry);
        for (size_t i= index-1; i >= dArray->length; i--) {
            dArray->array[i].value= NULL;
            dArray->array[i].type= EMPTY;
        }
        dArray->length+= newElements;

    }

    dArray->array[index].value= malloc(sizeof(double));
    dArray->array[index].type= DOUBLE;

    *((double *)(dArray->array[index].value))= value;

    return;
}
static void insertChar(DynamicArray *dArray, size_t index, char value) {
    // If inserting a value on the last position, call push method.
    if (index == dArray->length) {
        return pushChar(dArray, value);
    }

    // If inserting a value on a existent position, move everything to the left.
    if (index < dArray->length) {
        if (dArray->allocatedSize < dArray->size + sizeof(DynamicArrayEntry)) {
            resize(dArray, GROW);
        }
        dArray->size+= sizeof(DynamicArrayEntry);

        for (size_t i= dArray->length; i > index; i--) {
            dArray->array[i].type= dArray->array[i-1].type; 
            dArray->array[i].value= dArray->array[i-1].value; 
        }
        dArray->length++;
    }

    // If inserting a value thats many slots ahead of last, fill the in between values with EMPTY.
    if (index > dArray->length) {
        size_t newElements= (index+1) - dArray->length;
        if (newElements * sizeof(DynamicArrayEntry) + dArray->size > dArray->allocatedSize) {
            size_t resizeNTimes= (size_t) ceil(newElements/5);
            repeatResize(dArray, resizeNTimes);
        }
        dArray->size+= newElements * sizeof(DynamicArrayEntry);
        for (size_t i= index-1; i >= dArray->length; i--) {
            dArray->array[i].value= NULL;
            dArray->array[i].type= EMPTY;
        }
        dArray->length+= newElements;
    }
    
    dArray->array[index].value= malloc(sizeof(char));
    dArray->array[index].type= CHAR;

    *((char *)(dArray->array[index].value))= value;

    return;
}
static void insertBool(DynamicArray *dArray, size_t index, bool value) {
    // If inserting a value on the last position, call push method.
    if (index == dArray->length) {
        return pushBool(dArray, value);
    }

    // If inserting a value on a existent position, move everything to the left.
    if (index < dArray->length) {
        if (dArray->allocatedSize < dArray->size + sizeof(DynamicArrayEntry)) {
            resize(dArray, GROW);
        }
        dArray->size+= sizeof(DynamicArrayEntry);

        for (size_t i= dArray->length; i > index; i--) {
            dArray->array[i].type= dArray->array[i-1].type; 
            dArray->array[i].value= dArray->array[i-1].value; 
        }
        dArray->length++;
    }

    // If inserting a value thats many slots ahead of last, fill the in between values with EMPTY.
    if (index > dArray->length) {
        size_t newElements= (index+1) - dArray->length;
        if (newElements * sizeof(DynamicArrayEntry) + dArray->size > dArray->allocatedSize) {
            size_t resizeNTimes= (size_t) ceil(newElements/5);
            repeatResize(dArray, resizeNTimes);
        }
        dArray->size+= newElements * sizeof(DynamicArrayEntry);
        for (size_t i= index-1; i >= dArray->length; i--) {
            dArray->array[i].value= NULL;
            dArray->array[i].type= EMPTY;
        }
        dArray->length+= newElements;
    }
    
    dArray->array[index].value= malloc(sizeof(bool));
    dArray->array[index].type= BOOL;

    *((bool *)(dArray->array[index].value))= value;

    return;
}
static void insertSize_t(DynamicArray *dArray, size_t index, size_t value) {
    // If inserting a value on the last position, call push method.
    if (index == dArray->length) {
        return pushSize_t(dArray, value);
    }

    // If inserting a value on a existent position, move everything to the left.
    if (index < dArray->length) {
        if (dArray->allocatedSize < dArray->size + sizeof(DynamicArrayEntry)) {
            resize(dArray, GROW);
        }
        dArray->size+= sizeof(DynamicArrayEntry);

        for (size_t i= dArray->length; i > index; i--) {
            dArray->array[i].type= dArray->array[i-1].type; 
            dArray->array[i].value= dArray->array[i-1].value; 
        }
        dArray->length++;
    }

    // If inserting a value thats many slots ahead of last, fill the in between values with EMPTY.
    if (index > dArray->length) {
        size_t newElements= (index+1) - dArray->length;
        if (newElements * sizeof(DynamicArrayEntry) + dArray->size > dArray->allocatedSize) {
            size_t resizeNTimes= (size_t) ceil(newElements/5);
            repeatResize(dArray, resizeNTimes);
        }
        dArray->size+= newElements * sizeof(DynamicArrayEntry);
        for (size_t i= index-1; i >= dArray->length; i--) {
            dArray->array[i].value= NULL;
            dArray->array[i].type= EMPTY;
        }
        dArray->length+= newElements;
    }
    
    dArray->array[index].value= malloc(sizeof(size_t));
    dArray->array[index].type= SIZE_T;

    *((size_t *)(dArray->array[index].value))= value;

    return;
}

static void deleteEntry(DynamicArray *dArray, size_t index) {
    if (index > dArray->length-1) {
        return;
    }
    
    if (index == dArray->length-1) {
        return popLast(dArray);
    }

    free(dArray->array[index].value);

    dArray->size-= sizeof(DynamicArrayEntry);
    dArray->length--;
    for (size_t i= index; i < dArray->length; i++) {
        dArray->array[i].type= dArray->array[i+1].type; 
        dArray->array[i].value= dArray->array[i+1].value; 
    }

    if (dArray->allocatedSize - dArray->size >= 5*sizeof(DynamicArrayEntry)) {
        resize(dArray, SHRINK);
    }
    return;
}

static void writeString(DynamicArray *dArray, size_t index, char *str) {
    if (index > dArray->length-1) {
        return;
    }
    free(dArray->array[index].value);
    dArray->array[index].type= STRING;
    dArray->array[index].value= malloc(sizeof(char) * (strlen(str)+1));
    strcpy(dArray->array[index].value, str);
    return;
}
static void writeInt(DynamicArray *dArray, size_t index, int value) {
    if (index > dArray->length-1) {
        return;
    }
    if (dArray->array[index].type != INT) {
        free(dArray->array[index].value);
        dArray->array[index].value= malloc(sizeof(int));
        dArray->array[index].type= INT;
    }
    *((int *)(dArray->array[index].value))= value;
    return;
}
static void writeDouble(DynamicArray *dArray, size_t index, double value) {
    if (index > dArray->length-1) {
        return;
    }
    if (dArray->array[index].type != DOUBLE) {
        free(dArray->array[index].value);
        dArray->array[index].value= malloc(sizeof(double));
        dArray->array[index].type= DOUBLE;
    }
    *((double *)(dArray->array[index].value))= value;
    return;
}
static void writeChar(DynamicArray *dArray, size_t index, char value) {
    if (index > dArray->length-1) {
        return;
    }
    if (dArray->array[index].type != CHAR) {
        free(dArray->array[index].value);
        dArray->array[index].value= malloc(sizeof(char));
        dArray->array[index].type= CHAR;
    }
    *((char *)(dArray->array[index].value))= value;
    return;
}
static void writeBool(DynamicArray *dArray, size_t index, bool value) {
    if (index > dArray->length-1) {
        return;
    }
    if (dArray->array[index].type != BOOL) {
        free(dArray->array[index].value);
        dArray->array[index].value= malloc(sizeof(bool));
        dArray->array[index].type= BOOL;
    }
    *((bool *)(dArray->array[index].value))= value;
    return;
}
static void writeSize_t(DynamicArray *dArray, size_t index, size_t value) {
    if (index > dArray->length-1) {
        return;
    }
    if (dArray->array[index].type != SIZE_T) {
        free(dArray->array[index].value);
        dArray->array[index].value= malloc(sizeof(size_t));
        dArray->array[index].type= SIZE_T;
    }
    *((size_t *)(dArray->array[index].value))= value;
    return;
}

static const enum DataType getType(DynamicArray *dArray, size_t index) {
    return dArray->array[index].type;
}
static void *getPtrToValue(DynamicArray *dArray, size_t index) {
    return dArray->array[index].value;
}

static char *getString(DynamicArray *dArray, size_t index) {
    return (char *)dArray->array[index].value;
}
static int getInt(DynamicArray *dArray, size_t index) {
    return *((int *)(dArray->array[index].value));
}
static double getDouble(DynamicArray *dArray, size_t index) {
    return *((double *)(dArray->array[index].value));
}
static char getChar(DynamicArray *dArray, size_t index) {
    return *((char *)(dArray->array[index].value));
}
static bool getBool(DynamicArray *dArray, size_t index) {
    return *((bool *)(dArray->array[index].value));
}
static size_t getSize_t(DynamicArray *dArray, size_t index) {
    return *((size_t *)(dArray->array[index].value));
}

static bool forEach(DynamicArray *dArray, dyn_ForEachCallback callback, void *cbParams) {
    for (size_t i= 0; i < dArray->length; i++) {
        if (callback(i, dArray->array[i].value, dArray->array[i].type, cbParams)) return true;
    }
    return false;
}

static void logTypes(DynamicArray *dArray) {
    for (size_t i= 0; i < dArray->length; i++) {
        char *isType;
        switch (dArray->array[i].type) {
            case INT: {
                isType= "INT";
                break;
            }
            case STRING: {
                isType= "STRING";
                break;
            }
            case DOUBLE: {
                isType= "DOUBLE";
                break;
            }
            case CHAR: {
                isType= "CHAR";
                break;
            }
            case BOOL: {
                isType= "BOOL";
                break;
            }
            case SIZE_T: {
                isType= "SIZE_T";
                break;
            }
            case EMPTY: {
                isType= "EMPTY";
                break;
            }
            default: {
                exit(1);
                break;
            }
        }
        printf("%zu: %s\n", i, isType);
    }
    return;
}
//

#undef GROW
#undef SHRINK