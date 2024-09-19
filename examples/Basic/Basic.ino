#include "Arduino.h"

unsigned int PWM;
float WSPE;
float TEMP;
unsigned int CRC;
String FRAME;

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

      // Cáculos estadísticos
      wind_sum += wind;
      CountRead ++;

      if (wind > wind_peak) {
        wind_peak = wind;
        Serial.print("wind peak: ");
        Serial.println(wind_peak);
       }
      if (wind < wind_min) {
        wind_min = wind;
        Serial.print("wind min: ");
        Serial.println(wind_min);
      }
      
    } else {
      Serial.println("Error: Trama de datos incorrecta");
      clearSerialBuffer();
    }
  }
}
