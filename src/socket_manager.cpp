#include "../include/socket_manager.hpp"

SocketManager::SocketManager(const char *serverIP, int serverPort)
{
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    serverAddr.sin_addr.s_addr = inet_addr(serverIP);
    if (clientSocket == -1) {
        throw std::runtime_error("Error creating socket");
    }
}

SocketManager::~SocketManager()
{
    close(clientSocket);
}

bool SocketManager::connectToServer()
{
    int connectionStatus = connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    if (connectionStatus == -1)
    {
        throw std::runtime_error("Error connecting to server");
    }

    return true;
}

void SocketManager::closeConnection()
{
    close(clientSocket);
}


void SocketManager::sendData(std::string message)
{
    try {
        message += '\n';
        ssize_t bytesSent = send(clientSocket, message.c_str(), message.size(), 0);

        if (bytesSent == -1) {
            throw std::runtime_error("Error sending data");
        }

    } catch (const std::exception &e) {
        std::cerr << "SendData Error: " << e.what() << std::endl;
    }
}

std::string SocketManager::receiveData()
{
    try {
        char buffer[1024] = {0};
        ssize_t valread = read(clientSocket, buffer, 1024);

        if (valread == -1) {
            throw std::runtime_error("Error receiving data");
        }

        return buffer;
    } catch (const std::exception &e) {
        std::cerr << "ReceiveData Error: " << e.what() << std::endl;
        return "";
    }
}
