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

// Set motor speeds:
const int motor1DefaultSpeed = 200;
const int motor2DefaultSpeed = 200;
const int motor1TurnSpeed = 125;
const int motor2TurnSpeed = 125;

// Set minimum distance for robot to start turning:
const int minDistance = 50; //cm

// Set motor pins:
AF_DCMotor motor1(1);
AF_DCMotor motor2(4);

// Set distance sensor pins:
const int trigPin = A0;
const int echoPin = A2;

// Define variable types:
long duration;
int distance;

void setup() {

  // Initialize serial communication:
  Serial.begin(9600);

  // Set analog pin modes:
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  
  // Set default motor speed:
  motor1.setSpeed(motor1DefaultSpeed);
  motor1.run(RELEASE);
  motor2.setSpeed(motor2DefaultSpeed);
  motor2.run(RELEASE);
  
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

  // Turn right if obstacle is present
  else {
    // Motor 1 forward
    motor1.setSpeed(0);
    motor1.setSpeed(motor1TurnSpeed);
    // Motor 2 backward
    motor2.setSpeed(0);
    motor2.run(BACKWARD);
    motor2.setSpeed(motor2TurnSpeed);
  }
  
  // Wait 0.5 seconds
  delay(500);

}
