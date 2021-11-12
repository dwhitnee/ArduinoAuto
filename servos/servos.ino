// Arduino code to count 9-0 LED style using servos
// Servos apparently only work well on PWM (pulse width modulation pins)

#include <Servo.h>

const int numServos = 7;
Servo servo[numServos]; 
int pwmPin[] = {3,5,6,9,10,11,12};  // (PWM) pins for servos

const int OFF = 10;  // "time" with no LEDs

int time[][7] = {
  { 1,1,1,1,1,1,0 },  // 0
  { 0,0,1,0,1,0,0 },
  { 1,0,1,1,0,1,1 },
  { 1,0,1,0,1,1,1 },
  { 0,1,1,0,1,0,1 },  // 4
  { 1,1,0,0,1,1,1 },
  { 1,1,0,1,1,1,1 },
  { 1,0,1,0,1,0,0 },
  { 1,1,1,1,1,1,1 },  // 8
  { 1,1,1,0,1,1,1 },
  { 0,0,0,0,0,0,0 },  // no time
};
    

void setup()
{
  Serial.begin(9600);
  for (int i=0; i < numServos ; i++) {
    servo[i].attach( pwmPin[i] );
  }
}

// turn on "LEDs" for this digit 
void displayTime( int t ) {
  for (int s=0; s < numServos; s++) {
    servo[s].write( 100 * time[t][s] ); 
  }
}


void loop()
{
  Serial.println("Howdy\n");
  //displayTime( 8 );delay(1000); exit(0);


  displayTime( OFF ); delay( 1000 );

  for (int t=0; t < 10; t++) {
    Serial.println( t );
    displayTime( t ); 
    delay(1000);   
  }

  displayTime( OFF ); 
  Serial.println("Boydy\n");
  
  delay(1000); exit(0);
}
