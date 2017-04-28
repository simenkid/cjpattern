// Hardware Proxy Pattern – Encapsulate the hardware into a class or struct

#include <stdlib.h>
#include <stdio.h>
#define TURN_OFF (0x00)
#define INITIALIZE (0x61)
#define RUN (0x69)
// #define CHECK_ERROR (0x02)
#define CHECKERROR (1<<1)
#define DEVICE_ADDRESS (0x01FFAFD0)

void emergencyShutDown(void){
    printf("OMG We’re all gonna die!\n");
}

int main() {
    unsigned char* pDevice;
    pDevice = (unsigned char *)DEVICE_ADDRESS; // pt to device
    // for testing you can replace the above line with pDevice = malloc(1);
    *pDevice = 0xFF; // start with all bits on
    printf ("Device bits %X\n", *pDevice);

    *pDevice = *pDevice & INITIALIZE; // and the bits into
    printf ("Device bits %X\n", *pDevice);

    if (*pDevice & CHECK_ERROR) { // system fail bit on?
        emergencyShutDown();
        abort();
    } else {
        *pDevice = *pDevice & RUN;
        printf ("Device bits %X\n", *pDevice);
    };

    return 0;
};

//--------------------------------------------
#include <stdlib.h>
#include <stdio.h>

int main() {
    // Bit field
    typedef struct _statusBits {
        unsigned char enable: 1;
        unsigned char errorStatus: 1;
        unsigned char motorSpeed: 4;
        unsigned char LEDColor: 2;
    } statusBits;

    statusBits status;
    printf("size = %d\n",sizeof(status));

    status.enable = 1;
    status.errorStatus = 0;
    status.motorSpeed = 3;
    status.LEDColor = 2;

    if (status.enable)
        printf("Enabled\n");
    else
        printf ("Disabled\n");

    if (status.errorStatus)
        printf("ERROR!\n");
    else
        printf("No error\n");

    printf ("Motor speed %d\n",status.motorSpeed);
    printf ("Color %d\n",status.LEDColor);

    return 0;
};

//-- Example: HWProxyExample.h
#ifndef HWProxyExample_H
#define HWProxyExample_H

struct MotorController;
struct MotorData;
struct MotorDisplay;
struct MotorProxy;

typedef enum DirectionType {
    NO_DIRECTION,
    FORWARD,
    REVERSE
} DirectionType;

#endif

// MotorData.h
#ifndef MotorData_H
#define MotorData_H
#include "HWProxyExample.h"
typedef struct MotorData MotorData;

struct MotorData {
    unsigned char on_off;
    DirectionType direction;
    unsigned int speed;
    unsigned char errorStatus;
    unsigned char noPowerError;
    unsigned char noTorqueError;
    unsigned char BITError;
    unsigned char overTemperatureError;
    unsigned char reservedError1;
    unsigned char reservedError2;
    unsigned char unknownError;
};
#endif

// MotorProxy.h
#ifndef MotorProxy_H
#define MotorProxy_H
#include "HWProxyExample.h"
#include "MotorData.h"

/* class MotorProxy */
typedef struct MotorProxy MotorProxy;
    /* This is the proxy for the motor hardware. */
    /* Note that the speed of the motor is adjusted for the length of the rotary arm */
    /* to keep a constant speed at the end of the arm. */
struct MotorProxy {
    unsigned int* motorAddr;
    unsigned int rotaryArmLength;
};

void MotorProxy_Init(MotorProxy* const me);
void MotorProxy_Cleanup(MotorProxy* const me);

DirectionType* MotorProxy_accessMotorDirection(MotorProxy* const me);
unsigned int MotorProxy_accessMotorSpeed(MotorProxy* const me);
unsigned int MotorProxy_aceessMotorState(MotorProxy* const me);

/* keep all settings the same but clear error bits */
void MotorProxy_clearErrorStatus(MotorProxy* const me);

/* Configure must be called first, since it sets up the */
/* address of the device. */
void MotorProxy_configure(MotorProxy* const me, unsigned int length, unsigned int* location);

/* turn motor off but keep original settings */
void MotorProxy_disable(MotorProxy* const me);

/* Start up the hardware but leave all other settings of the */
/* hardware alone */
void MotorProxy_enable(MotorProxy* const me);

/* precondition: must be called AFTER configure() function. */
/* turn on the hardware to a known default state. */
void MotorProxy_initialize(MotorProxy* const me);

/* update the speed and direction of the motor together */
void MotorProxy_writeMotorSpeed(MotorProxy* const me, const DirectionType* direction, unsigned int speed);

MotorProxy * MotorProxy_Create(void); void MotorProxy_Destroy(MotorProxy* const me);
#endif


// MotorProxy.c
#include "MotorProxy.h"
/* class MotorProxy */
/* This function takes a MotorData structure and creates */
/* a device-specific unsigned int in device native format. */
static unsigned int marshal(MotorProxy* const me, const struct MotorData* mData);
static struct MotorData* unmarshal(MotorProxy* const me, unsigned int encodedMData);

void MotorProxy_Init(MotorProxy* const me) { me->motorAddr = NULL;
}

void MotorProxy_Cleanup(MotorProxy* const me) {
}

