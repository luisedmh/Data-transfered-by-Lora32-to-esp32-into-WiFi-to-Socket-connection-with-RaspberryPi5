#include <Arduino.h>

#define PIN_M0 22
#define PIN_M1 23
#define PIN_AUX 21

void setMode(bool m0, bool m1) {
  digitalWrite(PIN_M0, m0);
  digitalWrite(PIN_M1, m1);
  delay(50);
}

void waitAuxHigh() {
  while (digitalRead(PIN_AUX) == LOW);
  delay(2);
}

void setup() {
  pinMode(PIN_M0, OUTPUT);
  pinMode(PIN_M1, OUTPUT);
  pinMode(PIN_AUX, INPUT);

  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, 16, 17);

  setMode(LOW, LOW);   // Normal mode
  waitAuxHigh();

  Serial.println("Emisor listo...");
}

void loop() {
  String mensaje = "Hola desde el EMISOR\n";

  waitAuxHigh();
  Serial2.print(mensaje);

  Serial.print("Enviado: ");
  Serial.println(mensaje);

  delay(2000);
}
