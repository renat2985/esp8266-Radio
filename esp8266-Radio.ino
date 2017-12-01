#include "Arduino.h"
#include "ESP8266WiFi.h"                // Содержится в пакете. https://github.com/esp8266/Arduino

#include "ESP8266WebServer.h"           // Содержится в пакете.
#include "DNSServer.h"                  // Содержится в пакете.
#include "WiFiManager.h"                // https://github.com/tzapu/WiFiManager

#include "AudioFileSourceHTTPStream.h"  // https://github.com/earlephilhower/ESP8266Audio
#include "AudioFileSourceBuffer.h"      // https://github.com/earlephilhower/ESP8266Audio
#include "AudioGeneratorMP3.h"          // https://github.com/earlephilhower/ESP8266Audio
#include "AudioOutputI2SNoDAC.h"        // https://github.com/earlephilhower/ESP8266Audio

AudioGeneratorMP3 *mp3;
AudioFileSourceHTTPStream *file;
AudioFileSourceBuffer *buff;
AudioOutputI2SNoDAC *out;

void setup() {
  system_update_cpu_freq(SYS_CPU_160MHZ);
  Serial.begin(115200);
  WiFiManager wifiManager;
  wifiManager.autoConnect("radio");
  Serial.println("connected...yeey :)");
  AUDIO_init();
}

void loop() {
  handleAudio();
}
