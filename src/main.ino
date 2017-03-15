#include <SensorflowListener.h>
#include <INA219Sensor.h>


#define INTERRUPT_PIN 2
#define WAKE_PIN 3
#define MAX485_WRITE_PIN 13
SensorflowListener listener(&Serial, INTERRUPT_PIN, WAKE_PIN, MAX485_WRITE_PIN);

uint8_t relayPins[] = {9,8,6,7,5,4};
size_t totalRelays = sizeof(relayPins)/2;



void initRelays() {
  for(size_t i = 0; i < sizeof(relayPins); i++){
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], LOW);
  }
}

bool setRelay(uint8_t channel, bool enabled) {
  if(channel < totalRelays){
    digitalWrite(relayPins[2*channel], !enabled);
    digitalWrite(relayPins[2*channel + 1], enabled);
    delay(100);
    digitalWrite(relayPins[2*channel], LOW);
    digitalWrite(relayPins[2*channel + 1], LOW);
    return true;
  }
  return false;
}

void setup() {
  Serial.begin(115200);
  initRelays();
  // TODO: intialize relays with external switch
  // Canal 0 -> Bateria
  //setRelay(0, true);
  // Canal 1 -> load
  //setRelay(1, true);
  //Canal 2 -> panel
  setRelay(2, false);

  Sensor *s;
  s = new INA219Sensor(0x40, "load");
  listener.devices[s->getName()] = s;
  s = new INA219Sensor(0x41, "battery");
  listener.devices[s->getName()] = s;
  listener.online();

}

void loop() {
  // put your main code here, to run repeatedly:
  listener.next(false);
}
