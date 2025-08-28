#include "ArduinoJson.h"
#include<string.h>

JsonDocument doc;

void setup() {
  Serial.begin(9600);
  Serial.println("Welcome");

}

void onSwitchEvent(const char* id, const bool& state) {
  Serial.println();
  Serial.print("Switch(");
  Serial.print(" id = ");
  Serial.print(id);
  Serial.print(" state = ");
  Serial.print(state);
  Serial.print(" )");
  Serial.println();
}

void onSliderEvent(const char* id, const double& value) {
  Serial.println();
  Serial.print("Slider( id = ");
  Serial.print(id);
  Serial.print(", value = ");
  Serial.print(value, 8);
  Serial.print(" )");
  Serial.println();
}

void onButtonEvent(const char* id, const char* state) {
  Serial.println();
  Serial.print("Button(");
  Serial.print(" id = ");
  Serial.print(id);
  Serial.print(" state = ");
  Serial.print(state);
  Serial.print(" )");
  Serial.println();
}

void onDpadEvent(const char* id, const char* button, const char* state) {
  Serial.println();
  Serial.print("Dpad( id = ");
  Serial.print(id);
  Serial.print(", button = ");
  Serial.print(button);
  Serial.print(", state = ");
  Serial.print(state);
  Serial.print(" )");
  Serial.println();
}

void onJoystickEvent(const char* id, const double& x, const double& y ) {
  Serial.println();
  Serial.print("Joystick( id = ");
  Serial.print(id);
  Serial.print(", x = ");
  Serial.print(x, 8);
  Serial.print(", y = ");
  Serial.print(y, 8);
  Serial.print(" )");
  Serial.println();
}

void onSteeringWheelEvent(const char* id, const double& angle ) {
  Serial.println();
  Serial.print("SteeringWheel( id = ");
  Serial.print(id);
  Serial.print(", angle = ");
  Serial.print(angle, 8);
  Serial.print(" )");
  Serial.println();
}

void onAccelerometerEvent(const double& x, const double& y, const double& z) {
  Serial.println();
  Serial.print("Accelerometer(x = ");
  Serial.print(x, 8);
  Serial.print(" y = ");
  Serial.print(y, 8);
  Serial.print(" z = ");
  Serial.print(z, 8);
  Serial.print(" )");
  Serial.println();
}

void onGyroscopeEvent(const double& x, const double& y, const double& z) {
  Serial.println();
  Serial.print("Gyroscope(x = ");
  Serial.print(x, 8);
  Serial.print(" y = ");
  Serial.print(y, 8);
  Serial.print(" z = ");
  Serial.print(z, 8);
  Serial.print(" )");
  Serial.println();
}

void loop() {

  if (Serial.available()) {

    deserializeJson(doc, Serial);


    const char* type = doc["type"];

    // For a sensor event there is no id in json message
    if (strcmp(type, "ACCELEROMETER") == 0) {
      onAccelerometerEvent(doc["x"], doc["y"], doc["z"]);
      return;
    } else if (strcmp(type, "GYROSCOPE") == 0) {
      onGyroscopeEvent(doc["x"], doc["y"], doc["z"]);
      return;
    }
    
    // Any event other then sensor event contains id
    const char* id = doc["id"];

    if (strcmp(type, "SWITCH") == 0){
      onSwitchEvent(id,doc["state"]);
    }
    else if (strcmp(type, "SLIDER") == 0){
      onSliderEvent(id,doc["value"]);
    }
    else if (strcmp(type, "BUTTON") == 0){
      onButtonEvent(id,doc["state"]);
    }
    else if (strcmp(type, "DPAD") == 0){
      onDpadEvent(id,doc["button"],doc["state"]);
    }
    else if (strcmp(type, "JOYSTICK") == 0){
      onJoystickEvent(id,doc["x"],doc["y"]);
    }
    else if (strcmp(type, "STEERING_WHEEL") == 0){
      onSteeringWheelEvent(id,doc["angle"]);
    }
    

  }


}
