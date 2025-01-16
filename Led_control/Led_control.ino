#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

#define D1 5

const char* ssid = "ESP8266_AP";
const char* password = "12345678";
const int ledPin = 5; 

ESP8266WebServer server(80);

int brightness = 0;
bool ledState = false; 

void setup() {
    Serial.begin(115200);

    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW); 

    WiFi.softAP(ssid, password);
    Serial.println("Access Point started");
    Serial.print("SSID: ");
    Serial.println(ssid);
    Serial.print("Password: ");
    Serial.println(password);
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP()); 

    server.on("/", HTTP_GET, []() {
        String html = "<!DOCTYPE html>\n";
        html += "<html>\n";
        html += "<head><title>ESP8266 LED Control</title></head>\n";
        html += "<body>\n";
        html += "<h1>ESP8266 LED Control</h1>\n";
        html += "<p>Use the buttons below to control the LED.</p>\n";
        html += "<button onclick=\"fetch('/state', {method: 'POST', body: JSON.stringify({command: 'ON'})})\">Turn ON</button>\n";
        html += "<button onclick=\"fetch('/state', {method: 'POST', body: JSON.stringify({command: 'OFF'})})\">Turn OFF</button>\n";
        html += "<p>Set Brightness:</p>\n";
        html += "<input type=\"range\" min=\"0\" max=\"255\" value=\"0\" id=\"brightness\" onchange=\"setBrightness()\">\n";
        html += "<script>\n";
        html += "function setBrightness() {\n";
        html += "  let brightness = document.getElementById('brightness').value;\n";
        html += "  fetch('/brightness', {method: 'POST', body: JSON.stringify({brightness: parseInt(brightness)})});\n";
        html += "}\n";
        html += "</script>\n";
        html += "</body>\n";
        html += "</html>\n";
        server.send(200, "text/html", html);
    });

    server.on("/state", HTTP_POST, []() {
        if (server.hasArg("plain")) {
            StaticJsonDocument<200> doc;
            DeserializationError error = deserializeJson(doc, server.arg("plain"));

            if (!error) {
                const char* command = doc["command"];

                if (strcmp(command, "ON") == 0) {
                    digitalWrite(ledPin, HIGH); 
                    ledState = true;
                    server.send(200, "application/json", "{\"message\": \"LED is ON\"}");
                } else if (strcmp(command, "OFF") == 0) {
                    digitalWrite(ledPin, LOW); 
                    ledState = false;
                    server.send(200, "application/json", "{\"message\": \"LED is OFF\"}");
                } else {
                    server.send(400, "application/json", "{\"error\": \"Invalid command\"}");
                }
            } else {
                server.send(400, "application/json", "{\"error\": \"Invalid JSON\"}");
            }
        } else {
            server.send(400, "application/json", "{\"error\": \"Missing payload\"}");
        }
    });

    server.on("/brightness", HTTP_POST, []() {
        if (server.hasArg("plain")) {
            StaticJsonDocument<200> doc;
            DeserializationError error = deserializeJson(doc, server.arg("plain"));

            if (!error) {
                int value = doc["brightness"];

                if (value >= 0 && value <= 255) {
                    brightness = value;
                    analogWrite(ledPin, brightness);
                    server.send(200, "application/json", "{\"message\": \"Brightness updated\"}");
                } else {
                    server.send(400, "application/json", "{\"error\": \"Brightness value out of range\"}");
                }
            } else {
                server.send(400, "application/json", "{\"error\": \"Invalid JSON\"}");
            }
        } else {
            server.send(400, "application/json", "{\"error\": \"Missing payload\"}");
        }
    });
    server.begin();
    Serial.println("Server started");
}

void loop() {
    server.handleClient();
}
