int gasPin = A0; // Analog pin connected to the gas sensor
int threshold = 300; // Set your threshold value based on the sensor characteristics

void setup() {
  Serial.begin(9600);
}

void loop() {
  int gasValue = analogRead(gasPin);

  Serial.print("Gas Value: ");
  Serial.println(gasValue);

  if (gasValue > threshold) {
    Serial.println("Gas Leakage Detected!");
    // Add additional actions here, such as activating an alarm or sending a notification.
  }

  delay(1000); // Adjust the delay based on your application needs
}
