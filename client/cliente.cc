#include <iostream>
#include <fstream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

const char* SERVER_IP = "127.0.0.1";  // Localhost para prueba inicial
const int SERVER_PORT = 8080;
const int BUFFER_SIZE = 1024;

void enviar_archivo(const char* nombre_archivo, int sock) {
    std::ifstream file(nombre_archivo, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error al abrir " << nombre_archivo << std::endl;
        return;
    }

    char buffer[BUFFER_SIZE];
    while (!file.eof()) {
        file.read(buffer, BUFFER_SIZE);
        ssize_t bytes_leidos = file.gcount();
        if (send(sock, buffer, bytes_leidos, 0) == -1) {
            std::cerr << "Error al enviar datos" << std::endl;
            break;
        }
        std::cout << "Enviados " << bytes_leidos << " bytes" << std::endl;
    }
    file.close();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <archivo_a_enviar>" << std::endl;
        return 1;
    }

    // Crear socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        std::cerr << "Error al crear socket" << std::endl;
        return 1;
    }

    // Configurar dirección del servidor
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    // Conectar
    if (connect(sock, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Error al conectar" << std::endl;
        close(sock);
        return 1;
    }

    std::cout << "Conectado al servidor. Enviando " << argv[1] << "..." << std::endl;
    enviar_archivo(argv[1], sock);

    close(sock);
    std::cout << "Transferencia completada" << std::endl;
    return 0;
}