// Called when a metadata event occurs (i.e. an ID3 tag, an ICY block, etc.
void MDCallback(void *cbData, const char *type, bool isUnicode, Stream *stream)
{
 const char *ptr = reinterpret_cast<const char *>(cbData);
 (void) isUnicode; // Punt this ball for now
 Serial.printf("METADATA(%s) '%s' = '%s'\n", ptr, type, stream->readString().c_str());
 Serial.flush();
}

// Called when there's a warning or error (like a buffer underflow or decode hiccup)
void StatusCallback(void *cbData, int code, const char *string)
{
 const char *ptr = reinterpret_cast<const char *>(cbData);
 Serial.printf("STATUS(%s) '%d' = '%s'\n", ptr, code, string);
 if (code == 3) {
  Serial.printf("Buffering restart");
  ESP.restart();
 }
 Serial.flush();
}

void AUDIO_init(void) {
 //file = new AudioFileSourceICYStream(URL);
 file = new AudioFileSourceICYStream(URLs.c_str());
// file->RegisterMetadataCB(MDCallback, (void*)"ICY");
 buff = new AudioFileSourceBuffer(file, 1024*4); // you can increase default 2048 bufffersize to 4096 (seems better) or 8192
 buff->RegisterStatusCB(StatusCallback, (void*)"buffer");
 out = new AudioOutputI2SNoDAC();
 mp3 = new AudioGeneratorMP3();
 mp3->RegisterStatusCB(StatusCallback, (void*)"mp3");
 mp3->begin(buff, out);
 delay(1000);
}

void  handleAudio() {
 //static int lastms = 0;
 if (mp3->isRunning()) {
  //if (millis()-lastms > 1000) {
  // lastms = millis();
  // Serial.printf("Running for %d ms...\n", lastms);
  // Serial.flush();
  //}
  if (!mp3->loop()) mp3->stop();
 } else {
  Serial.printf("MP3 done\n");
  delay(1000);
 }
}
