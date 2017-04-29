typedef struct _Basic
{
    void *pData;
    void (*step1)(struct _Basic* pBasic);
    void (*step2)(struct _Basic* pBasic);
    void (*process)(struct _Basic* pBasic);
} Basic;

//-- usage
void process(struct _Basic *pBasic)
{
    pBasic->step1(pBasic);
    pBasic->step2(pBasic);
}

// user should implement step1 and step2 by themselves
