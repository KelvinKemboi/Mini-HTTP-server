#include <iostream>
#include <sys/socket.h> //for socket funcitons ie, socket, bind, listen..
#include <netinet/in.h> //network structs- for address
#include <unistd.h> //close
#include <string>
#include <fstream> //file handling
#include <sstream> 
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

    cout<<"Server listening on port 8080"<<endl;

    while(true){
    int client=accept(server, nullptr, nullptr); //accept client- socket for client conneection

    //read request
    char buffer[4096]={}; //make a char array with size 4kb
    recv(client, buffer, sizeof(buffer),0); //read client message and store in buffer
    cout<<"Message from client: "<<buffer<<endl; //print message stored

    string request(buffer); //turns into string
    
    string firstline= request.substr(0, request.find("\r\n")); //firstline
    size_t space=firstline.find(' '); //first space before path
    size_t space2=firstline.find(' ', space+1); //second space after path

    string method=firstline.substr(0, space); //everything till first space
    string path=firstline.substr(space+1, space2-space-1); //path

    // cout<<"Method: "<<method<<endl;
    // cout<<"Path: "<<path<<endl;
    if (path == "/") {
        path = "/index.html";
    }
    //Hardcoded HTTP response
    string file_path="/home/kemboi/projects/http-server/public"+path;
    ifstream file(file_path); //open file

    //handling errors
    string body;
    string status;
    if(file) {
        stringstream ss;
        ss<<file.rdbuf();
        body=ss.str();
        status="HTTP/1.1 200 OK\r\n";
    } else {
        body="<h1>404 Not Found</h1>";
        status="HTTP/1.1 404 Not Found\r\n";
    }

    string response =
        status+
        "Content-Type: text/html\r\n"
        "Content-Length: "+ to_string(body.size()) + "\r\n"
        "\r\n" + body;

    send(client, response.c_str(), response.size(), 0); //convert repsonse into s-string and send to client

    //close both server and client
    close(client);
    close(server);
    }
    return 0;
}