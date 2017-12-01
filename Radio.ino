void AUDIO_init(void) {
  //http://kpradio.hostingradio.ru:8000/
  //http://radio.horoshee.fm:8000/mp3
  //http://kpradio.hostingradio.ru:8000/russia.radiokp128.mp3
  //const char *URL = "http://fomenkofm.hostingradio.ru:8002/fomenkoradio128.mp3";
  //const char *URL = "http://icecast.russkoeradio.cdnvideo.ru:8000/rr_m.mp3";
  //const char *URL = "http://music.myradio.ua/rep128.mp3";
  //const char *URL = "http://jazz.streamr.ru/jazz-128.mp3";
  const char *URL = "http://jazz.streamr.ru/jazz-64.mp3"; //GOOD
  //const char *URL = "http://87.110.219.34:8000/swhmp3";
  //const char *URL = "http://87.110.219.34:8000/plusmp3";
  //const char *URL = "http://91.90.255.111:80/MixFM_96"; //GOOD
  //const char *URL = "https://nashe1.hostingradio.ru:18000/nashe20-64.mp3";

  file = new AudioFileSourceHTTPStream(URL);
  buff = new AudioFileSourceBuffer(file, 4096); // you can increase default 2048 bufffersize to 4096 (seems better) or 8192 (seems much worse)
  out = new AudioOutputI2SNoDAC();
  mp3 = new AudioGeneratorMP3();
  //mp3->SetBufferSize(1000);
  //file->SetReconnect(3, 500);
  mp3->begin(buff, out);
}

void  handleAudio() {
  if (mp3->isRunning()) {
    if (!mp3->loop()) mp3->stop();
  } else {
    Serial.printf("MP3 done\n");
    delay(1000);
    //ESP.restart();
    //Serial.printf("OK! Fix\n");
  }
}
