
// ESPino (ESP-12 Module)
// Baud 115200

#define openPin 5
#define closePin 4
#define remotePin 12
#define currentPin A0

int status = 0;
int overload = 670;

void setup() {
	Serial.begin(115200);
  pinMode(openPin, OUTPUT);
  pinMode(closePin, OUTPUT);

  pinMode(remotePin, INPUT_PULLUP);
  Serial.println("SCRIPT READY");
}

void loop() {
  if(digitalRead(remotePin)) {
    closeGate();
  } else {
    openGate();
  }
}

void openGate() {
  if(status == 1) return;
  status = 1;

  Serial.println("OPEN Gate");
  digitalWrite(openPin, true);
  digitalWrite(closePin, false);
  delay(100);
}

void closeGate() {
  if(status == 0) return;
  status = 0;

  Serial.println("CLOSE Gate");
  digitalWrite(openPin, false);
  digitalWrite(closePin, true);
  delay(100);
}

void stopGate() {
  if(status == 2) return;
  status = 2;

  Serial.println("STOP Gate");
  digitalWrite(openPin, false);
  digitalWrite(closePin, false);
  delay(100);
}

void gotoSleep() {
  sleep_enable();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  attachInterrupt(digitalPinToInterrupt(2), wakeUp, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), wakeUp, CHANGE);
  delay(100);
  sleep_cpu();
}

void wakeUp() {
  sleep_disable();
  detachInterrupt(digitalPinToInterrupt(2));
  detachInterrupt(digitalPinToInterrupt(3));
}

