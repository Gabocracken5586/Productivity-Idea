#include <iostream>
#include <sys/socket.h> // The core socket library
#include <netinet/in.h> // For internet addresses
#include <unistd.h>     // For closing the socket
#include <string.h>

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

int main() {
    // 1. Create the hardware handle (Socket)

    int server_id = socket(AF_INET, SOCK_STREAM, 0);

    

    // 2. Set up the address "Pinout"
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    // 3. Bind and Listen
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    std::cout << "Listening for Browser signals on port 8080..." << std::endl;

    while(true) {
        int addrlen = sizeof(address);
        int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

        // --- THE READING PART ---
        char buffer[1024] = {0}; // Create a 1KB buffer (memory space)
        read(new_socket, buffer, 1024); // Read the incoming electrical signals into our buffer
        
        std::cout << "\n--- RAW DATA FROM BROWSER ---\n" << buffer << "\n----------------------------\n";

        // 4. Send a manual HTTP response
        // We must include the Header "HTTP/1.1 200 OK" or the browser won't understand
        std::string response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<h1>Connected to Vanilla C++</h1>";
        send(new_socket, response.c_str(), response.length(), 0);

        close(new_socket);
    }
    return 0;
}