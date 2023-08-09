#include <Servo.h>
Servo myservo;

// Motor pins
int rightMotorForward = 8; //in1
int rightMotorBackward = 9; //in2
int leftMotorForward = 10; //in3
int leftMotorBackward = 11; //in4

// Ultrasonic sensor pins
const int trigPin = 7;
const int echoPin = 6;

// Minimum distance
int minDistance = 10;

// Constants for servo angles
const int servoLeftAngle = 30;
const int servoRightAngle = 150;
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
}

void loop() 
{
  float frontDistance = getDistance();

  if (frontDistance < minDistance) 
  {
    stop();
    delay(4000);

    // Calculating distance from both sides

    myservo.write(servoLeftAngle);
    delay(500);
    float leftDistance = getDistance();

    myservo.write(servoRightAngle);
    delay(500);
    float rightDistance = getDistance();

    // Choosing direction

    if (leftDistance > rightDistance) 
    {
      turnLeft();
    } 
    else 
    {
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
  delay(3500);
  stop();
  delay(500);
}

void turnRight()
{
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(rightMotorBackward, HIGH);
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(leftMotorBackward, LOW);
  delay(3500);
  stop();
  delay(500);
}