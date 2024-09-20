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

/* reading variables */
unsigned int PWM;
float WSPE;
float TEMP;
unsigned int CRC;
String FRAME;

/* Measurements values */
float temperature;
float wind;

void setup() {
  Serial.begin(115200);
}

void clearSerialBuffer() {
  while (Serial.available() > 0) {
    Serial.read(); // Read and discard the incoming byte
  }
}

void loop() {
  if (Serial.available() > 0) {
    FRAME = Serial.readStringUntil('\n'); // Lee la FRAME hasta encontrar un salto de línea
    Serial.println(FRAME);

    // Divide la trama en sus componentes separados por espacios
    int values[4];
    int counter = 0;
    char *ptr = strtok((char *)FRAME.c_str(), " ");
    while (ptr != NULL && counter < 4) {
      values[counter] = atoi(ptr);
      ptr = strtok(NULL, " ");
      counter++;
    }

    // Asegúrate de que se hayan encontrado los 4 valores esperados
    if (counter == 4) {
      PWM = values[0];
      WSPE = values[1];
      TEMP = values[2];
      CRC = values[3];

      wind = WSPE / 10;
      temperature = TEMP / 100;
      Serial.print("Wind: ");
      Serial.println(wind);
      Serial.print("Temperature: ");
      Serial.println(temperature);
    } else {
      Serial.println("Error: Trama de datos incorrecta");
      clearSerialBuffer();
    }
    delay (1000);
  }
}
