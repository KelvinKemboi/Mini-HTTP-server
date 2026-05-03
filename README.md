# Mini-HTTP-server

A mini HTTP server built from scratch in C++ using raw POSIX sockets.

## Features

- Serves static files from a `public/` directory
- Parses HTTP requests and routes by path
- Correct `Content-Type` headers for HTML, CSS, JS, and images
- Custom 404 page
- Handles multiple requests in a loop

## Project Structure

```
http-server/
├── server.cpp
└── public/
    ├── index.html
    ├── style.css
    └── 404.html
```

## Build and Run

```bash
g++ -std=c++20 server.cpp -o server
./server
```

Then open your browser and visit:

```
http://localhost:8080
```

## How It Works

**1. Socket setup**
Creates a TCP socket, binds it to port 8080, and listens for incoming connections.

**2. Accept loop**
Loops forever calling `accept()` — each iteration blocks until a client connects.

**3. Read the request**
Uses `recv()` to read the raw HTTP request into a buffer. The first line looks like:
```
GET /index.html HTTP/1.1
```

**4. Parse the path**
Extracts the method and path from the first line using string parsing.

**5. Serve the file**
Opens the matching file from `public/`, reads it into a string, and sends it back as an HTTP response with the correct status code and headers.

**6. Close and repeat**
Closes the client socket and loops back to `accept()`.

## Example Request / Response

**Request received:**
```
GET / HTTP/1.1
Host: localhost:8080
```

**Response sent:**
```
HTTP/1.1 200 OK
Content-Type: text/html
Content-Length: 342

<!DOCTYPE html>...
```
