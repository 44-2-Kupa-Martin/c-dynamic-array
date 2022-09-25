#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dyn.h"

DynamicArray *makeDynamicArray(void) {
    DynamicArray *dArray= malloc(sizeof *dArray);
    dArray->length= 0;
    dArray->size= sizeof *dArray;
    return dArray;
}
void freeDynamicArray(DynamicArray *dArray) {
    for (size_t i= 0; i < dArray->length; i++) {
        free(dArray->array[i].value);
    }
    free(dArray);
    return;
}

DynamicArray *pushString(DynamicArray *dArray, char *str) {
    dArray= realloc(dArray, dArray->size + sizeof(DynamicArrayEntry));
    dArray->size+= sizeof(DynamicArrayEntry);
    dArray->array[dArray->length].type= STRING;
    dArray->array[dArray->length].value= malloc(sizeof(char) * (strlen(str)+1));
    strcpy(dArray->array[dArray->length].value, str);
    dArray->length++;
    return dArray;
}
DynamicArray *pushInt(DynamicArray *dArray, int value) {
    dArray= realloc(dArray, dArray->size + sizeof(DynamicArrayEntry));
    dArray->size+= sizeof(DynamicArrayEntry);
    dArray->array[dArray->length].type= INT;
    dArray->array[dArray->length].value= malloc(sizeof(int));
    *((int *)(dArray->array[dArray->length].value))= value;
    dArray->length++;
    return dArray;
}
DynamicArray *pushDouble(DynamicArray *dArray, double value) {
    dArray= realloc(dArray, dArray->size + sizeof(DynamicArrayEntry));
    dArray->size+= sizeof(DynamicArrayEntry);
    dArray->array[dArray->length].type= DOUBLE;
    dArray->array[dArray->length].value= malloc(sizeof(double));
    *((double *)(dArray->array[dArray->length].value))= value;
    dArray->length++;
    return dArray;
}
DynamicArray *pushChar(DynamicArray *dArray, char value) {
    dArray= realloc(dArray, dArray->size + sizeof(DynamicArrayEntry));
    dArray->size+= sizeof(DynamicArrayEntry);
    dArray->array[dArray->length].type= CHAR;
    dArray->array[dArray->length].value= malloc(sizeof(char));
    *((char *)(dArray->array[dArray->length].value))= value;
    dArray->length++;
    return dArray;
}
DynamicArray *pushBool(DynamicArray *dArray, bool value) {
    dArray= realloc(dArray, dArray->size + sizeof(DynamicArrayEntry));
    dArray->size+= sizeof(DynamicArrayEntry);
    dArray->array[dArray->length].type= BOOL;
    dArray->array[dArray->length].value= malloc(sizeof(bool));
    *((bool *)(dArray->array[dArray->length].value))= value;
    dArray->length++;
    return dArray;
}
DynamicArray *pushSize_t(DynamicArray *dArray, size_t value) {
    dArray= realloc(dArray, dArray->size + sizeof(DynamicArrayEntry));
    dArray->size+= sizeof(DynamicArrayEntry);
    dArray->array[dArray->length].type= SIZE_T;
    dArray->array[dArray->length].value= malloc(sizeof(size_t));
    *((size_t *)(dArray->array[dArray->length].value))= value;
    dArray->length++;
    return dArray;
}

DynamicArray *popLast(DynamicArray *dArray) {
    if (dArray->length == 0) {
        return NULL;
    }
    free(dArray->array[dArray->length - 1].value);
    dArray= realloc(dArray, dArray->size - sizeof(DynamicArrayEntry));
    dArray->size-= sizeof(DynamicArrayEntry);
    dArray->length--;
    return dArray;
}

