typedef struct _Sate
{
    void (*process)();
    struct _State* (*change_state)();
} State;

void normal_process()
{
    printf("normal process!\n");
}

struct _State* change_state()
{
    State* pNextState = NULL;

    pNextState = (struct _State*)malloc(sizeof(struct _State));
    assert(NULL != pNextState);

    pNextState->process = next_process;
    pNextState->change_state = next_change_state;

    return pNextState;
}

// in all contexts, there must by only one state variable, and a change change function
typedef struct _Context
{
    State* pState;
    void (*change)(struct _Context* pContext);
} Context;

void context_change(struct _Context* pContext)
{
    State* pPre;
    assert(NULL != pContext);

    pPre = pContext->pState;
    pContext->pState = pPre->changeState();

    free(pPre);
    return;
}