const char* mqtt_server = "MQTT_Server_IP";
const int mqtt_port = 1883;
const char* mqtt_user = "MQTT User";
const char* mqtt_pwd = "MQTT Password";
char topic[100] = {0};

void mqtt_setup()
{
  espClient.setInsecure();
  mqtt_client.setServer(mqtt_server, mqtt_port);
  mqtt_connect();
}

void mqtt_connect() {
  int retry = 0;
  while (!mqtt_client.connected())
  {
    retry++;
    Serial.print("Attempting MQTT connection...");
    if (mqtt_client.connect(getStrMac(), mqtt_user, mqtt_pwd))
    {
      Serial.println("connected");
    } else
    {
      if ( 5 == retry )
      {
        Serial.print("failed, rc=");
        Serial.print(mqtt_client.state());
        Serial.println(" restart");
        ESP.restart();
      }
      else
      {
        Serial.print("failed, rc=");
        Serial.print(mqtt_client.state());
        Serial.println(" try again in 5 seconds");
        delay(5000);
      }
    }

    mqtt_client.loop();
  }
}

void mqtt_send_detect_status(int id)
{
  sprintf(topic, "/audoche/home/smartmodule/%s/detector/pir%i", getStrMac(), id);
  mqtt_client.publish(topic, "movement");
}
