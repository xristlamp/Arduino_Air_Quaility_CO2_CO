#include <Wire.h>
#include "Adafruit_SGP30.h"

Adafruit_SGP30 sgp;

void setup() {
  Wire.begin(); // Initialize I2C bus
  Serial.begin(9600);
  while (!Serial) {
    
  }

  if (!sgp.begin()) {
    Serial.println("Failed to initialize SGP30 sensor. Please check your connections.");
    while (1);
  }
}

void loop() {
  if (!sgp.IAQmeasure()) {
    Serial.println("Failed to read IAQ values from SGP30 sensor");
    return;
  }

  // Read and print the TVOC and eCO2 values
  uint16_t TVOC = sgp.TVOC;
  uint16_t eCO2 = sgp.eCO2;

  Serial.print("TVOC: ");
  Serial.print(TVOC);
  Serial.print(" ppb\tCO2: ");
  Serial.print(eCO2);
  Serial.println(" ppm");

  // Check the values and print appropriate messages
  if (eCO2 >= 2000 || TVOC >= 1000) {
    Serial.println("Dangerous levels detected! Take immediate action!");
  } else if (eCO2 >= 1000 || TVOC >= 500) {
    Serial.println("Be careful! The air quality is moderate.");
  } else {
    Serial.println("Good air quality.");
  }

  delay(1000); 
}
