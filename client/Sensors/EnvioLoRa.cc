#include <SPI.h>
#include <LoRa.h>

// Pines LoRa (ajusta según tu placa)
#define LORA_SCK     5
#define LORA_MISO   19
#define LORA_MOSI   27
#define LORA_SS     18
#define LORA_RST    14
#define LORA_DIO0   26
#define LORA_BAND 868E6

const char* sensorID = "Sensor1";  // Cambia por el ID único de cada sensor

void setup() {
	Serial.begin(115200);

	// Iniciar LoRa
	SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS);
	LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

	if (!LoRa.begin(LORA_BAND)) {
		Serial.println("No se pudo inicializar LoRa");
		while (true);
	}

	Serial.println("LoRa inicializado correctamente");
}

void loop() {
	// Simulamos datos
	float temperatura = random(200, 300) / 10.0;  // 20.0 a 30.0 °C
	float humedad     = random(400, 700) / 10.0;  // 40.0 a 70.0 %

	// Creamos el mensaje
	String mensaje = "sensor=" + String(sensorID) + 
					 ";temp=" + String(temperatura, 1) +
					 ";hum=" + String(humedad, 1) + ";";

	Serial.println("Enviando: " + mensaje);

	// Enviar por LoRa
	LoRa.beginPacket();
	LoRa.print(mensaje);
	LoRa.endPacket();

	// Esperamos 60 segundos
	delay(15 * 60000);
}
