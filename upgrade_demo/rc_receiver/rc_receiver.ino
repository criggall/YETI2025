// Import libraries:
#include <nRF24L01.h>
#include <RF24.h>

// Create RF24 object:
RF24 radio(12,11); // CE, CSN pins

// Assign address for module communication:
const byte address[6] = "00001";

// Create data structure variable for data to read-in:
struct Data_Package{
  byte X; // position
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
  
  // Read RC data:
  if (radio.available()){
    radio.read(&data, sizeof(Data_Package));
    }

  // Set to 0 if no radio connection:
  else{
    data.X = 0;
    data.T = 0;
    }

  // Print data:
  Serial.print(" X: ");
  Serial.print(data.X);
  Serial.print(" T: ");
  Serial.print(data.T);
  
}
