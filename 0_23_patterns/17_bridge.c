typedef struct _MeatDumpling
{
    void (*make)();
} MeatDumpling;

typedef struct _NormalDumpling
{
    void (*make)();
} NormalDumplin;

typedef struct _DumplingRequest
{
    int type;
    void* pDumpling;
} DumplingRequest;

//-----------
void buy_dumpling(DumplingRequest* pDumplingRequest)
{
    assert(NULL != pDumplingRequest);

    if (MEAT_TYPE == pDumpling->type)
        return (MeatDumpling*)(pDumplingRequest->pDumpling)->make();
    else
        return (NormalDumplin*)(pDumplingRequest->pDumpling)->make();
}
