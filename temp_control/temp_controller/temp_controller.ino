// ************************************************
// Electrical Connection
// ************************************************

// Temp Sensor
// ---------------------
// White (ground)
// Orange Stripe (+5v)
// Blue Stripe (Signal)
//
// 4.7K ohm resistor between the 5v (Red) and signal (White) wires
//
// Signal LED
// ---------------------
// 1K ohm resistor on LED driven by 5v
//
// Latching Relay
// ---------------------
// 5V
// GND
// Set Coil
// Reset Coil
//

// ************************************************
// Import Libraries
// ************************************************

// Libraries for the DS18B20 Temperature Sensor
#include <OneWire.h>
#include <DallasTemperature.h>


// ************************************************
// Pin definitions
// ************************************************

// Output Relay
#define RelayPinSet 6
#define RelayPinReset 5
boolean relay_status;

// Output LED
#define SignalLED 4

// One-Wire Temperature Sensor
// (Use GPIO pins for power/ground to simplify the wiring)
#define ONE_WIRE_BUS 8


// ************************************************
// Variables and constants
// ************************************************

//Define Variables we'll be connecting to
double hysteresis = 0.2;

//initialize the variables we're linked to
double Setpoint = 21.2; // 70.16 F

// setup Input variable
double Input;


// ************************************************
// Sensor Variables and constants
// ************************************************

// Setup a oneWire instance to communicate with any OneWire devices
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

// arrays to hold device address
DeviceAddress tempSensor;


// ************************************************
// Setup and Initiate
// ************************************************

void setup()
{
  // Baud Rate Set
  Serial.begin(9600);

  // Initialize Relay Control:
  pinMode(RelayPinSet, OUTPUT);      // Output mode to drive relay
  pinMode(RelayPinReset, OUTPUT);    // Output mode to drive relay
  digitalWrite(RelayPinSet, LOW);    // make sure it is off to start
  digitalWrite(RelayPinReset, LOW);  // make sure it is off to start
  pulseRelay(false, RelayPinReset);  // pulse to set relay status

  // Initialize LED Control:
  pinMode(SignalLED, OUTPUT);    // Output mode to drive LED
  digitalWrite(SignalLED, LOW);  // make sure it is off to start

  Serial.println("Initialize Controller...");

  // Start up the DS18B20 One Wire Temperature Sensor
  sensors.begin();
  if (!sensors.getAddress(tempSensor, 0))
  {
    for (int i=0; i <= 10; i++){
      Serial.println("Error starting temperature sensor");
      digitalWrite(SignalLED, HIGH);
      delay(100); // 100mS delay
      digitalWrite(SignalLED, LOW);
      delay(100); // 100mS delay
    }
  }
  sensors.setResolution(tempSensor, 12);
  sensors.setWaitForConversion(false);

}

// ************************************************
// Main Loop
// ************************************************

void loop() {

  // Start an asynchronous temperature reading
  sensors.requestTemperatures();

  // Read the real value of temperature
  Input = readTemp();
  if (Input != -127.00){

    if (relay_status == true){
      Serial.print("Relay ON/CLOSED");
    }
    else{
      Serial.print("Relay OFF/OPEN");
    }
    Serial.print(", Desired Temp (C): "); Serial.print(Setpoint);
    Serial.print(", Current Temp (C): "); Serial.println(Input);

    if (Setpoint - hysteresis > Input && relay_status == false){
      pulseRelay(true, RelayPinSet);
    }
    else if (Setpoint + hysteresis < Input && relay_status == true){
      pulseRelay(false, RelayPinReset);
    }
  }
  else {
    Serial.println("Error reading temp.");
  }
}

// ************************************************
// Read Temperature Function
// ************************************************

double readTemp() {

  double value;

  // read the input
  value = sensors.getTempC(tempSensor);
  if (value == -127.00){
    Serial.println("Error getting temperature");
    for (int i=0; i <= 5; i++){
      digitalWrite(SignalLED, HIGH);
      delay(1000); // 200mS delay
      digitalWrite(SignalLED, LOW);
      delay(1000); // 200mS delay
    }
  }
  return value;
}

// ************************************************
// Pulse Relay ON/OFF
// ************************************************

void pulseRelay(bool state, int pin) {

  if (state == true){
    relay_status = true;
    Serial.println("Set Relay");
    digitalWrite(SignalLED, HIGH);
  }
  else {
    relay_status = false;
    Serial.println("Reset Relay");
    digitalWrite(SignalLED, LOW);
  }

  // pulse pin high momentarily
  digitalWrite(pin, HIGH);
  delay(10);
  digitalWrite(pin, LOW);

  return;
}
