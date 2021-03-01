int buttonPin = 3;
int buzzerPin = 2;
int lampPin = 4;

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(lampPin, OUTPUT);
}

void loop() {
  if (digitalRead(buttonPin)) {
    Serial.println("butona basildi");
    startLampLoop();
    switchOnBuzzer();
  }
}


void startLampLoop() {
  digitalWrite(lampPin, HIGH);
  digitalWrite(lampPin, LOW);
}

void switchOnBuzzer() {
  digitalWrite(buzzerPin, HIGH);
  delay(100);
  digitalWrite(buzzerPin, LOW);
  delay(100);
}
