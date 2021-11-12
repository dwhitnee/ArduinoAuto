#include "I2CScanner.h"

I2CScanner scanner;

const uint8_t num_addresses = 5;
const byte addresses[num_addresses] = { 0x0D, 0x20, 0x21, 0x40, 0x41 };
bool results[num_addresses] = { false, false, false, false};


void setup() 
{
  Serial.begin(9600);
  Serial.println("\nLooking for I2C serial bus devices");
  
  scanner.Init();
}

void loop() 
{
  Serial.println("Checking bus...");
  
  for (uint8_t addr = 0; addr < 0xFF; addr++) {
    bool yes = scanner.Check( addr );
    if (yes) {
      Serial.println( addr, HEX );
    }
   
  }
 /* 
  for (uint8_t index = 0; index < num_addresses; index++) {
    results[index] = scanner.Check(addresses[index]);
  }
  
  for (uint8_t index = 0; index < num_addresses; index++) {
    if (results[index]) {
      Serial.print("Found device ");
      Serial.print(index);
      Serial.print(" at address ");
      Serial.println(addresses[index], HEX);
    }
  }
  */
  delay(5000);
}
