// Sensor pins
#define sensorPower 7  // Power pin for the water level sensor
#define sensorPin A0  // Analog pin to read the water level

// Value for storing water level
int waterlevel = 0; // Variable to store the waterlevel
int lowerThreshold = 300; // Lower threshold for waterlevel
int upperThreshold = 500; // Upper threshold for waterlevel

int redLED = 2; // Pin for the red LED indicator
int yellowLED = 3; // Pin for the yellow LED indicator
int greenLED = 4; // Pin for the green LED indicator

const int analogInPin = A1; // Analog pin to read the moisture value
int sensorValue = 0; // Variable to store the moisture value


void setup() {
  pinMode(5, OUTPUT);  // define output for moisture sensor

  // Set D7 as an OUTPUT
  pinMode(sensorPower, OUTPUT);

  // Set to LOW so no power flows through the sensor
  digitalWrite(sensorPower, LOW);
  Serial.begin(9600); // Initialize serial communication for debugging

  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);
}

void loop() {
  int level = readSensor();

  pump();  // pump, kallar på funktion

  //get the reading from the function below and print it
  vattenSensor();  // water sensor, kallar på funktionen

  Serial.print("Water level: ");
  Serial.println(level);

  delay(1000); // Delay for one second before the next iteration
}

void pump() {
  int level = readSensor();
  sensorValue = analogRead(analogInPin);

  // Check if soil moisture is below a certain threshold and water container level is sufficient
  if (sensorValue < 250) {
    while (sensorValue <= 380 && level >= lowerThreshold) {
      digitalWrite(5, HIGH); // Activate the pump
      sensorValue = analogRead(analogInPin); // checks moisture value
      int level = readSensor(); // checks waterlevel value
    }
    digitalWrite(5, LOW); // Deactivate the pump
  }

  Serial.println(sensorValue); // Print the moisture level
}

void vattenSensor() {
  int level = readSensor();

  // Check waterlevel and activate corresponding LED indicators
  if (level >= 0 && level <= lowerThreshold) {
    Serial.println("Water Level: Low");
    digitalWrite(redLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
  } else if (level > lowerThreshold && level <= upperThreshold) {
    Serial.println("Water Level: Medium");
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(greenLED, LOW);
  } else if (level > upperThreshold) {
    Serial.println("Water Level: High");
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, HIGH);
  }
}
//This is a function used to get the reading
int readSensor() {
  digitalWrite(sensorPower, HIGH);     // Turn the sensor ON
  delay(10);                           // wait 10 milliseconds
  waterlevel = analogRead(sensorPin);  // Read the analog value form sensor
  digitalWrite(sensorPower, LOW);      // Turn the sensor OFF
  return waterlevel;                   // send current reading
}
