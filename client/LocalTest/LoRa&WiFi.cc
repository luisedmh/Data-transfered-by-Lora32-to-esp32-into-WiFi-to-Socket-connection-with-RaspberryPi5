#include <WiFi.h>
#include <SPI.h>
#include <LoRa.h>

// WiFi e IP:Puerto
const char* ssid     = "MOVISTAR_4E80";
const char* password = "UC73C7E3wCJ7yAy9F733";
const char* host = "192.168.1.192";
const uint16_t port = 8080;

// Pines LoRa (ajusta según tu placa TTGO LoRa32)
#define LORA_SCK     5
#define LORA_MISO   19
#define LORA_MOSI   27
#define LORA_SS     18
#define LORA_RST    14
#define LORA_DIO0   26
#define LORA_BAND 868E6

// Tiempo de recolección en milisegundos (15 minutos)
const unsigned long RECOLECCION_MS = 15UL * 60UL * 1000UL;

unsigned long tiempoInicio = 0;
String bufferMensajes = "";

void setup() {
	Serial.begin(115200);

	// Inicializar WiFi
	WiFi.begin(ssid, password);
	Serial.print("Conectando a WiFi");
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println("\nWiFi conectado");

	// Inicializar LoRa
	SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS);
	LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

	if (!LoRa.begin(LORA_BAND)) {
		Serial.println("Falló la inicialización de LoRa");
		while (true);
	}

	Serial.println("LoRa iniciado correctamente");

	// Guardar tiempo de inicio
	tiempoInicio = millis();
}

void loop() {
	// Escuchar mensajes LoRa
	int packetSize = LoRa.parsePacket();
	if (packetSize) {
		String mensaje = "";
		while (LoRa.available()) {
		mensaje += (char)LoRa.read();
		}

		// Agregar al buffer con salto de línea
		bufferMensajes += mensaje + "\n";
		Serial.println("Recibido por LoRa:");
		Serial.println(mensaje);
	}

	// Verificar si pasaron 15 minutos
	if (millis() - tiempoInicio >= RECOLECCION_MS) {
		Serial.println("Tiempo cumplido. Enviando datos al servidor...");

		if (bufferMensajes.length() > 0) {
			WiFiClient client;
			if (client.connect(host, port)) {
				client.print(bufferMensajes);
				Serial.println("Datos enviados:");
				Serial.println(bufferMensajes);
				client.stop();
			} else {
				Serial.println("No se pudo conectar al servidor");
			}

			// Limpiar buffer
			bufferMensajes = "";
		} else {
			Serial.println("No hay datos que enviar");
		}

		// Reiniciar el temporizador
		tiempoInicio = millis();
	}
}
