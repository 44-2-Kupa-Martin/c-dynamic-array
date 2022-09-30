#ifndef DYN_INCLUDED
#define DYN_INCLUDED

#include <stddef.h>
#include <stdbool.h>
// Private macros

#define DYNPRIV_CAST____INT int
#define DYNPRIV_CAST____DOUBLE double
#define DYNPRIV_CAST____CHAR char
#define DYNPRIV_CAST____BOOL bool
#define DYNPRIV_CAST____SIZE_T size_t
//

// User accessible

#define FOREACH_PARAMS(index, value, type, cbParams) size_t index, void *value, enum DataType type, void *cbParams
#define READ_VALUE(value, type) (*((DYNPRIV_CAST____##type *)value))
//

typedef struct DynamicArray DynamicArray;

enum DataType {
    INT,
    DOUBLE,
    STRING,
    CHAR,
    BOOL,
    SIZE_T,
    EMPTY
};

typedef bool (*dyn_ForEachCallback)(size_t index, void *value, enum DataType type, void *cbParams);

struct Dyn {
    DynamicArray *(*makeDynamicArray)(void);
    void (*freeDynamicArray)(DynamicArray *dArray);

    void (*pushString)(DynamicArray *dArray, char *str);
    void (*pushInt)(DynamicArray *dArray, int value);
    void (*pushDouble)(DynamicArray *dArray, double value);
    void (*pushChar)(DynamicArray *dArray, char value);
    void (*pushBool)(DynamicArray *dArray, bool value);
    void (*pushSize_t)(DynamicArray *dArray, size_t value);

    void (*popLast)(DynamicArray *dArray);

    void (*insertString)(DynamicArray *dArray, size_t index, char *str);
    void (*insertInt)(DynamicArray *dArray, size_t index, int value);
    void (*insertDouble)(DynamicArray *dArray, size_t index, double value);
    void (*insertChar)(DynamicArray *dArray, size_t index, char value);
    void (*insertBool)(DynamicArray *dArray, size_t index, bool value);
    void (*insertSize_t)(DynamicArray *dArray, size_t index, size_t value);

    void (*deleteEntry)(DynamicArray *dArray, size_t index);

    void (*writeString)(DynamicArray *dArray, size_t index, char *str);
    void (*writeInt)(DynamicArray *dArray, size_t index, int value);
    void (*writeDouble)(DynamicArray *dArray, size_t index, double value);
    void (*writeChar)(DynamicArray *dArray, size_t index, char value);
    void (*writeBool)(DynamicArray *dArray, size_t index, bool value);
    void (*writeSize_t)(DynamicArray *dArray, size_t index, size_t value);

    const enum DataType (*getType)(DynamicArray *dArray, size_t index);
    void *(*getPtrToValue)(DynamicArray *dArray, size_t index);

    char *(*getString)(DynamicArray *dArray, size_t index);
    int (*getInt)(DynamicArray *dArray, size_t index);
    double (*getDouble)(DynamicArray *dArray, size_t index);
    char (*getChar)(DynamicArray *dArray, size_t index);
    bool (*getBool)(DynamicArray *dArray, size_t index);
    size_t (*getSize_t)(DynamicArray *dArray, size_t index);

    bool (*forEach)(DynamicArray *dArray, dyn_ForEachCallback callback, void *cbParams);
    void (*logTypes)(DynamicArray *dArray);
};

extern const struct Dyn Dyn;

#endif