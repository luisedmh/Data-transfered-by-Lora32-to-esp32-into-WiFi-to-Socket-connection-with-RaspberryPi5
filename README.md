Data Transfer from LoRa32 to ESP32 via WiFi to Raspberry Pi 5 Socket Connection
Project Description

This project establishes an end-to-end IoT data pipeline that collects sensor data using LoRa wireless communication, bridges it to WiFi via ESP32, and finally stores it on a Raspberry Pi 5 server through a custom socket connection.
Key Components

    LoRa32 Node:

        Collects sensor data (temperature, humidity, etc.)

        Transmits via LoRa's long-range, low-power protocol

    ESP32 Gateway:

        Receives LoRa transmissions

        Bridges data to WiFi network

        Implements socket client to forward data

    Raspberry Pi 5 Server:

        Custom C++ socket server

        Timestamped file storage

        Data persistence and management

Technical Highlights

✔ Hybrid Wireless Architecture: Combines LoRa's long-range capabilities with WiFi's high bandwidth
✔ Custom Protocol Implementation: Efficient binary data transmission
✔ Time-Series Data Storage: Automatic file organization with timestamped archives
✔ Network Resiliency: Handles intermittent connections and retransmissions
Target Applications

    Remote environmental monitoring

    Agricultural sensor networks

    Long-range IoT deployments

Future Roadmap

◉ Add data encryption for secure transmission
◉ Implement MQTT fallback channel
◉ Develop web-based data visualization
◉ Create Docker container for Pi server