DynamicArray *insertString(DynamicArray *dArray, size_t index, char *str) {
    if (index == dArray->length) {
        return pushString(dArray, str);
    }

    // Temporally storage here
    size_t moveNItems= dArray->length - index;
    DynamicArrayEntry temp[moveNItems];
    for (size_t i= 0; i < moveNItems; i++) {
        temp[i].type= dArray->array[index + i].type;
        temp[i].value= dArray->array[index + i].value;
    }

    dArray= realloc(dArray, dArray->size + sizeof(DynamicArrayEntry));
    dArray->size+= sizeof(DynamicArrayEntry);
    dArray->length++;

    dArray->array[index].value= malloc(sizeof(char) * (strlen(str) + 1)); 
    dArray->array[index].type= STRING;

    strcpy(dArray->array[index].value, str);

    for (size_t i= 0; i < moveNItems; i++) {
        dArray->array[index + 1 + i].type= temp[i].type;
        dArray->array[index + 1 + i].value= temp[i].value;
    }

    return dArray;
}
DynamicArray *insertInt(DynamicArray *dArray, size_t index, int value) {
    if (index == dArray->length) {
        return pushInt(dArray, value);
    }

    // Temporally storage here
    size_t moveNItems= dArray->length - index;
    DynamicArrayEntry temp[moveNItems];
    for (size_t i= 0; i < moveNItems; i++) {
        temp[i].type= dArray->array[index + i].type;
        temp[i].value= dArray->array[index + i].value;
    }

    dArray= realloc(dArray, dArray->size + sizeof(DynamicArrayEntry));
    dArray->size+= sizeof(DynamicArrayEntry);
    dArray->length++;

    dArray->array[index].value= malloc(sizeof(int));
    dArray->array[index].type= INT;

    *((int *)(dArray->array[index].value))= value;

    for (size_t i= 0; i < moveNItems; i++) {
        dArray->array[index + 1 + i].type= temp[i].type;
        dArray->array[index + 1 + i].value= temp[i].value;
    }

    return dArray;
}
DynamicArray *insertDouble(DynamicArray *dArray, size_t index, double value) {
    if (index == dArray->length) {
        return pushDouble(dArray, value);
    }

    // Temporally storage here
    size_t moveNItems= dArray->length - index;
    DynamicArrayEntry temp[moveNItems];
    for (size_t i= 0; i < moveNItems; i++) {
        temp[i].type= dArray->array[index + i].type;
        temp[i].value= dArray->array[index + i].value;
    }

    dArray= realloc(dArray, dArray->size + sizeof(DynamicArrayEntry));
    dArray->size+= sizeof(DynamicArrayEntry);
    dArray->length++;

    dArray->array[index].value= malloc(sizeof(double));
    dArray->array[index].type= DOUBLE;

    *((double *)(dArray->array[index].value))= value;

    for (size_t i= 0; i < moveNItems; i++) {
        dArray->array[index + 1 + i].type= temp[i].type;
        dArray->array[index + 1 + i].value= temp[i].value;
    }

    return dArray;
}
DynamicArray *insertChar(DynamicArray *dArray, size_t index, char value) {
    if (index == dArray->length) {
        return pushChar(dArray, value);
    }

    // Temporally storage here
    size_t moveNItems= dArray->length - index;
    DynamicArrayEntry temp[moveNItems];
    for (size_t i= 0; i < moveNItems; i++) {
        temp[i].type= dArray->array[index + i].type;
        temp[i].value= dArray->array[index + i].value;
    }

    dArray= realloc(dArray, dArray->size + sizeof(DynamicArrayEntry));
    dArray->size+= sizeof(DynamicArrayEntry);
    dArray->length++;

    dArray->array[index].value= malloc(sizeof(char));
    dArray->array[index].type= CHAR;

    *((char *)(dArray->array[index].value))= value;

    for (size_t i= 0; i < moveNItems; i++) {
        dArray->array[index + 1 + i].type= temp[i].type;
        dArray->array[index + 1 + i].value= temp[i].value;
    }

    return dArray;
}
DynamicArray *insertBool(DynamicArray *dArray, size_t index, bool value) {
    if (index == dArray->length) {
        return pushBool(dArray, value);
    }

    // Temporally storage here
    size_t moveNItems= dArray->length - index;
    DynamicArrayEntry temp[moveNItems];
    for (size_t i= 0; i < moveNItems; i++) {
        temp[i].type= dArray->array[index + i].type;
        temp[i].value= dArray->array[index + i].value;
    }

    dArray= realloc(dArray, dArray->size + sizeof(DynamicArrayEntry));
    dArray->size+= sizeof(DynamicArrayEntry);
    dArray->length++;

    dArray->array[index].value= malloc(sizeof(bool));
    dArray->array[index].type= BOOL;

    *((bool *)(dArray->array[index].value))= value;

    for (size_t i= 0; i < moveNItems; i++) {
        dArray->array[index + 1 + i].type= temp[i].type;
        dArray->array[index + 1 + i].value= temp[i].value;
    }

    return dArray;
}
DynamicArray *insertSize_t(DynamicArray *dArray, size_t index, size_t value) {
    if (index == dArray->length) {
        return pushSize_t(dArray, value);
    }

    // Temporally storage here
    size_t moveNItems= dArray->length - index;
    DynamicArrayEntry temp[moveNItems];
    for (size_t i= 0; i < moveNItems; i++) {
        temp[i].type= dArray->array[index + i].type;
        temp[i].value= dArray->array[index + i].value;
    }

    dArray= realloc(dArray, dArray->size + sizeof(DynamicArrayEntry));
    dArray->size+= sizeof(DynamicArrayEntry);
    dArray->length++;

    dArray->array[index].value= malloc(sizeof(size_t));
    dArray->array[index].type= SIZE_T;

    *((size_t *)(dArray->array[index].value))= value;

    for (size_t i= 0; i < moveNItems; i++) {
        dArray->array[index + 1 + i].type= temp[i].type;
        dArray->array[index + 1 + i].value= temp[i].value;
    }

    return dArray;
}

