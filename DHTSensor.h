//
// Created by alvaro on 8/08/15.
//
#include "Sensor.h"
#include "DHT.h"

#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H


class DHTSensor: public Sensor {
public:
  DHTSensor(int pin, int dhtType, String name = "");
  const char* getName();
  float* getValues(unsigned int quantities, unsigned int * readValues);
  static const char* getType();
  static Sensor* fromConfig(void *);
private:
  char name_[10];
  float values_[2];
  DHT *sensor_;
};


#endif //SENSOR_MONITOR_DEVICE_H
