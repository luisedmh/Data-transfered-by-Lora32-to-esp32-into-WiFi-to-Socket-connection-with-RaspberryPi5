// Receptor simple para E32 (ESP32)

void setup() {
  Serial.begin(9600);   // Monitor serie por USB
  
  // Inicializar Serial2: velocidad 9600, RX=16, TX=17
  Serial2.begin(9600, SERIAL_8N1, 16, 17);

  Serial.println("Receptor listo, esperando mensajes...");
}

void loop() {
  if (Serial2.available()) {
    String recibido = Serial2.readStringUntil('\n');  // Leer hasta salto de línea
    Serial.print("Recibido: ");
    Serial.println(recibido);
  }
}
