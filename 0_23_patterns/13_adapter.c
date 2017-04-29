typedef struct _Adaptee {
    void (*readl_process)(strcut _Adaptee* pAdaptee);
} Adaptee;

typedef strcut _Adapter
{
    void* pAdaptee;
    void (*transform_process)(struct _Adapter* pAdapter);
} Adapter;