DirectionType* MotorProxy_accessMotorDirection(MotorProxy* const me) {
    MotorData mData;
    if (!me->motorData)
        return 0;

    mData = unmarshall(*me->motorAddr);
    return mData.direction;
}

unsigned int MotorProxy_accessMotorSpeed(MotorProxy* const me) {
    MotorData mData;
    if (!me->motorData)
        return 0;

    mData = unmarshall(*me->motorAddr);
    return mData.speed;
}

unsigned int MotorProxy_aceessMotorState(MotorProxy* const me) {
    MotorData mData;
    if (!me->motorData)
        return 0;

    mData = unmarshall(*me->motorAddr);
    return mData.errorStatus;
}

void MotorProxy_clearErrorStatus(MotorProxy* const me) {
    if (!me->motorData)
        return;
    *me->motorAddr &= 0xFF;
}

void MotorProxy_configure(MotorProxy* const me, unsigned int length, unsigned int* location) {
    me->rotaryArmLength = length;
    me->motorAddr = location;
}

void MotorProxy_disable(MotorProxy* const me) {
    // and with all bits set except for the enable bit
    if (!me->motorData)
        return;

    me->MotorAddr & = 0xFFFE;
}

void MotorProxy_enable(MotorProxy* const me) {
    if (!me->motorData)
        return;

    *me->motorAddr |= 1;
}

void MotorProxy_initialize(MotorProxy* const me) {
    MotorData mData;
    if (!me->motorData)
        return;

    mData.on_off = 1;
    mData.direction = 0;
    mData.speed = 0;
    mData.errorStatus = 0;
    mData.noPowerError = 0;
    mData.noTorqueError = 0;
    mData.BITError = 0;
    mData.overTemperatureError = 0;
    mData.reservedError1 = 0;
    mData.reservedError2 = 0;
    Data.unknownError = 0;
    *me->motorAddr = marshall(mData);
}

void MotorProxy_writeMotorSpeed(MotorProxy* const me, const DirectionType* direction, unsigned int speed) {
    MotorData mData
    double dPi, dArmLength, dSpeed, dAdjSpeed;

    if (!me->motorData)
        return;

    mData = unmarshall(*me->motorAddr); mData.direction = direction;

    // ok, let’s do some math to adjust for the length of the rotary arm times 10
    if (me->rotaryArmLength > 0) {
        dSpeed = speed;
        dArmLength = me->rotaryArmLength;
        dAdjSpeed = dSpeed / 2.0 / 3.14159 / dArmLength * 10.0;
        mData.speed = (int)dAdjSpeed;
    } else {
        mData.speed = speed;
    }

    *me->motorData = marshal(mData);
    return;
}

// marshal() – converts presentation (client) data format to native (motor) format
static unsigned int marshal(MotorProxy* const me, const struct MotorData* mData) {
    unsigned int deviceCmd;
    deviceCmd = 0; // set all bits to zero

    if (mData.on_off) deviceCmd |= 1; // OR in the appropriate bit

    if (mData.direction == FORWARD)
        deviceCmd |= (2 << 1);
    else if (mData.direction == REVERSE)
        deviceCmd |= (1 << 1);
    if (mData.speed < 32 && mData.speed >= 0)
        deviceCmd |= mData.speed << 3;

    if (mData.errorStatus) deviceCmd |= 1 << 8;
    if (mData.noPowerError) deviceCmd |= 1 << 9;
    if (mData.noTorqueError) deviceCmd |= 1 << 10;
    if (mData.BITError) deviceCmd |= 1 << 11;
    if (mData.overTemperatureError) deviceCmd |= 1 << 12;
    if (mData.reservedError1) deviceCmd |= 1 << 13;
    if (mData.reservedError2) deviceCmd |= 1 << 14;
    if (mData.unknownError) deviceCmd |= 1 << 15;

    return deviceCmd;
}

// unmarshal() – converts native (motor) data format to presentation (client) format
static struct MotorData* unmarshal(MotorProxy* const me, unsigned int encodedMData) {
    MotorData mData
    int temp;

    mData.on_off = encodedMData & 1;
    temp = (encodedMData & (3 << 1)) >> 1;

    if (temp == 1)
        mData.direction = REVERSE;
    else if (temp == 2)
        mData.direction = FORWARD;
    else
        mData.direction = NO_DIRECTION;

    mData.speed = encodedMData & (31 << 3);
    mData.errorStatus = encodedMData & (1 << 8);
    mData.noPowerError = encodedMData & (1 << 9);
    mData.noTorqueError = encodedMData & (1 << 10);
    mData.BITError = encodedMData & (1 <<11);
    mData.overTemperatureError = encodedMData & (1 << 12);
    mData.reservedError1 = encodedMData & (1 << 13);
    mData.reservedError2 = encodedMData & (1 << 14);
    Data.unknownError = encodedMData & (1 << 15);

    return mData;
}

MotorProxy * MotorProxy_Create(void) {
    MotorProxy* me = (MotorProxy *) malloc(sizeof(MotorProxy));

    if (me!=NULL) {
        MotorProxy_Init(me);
    }

    return me;
}

void MotorProxy_Destroy(MotorProxy* const me) {
    if (me!=NULL) {
        MotorProxy_Cleanup(me);
    }

    free(me);
}