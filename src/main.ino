#include <SensorflowListener.h>
#include <INA219Sensor.h>
#include <LatchingRelaySensor.h>
#include "proto/relay.pb.h"


#define INTERRUPT_PIN 2
#define WAKE_PIN 3
#define MAX485_WRITE_PIN 13
SensorflowListener listener(&Serial, INTERRUPT_PIN, WAKE_PIN, MAX485_WRITE_PIN);

uint8_t relayPins[] = {9,8,6,7,5,4};
size_t totalRelays = sizeof(relayPins)/2;

#define COMMAND_SET_RELAY 20
bool decode_string2(pb_istream_t *stream, const pb_field_t *field, void **arg)
{

    uint8_t *buffer = (uint8_t *)*arg;
    buffer[stream->bytes_left] = 0;
    if (!pb_read(stream, buffer, stream->bytes_left))
        return false;

    return true;
}

void commandSetRelay(SensorflowListener *listener){
  RelayState s = {};
  char buffer[50];
  s.name.funcs.decode = &decode_string2;
  s.name.arg = buffer;

  if(listener->receive(RelayState_fields, &s)) {
    LatchingRelaySensor *sensor = (LatchingRelaySensor*)listener->devices[buffer];
    sensor->setEnabled(s.enabled);
  }
}


void setup() {
  Serial.begin(115200);
  //initRelays();
  // TODO: intialize relays with external switch
  // Canal 0 -> Bateria
  // Canal 1 -> load
  //Canal 2 -> panel

  Sensor *s;
  s = new INA219Sensor(0x40, "load");
  listener.devices[s->getName()] = s;
  s = new INA219Sensor(0x41, "battery");
  listener.devices[s->getName()] = s;
  s = new LatchingRelaySensor(relayPins[0], relayPins[1], true, "bat_relay");
  listener.devices[s->getName()] = s;
  s = new LatchingRelaySensor(relayPins[3], relayPins[2], true, "load_relay");
  listener.devices[s->getName()] = s;
  s = new LatchingRelaySensor(relayPins[4], relayPins[5], true, "panel_relay");
  listener.devices[s->getName()] = s;
  // Setup relay commands
  listener.commands.push_back(AvailableCommand {COMMAND_SET_RELAY, &commandSetRelay});
  listener.online();

}

void loop() {
  // put your main code here, to run repeatedly:
  listener.next();
}
