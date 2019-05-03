#include <ResponsiveAnalogRead.h>
#include <Bounce2.h>

// (de)bouncing the switches

const int pb1_pin = 2;
const int pb2_pin = 5;
const int button_ms_delay = 20;

Bounce pb1 = Bounce();
Bounce pb2 = Bounce();

// responsive analog read on the pots

ResponsiveAnalogRead a1(A9,false);
ResponsiveAnalogRead a2(A8,false);
ResponsiveAnalogRead a3(A7,false);
ResponsiveAnalogRead a4(A6,false);

void setup() {
  // maybe teensy serial debugging
  //Serial.begin(115200);
  
  // taking to serial2 (esp8266) 115200
  Serial2.begin(115200);
  
  // switches are pulled high internally
  // short to ground when connected
  pinMode(pb1_pin, INPUT_PULLUP);
  pinMode(pb2_pin, INPUT_PULLUP);
  pb1.attach(pb1_pin);
  pb1.interval(button_ms_delay);
  pb2.attach(pb2_pin);
  pb2.interval(button_ms_delay);
}

void update_all_switches() {
  // stuff and things
  pb1.update();
  pb2.update();
}

void update_all_analogs() {
  a1.update();
  a2.update();
  a3.update();
  a4.update();
}

void send_data_to_esp() {
  Serial2.print("A1:");
  Serial2.print(a1.getValue());
  Serial2.print(";A2:");
  Serial2.print(a2.getValue());
  Serial2.print(";A3:");
  Serial2.print(a3.getValue());
  Serial2.print(";A4:");
  Serial2.print(a4.getValue());
  Serial2.print(";D1:");
  Serial2.print(pb1.read());
  Serial2.print(";D2:");
  Serial2.print(pb2.read());
  Serial2.println();
}

void loop() {
  // put your main code here, to run repeatedly:
  // update all analog sensors
  update_all_analogs();
  update_all_switches();
  send_data_to_esp();
  delay(16);
}
