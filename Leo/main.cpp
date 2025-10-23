#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>        // Ethernet_Generic funciona aquí
#include <ThingSpeak.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme;

// Ethernet config
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177); // Ajusta a tu red
EthernetClient client;

// ThingSpeak
unsigned long myChannelNumber = 2699399;
const char *myWriteAPIKey = "H8WPPOKA4RE22GNQ";

void setup() {
  Serial.begin(9600);
  delay(1000);

  // Inicializa Ethernet
  Ethernet.begin(mac, ip);
  Serial.print("IP asignada: ");
  Serial.println(Ethernet.localIP());

  // Inicializa sensor
  if (!bme.begin(0x76)) {
    Serial.println("Error al iniciar BME280");
    while (1);
  }

  ThingSpeak.begin(client);
  delay(500);

  float tempe = bme.readTemperature();
  float pres = bme.readPressure() / 100.0F;
  float hum = bme.readHumidity();

  ThingSpeak.setField(1, tempe);
  ThingSpeak.setField(2, pres);
  ThingSpeak.setField(3, hum);

  int result = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (result == 200) {
    Serial.println("Datos enviados correctamente a ThingSpeak");
  } else {
    Serial.print("Error al enviar datos: ");
    Serial.println(result);
  }

  Serial.print("Temp: "); Serial.print(tempe);
  Serial.print(" °C, Hum: "); Serial.print(hum);
  Serial.print(" %, Pres: "); Serial.print(pres);
  Serial.println(" hPa");

  delay(10000);
  ESP.deepSleep(50e6); // 50 segundos
}

void loop() {}
