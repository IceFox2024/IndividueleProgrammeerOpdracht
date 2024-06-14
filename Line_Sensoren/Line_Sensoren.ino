#include <Wire.h>
#include <Zumo32U4.h>
Zumo32U4ButtonB buttonB;
Zumo32U4LineSensors lineSensors;

/*! Een array wordt aangemaakt van de type uint16_t (16-bits unsigned integers)  */
uint16_t lineSensorValues[3] = { 0, 0, 0 };

/*! De Sensoren worden geinitaliseerd. Pin 5 wordt als output gezien(Deze wordt gebruikt in de void loop voor de groene led). CalibrateLineSensors wordt aangeroepen  */
void setup() {
  lineSensors.initThreeSensors();
  pinMode(5, OUTPUT);
  calibrateLineSensors();
  Serial.begin(9600);
}

/*! Kalibreren van de lijnsensoren(Wordt 200 keer gedaan) + Groene Led gaat aan */
void calibrateLineSensors() {
   digitalWrite(5, LOW);
  for (uint16_t i = 0; i < 200; i++) {
    lineSensors.calibrate();
  }
  digitalWrite(5, HIGH);
}
/*! Roep de printReadingsToSerial functie aan elke 100 ms + Calibrate de sensoren als knop B wordt ingedrukt */
void loop() {
  static uint16_t LaatsteGelezenUitvoer = 0;
  if ((uint16_t)(millis() - LaatsteGelezenUitvoer) >= 100) {
    LaatsteGelezenUitvoer = millis();
    lineSensors.readCalibrated(lineSensorValues);
    printReadingsToSerial(); 
  }
  if (buttonB.isPressed()){
  calibrateLineSensors();
 }
}
/*! Print de output naar de seriële monitor */
void printReadingsToSerial() {
  Serial.print("Line sensoren output: ");
  for (uint8_t i = 0; i < 3; i++) {
    Serial.print(lineSensorValues[i]);
    Serial.print(" ");
  }
  Serial.println();
}
