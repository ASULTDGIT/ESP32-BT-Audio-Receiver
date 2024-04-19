# ESP32-BT-Audio-Receiver
Code to turn your esp32 into a bluetooth audio receiver utilising pin 25,26 and the internal DAC. Compiled in Arduino IDE.

## Ensure you have the following libraries installed:
https://github.com/pschatzmann/ESP32-A2DP
https://github.com/pschatzmann/arduino-audio-tools

## Change the following to suit your boards button layout:

```
const int buttonPin35 = 35; // Button pin 35
const int buttonPin0 = 0;
```

## Change Device Name here
```
const char *kDeviceName = "ESP32-BT";
```
