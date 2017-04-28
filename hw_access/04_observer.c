// Observer Pattern – Support efficient sensor data distribition

// GasSensor.h
#ifndef GasSensor_H
#define GasSensor_H
#include "GasData.h"
/* the function pointer type
    The first value of the function pointer is to the instance
    data of the class. The second is a ptr to the new gas data
*/
typedef void (*gasDataAcceptorPtr)(void *, struct GasData*);
struct GasNotificationHandle;

/* class GasSensor */
typedef struct GasSensor GasSensor;

struct GasSensor {
    struct GasData* itsGasData;
    struct GasNotificationHandle *itsGasNH[100];
};

/* Constructors and destructors:*/
void GasSensor_Init(GasSensor* const me);
void GasSensor_Cleanup(GasSensor* const me);

/* Operations */
void GasSensor_dumpList(GasSensor* const me);
void GasSensor_newData(GasSensor* const me, unsigned int flow, unsigned int n2, unsigned int o2);
void GasSensor_notify(GasSensor* const me);
void GasSensor_subscribe(GasSensor* const me, void * instancePtr, const gasDataAcceptorPtr* aPtr);
void GasSensor_unsubscribe(GasSensor* const me, const gasDataAcceptorPtr* aPtr);
struct GasData* GasSensor_getItsGasData(const GasSensor* const me);
void GasSensor_setItsGasData(GasSensor* const me, struct GasData* p_GasData);
int GasSensor_getItsGasNH(const GasSensor* const me);
void GasSensor_addItsGasNH(GasSensor* const me, struct GasNotificationHandle * p_GasNotificationHandle);
void GasSensor_removeItsGasNH(GasSensor* const me, struct GasNotificationHandle * p_GasNotificationHandle);
void GasSensor_clearItsGasNH(GasSensor* const me);
GasSensor * GasSensor_Create(void);
void GasSensor_Destroy(GasSensor* const me);
#endif

// GasSensor.c
#include "GasSensor.h"
#include "GasData.h"
#include "GasNotificationHandle.h"

static void cleanUpRelations(GasSensor* const me);

void GasSensor_Init(GasSensor* const me) {
    me->itsGasData = NULL;
    int pos;
    for(pos = 0; pos < 100; ++pos) {
        me->itsGasNH[pos] = NULL;
    }
}

void GasSensor_Cleanup(GasSensor* const me) {
    cleanUpRelations(me);
}

void GasSensor_dumpList(GasSensor* const me) {
    int pos;
    char s[100];

    printf("Dumping registered elements/n");

    for (pos=0; pos<100; pos++) {
        if (me->itsGasNH[pos])
            if (me->itsGasNH[pos]->acceptorPtr)
                printf("Client %d: InstancePtr=%p, acceptPtr=%p/n", pos,me->itsGasNH[pos]->instancePtr, me->itsGasNH[pos]>acceptorPtr);
    };
}

void GasSensor_newData(GasSensor* const me, unsigned int flow, unsigned int n2, unsigned int o2) {
    if (!me->itsGasData)
        me->itsGasData = GasData_Create();
    
    me->itsGasData->flowRate = flow;
    me->itsGasData->N2Conc = n2;
    me->itsGasData->O2Conc = o2;
    GasSensor_notify(me);
}

void GasSensor_notify(GasSensor* const me) {
    int pos;
    char s[100];

    for (pos=0; pos<100; pos++)
        if (me->itsGasNH[pos])
            if (me->itsGasNH[pos]->acceptorPtr)
                me->itsGasNH[pos]->acceptorPtr(me->itsGasNH[pos]->instancePtr, me->itsGasData);
}

void GasSensor_subscribe(GasSensor* const me, void * instancePtr, const gasDataAcceptorPtr* aPtr) {
    struct GasNotificationHandle* gnh;
    gnh = GasNotificationHandle_Create();
    gnh->instancePtr = instancePtr;
    gnh->acceptorPtr = aPtr;
    GasSensor_addItsGasNH(me, gnh);
}

void GasSensor_unsubscribe(GasSensor* const me, const gasDataAcceptorPtr* aPtr) {
    int pos;

    for(pos = 0; pos < 100; ++pos) {
        if (me->itsGasNH[pos])
            if (me->itsGasNH[pos]->acceptorPtr == aPtr) {
                GasNotificationHandle_Destroy(me->itsGasNH[pos]);
                me->itsGasNH[pos] = NULL;
            }
    }
}

struct GasData* GasSensor_getItsGasData(const GasSensor* const me) {
    return (struct GasData*)me->itsGasData;
}

void GasSensor_setItsGasData(GasSensor* const me, struct GasData* p_GasData) {
    me->itsGasData = p_GasData;
}

int GasSensor_getItsGasNH(const GasSensor* const me) {
    int iter = 0;
    return iter;
}

void GasSensor_addItsGasNH(GasSensor* const me, struct GasNotificationHandle *p_GasNotificationHandle) {
    int pos;

    for(pos = 0; pos < 100; ++pos) {
        if (!me->itsGasNH[pos]) {
            me->itsGasNH[pos] = p_GasNotificationHandle;
            break;
        }
    }
}

void GasSensor_removeItsGasNH(GasSensor* const me, struct GasNotificationHandle *p_GasNotificationHandle) {
    int pos;

    for(pos = 0; pos < 100; ++pos) {
        if (me->itsGasNH[pos] == p_GasNotificationHandle) {
            me->itsGasNH[pos] = NULL;
        }
    }
}

