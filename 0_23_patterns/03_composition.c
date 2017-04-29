// example: binary tree
//----------------------------------------------------
typedef struct _NODE
{
    void *pDate;
    struct _NODE* left;
    struct _NODE* right;
} NODE;

// leaf node: left == NULL, right == NULL
// parent node: one of left and right is not NULL

//---------------------------------------------------
typedef struct _Object
{
    struct _Object** ppObject;
    int number;
    void (*operate)(struct _Object* pObject);
} Object;

void operate_of_parent(struct _Object* pObject)
{
    int index;

    assert(NULL != pObject);
    assert((NULL != pObject->ppObject) && (0 != pObject->number));

    for (index = 0; index < pObject->number; index++) {
        pObject->ppObject[index]->operate(pObject->ppObject[index]);
    }
}

void operate_of_child(struct _Object* pObject)
{
    assert(NULL != oObject);
    printf("child node!\n");
}

//-- usage
void process(Object* pObject)
{
    assert(NULL != pObject);
    pObject->operate(pObject);
}
