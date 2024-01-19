#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo servo;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  servo.attach(8); // Attach servo to pin 8
}

void loop() {
  // Look for new RFID cards
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Get the UID of the card
    String cardUID = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      cardUID += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
      cardUID += String(mfrc522.uid.uidByte[i], HEX);
    }
    
    Serial.print("Card UID: ");
    Serial.println(cardUID);

    // Check if the card UID is authorized
    if (isAuthorized(cardUID)) {
      Serial.println("Access Granted");
      unlockDoor();
    } else {
      Serial.println("Access Denied");
    }

    // Halt for a moment to avoid multiple card reads
    delay(2000);
  }

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

bool isAuthorized(String cardUID) {
  // Replace this with your own list of authorized card UIDs
  String authorizedUIDs[] = {"xxxxxxxxxxxx"};

  for (int i = 0; i < sizeof(authorizedUIDs) / sizeof(authorizedUIDs[0]); i++) {
    if (cardUID.equals(authorizedUIDs[i])) {
      return true;
    }
  }
  return false;
}

void unlockDoor() {
  // Unlock the door by rotating the servo
  servo.write(90); // Adjust the angle based on your locking mechanism
  delay(2000);     // Keep the door unlocked for 2 seconds
  servo.write(0);  // Lock the door by resetting the servo to its initial position
}