void GasSensor_clearItsGasNH(GasSensor* const me) {
    int pos;
    for(pos = 0; pos < 100; ++pos)
    {
        me->itsGasNH[pos] = NULL;
    }
}

GasSensor * GasSensor_Create(void) {
    GasSensor* me = (GasSensor *) malloc(sizeof(GasSensor));
    if(me!=NULL) {
        GasSensor_Init(me);
    }
    return me;
}

void GasSensor_Destroy(GasSensor* const me) {
    if(me!=NULL) {
        GasSensor_Cleanup(me);
    }
    free(me);
}

static void cleanUpRelations(GasSensor* const me) {
    if(me->itsGasData != NULL) {
        me->itsGasData = NULL;
    }
}

// DisplayClient.h
#ifndef DisplayClient_H
#define DisplayClient_H
#include "GasSensor.h"

typedef struct DisplayClient DisplayClient;

struct DisplayClient {
    struct GasData* itsGasData;
    struct GasSensor* itsGasSensor;
};

/* Constructors and destructors:*/
void DisplayClient_Init(DisplayClient* const me);
void DisplayClient_Cleanup(DisplayClient* const me);

/* Operations */
void DisplayClient_accept(DisplayClient* const me, struct GasData* g);
void DisplayClient_alarm(DisplayClient* const me, char* alarmMsg);
void DisplayClient_register(DisplayClient* const me);
void DisplayClient_show(DisplayClient* const me);
struct GasData* DisplayClient_getItsGasData(const DisplayClient* const me);
void DisplayClient_setItsGasData(DisplayClient* const me, struct GasData* p_GasData);
struct GasSensor* DisplayClient_getItsGasSensor(const DisplayClient* const me);
void DisplayClient_setItsGasSensor(DisplayClient* const me, struct GasSensor* p_GasSensor);
DisplayClient * DisplayClient_Create(void);
void DisplayClient_Destroy(DisplayClient* const me);
#endif

// DisplayClient.c
#include "DisplayClient.h"
#include "GasData.h"
#include "GasSensor.h"

static void cleanUpRelations(DisplayClient* const me);

void DisplayClient_Init(DisplayClient* const me)
{
    me->itsGasData = NULL;
    me->itsGasSensor = NULL;
}

void DisplayClient_Cleanup(DisplayClient* const me)
{
    cleanUpRelations(me);
}

void DisplayClient_accept(DisplayClient* const me, struct GasData* g)
{
    if (!me->itsGasData)
        me->itsGasData = GasData_Create();

    if (me->itsGasData) {
        me->itsGasData->flowRate = g->flowRate;
        me->itsGasData->N2Conc = g->N2Conc;
        me->itsGasData->O2Conc = g->O2Conc;
        DisplayClient_show(me);
    };
}

void DisplayClient_alarm(DisplayClient* const me, char* alarmMsg)
{
    printf("ALERT! ");
    printf(alarmMsg);
    printf("/n/n");
}

void DisplayClient_register(DisplayClient* const me) {
    if (me->itsGasSensor)
        GasSensor_subscribe(me->itsGasSensor, me,&DisplayClient_accept);
}

void DisplayClient_show(DisplayClient* const me) {
    if (me->itsGasData) {
        printf("Gas Flow Rate = %5d/n", me->itsGasData->flowRate);
        printf("O2 Concentration = %2d/n", me->itsGasData->N2Conc);
        printf("N2 Concentration = %2d/n/n", me->itsGasData->N2Conc);
    } else {
        printf("No data available/n/n");
    }
}

struct GasData* DisplayClient_getItsGasData(const DisplayClient* const me)
{
    return (struct GasData*)me->itsGasData;
}

void DisplayClient_setItsGasData(DisplayClient* const me, struct GasData* p_GasData)
{
    me->itsGasData = p_GasData;
}

struct GasSensor* DisplayClient_getItsGasSensor(const DisplayClient* const me)
{
    return (struct GasSensor*)me->itsGasSensor;
}

void DisplayClient_setItsGasSensor(DisplayClient* const me, struct GasSensor* p_GasSensor)
{
    me->itsGasSensor = p_GasSensor;
}

DisplayClient * DisplayClient_Create(void) {
    DisplayClient* me = (DisplayClient *)
    malloc(sizeof(DisplayClient));

    if(me!=NULL) {
        DisplayClient_Init(me);
    }
    return me;
}

void DisplayClient_Destroy(DisplayClient* const me) {
    if(me!=NULL) {
        DisplayClient_Cleanup(me);
    }

    free(me);
}

static void cleanUpRelations(DisplayClient* const me) {
    if(me->itsGasData != NULL) {
        me->itsGasData = NULL;
    }

    if(me->itsGasSensor != NULL) {
        me->itsGasSensor = NULL;
    }
}

// GasData.h
#ifndef GasData_H
#define GasData_H
typedef struct GasData GasData;

struct GasData {
    unsigned short N2Conc;
    unsigned short O2Conc;
    unsigned int flowRate;
};

/* Constructors and destructors:*/
oid GasData_Init(GasData* const me);
void GasData_Cleanup(GasData* const me);
GasData * GasData_Create(void);
void GasData_Destroy(GasData* const me);
#endif

// GasData.c
#include "GasData.h"

void GasData_Init(GasData* const me)
{
}

void GasData_Cleanup(GasData* const me)
{
}

GasData * GasData_Create(void) {
    GasData* me = (GasData *) malloc(sizeof(GasData));

    if(me!=NULL) {
        GasData_Init(me);
    }
    return me;
}

void GasData_Destroy(GasData* const me) {
    if(me!=NULL) {
        GasData_Cleanup(me);
    }

    free(me);
}

