#include <Arduino.h>
#include <Wire.h>
#include "SHTSensor.h"
#include "EspMQTTClient.h"

#define uS_TO_S_FACTOR 1000000 /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP 300      /* Time ESP32 will go to sleep (in seconds) */

double temperature;
double humidity;

EspMQTTClient client(
    "Fontys",         //Wifi SSID
    "fontys2019",     //Wifi Password
    "192.168.178.10", // MQTT Broker server ip
    "IvoESP",         // Client name that uniquely identify your device
    1883              // The MQTT port, default to 1883.
);

SHTSensor sht(SHTSensor::SHT3X); //Temperature and humidity sensor instance

void setup()
{
  Wire.begin();
  Serial.begin(115200);

  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);

  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output

  if (sht.init()) //Make sure the sensor initializes properly
  {
    Serial.print("init(): success\n");
  }
  else
  {
    Serial.print("init(): failed\n");
  }

  sht.setAccuracy(SHTSensor::SHT_ACCURACY_MEDIUM);

  while (!client.isConnected()) //Waits until everything is connected
  {
    client.loop();
  }

  if (sht.readSample()) //Reads the readings from the sensor. Returns false if readings are invalid.
  {
    temperature = sht.getTemperature();
    humidity = sht.getHumidity();
    Serial.print("SHT:\r\n");
    Serial.print("  T:  ");
    Serial.print(temperature, 2);
    Serial.print("\r\n");
    Serial.print("  RH: ");
    Serial.print(humidity, 2);
    Serial.print("\r\n");
  }
  else
  {
    // Serial.print("Error in readSample()\n");
  }

  //Publish the readings to the dashboard
  client.publish("esp/sht3x/tem", String(temperature));
  delay(100);
  client.publish("esp/sht3x/hum", String(humidity));

  Serial.println("Going to sleep.");
  esp_deep_sleep_start();
}

void onConnectionEstablished()
{
}

void loop()
{

  delay(300000);
}