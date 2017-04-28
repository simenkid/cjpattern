typedef struct _Object
{
	struct _Object* prev;

	void (*decorate)(struct _Object* pObject);
} Object;

void decorate(struct _Object* pObject)
{
	assert(NULL != pObject);

	if (NULL != pObject->prev)
		pObject->prev->decorate(pObject->prev);

	printf("Normal decorate\n");
}
