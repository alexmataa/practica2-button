#include <Arduino.h>
#include <string>

#define LED1 17
#define LED2 18

struct Button {
  const uint8_t PIN;
  uint32_t numberKeyPresses;
  bool pressed;
};

Button button1 = {16, 0, false};

void IRAM_ATTR isr() {
  button1.numberKeyPresses += 1;
  button1.pressed = true;
}

void setup() {
  Serial.begin(115200);
  pinMode(17,OUTPUT);
  pinMode(18,OUTPUT);
  pinMode(button1.PIN, INPUT_PULLUP);
  attachInterrupt(button1.PIN, isr, FALLING);
}
void loop() {
if (button1.pressed) {
  Serial.printf("Button 1 has been pressed %u times\n", button1.numberKeyPresses);
  button1.pressed = false;
  if(button1.numberKeyPresses%2==0)
  {
    digitalWrite(17,HIGH);
    digitalWrite(18,LOW);
  }
  else
  {
    digitalWrite(17,LOW);
    digitalWrite(18,HIGH);
  }

}

}
