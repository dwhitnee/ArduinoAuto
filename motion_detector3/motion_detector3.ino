/*
  Motion Detector Test

  PIR output on pin 3.
  LED also on pin 3 for feedback (+200 Ohm resistor)
*/

enum { LEFT, CENTER, RIGHT };
const char* directionStr[3] = { "left", "center", "right"};

const int detector[3] = { 10, 9, 8  };  // LCD pins
const int led[3] = { 13, 12, 11 };
boolean inMotion[3] = { true, true, true };
int course = 180;
int heading = 180;

unsigned long whenNoticed = 0;

void setup()
{
  pinMode( detector[LEFT], INPUT); 
  pinMode( detector[CENTER], INPUT); 
  pinMode( detector[RIGHT], INPUT); 

  for (int i=0; i < 3; i++) {
    pinMode(led[i], OUTPUT); 
    digitalWrite( led[i], LOW );
  }
  
  Serial.begin(9600);
  Serial.println("Moof");
}


//----
// Check motion sensor's instantaneous state (ignore any state change)
//----
void checkMotionSensor( int id ) {
  int motionSensor = digitalRead( detector[id] );
  digitalWrite( led[id], motionSensor );

  if (motionSensor == HIGH) {
    inMotion[id] = true;
    Serial.print("I see you ");
    Serial.println( directionStr[id] );
  } else {
    inMotion[id] = false;
  }
}

//----
// For continuous checking, only generate events when motion first turns on or off
// @output inMotion[id] 
//----
void updateMotionStateContinuous( int id ) {
   int motionSensor = digitalRead( detector[id] );

  if (inMotion[id]) {
    if (motionSensor == LOW) {
      inMotion[id] = false;
      // generate a "motionless" event
      Serial.println("Where are you?");
      digitalWrite( led[id], LOW );
    }
  } else {
    if (motionSensor == HIGH) {
      inMotion[id] = true;
      // generate a "motion" event
      Serial.print("I see you to the ");
      Serial.println( directionStr[id] );
      digitalWrite( led[id], HIGH );
    }
  }

}

//-------
// based on motion figure out where to go
//------
void setCourse() {
  int courseChange = 0;
  int delta = 30;  // max dir change
  
  if (inMotion[LEFT]) {
    courseChange -= delta;
  }
  if (inMotion[RIGHT]) {
    courseChange += delta;
  }
  if (inMotion[CENTER]) {
    courseChange /= 2;     // moderate course change by 50% is motion ahead
  }

  course += courseChange;
  heading = course;  // TBD
  
  if (courseChange) {
    Serial.print("Changing course "  );
    Serial.println( courseChange );
    Serial.print("New course: "  );
    Serial.println( course );
  }
}

//---
void drive() {
  Serial.println("Driving for 3 seconds");
  delay( 3000 );
}

void loop()
{  
  Serial.println("Looking around");

  checkMotionSensor( LEFT );
  checkMotionSensor( CENTER );
  checkMotionSensor( RIGHT );
  
  setCourse();
 // drive();

  Serial.println("Stopping");
  // delay( 3000 );  // stop motion so motion detectors do real work
}
