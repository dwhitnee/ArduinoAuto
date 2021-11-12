//----------------------------------------------------------------------
//----------------------------------------------------------------------

#include "RC_Car.h"


int steeringRxPin = 5;

Car* car = NULL;

//-------------------------
void setup() {
  Serial.begin( 9600 );

  if (!car) {
    car = new Car( 4, 5 );

    car->setRxPulseTurnRange( 1000, 1530, 2000 );
    car->setServoTurnRange( 50, 95, 165 );

    car->setRxPulseSpeedRange( 1000, 1530, 2000 );
    // TBD car->setServoSpeedRange( 50, 95, 165 );
}

  Serial.println("Go go gadget car!");
}


/*//-----
void calibratePulseRange( unsigned long pulse ) {
  if (pulse < rxMin) { rxMin = pulse; }
  if (pulse > rxMax) { rxMax = pulse; }
}*/

//-----
// convert Rx pulse to (0-range) value
/*
unsigned long pulseDurationToRange( unsigned long rxPulse,
                                    unsigned long range )
{
  // confine to calibrated range
  rxPulse = min( rxPulse, rxMax );
  rxPulse = max( rxPulse, rxMin );

  return ( range * (rxPulse - min) / (max-min) );
}
*/


//-----
void loop() {
  unsigned long rxPulse = pulseIn( steeringRxPin, HIGH);
 // calibrate( rxPulse );

/*
  Serial.print( min );   Serial.print(", ");
  Serial.print( max );   Serial.print(", ");
  Serial.print( rxPulse );   Serial.print(", ");
 // Serial.println();
  Serial.println( pulseDurationToRange( rxPulse, 180 ));
  steer( pulseDurationToRange( rxPulse, 180 ));
*/


/*. USE ME
  for (int  a=0; a < 45; a++) {
    car->steerToAngle( a );
    delay(100);
  }
  */
}
