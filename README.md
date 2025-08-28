# Arduino template for [DroidPad](https://github.com/umer0586/DroidPad)

In the files [DroidPad-CSV-Parsing/sketch.ino](https://github.com/umer0586/DroidPad-Arduino-template/blob/main/DroidPad-CSV-Parsing/sketch.ino) and [DroidPad-Json-Parsing/sketch.ino](https://github.com/umer0586/DroidPad-Arduino-template/blob/main/DroidPad-Json-Parsing/sketch.ino), you’ll find following functions which gets triggered whenever a message is received from DroidPad. The templates are designed for serial communication, but they can be easily adapted for use with a Wi-Fi module (only JSON not CSV).

```C++
void onSwitchEvent(const char* id, const bool& state) {

}

void onSliderEvent(const char* id, const double& value) {

}

void onButtonEvent(const char* id, const char* state) {

}

void onDpadEvent(const char* id, const char* button, const char* state) {

}

void onJoystickEvent(const char* id, const double& x, const double& y ) {

}

void onSteeringWheelEvent(const char* id, const double& angle ) {
  
}

void onAccelerometerEvent(const double& x, const double& y, const double& z) {
  
}

void onGyroscopeEvent(const double& x, const double& y, const double& z) {

}

```
