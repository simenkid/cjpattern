typedef struct _PC_Client
{
    void (*request)();
} PC_Client;

void ftp_request()
{
    printf("Request from ftp!\n");
}

void http_request()
{
    printf("Request from http!\n");
}

void smtp_request()
{
    printf("Request from smtp!\n");
}

//---
typedef struct _Proxy {
    PC_Client* pClient;
} Proxy;

void process(Proxy *pProxy)
{
    assert(NULL != pProxy);

    pProxy->pClient->request();
}