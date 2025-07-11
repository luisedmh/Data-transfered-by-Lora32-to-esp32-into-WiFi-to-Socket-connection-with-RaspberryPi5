#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

const int Puerto = 8080;
const int TamanoBuffer = 1024;

// Función para crear el nombre del archivo con la fecha y hora actual
std::string obtener_timestamp() {
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);
    
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y_%H-%M");
    return oss.str();
}


int main() {
    // Primero creamos el socket del servidor
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    // Comprobamos el fd
    if (server_socket == -1) {
        std::cerr << "Error al crear el socket (socket) " << strerror(errno) << std::endl;
        return 1;
    }

    std::cout << "socket() exitoso" << std::endl;

    // Necesitamoe el struct sockaddr_in para declarar la dirección
    struct sockaddr_in address;
    address.sin_family = AF_INET;           // IPv4
    address.sin_addr.s_addr = INADDR_ANY;   // Dentro del struct hay otro struct. Escucha en cualquier interfaz
    address.sin_port = htons(Puerto);       // Usamos el puerto 8080, por ejemplo

    // Creamos una relación entre nuestro socket y nuestra dirección con bind, la hacemos directamente en la comprobación de esta
    // Necesitamos hacer un cast de sockaddr_in a sockaddr
    if (bind(server_socket, (struct sockaddr *)&address, sizeof(address)) == -1) {
        std::cerr << "Error en la relación socket-dirección (bind) " << strerror(errno) << std::endl;
        return 1;
    }

    std::cout << "bind() exitoso" << std::endl;

    // Usamos listen para esperar conexiones, lo hacemos directamente en su comprobación
    if (listen(server_socket, 1) == -1) {
        std::cerr << "Error en la escucha (listen) " << strerror(errno) << std::endl;
        return 1;
    }

    std::cout << "listen() exitoso" << std::endl;

    // Aceptamos las conexiones
    // Necesitamos tener donde almacenar la dirección del cliente
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    while (true) {
        int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);    // Tener en cuenta el cast
        if (client_socket == -1) {
            std::cerr << "Error en accept: " << strerror(errno) << std::endl;
            continue;   
        }

        std::cout << "accept() exitoso" << std::endl;

        // Crear el nombre del archivo
        std::string nombre_archivo = "datos_" + obtener_timestamp() + ".txt";

        // Crear el archivo con ese nombre
        std::ofstream output_file(nombre_archivo, std::ios::binary);

        // Recibir los datos del cliente
        char buffer[TamanoBuffer];
        ssize_t bytes_received;

        while ((bytes_received = recv(client_socket, buffer, TamanoBuffer, 0)) > 0) {
            output_file.write(buffer, bytes_received);
            std::cout << "Recibidos " << bytes_received << " bytes" << std::endl;
        }

        if (bytes_received == -1) {
            std::cerr << "Error al recibir datos (recv): " << strerror(errno) << std::endl;
        }

        // Cerrar finalmente la conexión
        output_file.close();
        close(client_socket);
    }

    // Cerrar el socket original del servidor
    close(server_socket);
    return 0;
}