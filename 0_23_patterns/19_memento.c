typedef struct _Action
{
    int type;
    struct _Action* next;

    void* pDate;
    void (*process)(void* pData);
} Action;

typedef struct _Organizer
{
    int number;
    Action* pActionHead;

    Action* (*create)();
    void (*restore)(struct _Organizer* pOrganizer);
} Organizer;


//---------
void restore(struct _Organizer* pOrganizer)
{
    Action* pHead;
    assert(NULL != pOrganizer);

    pHead = pOrganizer->pActionHead;
    pHead->process(pHead->pData);
    pOrganizer->pActionHead = pHead->next;
    pOrganizer->number--;
    free(pHead);

    return;
}