typedef struct _DATA
{
    void *pData;
} DATA;

void* getData()
{
    // pDate is static in this C module, will not disappear after assigned
    static DATA* pData = NULL;

    // if pData is there, return it
    if (NULL != pData) {
        return pData;
    }

    // else create a new one
    pData = (DATA*)malloc(sizeof(DATA));
    assert(NULL != pData);

    return (void*)pData;
}

//-- usage
int* x = (int *)getData();  // cast to data type
