
// ESPino (ESP-12 Module)
// Baud 115200

#define openPin 5
#define closePin 4
#define remotePin 12
#define currentPin A0

int status = 0;
int overloadThreshold = 500;
int overloaded = 0;
int currentReading = 0;

int32_t sleeptime = 60000;
int32_t sleeper = sleeptime;
int sleep = 0;

void setup() {
  Serial.begin(115200);
  pinMode(openPin, OUTPUT);
  pinMode(closePin, OUTPUT);

  pinMode(remotePin, INPUT_PULLUP);
  Serial.println("Program Ready");
}

void loop() {
  if(!overloaded) {
    if(digitalRead(remotePin)) {
      closeGate();
    } else {
      openGate();
    }
  } else {
    if ((digitalRead(remotePin) && status == 1) || (!digitalRead(remotePin) && status == 0)) {
      Serial.println("Overload Recovery");
      overloaded = 0;
    }
  }

  currentReading = analogRead(currentPin);
  if(currentReading < overloadThreshold && !overloaded) {
    Serial.println("Overload Protection Triggered");
    overloaded = 1;
    stopGate();
  }
}

void openGate() {
  if(status == 1) return;
  status = 1;
  sleep = 0;

  Serial.println("OPEN Gate");
  digitalWrite(openPin, true);
  digitalWrite(closePin, false);
  delay(100);
}

void closeGate() {
  if(sleeper < millis() && status == 0 && !sleep) {
    sleep = 1;
    Serial.println("Disengage Gate Relays");
    stopGate();
  }

  if(status == 0) return;
  status = 0;
  sleeper = millis() + sleeptime;

  Serial.println("CLOSE Gate");
  digitalWrite(openPin, false);
  digitalWrite(closePin, true);
  delay(100);
}

void stopGate() {
  Serial.println("STOP Gate");
  digitalWrite(openPin, false);
  digitalWrite(closePin, false);
  delay(100);
}
