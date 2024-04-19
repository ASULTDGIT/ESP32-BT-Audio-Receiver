#include "AudioTools.h"
#include "BluetoothA2DPSink.h"

//Set Buttons
const int buttonPin35 = 35; 
const int buttonPin0 = 0;

// Set Device Names
const char *kDeviceName = "ESP32-BT";

// Vars for maintaing current play state for play/pause functionality and next/previous functionality.
bool playState = false;
const unsigned long longPressDelay = 500;
unsigned long pressStartTime = 0;

//Initialize Internal DAC and AD2P Sink
AnalogAudioStream out;
BluetoothA2DPSink a2dp_(out);


// Forward declaration of the volume change callback in bluetooth sink mode
void avrc_volume_change_callback(int vol);

// Get Current Play State
void showPlayState(bool isPlaying) {
  if (isPlaying) {
    playState = isPlaying;
  } else {
    playState = false;
  }
}

//Start A2DP
void startA2dp() {
  a2dp_.start(kDeviceName);
  vTaskDelay(2000 / portTICK_PERIOD_MS);
}

void setup() {
  startA2dp();
  // Init Buttons
  pinMode(buttonPin35, INPUT_PULLUP);
  pinMode(buttonPin0, INPUT_PULLUP); 
}

void loop() {
  // Determine Button Pressed
  if (digitalRead(buttonPin35) == LOW) {
    // Grabs time for determining if next/previous
    pressStartTime = millis();
    //Holds Loop until button is Released
    while (digitalRead(buttonPin35) == LOW) {}
    //Determines if button was held longer than .5 seconds and if so will go previous, if yes will go next
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
     
  }
  //Gets Play state
  showPlayState(a2dp_.get_audio_state() == ESP_A2D_AUDIO_STATE_STARTED);
  vTaskDelay(20 / portTICK_PERIOD_MS);  // Wait until next cycle
}

