int PIR_PIN = 14;

void pin_setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  pinMode(PIR_PIN, INPUT);

  // TODO
  //attachInterrupt(digitalPinToInterrupt(PIR_PIN), pirDetect1, RISING);
}

void pin_led(bool up)
{
  if ( up )
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
  else
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }
}

bool pir_pin_state()
{
  if ( digitalRead(14) == 1 )
    return true;
  else
    return false;
}
