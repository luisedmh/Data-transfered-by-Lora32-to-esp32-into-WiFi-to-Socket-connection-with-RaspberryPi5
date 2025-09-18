#include <Arduino.h>
#include <WiFi.h>

const char* ssid     = "MOVISTAR_4E80";           // Nombre conexión WiFi
const char* password = "UC73C7E3wCJ7yAy9F733";    // Contraseña WiFi

const char* host 		= "192.168.1.192";      // IP a enviar los datos, ya sea PC o Router con PF
const uint16_t port = 8080;             // Puerto específico

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

  // Conexión a WiFi
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado.");

  pinMode(PIN_M0, OUTPUT);
  pinMode(PIN_M1, OUTPUT);
  pinMode(PIN_AUX, INPUT);

  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, 16, 17);

  setMode(LOW, LOW);   // Normal mode
  waitAuxHigh();

  Serial.println("Receptor listo, esperando mensajes...");
}

void loop() {
  if (Serial2.available()) {
    String mensaje = Serial2.readStringUntil('\n');
    Serial.print("Recibido: ");
    Serial.println(mensaje);	
		
		WiFiClient client;
		if (!client.connect(host, port)) {
			Serial.println("No se pudo conectar al servidor");
			return;
		}

		Serial.println("Conexión establecida con el servidor TCP");

		// Enviar datos recibidos por radio
		client.print(mensaje);
		Serial.println("Mensaje enviado: ");
		Serial.println(mensaje);

  	client.stop();  // Cerramos la conexión
  }
}

