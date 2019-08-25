#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

WiFiClientSecure espClient;
PubSubClient mqtt_client(espClient);

volatile bool readPir1 = false;

void setup()
{
  pin_setup();

  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  while (!Serial) ;

  Serial.println();
  Serial.println("Smart Sensor V1 Booting");

  wifi_setup(false);

  ota_setup();

  mqtt_setup();

  Serial.println("Launched");
  pin_led(false);
}

void loop()
{
  wifi_check();

  if (!mqtt_client.connected())
  {
    // Stop interrupt events
    readPir1 = true;

    pin_led(true);
    mqtt_connect();
    pin_led(false);

    readPir1 = false;
  }

  if ( digitalRead(14) == 1 )
  {
    pin_led(true);

    if ( pir_pin_state() )
    {
      Serial.println("Detect");
      mqtt_send_detect_status(1);
    }

    // Avoid taking too much interrupt
    delay(10000);
    readPir1 = false;

    pin_led(false);
  }

  mqtt_client.loop();
  ArduinoOTA.handle();
}

void pirDetect1()
{
  if ( !readPir1 )
  {
    readPir1 = true;
  }
}
