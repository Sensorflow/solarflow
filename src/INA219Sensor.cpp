//
// Created by alvaro on 8/08/15.
//

#include "INA219Sensor.h"

INA219Sensor::INA219Sensor(int address, String name){
  sensor_ = new Adafruit_INA219(address);
  sensor_->begin();
  if(name.length() == 0){
    sprintf(name_, "ina219_%d",address);
  } else {
    strcpy(name_, name.c_str());
  }
}

const char * INA219Sensor::getName(){
    return name_;
}

const char * INA219Sensor::getType(){
    return "INA219";
}


float * INA219Sensor::getValues(unsigned int quantities, unsigned int * readValues){
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;

  shuntvoltage = sensor_->getShuntVoltage_mV();
  busvoltage = sensor_->getBusVoltage_V();
  current_mA = sensor_->getCurrent_mA();
  loadvoltage = busvoltage + (shuntvoltage / 1000);

  values_[0] = shuntvoltage;
  values_[1] = busvoltage;
  values_[2] = current_mA;
  values_[3] = loadvoltage;

  *readValues = 4;
  return values_;
}

Sensor * INA219Sensor::fromConfig(void *data){

  INA219Sensor *s = new INA219Sensor();
  return (Sensor *)s;

}
