#include <stdio.h>
#include "mylibs/maleta_dyn.h"


int main(int argc, char const *argv[])
{
    DynamicArray *myDynArray= newDynamicArray();
    printf("%p\n", myDynArray);
    myDynArray= pushString(myDynArray, "hello");
    printf("%p\n", myDynArray);
    myDynArray= pushInt(myDynArray, 5);
    printf("%p\n", myDynArray);
    myDynArray= pushDouble(myDynArray, 14.2);
    printf("%p\n", myDynArray);
    size_t read;
    printf("Read: ");
    scanf("%zu", &read);
    switch (getType(myDynArray, read)) {
        case STRING: {
            printf("Value: %s\n", getString(myDynArray, read));
            break;
        }
        case INT: {
            printf("Value: %d\n", getInt(myDynArray, read));
            break;
        }
        case DOUBLE: {
            printf("Value: %lf\n", getDouble(myDynArray, read));
            break;
        }
        default: {
            break;
        }
    }
    freeDynamicArray(myDynArray);
    return 0;
}