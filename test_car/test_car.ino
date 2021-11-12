#include <AUnit.h>
#include <RC_Car.h>

#include <RC_Car.h>
Car* car = NULL;

void setup() {
  Serial.begin( 9600 );
  delay(1000); // wait for stability on some boards to prevent garbage Serial

  if (!car) {
    car = new Car( 4, 5 );

    car->setRxPulseTurnRange( 1000, 1530, 2000 );
    car->setServoTurnRange( 50, 95, 165 );

    car->setRxPulseSpeedRange( 1000, 1530, 2000 );
    car->setServoSpeedRange( 50, 95, 165 );
  }
}

unsigned long poop( int v ) {
  return 2;
}

test(poopy) {
  assertEqual( poop(0), 2);
}

test(car) {  
  assertEqual( car->convertPulseToRange( 1000, 100, car->rxPulseTurnRange ), -100 );
  assertEqual( car->convertPulseToRange( 1530, 100, car->rxPulseTurnRange ), 0 );
  assertEqual( car->convertPulseToRange( 2000, 100, car->rxPulseTurnRange ), 100 );
}


void loop() {
  aunit::TestRunner::run();
}
