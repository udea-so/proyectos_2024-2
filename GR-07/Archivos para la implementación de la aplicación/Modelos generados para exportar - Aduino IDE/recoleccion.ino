#include "esp_camera.h"
#include <WiFi.h>
#include <eloquent_esp32cam.h>
#include <eloquent_esp32cam/extra/esp32/wifi/sta.h>
#include <eloquent_esp32cam/viz/image_collection.h>

// WiFi credentials
const char* ssid = "***";
const char* password = "***";

// Hostname for mDNS
#define HOSTNAME "esp32cam"

// Use eloquent library namespaces
using eloq::camera;
using eloq::wifi;
using eloq::viz::collectionServer;

void setup() {
  delay(3000);
  Serial.begin(115200);
  Serial.println("___EDGE IMPULSE IMAGE COLLECTION___");

  // Configure camera settings using eloquent library
  camera.pinout.wrover();   // Change to your camera model
  camera.brownout.disable();
  camera.resolution.face(); // Set resolution to 240x240
  camera.quality.high();

  // Initialize the camera
  while (!camera.begin().isOk()) {
    Serial.println(camera.exception.toString());
  }
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.println(WiFi.localIP());

  // Start image collection server
  while (!collectionServer.begin().isOk()) {
    Serial.println(collectionServer.exception.toString());
  }

  Serial.println("Camera ready for Edge Impulse");
  Serial.println("Image Collection Server running at:");
  Serial.println(collectionServer.address());
}

void loop() {
  // The server runs independently in its own task
  delay(1000);
}
