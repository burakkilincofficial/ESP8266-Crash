#define potpin A0
int value = 0;
void setup(){
  Serial.begin(9600);
  Serial.println("Potansiyemetre Deger Okuma");
}
void loop(){
  Serial.println(5.00/1024.00*analogRead(potpin));3.0
  delay(100);
}
