/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-gps

 * https://www.baldengineer.com/arduino-f-macro.html
 */

#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

const uint32_t GPSBaud = 9600; //Default baud of NEO-6M is 9600

TinyGPSPlus gps;
SoftwareSerial gpsSerial(11, 12); // RX, Tx pins.  the serial interface to the GPS device

const double LONDON_LAT = 51.508131;
const double LONDON_LON = -0.128002;

void setup() {
  Serial.begin( 9600 );
  gpsSerial.begin( 9600 );

  Serial.println(F("Arduino - GPS module"));
}

void loop() {
  
  if (gpsSerial.available() > 0) {

    char data = gpsSerial.read();
 //   Serial.print("GPS:");
 //   Serial.println( data );

    if (gps.encode( data )) {
      if (gps.location.isValid()) {
        double latitude = gps.location.lat();
        double longitude = gps.location.lng();
        unsigned long distanceKm = TinyGPSPlus::distanceBetween(latitude, longitude, LONDON_LAT, LONDON_LON) / 1000;

        Serial.print(F("- latitude: "));
        Serial.println(latitude);

        Serial.print(F("- longitude: "));
        Serial.println(longitude);

        Serial.print(F("- distance to London: "));
        Serial.println(distanceKm);
      } else {
        Serial.println(F("- location: INVALID"));
      }

      Serial.println();
    }
  }

  // 5 second timeout
  if (millis() > 5000 && gps.charsProcessed() < 10) {
    Serial.println(F("Nope GPS data received: check wiring"));
    delay( 100 );
    exit(-1);
  }
}
