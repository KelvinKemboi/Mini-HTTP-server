#include <iostream>
#include <sys/socket.h> //for socket funcitons ie, socket, bind, listen..
#include <netinet/in.h> //network structs- for address
#include <unistd.h> //close
using namespace std;

int main() {
    //creating socket-file descriptor
    int server=socket(AF_INET, SOCK_STREAM, 0);

    //address 
    sockaddr_in addr{}; //struct with network addr
    addr.sin_family=AF_INET; //ipv4 family
    addr.sin_port=htons(8080); //sets port to 8080
    addr.sin_addr.s_addr=INADDR_ANY; //accept connections

    bind(server, (sockaddr*)&addr, sizeof(addr)); //attach socket by address pointer
    listen(server, 1); //listen 

    std::cout<<"Server listening on port 8080";

    int client=accept(server, nullptr, nullptr); //accept client- socket for client conneection

    //response
    const char* msg =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "\r\n"
        "What's up! This is my simple practice server";

    send(client, msg, str_len(msg), 0); //send response to client

    //close both server and client
    close(client);
    close(server);

    return 0;
}