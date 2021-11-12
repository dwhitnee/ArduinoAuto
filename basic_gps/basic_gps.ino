/*
 * Complete Project Details http://randomnerdtutorials.com

  * Basic GPS dump
  * $GPVTG – Velocity made good
  * $GPRMC – Essential GPS pvt (position, velocity, time) data
  * $GPGGA is the basic GPS NMEA message, that provides 3D location and accuracy data.
  * $GPGLL – Geographic Latitude and Longitude
  * $GPGSA – GPS DOP (dilution of precision) and active satellites
  * $GPGSV – Detailed GPS satellite information


$GPRMC,013919.00,V,,,,,,,301021,,,N*7F
$GPVTG,,,,,,,,,N*30
$GPGGA,013919.00,,,,,0,00,99.99,,,,,,*65
$GPGSA,A,1,,,,,,,,,,,,,99.99,99.99,99.99*30
$GPGSV,1,1,01,09,,,23*70
$GPGLL,,,,,013919.00,V,N*49

$GPGGA is the basic GPS NMEA message, that provides 3D location and accuracy data. In the following sentence:

$GPGGA,110617.00,41XX.XXXXX,N,00831.54761,W,1,05,2.68,129.0,M,50.1,M,,*42
110617 – represents the time at which the fix location was taken, 11:06:17 UTC
41XX.XXXXX,N – latitude 41 deg XX.XXXXX’ N
00831.54761,W – Longitude 008 deg 31.54761′ W
1 – fix quality (0 = invalid; 1= GPS fix; 2 = DGPS fix; 3 = PPS fix; 4 = Real Time Kinematic; 5 = Float RTK; 6 = estimated (dead reckoning); 7 = Manual input mode; 8 = Simulation mode)
05 – number of satellites being tracked
2.68 – Horizontal dilution of position
129.0, M – Altitude, in meters above the sea level
50.1, M – Height of geoid (mean sea level) above WGS84 ellipsoid
empty field – time in seconds since last DGPS update
empty field – DGPS station ID number
*42 – the checksum data, always begins with *
*
*
 
 */
 
#include <SoftwareSerial.h>
#include <TinyGPS.h>

TinyGPS gps;
SoftwareSerial gpsSerial(9, 10);  // TX, RX pin for GPS

void setup() {
  Serial.begin( 9600 );
  gpsSerial.begin( 9600 );

  Serial.println("Tiny GPS v");
//  Serial.println(TinyGPS::libraryVersion());
}

void loop() {
  while (gpsSerial.available() > 0){
    byte gpsData = gpsSerial.read();
    Serial.write( gpsData );
    gps.encode( gpsData );
  }
  Serial.println();
/*  
  Serial.print( gps.altitude() );
  Serial.print( gps.altitude() );
  Serial.print(",");
  Serial.print( gps.satellites() );
  Serial.println(" satellites\n");
*/
  delay( 5000 );
  
}
