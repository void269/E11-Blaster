/*What am I trying to figure out:
 * Can I call a specific sound at will by executing a line of code
 * 
 * What are the test parameters:
 * sound files stored on local storage named 001.wav - 010.wav.
 * Speakers connected to pins 8 and 7 (labled SPK1 and SPK2)
 * 
 * Did it work:
 * Yes, using the DFPlayer library I was able to play a sound file with 'myDFPlayer.playPhysicalTrack(track);'
 * where 'track' was a number value correlating to the name of the file (1 = 001.wav, 10 = 010.wav, etc)
 * 
 * Notes:
 * With some pointers from Protonerd I was able to get this to work.
 * Further below is his code as an example.
 */
 
#include <DFPlayer.h>
#include <DFPlayerSerial.h>



#define DFPLAYER_RX 8
#define DFPLAYER_TX 7
DFPlayer myDFPlayer;
uint8_t track = 0001;

void setup() {
  myDFPlayer.setSerial(DFPLAYER_TX, DFPLAYER_RX);
  myDFPlayer.setVolume(40);
  Serial.begin(9600);
}

void loop() {
  Serial.println(track);
  myDFPlayer.playPhysicalTrack(track);
  track++;
  delay(2000);
  
}
/*
// ====================================================================================
// ===                          SOUND FUNCTIONS                                     ===
// ====================================================================================

void HumRelaunch() {
  LoopPlay_Sound(soundFont.getHum((storage.soundFont)*NR_FILE_SF));
  sndSuppress = millis();
  hum_playing = true;
}

void SinglePlay_Sound(uint8_t track) {
#ifdef OLD_DPFPLAYER_LIB
  mp3_play_physical(track);
#else // DFPlayer_LSOS
  dfplayer.playPhysicalTrack(track);
#endif
}

void LoopPlay_Sound(uint8_t track) {
#ifdef OLD_DPFPLAYER_LIB
  mp3_loop_play(track);
#else // DFPlayer_LSOS
  dfplayer.playSingleLoop(track);
#endif
}

void Set_Volume(int8_t volumeSet) {
#ifdef OLD_DPFPLAYER_LIB
  mp3_set_volume (volumeSet);
#else
  dfplayer.setVolume(volumeSet); // Too Slow: we'll change volume on exit
#endif
delay(50);
}

void Set_Loop_Playback() {
#ifdef OLD_DPFPLAYER_LIB
  mp3_single_loop(true);
#else
  dfplayer.setSingleLoop(true);;
#endif
}

void InitDFPlayer() {
#ifdef OLD_DPFPLAYER_LIB
  mp3_set_serial (mp3player);  //set softwareSerial for DFPlayer-mini mp3 module
  mp3player.begin(9600);
  delay(50);
  mp3_set_device(1); //playback from SD card
  //delay(50);
  //mp3_set_volume (storage.volume);
#else
  dfplayer.setSerial(DFPLAYER_TX, DFPLAYER_RX);
  // AK 7.9.2016: if the storage.volume has no or invalid value, it will cause the
  // sketch to repeat setup (reset itself) - up till now no idea why?
  // this can happen if the EEPROM is erased (i.e. reflash of bootloader)
  //if (CS_LASTMEMBER < CS_VOLUME) { // if the volume cannot be set from the config menu, set it to the loudest
  //  storage.volume=31;
  //}
  //dfplayer.setVolume(storage.volume);
  //setup finished. Boot ready. We notify !
#endif
}

void Pause_Sound() {
#ifdef OLD_DPFPLAYER_LIB
  mp3_pause();
#else
  dfplayer.pause();
#endif
}

void Resume_Sound() {
#ifdef OLD_DPFPLAYER_LIB
  mp3_play();
#else
  dfplayer.play();
#endif
}
*/
