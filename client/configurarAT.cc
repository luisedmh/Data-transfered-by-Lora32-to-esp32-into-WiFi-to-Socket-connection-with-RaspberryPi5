// Configuración del módulo E32 como EMISOR (dir 0x0001)

#define PIN_M0 18
#define PIN_M1 19

void setMode(bool m0, bool m1) {
  digitalWrite(PIN_M0, m0);
  digitalWrite(PIN_M1, m1);
  delay(50); // un poco de margen
}

void setup() {
  Serial.begin(9600);       // Monitor serie
  Serial2.begin(9600);      // UART al E32 (GPIO16=RX, GPIO17=TX)

  pinMode(PIN_M0, OUTPUT);
  pinMode(PIN_M1, OUTPUT);

  // 1. Modo configuración (M0=1, M1=1)
  setMode(HIGH, HIGH);

  Serial.println("Configurando modulo EMISOR...");

  // Comando AT: C0 00 01 1A 06 46
  // -> Guardar config, direccion 0x0001, UART=9600, aire=2.4kbps, canal=0x06 (868 MHz), potencia=24dBm
  byte cmd[6] = {0xC0, 0x00, 0x01, 0x1A, 0x06, 0x46};
  // -> Guardar config, direccion 0x0002, UART=9600, aire=2.4kbps, canal=0x06 (868 MHz), potencia=24dBm
  //byte cmd[6] = {0xC0, 0x00, 0x02, 0x1A, 0x06, 0x46};
  Serial2.write(cmd, 6);

  delay(200);

  // Leer respuesta
  while (Serial2.available()) {
    byte b = Serial2.read();
    Serial.print("0x");
    Serial.print(b, HEX);
    Serial.print(" ");
  }
  Serial.println();

  Serial.println("Configuracion enviada.");
}

void loop() {
  // Nada, configuración es solo una vez
}
