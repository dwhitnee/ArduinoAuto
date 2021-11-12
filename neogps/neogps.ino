
//======================================================================
//  Program: NMEAdistance.ino
//
//  Description:  Display distance from a base location.
//
//  Prerequisites:
//     1) NMEA.ino works with your device (correct TX/RX pins and baud rate)
//     2) GPS_FIX_LOCATION has been enabled.
//     3) A sentence that contains lat/long has been enabled (GGA, GLL or RMC).
//     4) Your device sends at least one of those sentences.
//
//  'Serial' is for debug output to the Serial Monitor window.
//
//======================================================================


#include <AltSoftSerial.h>   // requires RX/TX on pins 9/10

// #define NEOGPS_USE_SERIAL1
// #include <NeoHWSerial.h>  // better than SoftwareSerial for interrupts 
//#define TX_PIN 9
//#define RX_PIN 10

#include <NMEAGPS.h>
#include <GPSport.h>

//------------------------------------------------------------
// Check that the config files are set up properly

#if !defined( NMEAGPS_PARSE_RMC ) &  \
    !defined( NMEAGPS_PARSE_GGA ) &  \
    !defined( NMEAGPS_PARSE_GLL )
  #error You must uncomment at least one of NMEAGPS_PARSE_RMC, NMEAGPS_PARSE_GGA or NMEAGPS_PARSE_GLL in NMEAGPS_cfg.h!
#endif

#if !defined( GPS_FIX_LOCATION )
  #error You must uncomment GPS_FIX_LOCATION in GPSfix_cfg.h!
#endif

NMEAGPS gps;

// The base location, in degrees * 10,000,000
// NeoGPS::Location_t base( -253448688L, 1310324914L ); // Ayers Rock, AU

NeoGPS::Location_t base( 47.68725, -122.2775 );



void setup()
{
  DEBUG_PORT.begin(9600);
  DEBUG_PORT.println( F("Looking for GPS device on " GPS_PORT_NAME) );

  gpsPort.begin(9600);

} 

//-----------
void printLocation( const gps_fix& fix ) {

  DEBUG_PORT.print( fix.dateTime.seconds );
  DEBUG_PORT.print(", ");

  DEBUG_PORT.print( fix.latitude(), 6); // floating-point display
  // DEBUG_PORT.print( fix.latitudeL() ); // integer display
  DEBUG_PORT.print(", ");

  DEBUG_PORT.print( fix.longitude(), 6 );
  DEBUG_PORT.print(", ");
  
  DEBUG_PORT.print( fix.altitude(), 6 );
  DEBUG_PORT.print(" m, ");
  
  if (fix.valid.satellites) {
    DEBUG_PORT.print( fix.satellites );
    DEBUG_PORT.print(" sats");
  }
  
  DEBUG_PORT.print(", ");
  DEBUG_PORT.print( fix.speed(), 6);
  DEBUG_PORT.print( F(" kts, "));
  DEBUG_PORT.print( fix.speed_mph(), 6);
  DEBUG_PORT.print( F(" mph, "));

  DEBUG_PORT.print( F(" error "));
  DEBUG_PORT.print( fix.lat_err());  
  DEBUG_PORT.print( fix.lon_err());  
  DEBUG_PORT.print( fix.spd_err());  
}


//-------------  
void printRangeTo( const gps_fix& fix, const NeoGPS::Location_t& base ) {

  float range = fix.location.DistanceKm( base ) * 1000;

  DEBUG_PORT.print( F(", Range: ") );
  DEBUG_PORT.print( range );
  DEBUG_PORT.println( F(" m") );
}


//----------------
void loop() {
  
  while (gps.available( gpsPort )) {

    gps_fix fix = gps.read();
    if (fix.valid.location) {
      printLocation( fix );
      printRangeTo( fix, base );

    } else { // Wait
      DEBUG_PORT.print( '.' );
    }
  }
} 
