#include <stdio.h>
#include "mylibs/dyn.h"

bool printValues(FOREACH_PARAMS(index, value, type, myArgs)) {
    switch (type) {
        case STRING: {
            printf((char *)value);
            printf("\n");
            break;
        }
        case DOUBLE: {
            printf("%lf\n", READ_VALUE(value, DOUBLE));
            break;
        }
        case INT: {
            printf("%d\n", READ_VALUE(value, INT));
            break;
        }
        case SIZE_T: {
            printf("%zu\n", READ_VALUE(value, SIZE_T));
            break;
        }
        default: {
            break;
        }
    }
    return false;
}

int main(int argc, char const *argv[]) {
    DynamicArray *myDynArray= makeDynamicArray();
    PUSH_STRING(myDynArray, "hello world");
    PUSH_DOUBLE(myDynArray, 3.1415);
    PUSH_INT(myDynArray, 16);
    PUSH_SIZE_T(myDynArray, 125);
    dyn_forEach(myDynArray, printValues, NULL);
    printf("\n");
    // POP_LAST(myDynArray);
    // printf("\n");
    // dyn_forEach(myDynArray, printValues, NULL);
    // INSERT_STRING(myDynArray, 1, "mytest");
    // INSERT_INT(myDynArray, 1, 69420);
    // printf("\n");
    // dyn_forEach(myDynArray, printValues, NULL);
    // DELETE_ENTRY(myDynArray, 2);
    // printf("\n");
    // dyn_forEach(myDynArray, printValues, NULL);
    WRITE_STRING(myDynArray, 2, "bruh");
    dyn_forEach(myDynArray, printValues, NULL);
    freeDynamicArray(myDynArray);
    return 0;
}