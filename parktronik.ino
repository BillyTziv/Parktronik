#define echoPin 7 // Echo Pin
#define trigPin 8 // Trigger Pin
#define LEDPin 13 // Onboard LED
#define LED2Pin 12
#define laserPin 5

int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
int buzzerPin = 6;


long duration, distance; // Duration used to calculate distance

void setup() {
 Serial.begin (9600);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(LEDPin, OUTPUT);
 pinMode(LED2Pin, OUTPUT);
 pinMode(laserPin, OUTPUT);
 pinMode(buzzerPin, OUTPUT);
}

void activateBuzzer(int dist) {
  if(dist < 0) {
    digitalWrite(buzzerPin, LOW);     // sets the LED on
    delay(0);                        // waits for a second
    digitalWrite(LEDPin, HIGH);
    digitalWrite(LED2Pin, LOW);
  }else if(dist >= 10) {
    digitalWrite(buzzerPin, HIGH);     // sets the LED on
    delay(dist);                        // waits for a second
    digitalWrite(buzzerPin, LOW);      // sets the LED off
    delay(dist);
    digitalWrite(LEDPin, HIGH);
    digitalWrite(LED2Pin, LOW);
  }else {
    digitalWrite(buzzerPin, HIGH);     // sets the LED on
    digitalWrite(LED2Pin, HIGH);
    digitalWrite(LEDPin, LOW);
  }
}

void loop() {
/* The following trigPin/echoPin cycle is used to determine the
 distance of the nearest object by bouncing soundwaves off of it. */ 
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 
 //Calculate the distance (in cm) based on the speed of sound.
 distance = duration/58.2;
 
 if (distance >= maximumRange || distance <= minimumRange){
 /* Send a negative number to computer and Turn LED ON 
 to indicate "out of range" */
 Serial.println("-1");
 activateBuzzer(-1); 
 }
 else {
 /* Send the distance to the computer using Serial protocol, and
 turn LED OFF to indicate successful reading. */
 Serial.println(distance);
 activateBuzzer(distance);
 }
 digitalWrite(laserPin, HIGH);
 //Delay 50ms before next reading.
 delay(50);
}
