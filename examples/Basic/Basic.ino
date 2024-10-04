/*****************************************************
  This is a basic example sketch to show the working of this library:
  Download the library here- https://github.com/McOrts/WindQX_Library
  With these devices: https://ecdsl.com/en/categoria-producto/windqx/

 * **************************************************
  Pinout connection for Arduino UNO

  WindQX SA.01 pin | Arduino UNO pin
    - (black)      | GND
    + (red)        | 5V
   RX (white)      | PIN 1 (TX)
   TX (yellow)     | PIN 0 (RX)

 * ***************************************************/

#include "Arduino.h"

void setup() {
  Serial.begin(115200);
}

void loop() {
  if (Serial.available() > 0) {
    /* reading variables */
    unsigned int PWM;
    float WSPE;
    float TEMP;
    unsigned int CRC;
    String FRAME;

    /* Measurements values */
    float temperature;
    float wind;

    /* Reading control */
    String status;

    FRAME = Serial.readStringUntil('\n'); // Read the FRAME until a line break is found
    Serial.println(FRAME);

    // Divide the frame into its components separated by spaces.
    int values[4];
    int counter = 0;
    char *ptr = strtok((char *)FRAME.c_str(), " ");
    while (ptr != NULL && counter < 4) {
      values[counter] = atoi(ptr);
      ptr = strtok(NULL, " ");
      counter++;
    }

    // Check that the 4 expected values ​​have been found
    if (counter == 4) {
      PWM = values[0];
      WSPE = values[1];
      TEMP = values[2];
      CRC = values[3];

      temperature = TEMP / 100 - 40;
      wind = WSPE / 10;
      if (wind > 200) {
        wind = 0;
        status = "Wet sensor";
      } else {
        status = "Ok";
      }

      Serial.print("Wind: ");
      Serial.println(wind);
      Serial.print("Temperature: ");
      Serial.println(temperature);
      Serial.print("Status: ");
      Serial.println(status);
    } else {
      Serial.println("Reading error");
      while (Serial.available() > 0) {
        Serial.read(); // Read and discard the incoming byte
      }
      status = "Reading error";
    }
  }
}
