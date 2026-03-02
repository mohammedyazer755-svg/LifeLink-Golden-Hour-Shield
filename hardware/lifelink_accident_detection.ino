#include <Wire.h>
#include <MPU6050.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

MPU6050 mpu;
TinyGPSPlus gps;

// GPS Pins
SoftwareSerial gpsSerial(4, 3); // RX, TX

// Buzzer Pin
const int buzzerPin = 8;

// Accident thresholds
const float minorThreshold = 2.0;
const float moderateThreshold = 4.0;
const float majorThreshold = 6.0;

unsigned long lastImpactTime = 0;
bool accidentDetected = false;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  gpsSerial.begin(9600);

  pinMode(buzzerPin, OUTPUT);

  Serial.println("Initializing MPU6050...");
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
    while (1);
  }

  Serial.println("System Ready.");
}

void loop() {
  detectAccident();
  readGPS();
}

void detectAccident() {
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  float accelX = ax / 16384.0;
  float accelY = ay / 16384.0;
  float accelZ = az / 16384.0;

  float totalAcceleration = sqrt(
    accelX * accelX +
    accelY * accelY +
    accelZ * accelZ
  );

  if (totalAcceleration > minorThreshold) {
    if (!accidentDetected) {
      accidentDetected = true;
      lastImpactTime = millis();

      String severity = classifySeverity(totalAcceleration);
      triggerAlert(severity, totalAcceleration);
    }
  }

  if (accidentDetected && millis() - lastImpactTime > 10000) {
    accidentDetected = false;
  }
}

String classifySeverity(float force) {
  if (force > majorThreshold) {
    return "MAJOR";
  } else if (force > moderateThreshold) {
    return "MODERATE";
  } else {
    return "MINOR";
  }
}

void triggerAlert(String severity, float force) {
  Serial.println("=================================");
  Serial.println("ACCIDENT DETECTED!");
  Serial.print("Severity: ");
  Serial.println(severity);
  Serial.print("Impact Force: ");
  Serial.println(force);
  Serial.println("Sending Emergency Signal...");
  Serial.println("=================================");

  // Sound buzzer
  digitalWrite(buzzerPin, HIGH);
  delay(2000);
  digitalWrite(buzzerPin, LOW);
}

void readGPS() {
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  if (gps.location.isUpdated()) {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
  }
}
