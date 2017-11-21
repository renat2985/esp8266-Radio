void AUDIO_init(void) {
  const char *URL = "http://fomenkofm.hostingradio.ru:8002/fomenkoradio128.mp3";
  file = new AudioFileSourceHTTPStream(URL);
  buff = new AudioFileSourceBuffer(file, 2048);
  out = new AudioOutputI2SNoDAC();
  mp3 = new AudioGeneratorMP3();
  mp3->begin(buff, out);
}

void  handleAudio() {
  if (mp3->isRunning()) {
    if (!mp3->loop()) mp3->stop();
  } else {
    Serial.printf("MP3 done\n");
    delay(1000);
  }
}
