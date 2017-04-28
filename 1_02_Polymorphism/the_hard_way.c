int acquireValue(Sensor* me)
{
    int *r, *w; // read and write addresses
    int j;

    switch (me->whatKindOfInterface) {
        case MEMORYMAPPED:
            w = (int*)WRITEADDR;    // address to write to sensor
            *w = WRITEMASK;         // sensor command to force a read

            for (j = 0; i < 100; j++) { /* wait loop */ };

            r = (int *)READADDR;
            me->Value = *r;
            break;
        case PORTMAPPED:
            me->Value = inp(SENSORPORT);
            /* inp() is a complier-specific port function */
            break;
    }

    return me->Value;
};
