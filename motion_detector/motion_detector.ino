/*
  Motion Detector Test

  PIR output on pin 3.
  LED also on pin 3 for feedback (+200 Ohm resistor)
*/
 
const int motionDetector = 3;
const int led = 4;

int inMotion = true;
unsigned long whenNoticed = 0;

void setup()
{
  pinMode(motionDetector, INPUT); 

  pinMode(led, OUTPUT); 
  digitalWrite( led, LOW );

  Serial.begin(9600);
  Serial.println("Moof");
}


void loop()
{  
  int motionDetected = digitalRead( motionDetector );

  if (inMotion) {
    if (motionDetected == LOW) {
      inMotion = false;
      Serial.print("Where are you? I saw you for ");
      Serial.println( (millis() - whenNoticed)/1000 );
      digitalWrite( led, LOW );
    }
  } else {
    if (motionDetected == HIGH) {
      inMotion = true;
      whenNoticed = millis();  // remember when we first saw you
      Serial.println("Dispensing product!");
      digitalWrite( led, HIGH );
    }
  }

}
