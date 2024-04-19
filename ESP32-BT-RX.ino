#include "AudioTools.h"
#include "BluetoothA2DPSink.h"

const int buttonPin35 = 35; // Button pin 35
const int buttonPin0 = 0;

const char *kDeviceName = "ESP32-BT";
bool playState = false;
const unsigned long longPressDelay = 500;
unsigned long pressStartTime = 0;

AnalogAudioStream out;
BluetoothA2DPSink a2dp_(out);


// Forward declaration of the volume change callback in bluetooth sink mode
void avrc_volume_change_callback(int vol);
void showPlayState(bool isPlaying) {
  if (isPlaying) {
    playState = isPlaying;
  } else {
    playState = false;
  }
}

void startA2dp() {
  a2dp_.start(kDeviceName);
  vTaskDelay(2000 / portTICK_PERIOD_MS);
}

void setup() {
  startA2dp();
  pinMode(buttonPin35, INPUT_PULLUP);
  pinMode(buttonPin0, INPUT_PULLUP); 
}

void loop() {
  if (digitalRead(buttonPin35) == LOW) {
    pressStartTime = millis();
    while (digitalRead(buttonPin35) == LOW) {}
    unsigned long pressDuration = millis() - pressStartTime;
    if (pressDuration >= longPressDelay) {
      a2dp_.previous(); // Call the function when the button is pressed
    }
    else {
      a2dp_.next();
    }
  }

  if (digitalRead(buttonPin0) == LOW) {
    while (digitalRead(buttonPin0) == LOW) {}
    if (playState) {
      a2dp_.pause();
    } 
    else {
      a2dp_.play();
    }
     // Call the function when the button is pressed
  }
  showPlayState(a2dp_.get_audio_state() == ESP_A2D_AUDIO_STATE_STARTED);
  vTaskDelay(20 / portTICK_PERIOD_MS);  // Wait until next cycle
}

