 /* Motor configuration:
 * 
 *    FRONT
 * 
 * (1)      (2)
 * 
 *     BACK
 * 
 */

// Import libraries:
#include <AFMotor.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Set motor speeds:
const int motor1DefaultSpeed = 200;
const int motor2DefaultSpeed = 200;
const int motor1TurnSpeed = 125;
const int motor2TurnSpeed = 125;

// Set minimum distance for robot to start turning:
const int minDistance = 50; //cm

// Set RC transceiver pins:
const int CEPin = A4;
const int CSNPin = A5;

// Set motor pins:
AF_DCMotor motor1(1);
AF_DCMotor motor2(4);

// Set distance sensor pins:
const int trigPin = A0;
const int echoPin = A2;

// Set temperature sensor pins:
const int temperaturePin = A3;

// Define variable types:
long duration;
int distance;

// Create data structure for position and temperature:
struct Data_Package{
  byte X; // position coordinate 1
  byte Y; // position coordinate 2
  byte T; // temperature
};
// Create variable with this structure:
struct Data_Package data;

// Create radio object:
RF24 radio(CEPin,CSNPin);
// Define RC address:
const byte address[6] = "00001";

void setup() {
  
  // Initialize serial connection:
  Serial.begin(9600);
  
  // Initialize RC:
  radio.begin();
  delay(200);
  // Set the address:
  radio.openWritingPipe(address);
  // Set module as transmitter:
  radio.stopListening();

  // Set analog pin modes:
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(CEPin,OUTPUT);
  pinMode(CSNPin,OUTPUT);

  // Set default motor speeds:
  motor1.setSpeed(motor1DefaultSpeed);
  motor1.run(RELEASE);
  motor2.setSpeed(motor2DefaultSpeed);
  motor2.run(RELEASE);
  delay(200);
  
}

void loop() {

  // Assign motor directions:
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  
  // Clear the trigPin:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Set the trigPin on HIGH state for 10 ms:
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Read the echoPin and return the sound wave travel time in ms:
  duration = pulseIn(echoPin, HIGH);
  // Calculate the distance in cm:
  distance = duration * 0.034 / 2;
  // Print the distance:
  Serial.print("Distance: ");
  Serial.println(distance);

  // Move forward if no obstacle is present:
  if (distance > minDistance) {
    motor1.setSpeed(motor1DefaultSpeed);
    motor2.setSpeed(motor2DefaultSpeed);
  }

  // Turn right if obstacle is present:
  else {
    // Motor 1 forward
    motor1.setSpeed(0);
    motor1.setSpeed(motor1TurnSpeed);
    // Motor 2 backward
    motor2.setSpeed(0);
    motor2.run(BACKWARD);
    motor2.setSpeed(motor2TurnSpeed);
  }

  // Read data from temperature sensor:
  data.T = analogRead(temperaturePin);

  // Read position data:
  
  
  // Send data to receiver:
  radio.write(&data, sizeof(Data_Package));
  
  // Wait 0.5 seconds:
  delay(500);

} 
