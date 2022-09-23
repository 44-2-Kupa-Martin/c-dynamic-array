#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum DataType {
    INT,
    STRING,
    DOUBLE
};

typedef struct DynamicArrayEntry
{
    void *value;
    enum DataType type;

} DynamicArrayEntry;

typedef struct DynamicArray {
    size_t length;
    size_t size;
    DynamicArrayEntry array[];
} DynamicArray;

DynamicArray *newDynamicArray(void);

DynamicArray *pushString(DynamicArray *, void *);
DynamicArray *pushInt(DynamicArray *, int);
DynamicArray *pushDouble(DynamicArray *, double);


int main(int argc, char const *argv[])
{
    DynamicArray *myDynArray= newDynamicArray();
    myDynArray= pushString(myDynArray, (char *)"test\n");
    myDynArray= pushInt(myDynArray, 5);
    printf((char *)myDynArray->array[0].value);
    printf("%d\n", *((int *)(myDynArray->array[1].value)));
    return 0;
}

DynamicArray *newDynamicArray(void) {
    DynamicArray *myArray= malloc(sizeof *myArray);
    myArray->size= sizeof *myArray;
    myArray->length= 0;
    return myArray;
}

DynamicArray *pushString(DynamicArray *dArray, void *value) {
    char *myStr= (char *)value;
    size_t strLength= strlen(myStr)+1;
    dArray= realloc(dArray, dArray->size + sizeof(DynamicArrayEntry));
    dArray->size+= sizeof(DynamicArrayEntry);
    dArray->array[dArray->length].value= malloc(sizeof(char)*strLength);
    dArray->array[dArray->length].type= STRING;
    if (value != NULL) {
        strcpy((char *)dArray->array[dArray->length].value, myStr);
    } else {
        char *temp= dArray->array[dArray->length].value;
        *temp= '\0';
    }
    dArray->length++;
    return dArray;
}

DynamicArray *pushInt(DynamicArray *dArray, int value) {
    dArray= realloc(dArray, dArray->size + sizeof(DynamicArrayEntry));
    dArray->size+= sizeof(DynamicArrayEntry);
    dArray->array[dArray->length].value= malloc(sizeof(int));
    dArray->array[dArray->length].type= INT;
    int *temp= dArray->array[dArray->length].value;
    *temp= value;
    dArray->length++;
    return dArray;
}

DynamicArray *pushDouble(DynamicArray *dArray, double value) {
    dArray= realloc(dArray, dArray->size + sizeof(DynamicArrayEntry));
    dArray->size+= sizeof(DynamicArrayEntry);
    dArray->array[dArray->length].value= malloc(sizeof(double));
    dArray->array[dArray->length].type= DOUBLE;
    double *temp= dArray->array[dArray->length].value;
    *temp= value;
    dArray->length++;
    return dArray;
}