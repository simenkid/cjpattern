#ifndef Sensor_H
#define Sensor_H

typedef struct Sensor Sensor;

// Class member
struct Sensor {
    int filterFrequency;
    int updateFrequency;
    int value;
};

// Use prefix "Sensor_" as the namesapce
int Sensor_getFilterFrequency(const Sensor* const me);
void Sensor_setFilterFrequency(Sensor* const me, int p_filterFrequency);
int Sensor_getUpdateFrequency(const Sensor* const me);
void Sensor_getValue(const Sensor* const me);

Sensor* Sensor_Create(void);
void Sensor_Destroy(Sensor* const me);

#endif