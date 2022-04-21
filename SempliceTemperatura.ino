/*
  HTS221 - Read Sensors

  This example reads data from the on-board HTS221 sensor of the
  Nano 33 BLE Sense and prints the temperature and humidity sensor
  values to the Serial Monitor once a second.

  The circuit:
  - Arduino Nano 33 BLE Sense

  This example code is in the public domain.
*/
#include <phyphoxBle.h>
char board_name[] = "Mobile"; 
// to change the name displayed by the board using BLE: 
// no space and no special character
#include <Arduino_HTS221.h>

void setup() {
//  Serial.begin(9600);
//  while (!Serial);
//   initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  
  if (!HTS.begin()) {
    Serial.println("Failed to initialize humidity temperature sensor!");
    digitalWrite(LED_BUILTIN, HIGH);
    while (1);
  }
 PhyphoxBLE::start(board_name); 
}

void loop() {
  float ST = 0.;
  float ST2 = 0.;
  float SU = 0.;
  float SU2 =0.;
  for (int i = 0; i < 1000; i++){
  // read all the sensor values
  float temperature   = HTS.readTemperature();
  float temperature2  =  temperature*temperature;
  ST += temperature;
  ST2 += temperature2;
  float humidity      = HTS.readHumidity();
  float humidity2     = humidity*humidity;
  SU += humidity;
  SU2 += humidity2;
  //delay(10);
  }
  float T = ST/1000; 
  float dT = sqrt((ST2/1000-(ST/1000)*(ST/1000)));
  // print each of the sensor values
 // Serial.print("Temperature = ");
//  Serial.print(T);
//  Serial.println(" °C");

  float U = SU/1000;
  float dU = sqrt((SU2/1000-(SU/1000)*(SU/1000)));
//  Serial.print("Humidity    = ");
//  Serial.print(U);
//  Serial.println(" %");

  // print an empty line
  //Serial.println();
  PhyphoxBLE::write(T, dT, U, dU);
  // wait 1 second to print again
  delay(10);
}
