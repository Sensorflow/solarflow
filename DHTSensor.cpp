//
// Created by alvaro on 8/08/15.
//

#include "DHTSensor.h"
#include "DHT.h"

DHTSensor::DHTSensor(int pin, int dhtType, String name){
  sensor_ = new DHT(pin, dhtType);
  sensor_->begin();
  if(name.length() == 0){
    sprintf(name_, "dht%d_%d",dhtType, pin);
  } else {
    strcpy(name_, name.c_str());
  }
}

const char * DHTSensor::getName(){
    return name_;
}

const char * DHTSensor::getType(){
    return "DHT";
}


float * DHTSensor::getValues(unsigned int quantities, unsigned int * readValues){
  unsigned int totalRead = 0;
  if(quantities & TEMPERATURE) {
    values_[totalRead] = sensor_->readTemperature();
    totalRead++;
  }

  if(quantities & HUMIDITY) {
    values_[totalRead] = sensor_->readHumidity();
    totalRead++;
  }
  *readValues = totalRead;
  return values_;
}

Sensor * DHTSensor::fromConfig(void *data){

  DHTSensor *s = new DHTSensor(4,4);
  return (Sensor *)s;

}
