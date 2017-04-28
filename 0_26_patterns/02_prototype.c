// prototype is about the data cloning (shallow copy)

typedef struct _DATA
{
    struct _DATA* (*copy)(struct _DATA* pData);
} DATA;

// copy function
struct _DATA* data_copy_A(struct _DATA* p)
{
    DATA* pResult = (DATA*)malloc(sizeof(DATA));

    assert(NULL != pResult);

    memmove(pResult, pData, sizeof(DATA));
    return pResult;
};

DATA data_A = {
    data_copy_A
};

//-- usage
struct _DATA* clone(struct _DATA* pData)
{
    return pData->copy(pDate);
}
