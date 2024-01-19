#include <Servo.h>

const int trigPin = 9;
const int echoPin = 10;
Servo servo;

void setup() {
  Serial.begin(9600);
  servo.attach(8); // Attach servo to pin 8
}

void loop() {
  // Perform a 180-degree scan
  for (int angle = 0; angle <= 180; angle++) {
    int distance = performScan(angle);
    // Print the angle and distance to the Serial Monitor
    Serial.print("Angle: ");
    Serial.print(angle);
    Serial.print(" degrees, Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Delay to make the scanning visible
    delay(50);
  }

  // Perform a reverse 180-degree scan
  for (int angle = 180; angle >= 0; angle--) {
    int distance = performScan(angle);
    // Print the angle and distance to the Serial Monitor
    Serial.print("Angle: ");
    Serial.print(angle);
    Serial.print(" degrees, Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Delay to make the scanning visible
    delay(50);
  }
}

int performScan(int angle) {
  // Move the servo to the specified angle
  servo.write(angle);

  // Allow the servo some time to reach the specified angle
  delay(100);

  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the distance from the ultrasonic sensor
  int duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  return distance;
}
