#include <WiFi.h>

const char* ssid     = "MOVISTAR_4E80";           // Nombre conexión WiFi
const char* password = "UC73C7E3wCJ7yAy9F733";    // Contraseña WiFi

const char* host = "192.168.1.192";      // IP a enviar los datos, ya sea PC o Router con PF
const uint16_t port = 8080;             // Puerto específico

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Conexión a WiFi
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado.");


}

void loop() {
  // No hacemos nada en el loop
  // Crear socket TCP y conectarse al servidor
  WiFiClient client;
  if (!client.connect(host, port)) {
    Serial.println("No se pudo conectar al servidor");
    return;
  }

  Serial.println("Conexión establecida con el servidor TCP");

  // Enviar datos de prueba
  String mensaje = "sensor=TTGO1;temp=23.4;humedad=60.2\n";
  client.print(mensaje);
  Serial.println("Mensaje enviado: ");
  Serial.println(mensaje);

  client.stop();  // Cerramos la conexión
  delay(120000);
}
