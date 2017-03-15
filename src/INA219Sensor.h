//
// Created by alvaro on 8/08/15.
//
#include "Sensor.h"
#include <Wire.h>
#include <Adafruit_INA219.h>
#ifndef INA219_SENSOR_H
#define INA219_SENSOR_H


class INA219Sensor: public Sensor {
public:
  INA219Sensor(int address=0x40, String name = "");
  const char* getName();
  float* getValues(unsigned int quantities, unsigned int * readValues);
  static const char* getType();
  static Sensor* fromConfig(void *);
private:
  char name_[10];
  float values_[4];
  Adafruit_INA219 *sensor_;
};


#endif //SENSOR_MONITOR_DEVICE_H
