// Import libraries:
#include <nRF24L01.h>
#include <RF24.h>

// Create RF24 object:
RF24 radio(12,11); // CE, CSN pins

// Assign address for module communication:
const byte address[6] = "00001";

// Create data structure variable for data to read-in:
struct Data_Package{
  byte X; // position coordinate 1
  byte Y; // position coordinate 2
  byte T; // temperature
};
struct Data_Package data;

void setup() {

  // Initialize serial communication:
  Serial.begin(9600);
  
  // Initialize RC:
   radio.begin();
  // Set the address:
  radio.openReadingPipe(0,address);
  // Set module as transmitter:
  radio.startListening();
  
}

void loop() {
  
  /* Commenting out radio receive commands for demo!
  Using dummy position and temperature values instead. */

  // // Read RC data:
  // if (radio.available()){
  //   radio.read(&data, sizeof(Data_Package));
  //   }

  // // Set to 0 if no radio connection:
  // else{
  //   data.X = 0;
  //   data.Y = 0;
  //   data.T = 0;
  //   }

  data.X = random(0,10) // random position between 0 and 10 m
  data.Y = random(0,10) // random position between 0 and 10 m
  data.T = random(60,80) // random temperature between 60 and 80 degrees F
  delay(500); // delay 0.5 s to simulate transmission from Vol-E

  // Print data:
  Serial.print(" X: ");
  Serial.print(data.X);
  Serial.print(" Y: ");
  Serial.print(data.Y);
  Serial.print(" T: ");
  Serial.print(data.T);
  
}
