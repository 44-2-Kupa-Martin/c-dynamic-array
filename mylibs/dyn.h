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

#define PUSH_STRING(dArray, value) dArray= pushString(dArray, value)
#define PUSH_INT(dArray, value) dArray= pushInt(dArray, value)
#define PUSH_DOUBLE(dArray, value) dArray= pushDouble(dArray, value)
#define PUSH_CHAR(dArray, value) dArray= pushChar(dArray, value)
#define PUSH_BOOL(dArray, value) dArray= pushBool(dArray, value)
#define PUSH_SIZE_T(dArray, value) dArray= pushSize_t(dArray, value)

#define INSERT_STRING(dArray, index, value) dArray= insertString(dArray, index, value)
#define INSERT_INT(dArray, index, value) dArray= insertInt(dArray, index, value)
#define INSERT_DOUBLE(dArray, index, value) dArray= insertDouble(dArray, index, value)
#define INSERT_STRING(dArray, index, value) dArray= insertString(dArray, index, value)
#define INSERT_CHAR(dArray, index, value) dArray= insertChar(dArray, index, value)
#define INSERT_BOOL(dArray, index, value) dArray= insertBool(dArray, index, value)
#define INSERT_SIZE_T(dArray, index, value) dArray= insertSize_t(dArray, index, value)

#define WRITE_STRING(dArray, index, value) dArray= writeString(dArray, index, value)
#define WRITE_INT(dArray, index, value) dArray= writeInt(dArray, index, value)
#define WRITE_DOUBLE(dArray, index, value) dArray= writeDouble(dArray, index, value)
#define WRITE_STRING(dArray, index, value) dArray= writeString(dArray, index, value)
#define WRITE_CHAR(dArray, index, value) dArray= writeChar(dArray, index, value)
#define WRITE_BOOL(dArray, index, value) dArray= writeBool(dArray, index, value)
#define WRITE_SIZE_T(dArray, index, value) dArray= writeSize_t(dArray, index, value)

#define POP_LAST(dArray) dArray= popLast(dArray)
#define DELETE_ENTRY(dArray, index) dArray= deleteEntry(dArray, index)
//


enum DataType {
    INT,
    DOUBLE,
    STRING,
    CHAR,
    BOOL,
    SIZE_T
};

typedef struct DynamicArrayEntry {
    void *value;
    enum DataType type;
} DynamicArrayEntry;

typedef struct DynamicArray {
    size_t length;
    size_t size;
    DynamicArrayEntry array[];
} DynamicArray;

typedef bool (*dyn_ForEachCallback)(size_t index, void *value, enum DataType type, void *cbParams);

DynamicArray *makeDynamicArray(void);
void freeDynamicArray(DynamicArray *dArray);

DynamicArray *pushString(DynamicArray *dArray, char *str);
DynamicArray *pushInt(DynamicArray *dArray, int value);
DynamicArray *pushDouble(DynamicArray *dArray, double value);
DynamicArray *pushChar(DynamicArray *dArray, char value);
DynamicArray *pushBool(DynamicArray *dArray, bool value);
DynamicArray *pushSize_t(DynamicArray *dArray, size_t value);

DynamicArray *popLast(DynamicArray *dArray);

DynamicArray *insertString(DynamicArray *dArray, size_t index, char *str);
DynamicArray *insertInt(DynamicArray *dArray, size_t index, int value);
DynamicArray *insertDouble(DynamicArray *dArray, size_t index, double value);
DynamicArray *insertChar(DynamicArray *dArray, size_t index, char value);
DynamicArray *insertBool(DynamicArray *dArray, size_t index, bool value);
DynamicArray *insertSize_t(DynamicArray *dArray, size_t index, size_t value);

DynamicArray *deleteEntry(DynamicArray *dArray, size_t index);

DynamicArray *writeString(DynamicArray *dArray, size_t index, char *str);
DynamicArray *writeInt(DynamicArray *dArray, size_t index, int value);
DynamicArray *writeDouble(DynamicArray *dArray, size_t index, double value);
DynamicArray *writeChar(DynamicArray *dArray, size_t index, char value);
DynamicArray *writeBool(DynamicArray *dArray, size_t index, bool value);
DynamicArray *writeSize_t(DynamicArray *dArray, size_t index, size_t value);



enum DataType getType(DynamicArray *dArray, size_t index);
void *getPtrToValue(DynamicArray *dArray, size_t index);

char *getString(DynamicArray *dArray, size_t index);
int getInt(DynamicArray *dArray, size_t index);
double getDouble(DynamicArray *dArray, size_t index);
char getChar(DynamicArray *dArray, size_t index);
bool getBool(DynamicArray *dArray, size_t index);
size_t getSize_t(DynamicArray *dArray, size_t index);

bool dyn_forEach(DynamicArray *dArray, dyn_ForEachCallback callback, void *cbParams);
void logTypes(DynamicArray *dArray);

#endif