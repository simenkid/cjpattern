typedef struct _Interpret
{
    int type;
    void* (*process)(void* pData, int* type, int* result);
} Interpret;

// define interpreters for digit, letter, and underline
#define DIGITAL_TYPE    1
#define LETTER_TYPE     2
#define UNDERLINE_TYPE  3

void* digital_process(void* pData, int* type, int* result)
{
    UINT8* str;
    assert(NULL != pDate && NULL !== type && NULL != result);


    str = (UINT8*) pData;

    while (*str >= '0' && *str <= '9') {
        str++;
    }

    if (*str == '\0') {
        *result = TRUE;
        return NULL;
    }

    if (*str == '_') {
        *result = TRUE;
        *type = UNDERLINE_TYPE;
        return str;
    }

    if (*str >= 'a' && *str <= 'z' || *str >= 'A' && *str <= 'Z') {
        *result = TRUE;
        *type = LETTER_TYPE;
        return str;
    }

    *result = FALSE;
    return NULL;
}

void* letter_process(void* pData, int* type, int* result)
{
    UINT8* str;
    assert(NULL != pDate && NULL !== type && NULL != result);


    str = (UINT8*) pData;

    while (*str >= 'a' && *str <= 'z' || *str >= 'A' && *str <= 'Z') {
        str++;
    }

    if (*str == '\0') {
        *result = TRUE;
        return NULL;
    }

    if (*str == '_') {
        *result = TRUE;
        *type = UNDERLINE_TYPE;
        return str;
    }

    if (*str >= '0' && *str <= '9') {
        *result = TRUE;
        *type = DIGITAL_TYPE;
        return str;
    }

    *result = FALSE;
    return NULL;
}

void* underline_process(void* pData, int* type, int* result)
{
    UINT8* str;
    assert(NULL != pDate && NULL !== type && NULL != result);


    str = (UINT8*) pData;

    while ('_' == *str) {
        str++;
    }

    if (*str == '\0') {
        *result = TRUE;
        return NULL;
    }

    if (*str >= 'a' && *str <= 'z' || *str >= 'A' && *str <= 'Z') {
        *result = TRUE;
        *type = LETTER_TYPE;
        return str;
    }

    if (*str >= '0' && *str <= '9') {
        *result = TRUE;
        *type = DIGITAL_TYPE;
        return str;
    }

    *result = FALSE;
    return NULL;
}
