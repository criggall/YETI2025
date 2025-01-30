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

int count = 0;

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

  // Generate dummy values:
  if (count == 0){
    data.X = 0; // arbitrary units, say cm
    data.Y = 0; // arbitrary units, say cm
    data.T = 70; // degrees F
  }
  else{
    int m = random(0,6);
    if (m == 0){
      data.X += 1; // change position by arbitrary small increment
    }
    else if (m == 1){
      data.Y += 1; // change position by arbitrary small increment
    }
    else if (m == 2){
      data.X += 1; // change position by arbitrary small increment
      data.Y += 1; // change position by arbitrary small increment
    }
    else if (m == 3){
      data.X += -1; // change position by arbitrary small increment
    }
    else if (m == 4){
      data.Y += -1; // change position by arbitrary small increment
    }
    else if (m == 5){
      data.X += -1; // change position by arbitrary small increment
      data.Y += -1; // change position by arbitrary small increment
    }
    int n = random(0,2);
    if (n == 0){
      data.T += float(random(0,3)); // increase temperature by random amount between 0 and 2 degrees F
    }
    else{
      data.T += -float(random(0,3)); // increase temperature by random amount between 0 and 2 degrees F
    }
  }

  // Write out data to be read in Python:
  Serial.write((byte*)&data, sizeof(data));

  // Delay 0.5 s to simulate transmission from Vol-E:
  delay(500);
  
  count++;

//  // Print data:
//  Serial.print(" X: ");
//  Serial.print(data.X);
//  Serial.print(" Y: ");
//  Serial.print(data.Y);
//  Serial.print(" T: ");
//  Serial.print(data.T);
  
}