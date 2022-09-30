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
    DynamicArray *myDynArray= Dyn.makeDynamicArray();
    Dyn.pushString(myDynArray, "hello world");
    Dyn.pushInt(myDynArray, 69420);
    Dyn.insertDouble(myDynArray, 6, 3.14);
    Dyn.logTypes(myDynArray);
    Dyn.deleteEntry(myDynArray, 1);
    Dyn.logTypes(myDynArray);
    Dyn.popLast(myDynArray);
    Dyn.logTypes(myDynArray);
    Dyn.forEach(myDynArray, printValues, NULL);
    return 0;
}