#include <string.h>
#include <stdlib.h>

#define MAX_TOKENS 5
#define MAX_TOKEN_LENGTH 30  // Maximum length of each token (adjust as needed)
#define BUFFER_SIZE 64
char buffer[BUFFER_SIZE]; // A character array to hold the incoming string


char tokens[MAX_TOKENS][MAX_TOKEN_LENGTH];
int splitString(const char*, char, char tokens[MAX_TOKENS][MAX_TOKEN_LENGTH]);
void parseEvent(const char*);

void setup() {
  Serial.begin(9600);
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
    int numBytes = Serial.readBytesUntil('\n', buffer, BUFFER_SIZE - 1);
    // Add a null terminator to the end of the string
    buffer[numBytes] = '\0';

    parseEvent(buffer);

  }

}

void parseEvent(const char* csvEvent) {
  int tokenCount = splitString(buffer, ',', tokens);
  if (strcmp(tokens[0], "ACCELEROMETER") == 0) {
    onAccelerometerEvent(
      strtod(tokens[1], NULL), strtod(tokens[2], NULL), strtod(tokens[3], NULL)
    );
    return;
  }
  else if (strcmp(tokens[0], "GYROSCOPE") == 0) {
    onGyroscopeEvent(
      strtod(tokens[1], NULL), strtod(tokens[2], NULL), strtod(tokens[3], NULL)
    );
    return;
  }

  const char* id = tokens[0];
  const char* type = tokens[1];

  if (strcmp(type, "SWITCH") == 0) {
    onSwitchEvent(id, strcmp(tokens[2], "true") ? true : false);
  }
  else if (strcmp(type, "SLIDER") == 0) {
    onSliderEvent(id, strtod(tokens[2], NULL));
  }
  else if (strcmp(type, "BUTTON") == 0) {
    onButtonEvent(id, tokens[2]);
  }
  else if (strcmp(type, "DPAD") == 0) {
    onDpadEvent(id, tokens[2], tokens[3]);
  }
  else if (strcmp(type, "JOYSTICK") == 0) {
    onJoystickEvent(id, strtod(tokens[2], NULL), strtod(tokens[3], NULL));
  }
  else if (strcmp(type, "STEERING_WHEEL") == 0) {
    onSteeringWheelEvent(id, strtod(tokens[2], NULL));
  }


}

int splitString(const char* str, char delimiter, char tokens[MAX_TOKENS][MAX_TOKEN_LENGTH]) {
  int tokenCount = 0;
  int startIdx = 0;
  int strLen = strlen(str);

  // Iterate through the string to find tokens
  for (int i = 0; i <= strLen; i++) {
    // If we find a delimiter or the end of the string
    if (str[i] == delimiter || str[i] == '\0') {
      // Only extract token if within MAX_TOKENS
      if (tokenCount < MAX_TOKENS) {
        int tokenLength = i - startIdx;  // Length of the token
        if (tokenLength < MAX_TOKEN_LENGTH) {
          // Copy the token into the tokens array
          strncpy(tokens[tokenCount], str + startIdx, tokenLength);
          tokens[tokenCount][tokenLength] = '\0';  // Null-terminate the token
          tokenCount++;  // Move to the next token
        }
      }
      // Move startIdx to the next character after the delimiter
      startIdx = i + 1;
    }
  }

  return tokenCount;  // Return the number of tokens found
}
