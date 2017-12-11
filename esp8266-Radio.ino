#include <Arduino.h>

#include "ESP8266WebServer.h"           // Содержится в пакете.
#include "DNSServer.h"                  // Содержится в пакете.
#include "WiFiManager.h"                // https://github.com/tzapu/WiFiManager

#include <ESP8266WiFi.h>
#include "AudioFileSourceICYStream.h"   // https://github.com/earlephilhower/ESP8266Audio
#include "AudioFileSourceBuffer.h"      // https://github.com/earlephilhower/ESP8266Audio
#include "AudioGeneratorMP3.h"          // https://github.com/earlephilhower/ESP8266Audio
//#include "AudioGeneratorAAC.h"          // https://github.com/earlephilhower/ESP8266Audio
#include "AudioOutputI2SNoDAC.h"        // https://github.com/earlephilhower/ESP8266Audio


// To run, set your ESP8266 build to 160MHz, update the SSID info, and upload.

// Randomly picked URL
  //http://kpradio.hostingradio.ru:8000/
  //http://radio.horoshee.fm:8000/mp3
  //http://kpradio.hostingradio.ru:8000/russia.radiokp128.mp3
  //const char *URL = "http://fomenkofm.hostingradio.ru:8002/fomenkoradio128.mp3";
  //const char *URL = "http://icecast.russkoeradio.cdnvideo.ru:8000/rr_m.mp3";
  //const char *URL = "http://music.myradio.ua/rep128.mp3";
  //const char *URL = "http://jazz.streamr.ru/jazz-128.mp3";
  //const char *URL = "http://87.110.219.34:8000/swhmp3";
  //const char *URL = "http://87.110.219.34:8000/plusmp3";
  //const char *URL = "http://91.90.255.111:80/MixFM_96"; //GOOD
  //const char *URL = "https://nashe1.hostingradio.ru:18000/nashe20-64.mp3";
  const char *URL = "http://jazz.streamr.ru/jazz-64.mp3"; //GOOD

AudioGeneratorMP3 *mp3;
AudioFileSourceICYStream *file;
AudioFileSourceBuffer *buff;
AudioOutputI2SNoDAC *out;

void setup(){
   system_update_cpu_freq(SYS_CPU_160MHZ);
  Serial.begin(115200);
  WiFiManager wifiManager;
  wifiManager.autoConnect("radio");
  Serial.println("connected...yeey :)");
  AUDIO_init();
}

void loop(){
 handleAudio();
}

