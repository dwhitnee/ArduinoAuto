// https://github.com/mprograms/QMC5883LCompass

// This is I2C bus-based so must use pins A4 (SDA serial data) and A5 (SCL clock) because of Wire library.
// Can also use other bus-based devices on same pins.
// https://www.arduino.cc/en/Reference/Wire

#include <Wire.h>    // redundant
#include <QMC5883LCompass.h>
// Grove HMC 5883L.h

QMC5883LCompass compass;


void setup()
{
  Serial.begin( 9600 );
  Serial.println("\n\nCompass!");

  Wire.begin();
  compass.setADDR( 0x1E );  // bad board? Should be 0x0D
  compass.init();
  compass.setADDR( 0x1E );  // bad board? Should be 0x0D

  // compass.setMode( 0x01, 0x00, 0x00, 0xC0);
  // default:  setMode(0x01,0x0C,0x10,0X00);

}

void loop()
{
  compass.read();

  int x = compass.getX();
  int y = compass.getY();
  int z = compass.getZ();

  int azimuth = compass.getAzimuth();  // degrees
  byte bearing = compass.getBearing( azimuth );  // N, NNW, etc 0-15

  char dirStr[4] = "XXX";  // dummy 3 char string so /0 is set properly, because this code sucks
  compass.getDirection( dirStr, azimuth);
  
  Serial.print( azimuth ); Serial.print(" deg, ");
  Serial.println( dirStr );
  Serial.print( x ); Serial.print(", ");
  Serial.print( y ); Serial.print(", ");
  Serial.println( z );

  delay(500);
}
