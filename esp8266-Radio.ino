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
  wifiManager.autoConnect("radio");
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
