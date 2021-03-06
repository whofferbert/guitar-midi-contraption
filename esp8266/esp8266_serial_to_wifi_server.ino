/*
 *  ESP8266 serial reader, push data to WiFi 
 *  
 *  by William Hofferbert
 *  
 *  Read serial data and send to remote server
 *  
 *  some bits were gleaned from Internet research (processIncomingByte)
 */

#include <ESP8266WiFi.h>

// wifi connections... default modep info
const char* ssid     = "MODEP";
const char* password = "blokaslabs";

// IP address of the host we push to
IPAddress host(172,24,1,1);

// tcp server port
const unsigned int httpPort = 1234;

// wait delay time
const unsigned int wait_ms = 10;

// max line size
// some small power of 2 ... 10^2
const unsigned int MAX_INPUT = 100;

// WiFiClient in global scope
WiFiClient client;

/*
 * space reserved for ideas
 */ 

void setup() {
  Serial.begin(115200);
  //Serial.begin(31250);
  //Serial.begin(500000);

  // We start by connecting to a WiFi network
  WiFi.begin(ssid, password);

  // wait for wifi to connect
  while (WiFi.status() != WL_CONNECTED) {
    delay(wait_ms);
  }

  // wait for connection to remote server
  while (! client.connect(host, httpPort)) {
    delay(wait_ms);
  }

  // Disable nagle alg.
  client.setNoDelay(true);

}


void process_data (const char * data) {
  // push to wifi destination
  client.print(data);
}


void processIncomingByte (const byte inByte) {
  static char input_line [MAX_INPUT];
  static unsigned int input_pos = 0;

  switch (inByte) {

    case '\n':   // end of text
      input_line [input_pos] = 0;  // terminating null byte
      
      // terminator reached! process input_line here ...
      process_data (input_line);
      
      // reset buffer for next time
      input_pos = 0;  
      break;

    case '\r':   // discard carriage return, probably unneeded
      break;

    default:
      // keep adding if not full ... allow for terminating null byte
      if (input_pos < (MAX_INPUT - 1)) {
        input_line [input_pos++] = inByte;
      }
    break;

  }  // end of switch
} 

void loop() {
  while (Serial.available () > 0) {
    processIncomingByte (Serial.read ());
  }
}
