#include <Arduino.h>

#include <radon_eye.h>

// use the MAC address for your sensor - see README.md
RadonEye radon_sensor("00:11:22:33:44:55");

void setup() {
  Serial.begin(115200);
  
  // returns false if it can't connect to the RadonEye
  while(!radon_sensor.setup()) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("RadonEye connected");
}

void loop() {
  // must call this to read current values from the RadonEye
  // returns false if it fails
  if(!radon_sensor.update()) {
    delay(1000);
    return;
  }

  Serial.printf("now %.2f hour %.2f day %.2f\n",
		radon_sensor.radon_now(),
		radon_sensor.radon_hour(),
		radon_sensor.radon_day());

  // one reading every 10 minutes
  delay(10*60*1000);
}
