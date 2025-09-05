#include <SPI.h>
#include <Ethernet.h>

// MAC única para tu módulo (evitar duplicados en la red)
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// IP del servidor Raspberry Pi
IPAddress server(192, 168, 1, 192);
const uint16_t port = 8080;

// Cliente TCP
EthernetClient client;

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Inicializar SPI (SCK=18, MISO=19, MOSI=23, CS=5)
  SPI.begin(18, 19, 23, 5);
  Ethernet.init(5);  // Pin CS para distinguir comunicaciones entre ESP32 y W5500

  Serial.println("Iniciando Ethernet con DHCP...");

  // MODO DHCP
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Fallo DHCP, puedes usar IP fija...");
    while (true) delay(1000); // se queda aquí si no hay red
  }
  
  Serial.print("Ethernet listo. IP asignada: ");
  Serial.println(Ethernet.localIP());

  // --- MODO IP FIJA ---
    // IPAddress ip(192, 168, 1, 150); IP INVENTADA
    // Ethernet.begin(mac, ip);
}

void loop() {
  if (client.connect(server, port)) {
    Serial.println("Conectado al servidor TCP");

    String mensaje = "sensor=TTGO1;temp=23.4;humedad=60.2\n";
    client.print(mensaje);

    Serial.print("Mensaje enviado: ");
    Serial.println(mensaje);

    client.stop(); // cerrar conexión
  } else {
    Serial.println("No se pudo conectar al servidor");
  }

  delay(120000); // espera 2 minutos antes de enviar otro mensaje
}

