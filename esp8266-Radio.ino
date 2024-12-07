#include <Arduino.h>

#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include "DNSServer.h"
WiFiClient wclient;
#elif defined(ESP32)
#include <esp_system.h>  // Для управления частотой процессора ESP32
#include <esp_clk.h>     // Для проверки текущей частоты
#include <WiFi.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include <DNSServer.h>
WiFiClient wclient;
#endif

#include "WiFiManager.h"  // https://github.com/tzapu/WiFiManager

#include "AudioFileSourceICYStream.h"
#include "AudioFileSourceBuffer.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2SNoDAC.h"

// Randomly picked URL
//http://kpradio.hostingradio.ru:8000/
String URLs = "http://ep64server.streamr.ru:8033/europaplus64.mp3";
AudioGeneratorMP3 *mp3;
AudioFileSourceICYStream *file;
AudioFileSourceBuffer *buff;
AudioOutputI2SNoDAC *out;


void setup() {
#ifdef ESP8266
  system_update_cpu_freq(SYS_CPU_160MHZ);
#elif defined(ESP32)
  //setCpuFrequencyMhz(240);  // Вы можете заменить 240 на 80, 160 или 240
#endif
  Serial.begin(115200);
  WiFiManager wifiManager;
  wifiManager.setCustomHeadElement("<style>body>div{background:#FFF;max-width:360px;margin:0 auto 100px;padding:45px;box-shadow:0 0 20px 0 rgba(0,0,0,0.2),0 5px 5px 0 rgba(0,0,0,0.24)}input,select{background:#f2f2f2;width:100%;border:0;margin:0 0 15px;padding:15px;box-sizing:border-box;font-size:14px}button{line-height:1em;border-radius:0;text-transform:uppercase;background:#5B2500;width:100%;border:0;padding:15px;color:#FFF;font-size:14px;transition:all .3 ease;cursor:pointer}form button:hover,form button:active,form .button:focus{background:#C44F00} p{margin:15px 0 0;color:#333333;font-size:12px}a{color:#5B2500}body{background:#C44F00;font-family:sans-serif}body h1{text-align: center;}.q{opacity:0.7;}h1,form[action=\"/info\"],form[action=\"/exit\"]{display:none}</style>");

  wifiManager.autoConnect("Radio");
  Serial.println("connected...yeey :)");
  String doneURL = getURL("http://backup.privet.lv/radio/?mac=" + WiFi.macAddress());
  Serial.println(WiFi.macAddress());
  if (doneURL == "") {
    doneURL = getURL("http://backup.privet.lv/radio/?mac=" + WiFi.macAddress());
  }
  if (doneURL != "") URLs = doneURL;
  Serial.println(URLs);
  AUDIO_init();
}

void loop() {
  handleAudio();
}

// ------------- Запрос на удаленный URL -----------------------------------------
String getURL(String urls) {
  String answer;
  HTTPClient http;
  WiFiClient client;         // Create a WiFiClient object
  http.begin(client, urls);  // Use the new API
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK) {  // If the server returns data
    answer = http.getString();     // Data is here
  }
  http.end();
  return answer;
}
