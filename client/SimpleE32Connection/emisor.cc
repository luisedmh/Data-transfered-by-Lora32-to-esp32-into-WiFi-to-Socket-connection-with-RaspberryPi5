// Emisor simple para E32 (ESP32)

void setup() {
  Serial.begin(9600);   // Monitor serie por USB
  
  // Inicializar Serial2: velocidad 9600, RX=16, TX=17
  Serial2.begin(9600, SERIAL_8N1, 16, 17);

  Serial.println("Emisor listo...");
}

void loop() {
  String mensaje = "Hola desde el EMISOR\n";
  
  Serial2.print(mensaje);   // Enviar al módulo E32
  Serial.print("Enviado: ");
  Serial.println(mensaje);

  delay(2000);
}