DynamicArray *deleteEntry(DynamicArray *dArray, size_t index) {
    free(dArray->array[index].value);
    size_t moveNItems= dArray->length -index -1;
    DynamicArrayEntry temp[moveNItems];
    for (size_t i= 0; i < moveNItems; i++) {
        temp[i].type= dArray->array[index + 1 + i].type;
        temp[i].value= dArray->array[index + 1 + i].value;
    }

    dArray= realloc(dArray, dArray->size - sizeof(DynamicArrayEntry));
    dArray->size-= sizeof(DynamicArrayEntry);
    dArray->length--;

    for (size_t i= 0; i < moveNItems; i++) {
        dArray->array[index + i].type= temp[i].type;
        dArray->array[index + i].value= temp[i].value;
    }
    return dArray;
}

DynamicArray *writeString(DynamicArray *dArray, size_t index, char *str) {
    dArray= deleteEntry(dArray, index);
    return insertString(dArray, index, str);
}
DynamicArray *writeInt(DynamicArray *dArray, size_t index, int value) {
    dArray= deleteEntry(dArray, index);
    return insertInt(dArray, index, value);
}
DynamicArray *writeDouble(DynamicArray *dArray, size_t index, double value) {
    dArray= deleteEntry(dArray, index);
    return insertDouble(dArray, index, value);
}
DynamicArray *writeChar(DynamicArray *dArray, size_t index, char value) {
    dArray= deleteEntry(dArray, index);
    return insertChar(dArray, index, value);
}
DynamicArray *writeBool(DynamicArray *dArray, size_t index, bool value) {
    dArray= deleteEntry(dArray, index);
    return insertBool(dArray, index, value);
}
DynamicArray *writeSize_t(DynamicArray *dArray, size_t index, size_t value) {
    dArray= deleteEntry(dArray, index);
    return insertSize_t(dArray, index, value);
}

enum DataType getType(DynamicArray *dArray, size_t index) {
    return dArray->array[index].type;
}
void *getPtrToValue(DynamicArray *dArray, size_t index) {
    return dArray->array[index].value;
}

char *getString(DynamicArray *dArray, size_t index) {
    return (char *)dArray->array[index].value;
}
int getInt(DynamicArray *dArray, size_t index) {
    return *((int *)(dArray->array[index].value));
}
double getDouble(DynamicArray *dArray, size_t index) {
    return *((double *)(dArray->array[index].value));
}
char getChar(DynamicArray *dArray, size_t index) {
    return *((char *)(dArray->array[index].value));
}
bool getBool(DynamicArray *dArray, size_t index) {
    return *((bool *)(dArray->array[index].value));
}
size_t getSize_t(DynamicArray *dArray, size_t index) {
    return *((size_t *)(dArray->array[index].value));
}

bool dyn_forEach(DynamicArray *dArray, dyn_ForEachCallback callback, void *cbParams) {
    for (size_t i= 0; i < dArray->length; i++) {
        if (callback(i, dArray->array[i].value, dArray->array[i].type, cbParams)) return true;
    }
    return false;
}

void logTypes(DynamicArray *dArray) {
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
            default: {
                exit(1);
                break;
            }
        }
        printf("%zu: %s\n", i, isType);
    }
    return;
}