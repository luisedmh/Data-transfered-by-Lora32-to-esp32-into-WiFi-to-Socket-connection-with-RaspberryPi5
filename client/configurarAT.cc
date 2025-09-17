#include <Arduino.h>

#define PIN_M0 22
#define PIN_M1 23
#define PIN_AUX 21   // AUX del módulo

void setMode(bool m0, bool m1) {
  digitalWrite(PIN_M0, m0);
  digitalWrite(PIN_M1, m1);
  delay(50); // margen
}

void waitAuxHigh() {
  while (digitalRead(PIN_AUX) == LOW);
  delay(2); // recomendado por datasheet
}

void setup() {
  pinMode(PIN_M0, OUTPUT);
  pinMode(PIN_M1, OUTPUT);
  pinMode(PIN_AUX, INPUT);

  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, 16, 17); // RX=16, TX=17

  // Entrar en modo configuración (M0=1, M1=1)
  setMode(HIGH, HIGH);
  waitAuxHigh();

  Serial.println("Configurando módulo...");

  // CONFIGURA AQUÍ:
  // Dirección = 0x0001 (emisor), Canal=0x06 (868 MHz), UART=9600, aire=2.4kbps, potencia=30dBm
  byte cmd[6] = {0xC0, 0x00, 0x01, 0x1A, 0x06, 0x44};
  // Dirección = 0x0002 (receptor), mismo canal
  // byte cmd[6] = {0xC0, 0x00, 0x02, 0x1A, 0x06, 0x44};

  Serial2.write(cmd, 6);
  waitAuxHigh();

  // Leer respuesta
  delay(200);
  while (Serial2.available()) {
    byte b = Serial2.read();
    Serial.print("0x");
    Serial.print(b, HEX);
    Serial.print(" ");
  }
  Serial.println();

  Serial.println("Configuración enviada.");
}

void loop() {
  // nada
}
