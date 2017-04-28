#ifndef QUEUE_H_
#define QUEUE_H_H

#define QUEUE_SIE 10

// Class Queue
typedef struct Queue Queue;

struct Queue {
    int buffer[QUEUE_SIE];
    int head;
    int size;
    int tail;
    int (*isFull)(Queue* const me);
    int (*isEmpty)(Queue* const me);
    int (*getSize)(Queue* const me);
    int (*insert)(Queue* const me, int k);
    int (*remove)(Queue* const me);
};

// Constructor and destructors
void Queue_Init(
    Queue* const me,
    int (*isFullfunction)(Queue* const me),
    int (*isEmptyfunction)(Queue* const me),
    int (*getSizefunction)(Queue* const me),
    void (*insertfunction)(Queue* const me, int k),
    int (*removefunction)(Queue* const me)
);

void Queue_Cleanup(Queue* const me);

// Operations
int Queue_isFull(Queue* const me);
int Queue_isEmpty(Queue* const me);
int Queue_getSize(Queue* const me);
void Queue_insert(Queue* const me, int k);
int Queue_remove(Queue* const me);

Queue* Queue_Create(void);
void Queue_Destroty(Queue* const me);

#endif /* QUEUE_H_ */