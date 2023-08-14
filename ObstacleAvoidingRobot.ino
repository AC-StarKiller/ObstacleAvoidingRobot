#include <Servo.h>
Servo myservo;

// Motor pins

int rightMotorBackward = 9; //in1
int rightMotorForward = 8; //in2
int leftMotorBackward = 10; //in3
int leftMotorForward = 11; //in4

// Ultrasonic sensor pins
const int trigPin = 7;
const int echoPin = 6;

// Minimum distance
int minDistance = 15;

// Constants for servo angles
const int servoLeftAngle = 180;
const int servoRightAngle = 0;
const int servoCenterAngle = 90;

void setup() 
{
  // Set motor pins as outputs
  pinMode(rightMotorForward, OUTPUT);
  pinMode(rightMotorBackward, OUTPUT);
  pinMode(leftMotorForward, OUTPUT);
  pinMode(leftMotorBackward, OUTPUT);

  // Set ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Attach servo to pin 12
  myservo.attach(12);

  // Set initial servo position to center
  myservo.write(servoCenterAngle);

  delay(10000);
}

void loop() 
{
  float frontDistance = getDistance();

  if (frontDistance < minDistance) 
  {
    stop();
    delay(2000);
    moveBackward();
    delay(1000);
    stop();

    // Calculating distance from both sides

    myservo.write(servoLeftAngle);
    delay(2000);
    float leftDistance = getDistance();

    myservo.write(servoRightAngle);
    delay(2000);
    float rightDistance = getDistance();

    // Choosing direction

    if (leftDistance > rightDistance) 
    {
      myservo.write(servoLeftAngle);
      turnLeft();
    } 
    else 
    {
      myservo.write(servoRightAngle);
      turnRight();
    }
  } 
  else 
  {
    moveForward();
  }

  myservo.write(servoCenterAngle);
}

float getDistance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  int duration = pulseIn(echoPin, HIGH);
  int distance = duration * (0.034 / 2);

  return distance;
}

void stop()
{
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(rightMotorBackward, LOW);
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(leftMotorBackward, LOW);
}

void moveForward()
{
  delay(100);
  digitalWrite(rightMotorForward, HIGH);
  digitalWrite(rightMotorBackward, LOW);
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(leftMotorBackward, LOW);
}

void moveBackward()
{
  delay(100);
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(rightMotorBackward, HIGH);
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(leftMotorBackward, HIGH);
}

void turnLeft()
{
  digitalWrite(rightMotorForward, HIGH);
  digitalWrite(rightMotorBackward, LOW);
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(leftMotorBackward, HIGH);
  delay(2500);
  stop();
  delay(500);
}

void turnRight()
{
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(rightMotorBackward, HIGH);
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(leftMotorBackward, LOW);
  delay(2500);
  stop();
  delay(500);
}