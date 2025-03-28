#include <Servo.h>

// ECHO to D4
#define inputPin 4
// TRIG to D5
#define outputPin 5
// Servo to D6
#define servoPin 6
// min and max angles
#define minAngle 0
#define maxAngle 180

int currentAngle = (minAngle + maxAngle) / 2;// in the middle;
int angleIncrement = 10;

Servo servo;

void setup()
{
  Serial.begin(9600);
  
  pinMode(inputPin, INPUT);
  pinMode(outputPin, OUTPUT);

  servo.attach(servoPin);

  // Go to the medium servo angle
  servo.write(currentAngle);
  delay(1000);
}

void loop()
{
  measure_distance_and_log();

  // increment/decrement servo angle
  currentAngle += angleIncrement;

  if (currentAngle <= minAngle)
  {
    currentAngle = minAngle;
    angleIncrement = -angleIncrement;
  }
  else if (currentAngle >= maxAngle)
  {
    currentAngle = maxAngle;
    angleIncrement = -angleIncrement;
  }

  servo.write(currentAngle);
  delay(100);//TODO use a formula instead
}

void measure_distance_and_log()
{
  digitalWrite(outputPin, LOW); 
  delayMicroseconds(2);
  
  digitalWrite(outputPin, HIGH); // Pulse for 10μs to trigger ultrasonic detection
  delayMicroseconds(10);
  
  digitalWrite(outputPin, LOW);   
  int distance = pulseIn(inputPin, HIGH);  // Read receiver pulse time
  
  distance= distance / 58;   // Transform pulse time to distance

  //Output distance
  Serial.print(currentAngle);
  Serial.print(": ");
  Serial.print(distance);
  Serial.println("cm");
}
